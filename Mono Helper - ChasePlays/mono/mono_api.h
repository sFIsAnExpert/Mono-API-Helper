#pragma once
#include "mono_types.h"

//#define APIEXPORT(o,t,n) o = reinterpret_cast<t>(_MonoMemory.GetExport((const wchar_t*)n)); 

namespace API {
	inline void Initialize() {
		mono_domain_assembly_open = reinterpret_cast<t_mono_domain_assembly_open>(_MonoMemory.GetExport(L"mono_domain_assembly_open"));
		mono_assembly_get_image = reinterpret_cast<t_mono_assembly_get_image>(_MonoMemory.GetExport(L"mono_assembly_get_image"));
		mono_class_from_name = reinterpret_cast<t_mono_class_from_name>(_MonoMemory.GetExport(L"mono_class_from_name"));
		mono_class_get_method_from_name = reinterpret_cast<t_mono_class_get_method_from_name>(_MonoMemory.GetExport(L"mono_class_get_method_from_name"));
		mono_compile_method = reinterpret_cast<t_mono_compile_method>(_MonoMemory.GetExport(L"mono_compile_method"));
		mono_runtime_invoke = reinterpret_cast<t_mono_runtime_invoke>(_MonoMemory.GetExport(L"mono_runtime_invoke"));

		mono_class_get_field_from_name = reinterpret_cast<t_mono_class_get_field_from_name>(_MonoMemory.GetExport(L"mono_class_get_field_from_name"));
		mono_field_get_value = reinterpret_cast<t_mono_field_get_value>(_MonoMemory.GetExport(L"mono_field_get_value"));
		mono_field_set_value = reinterpret_cast<t_mono_field_set_value>(_MonoMemory.GetExport(L"mono_field_set_value"));
		mono_field_static_get_value = reinterpret_cast<t_mono_field_static_get_value>(_MonoMemory.GetExport(L"mono_field_static_get_value"));
		mono_field_static_set_value = reinterpret_cast<t_mono_field_static_set_value>(_MonoMemory.GetExport(L"mono_field_static_set_value"));
		mono_method_get_class = reinterpret_cast<t_mono_method_get_class>(_MonoMemory.GetExport(L"mono_method_get_class"));
		mono_class_vtable = reinterpret_cast<t_mono_class_vtable>(_MonoMemory.GetExport(L"mono_class_vtable"));
		mono_vtable_get_static_field_data = reinterpret_cast<t_mono_vtable_get_static_field_data>(_MonoMemory.GetExport(L"mono_vtable_get_static_field_data"));
		mono_field_get_offset = reinterpret_cast<t_mono_field_get_offset>(_MonoMemory.GetExport(L"mono_field_get_offset"));
		mono_field_get_name = reinterpret_cast<t_mono_field_get_name>(_MonoMemory.GetExport(L"mono_field_get_name"));
		mono_vtable_class = reinterpret_cast<t_mono_vtable_class>(_MonoMemory.GetExport(L"mono_vtable_class"));
		mono_runtime_class_init = reinterpret_cast<t_mono_runtime_class_init>(_MonoMemory.GetExport(L"mono_runtime_class_init"));
		mono_image_get_name = reinterpret_cast<t_mono_image_get_name>(_MonoMemory.GetExport(L"mono_image_get_name"));
		mono_object_get_class = reinterpret_cast<t_mono_object_get_class>(_MonoMemory.GetExport(L"mono_object_get_class"));
		mono_class_get_image = reinterpret_cast<t_mono_class_get_image>(_MonoMemory.GetExport(L"mono_class_get_image"));
		mono_class_get_name = reinterpret_cast<t_mono_class_get_name>(_MonoMemory.GetExport(L"mono_class_get_name"));
		mono_class_get_namespace = reinterpret_cast<t_mono_class_get_namespace>(_MonoMemory.GetExport(L"mono_class_get_namespace"));
		mono_field_get_parent = reinterpret_cast<t_mono_field_get_parent>(_MonoMemory.GetExport(L"mono_field_get_parent"));
		mono_class_get_methods = reinterpret_cast<t_mono_class_get_methods>(_MonoMemory.GetExport(L"mono_class_get_methods"));
		mono_method_full_name = reinterpret_cast<t_mono_method_full_name>(_MonoMemory.GetExport(L"mono_method_full_name"));
		mono_object_unbox = reinterpret_cast<t_mono_object_unbox>(_MonoMemory.GetExport(L"mono_object_unbox"));
		mono_string_new_len = reinterpret_cast<t_mono_string_new_len>(_MonoMemory.GetExport(L"mono_string_new_len"));
		mono_string_chars = reinterpret_cast<t_mono_string_chars>(_MonoMemory.GetExport(L"mono_string_chars"));
		mono_object_new = reinterpret_cast<t_mono_object_new>(_MonoMemory.GetExport(L"mono_object_new"));
		mono_runtime_object_init = reinterpret_cast<t_mono_runtime_object_init>(_MonoMemory.GetExport(L"mono_runtime_object_init"));

		mono_thread_attach = reinterpret_cast<t_mono_thread_attach>(_MonoMemory.GetExport(L"mono_thread_attach"));
		mono_get_root_domain = reinterpret_cast<t_mono_get_root_domain>(_MonoMemory.GetExport(L"mono_get_root_domain"));
		mono_domain_get = reinterpret_cast<t_mono_domain_get>(_MonoMemory.GetExport(L"mono_domain_get"));
	}
}