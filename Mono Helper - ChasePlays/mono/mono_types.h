#pragma once
#include "mono_memory.h"

//#define DO_TYPE(c) typedef struct c;
//#define DO_FUNC(c, r, b, p, ...) typedef c* (*r)(__VA_ARGS__); inline r b = reinterpret_cast<r>(p);

typedef struct MonoThread;
typedef struct MonoDomain;
typedef struct MonoImage;
typedef struct MonoAssembly {

}MonoAssembly;
typedef struct MonoClass {

}MonoClass;
typedef struct MonoMethod {

}MonoMethod;
typedef struct MonoField {

}MonoField;
typedef struct MonoVTable;
typedef struct MonoObject {

}MonoObject;
typedef struct MonoType {

}MonoType;
typedef struct MonoString {

}MonoString;
typedef unsigned __int64 mono_array_size_t;
typedef struct MonoArray
{
	MonoObject* array_object;
	char pad_0x20[0x20];
	MonoObject* array_items[255];
} MonoArray;

typedef MonoThread* (*t_mono_thread_attach)(MonoDomain* domain);
inline t_mono_thread_attach mono_thread_attach;

typedef void* (*t_mono_object_unbox)(MonoObject* obj);
inline t_mono_object_unbox mono_object_unbox;

typedef MonoDomain* (*t_mono_get_root_domain)();
inline t_mono_get_root_domain mono_get_root_domain;

typedef MonoAssembly* (*t_mono_domain_assembly_open)(MonoDomain* doamin, const char* name);
inline t_mono_domain_assembly_open mono_domain_assembly_open;

typedef MonoImage* (*t_mono_assembly_get_image)(MonoAssembly* assembly);
inline t_mono_assembly_get_image mono_assembly_get_image;

typedef MonoClass* (*t_mono_class_from_name)(MonoImage* image, const char* name_space, const char* name);
inline t_mono_class_from_name mono_class_from_name;

typedef MonoMethod* (*t_mono_class_get_method_from_name)(MonoClass* klass, const char* name, int param_count);
inline t_mono_class_get_method_from_name mono_class_get_method_from_name;

typedef MonoClass* (*t_mono_field_get_parent)(MonoField* field);
inline t_mono_field_get_parent mono_field_get_parent;

typedef MonoObject* (*t_mono_object_new)(MonoDomain* dom, MonoClass* klass);
inline t_mono_object_new mono_object_new;

typedef void (*t_mono_runtime_object_init)(MonoObject* klass_instance);
inline t_mono_runtime_object_init mono_runtime_object_init;

typedef MonoMethod* (*t_mono_class_get_methods)(MonoClass* klass, void** iter);
inline t_mono_class_get_methods mono_class_get_methods;

typedef MonoString* (*t_mono_string_new_len)(MonoDomain* dom, const char* str, uint32_t len);
inline t_mono_string_new_len mono_string_new_len;

typedef wchar_t* (*t_mono_string_chars)(MonoString* str);
inline t_mono_string_chars mono_string_chars;

typedef void* (*t_mono_compile_method)(MonoMethod* method);
inline t_mono_compile_method mono_compile_method;

typedef MonoObject* (*t_mono_runtime_invoke)(MonoMethod* method, MonoObject* obj, void** params, MonoObject** exc);
inline t_mono_runtime_invoke mono_runtime_invoke;

typedef MonoField* (*t_mono_class_get_field_from_name)(MonoClass* klass, const char* name);
inline t_mono_class_get_field_from_name mono_class_get_field_from_name;

typedef const char* (*t_mono_field_get_name)(MonoField* field);
inline t_mono_field_get_name mono_field_get_name;

typedef void* (*t_mono_field_get_value)(MonoObject* obj, MonoField* field, void* value);
inline t_mono_field_get_value mono_field_get_value;

typedef size_t (*t_mono_array_length)(MonoArray* arr);
inline t_mono_array_length mono_array_length;

typedef void (*t_mono_field_set_value)(MonoObject* obj, MonoField* field, void* value);
inline t_mono_field_set_value mono_field_set_value;

typedef void(*t_mono_field_static_get_value)(MonoVTable* vtable, MonoField* field, void* value);
inline t_mono_field_static_get_value mono_field_static_get_value;

typedef void(*t_mono_field_static_set_value)(void* obj, MonoField* field, void* value);
inline t_mono_field_static_set_value mono_field_static_set_value;

typedef const char* (*t_mono_method_full_name)(MonoMethod* mth, int v);
inline t_mono_method_full_name mono_method_full_name;

typedef MonoClass* (*t_mono_method_get_class)(MonoMethod* method);
inline t_mono_method_get_class mono_method_get_class;

typedef MonoVTable* (*t_mono_class_vtable)(MonoDomain* domain, MonoClass* klass);
inline t_mono_class_vtable mono_class_vtable;

typedef void* (*t_mono_vtable_class)(MonoClass* klass);
inline t_mono_vtable_class mono_vtable_class;

typedef void* (*t_mono_vtable_get_static_field_data)(MonoVTable* vt);
inline t_mono_vtable_get_static_field_data mono_vtable_get_static_field_data;

typedef uint32_t(*t_mono_field_get_offset)(MonoField* field);
inline t_mono_field_get_offset mono_field_get_offset;

typedef void(*t_mono_runtime_class_init)(void* vtable);
inline t_mono_runtime_class_init mono_runtime_class_init;

typedef MonoDomain* (*t_mono_domain_get)();
inline t_mono_domain_get mono_domain_get;

typedef const char* (*t_mono_image_get_name)(MonoImage* image);
inline t_mono_image_get_name mono_image_get_name;

typedef MonoClass* (*t_mono_object_get_class)(MonoObject* obj);
inline t_mono_object_get_class mono_object_get_class;

typedef MonoImage* (*t_mono_class_get_image)(MonoClass* klass);
inline t_mono_class_get_image mono_class_get_image;

typedef const char* (*t_mono_class_get_name)(MonoClass* klass);
inline t_mono_class_get_name mono_class_get_name;

typedef const char* (*t_mono_class_get_namespace)(MonoClass* klass);
inline t_mono_class_get_namespace mono_class_get_namespace;
