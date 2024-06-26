#include "mono.h"

void Mono::Attach()
{
	domain = mono_get_root_domain();
	mono_thread_attach(domain);
	mono_thread_attach(mono_domain_get());
}

void Mono::Initialize()
{
	_MonoMemory.Initialize();
	API::Initialize();

	Mono::Attach();

	MH_Initialize();
}

Class* Object::GetClass()
{
	return (Class*)mono_object_get_class(this);
}

Field* Object::GetField(const char* Name)
{
	return this->GetClass()->GetField(Name);
}

Method* Object::GetMethod(const char* Name, int pCount)
{
	return (Method*)this->GetClass()->GetMethod(Name, pCount);
}

Class* Class::Resolve(const char* Asm, const char* Namespace, const char* Klass)
{
	return (Class*)mono_class_from_name(Assembly::Resolve(Asm)->GetImage(), Namespace, Klass);
}

Field* Class::GetField(const char* Name)
{
	return (Field*)mono_class_get_field_from_name(this, Name);
}

Method* Class::GetMethod(const char* Name, int pCount)
{
	return (Method*)mono_class_get_method_from_name(this, Name, pCount);
}

const char* Class::GetName()
{
	return mono_class_get_name(this);
}

void Class::Methods()
{
	void* iter = nullptr;
	MonoMethod* method;
	while (method = mono_class_get_methods(this, &iter))
	{
		std::cout << mono_method_full_name(method, 1) << "\n";
	}
}

Assembly* Assembly::Resolve(const char* Name)
{
	return (Assembly*)mono_domain_assembly_open(Mono::domain, Name);
}

MonoImage* Assembly::GetImage()
{
	return (MonoImage*)mono_assembly_get_image(this);
}

Method* Method::Resolve(const char* Asm, const char* Namespace, const char* Klass, const char* Name, int pCount)
{
	return (Method*)mono_class_get_method_from_name(Class::Resolve(Asm, Namespace, Klass), Name, pCount);
}

void* Method::GetAddress()
{
	return mono_compile_method(this);
}

void Method::Hook(void* vHk, void* vOrg)
{
	MH_CreateHook(mono_compile_method(this), vHk, (void**)vOrg);
	MH_EnableHook(mono_compile_method(this));
}

Field* Field::Resolve(const char* Asm, const char* Namespace, const char* Klass, const char* Name)
{
	return (Field*)mono_class_get_field_from_name(Class::Resolve(Asm, Namespace, Klass), Name);
}

String* String::New(const char* str)
{
	return (String*)mono_string_new_len(Mono::domain, str, strlen(str));
}

wchar_t* String::c_str()
{
	return (wchar_t*)mono_string_chars(this);
}

Type* Type::Resolve(Class* klass)
{
	return (Type*)mono_class_get_type(klass);
}

Type* Type::Resolve(const char* Asm, const char* Namespace, const char* Klass)
{
	return Type::Resolve(Class::Resolve(Asm, Namespace, Klass));
}

Class* Type::GetClass()
{
	return (Class*)mono_type_get_class(this);
}

Object* Type::GetObjectType()
{
	return (Object*)mono_type_get_object(Mono::domain, this);
}
