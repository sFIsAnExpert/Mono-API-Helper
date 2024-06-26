#pragma once
#include "mono_api.h"

namespace Mono {
	inline MonoDomain* domain = nullptr;
	void Attach();
	void Initialize();
}

struct Assembly;
struct Image;
struct Class;
struct Method;
struct Field;
struct Object;
struct Type;

struct String : public MonoString {
	static String* New(const char* Str);
	wchar_t* c_str();
};

struct Assembly : public MonoAssembly {
	static Assembly* Resolve(const char* Name);
	MonoImage* GetImage();
};

struct Class : public MonoClass {
	static Class* Resolve(const char* Asm, const char* Namespace, const char* Klass);
	Field* GetField(const char* Name);
	Method* GetMethod(const char* Name, int pCount);

	const char* GetName();

	void Methods();
};

struct Method : public MonoMethod {
	static Method* Resolve(const char* Asm, const char* Namespace, const char* Klass, const char* Name, int pCount);

	//Call Method That Returns A Object* Associated With The Input Type
	//If Calling Static Methods You May Use This Function To Return Value Type's
	template<class T>
	static T Call(const char* Asm, const char* Namespace, const char* Klass, const char* Name, int pCount) {
		return reinterpret_cast<T>(mono_compile_method(Method::Resolve(Asm, Namespace, Klass, Name, pCount)));
	}
	
	//Call Method That Returns A Value Type {structs, int's, etc...}
	//If Method Is Static, Set Object Parameter To nullptr Or Use Call<T>()
	template<class T, class... P>
	static T CallVT(const char* Asm, const char* Namespace, const char* Klass, const char* Name, int pCount, MonoObject* object, P... params) {
		return *reinterpret_cast<T*>(mono_object_unbox(mono_runtime_invoke(Method::Resolve(Asm, Namespace, Klass, Name, pCount), object, new void* { params... }, nullptr)));
	}

	void* GetAddress();
	void Hook(void* vHk, void* vOrg);
};

struct Field : public MonoField {
	static Field* Resolve(const char* Asm, const char* Namespace, const char* Klass, const char* Name);

	template <class T>
	T GetStaticValue() 
	{
		T val;
		MonoVTable* vTable = mono_class_vtable(Mono::domain, mono_field_get_parent(this));
		mono_runtime_class_init(vTable);
		mono_field_static_get_value(vTable, this, &val);
		return val;
	}

	template <class T>
	T GetValue(MonoObject* obj) {
		T val;
		mono_field_get_value(obj, this, &val);
		return val;
	}

	template <class T>
	void SetStaticValue(void* value) {
		MonoVTable* vTable = mono_class_vtable(Mono::domain, mono_field_get_parent(this));
		mono_runtime_class_init(vTable);
		mono_field_static_set_value(vTable, this, value);
	}

	template <class T>
	void SetValue(MonoObject* obj, T* value) {
		mono_field_set_value(obj, this, value);
	}
};

struct Object : public MonoObject {
	Class* GetClass();
	Field* GetField(const char* Name);
	Method* GetMethod(const char* Name, int pCount);

	//Create New Class Instance, Initializes Instance With Default Constructor.
	template <class T>
	T New(Class* klass) {
		Object* obj = mono_object_new(Mono::domain, klass);
		mono_runtime_object_init(obj);
		return (T)obj;
	}
};

template <class T>
struct Array : public Object {
public:
	T GetValue(int index) {
		return Method::Call<T(*)(Array<T>*, int)>("mscorlib", "System", "Array", "GetValueImpl", 1)(this, index - this->GetLowerBound(0));
	}
	int GetLength() {
		return Method::Call<int(*)(Array<T>*)>("mscorlib", "System", "Array", "get_Length", 0)(this);
	}
	int GetLowerBound(int bound) {
		return Method::Call<int(*)(Array<T>*, int)>("mscorlib", "System", "Array", "GetLowerBound", 1)(this, bound);
	}
	bool isEmpty() {
		return this->GetLength() == 0;
	}
};
struct Type : public MonoType {
	static Type* Resolve(Class* klass);
	static Type* Resolve(const char* Asm, const char* Namespace, const char* Klass);
	Class* GetClass();
	Object* GetObjectType();
};
