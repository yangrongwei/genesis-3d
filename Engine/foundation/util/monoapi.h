/****************************************************************************
Copyright (c) 2011-2013,WebJet Business Division,CYOU
 
http://www.genesis-3d.com.cn

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#include "util/monotypes.h"

#ifndef __MONO_API_H__
#define __MONO_API_H__

// - in order to make a dynamic link with mono.dll, I define mono API like this
// - so if you want to invoke a mono function, you shall make a sentence like the follow,that is all

// - make all api in a macro,thus,they can be repeat just writing a macro
#define ALL_MONO_API(UNFOLD) \
UNFOLD( MonoDomain*, mono_jit_init_version, (const char *root_domain_name, const char *runtime_version));\
UNFOLD( void, mono_jit_parse_options, (int argc, char* argv[]) );\
UNFOLD( void, mono_jit_cleanup, (MonoDomain *domain)); \
UNFOLD( MonoObject*, mono_object_new, (MonoDomain* domain, MonoClass* monoClass) );\
UNFOLD( void, mono_runtime_object_init, (MonoObject* monoObj) );\
UNFOLD( MonoDomain*, mono_domain_get,(void) );\
UNFOLD( gboolean,mono_domain_set,(MonoDomain *domain, gboolean force));\
UNFOLD( MonoDomain *, mono_domain_create_appdomain,(const char *domainname, const char* configfile));\
UNFOLD( void,mono_debug_open_image_from_memory,(MonoImage *image, const char *raw_contents, int size));\
UNFOLD( void, mono_domain_unload, (MonoDomain* domain));\
UNFOLD( MonoDomain*,mono_get_root_domain,());\
UNFOLD( void, mono_set_dirs, (const char* assembly_dir, const char* config_dir) );\
UNFOLD( void, mono_set_assemblies_path, (const char* path) );\
UNFOLD( void, mono_debug_init, (MonoDebugFormat format) );\
UNFOLD( MonoThread*, mono_thread_current, (void) );\
UNFOLD( void, mono_thread_set_main, (MonoThread* thread) );\
UNFOLD( MonoThread* ,mono_thread_attach, (MonoDomain *domain));\
UNFOLD( void, mono_thread_detach, (MonoThread *thread));\
UNFOLD( MonoMethodDesc*, mono_method_desc_new, (const char* name, gboolean include_namespace) );\
UNFOLD( void,	mono_method_desc_free,(MonoMethodDesc *desc) );\
UNFOLD( MonoMethod*, mono_method_desc_search_in_class, (MonoMethodDesc* desc, MonoClass* monoClass) );\
UNFOLD( MonoMethod* ,mono_method_get_last_managed, ());\
UNFOLD( mono_bool, mono_class_is_valuetype, (MonoClass* klass) );\
UNFOLD( void*, mono_object_unbox,(MonoObject* pObj) );\
UNFOLD( MonoObject*, mono_runtime_invoke, (MonoMethod* method, void* obj, void** params, MonoObject** exc) );\
UNFOLD( char*, mono_string_to_utf8,(MonoString* string_obj) );\
UNFOLD( mono_unichar2*, mono_string_to_utf16,(MonoString* string_obj) );\
UNFOLD( void, mono_free, (void*) );\
UNFOLD( mono_bool, mono_class_is_subclass_of, (MonoClass* klass, MonoClass* klassc, mono_bool check_interfaces) );\
UNFOLD( MonoMethod*, mono_class_get_method_from_name, (MonoClass* klass, const char* name, int param_count) );\
UNFOLD( MonoClass*, mono_class_get_parent, (MonoClass* klass) );\
UNFOLD( MonoClass*, mono_class_from_name, (MonoImage* image, const char* name_space, const char* name) );\
UNFOLD( const char*, mono_class_get_name, (MonoClass *klass) );\
UNFOLD( MonoAssembly*, mono_domain_assembly_open, (MonoDomain* domain, const char* name) );\
UNFOLD( MonoImage*,mono_image_open_from_data_full,(const void *data, guint32 data_len, gboolean need_copy, int *status, gboolean ref_only));\
UNFOLD( void,mono_image_close,(MonoImage *image));\
UNFOLD( MonoAssembly*,mono_assembly_load_from_full,(MonoImage *image, const char *fname,int *status,gboolean refonly));\
UNFOLD( MonoImage*, mono_assembly_get_image,  (MonoAssembly* assembly) );\
UNFOLD( uint32_t, mono_gchandle_new, (MonoObject* obj, mono_bool pinned) );\
UNFOLD( void, mono_gchandle_free, (uint32_t gchandle) );\
UNFOLD( guint32, mono_gchandle_new_weakref, (MonoObject *obj, gboolean track_resurrection)  );\
UNFOLD( MonoObject* , mono_gchandle_get_target , (uint32_t gchandle) );\
UNFOLD( void, mono_gc_collect, (int generation) );\
UNFOLD( int, mono_gc_max_generation, () );\
UNFOLD( gboolean,mono_object_is_alive ,(MonoObject* o));\
UNFOLD( void, mono_add_internal_call, (const char* name, gconstpointer method) );\
UNFOLD( MonoString*, mono_string_new_wrapper, (const char* text) );\
UNFOLD( MonoString*, mono_string_new_utf16, (MonoDomain* domain, const mono_unichar2 *text, int32_t len));\
UNFOLD( MonoClass*, mono_get_string_class, (void) );\
UNFOLD( MonoClass*, mono_get_byte_class, (void) );\
UNFOLD( uintptr_t, mono_array_length, (MonoArray* array));\
UNFOLD( char*, mono_array_addr_with_size, (MonoArray* array, int size, uintptr_t idx) );\
UNFOLD( MonoArray*, mono_array_new, (MonoDomain* domain, MonoClass* eclass, uintptr_t n) );\
UNFOLD( MonoClass*, mono_object_get_class,(MonoObject* obj) );\
UNFOLD( MonoClassField*, mono_class_get_fields,(MonoClass* klass, gpointer* iter) );\
UNFOLD( const char*, mono_field_get_name, (MonoClassField* field) );\
UNFOLD( MonoType*, mono_field_get_type, (MonoClassField* field) );\
UNFOLD( guint32, mono_field_get_flags, (MonoClassField* field) );\
UNFOLD( int, mono_type_get_type, (MonoType* type) );\
UNFOLD( MonoClass* ,mono_type_get_class, (MonoType *type) );\
UNFOLD( guint32, mono_field_get_offset, (MonoClassField *field) );\
UNFOLD( void, mono_field_get_value, (MonoObject *obj, MonoClassField *field, void *value) );\
UNFOLD( void, mono_field_set_value, (MonoObject *obj, MonoClassField *field, void *value) );\
UNFOLD( void, mono_security_enable_core_clr, (void) );\
typedef bool (*MonoCoreClrPlatformCB) (const char *image_name);\
UNFOLD( bool,mono_security_set_core_clr_platform_callback, (MonoCoreClrPlatformCB));\
// - NOTE:don't forget to put a slash'\'

// -
#ifndef __OSX__
#define MONO_API_EXTERN(ret,fun,params)	extern ret (*fun) params;
#else
#ifdef __cplusplus
#define MONO_API_EXTERN(ret,fun,params)	extern "C" ret fun params;
extern "C" void ManuallyCollection( float );
#else
#define MONO_API_EXTERN(ret,fun,params)	extern ret fun params;
extern void ManuallyCollection( float );
#endif
#endif
ALL_MONO_API(MONO_API_EXTERN)
#endif
