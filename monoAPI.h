#ifndef monoAPI_h
#define monoAPI_h

#pragma comment(lib,"mono.lib")
#define MONO_API __declspec(dllimport)

extern "C" {

typedef int                 gboolean;
typedef void*               gpointer;
typedef const void*         gconstpointer;
typedef __int8              gint8;
typedef unsigned __int8     guint8;
typedef __int16             gint16;
typedef unsigned __int16    guint16;
typedef __int32             gint32;
typedef unsigned __int32    guint32;
typedef __int64             gint64;
typedef unsigned __int64    guint64;
typedef float               gfloat;
typedef double              gdouble;
typedef unsigned __int16    gunichar2;

MONO_API void*          mono_domain_get();
MONO_API void*          mono_domain_assembly_open(void *domain, const char *assemblyName);
MONO_API void*          mono_assembly_get_image(void *assembly);
MONO_API void*          mono_string_new(void *domain, const char *text);
MONO_API void           mono_add_internal_call(const char *name, gconstpointer method);

MONO_API const char*    mono_type_get_name(void *type);
MONO_API void*          mono_type_get_class(void *type);

MONO_API const char*    mono_field_get_name(void *field);
MONO_API void*          mono_field_get_type(void *field);
MONO_API guint32        mono_field_get_offset(void *field);
MONO_API void           mono_field_get_value(void *obj, void *field, void *value);
MONO_API void           mono_field_set_value(void *obj, void *field, void *value);

MONO_API const char*    mono_property_get_name(void *prop);
MONO_API void*          mono_property_get_set_method(void *prop);
MONO_API void*          mono_property_get_get_method(void *prop);

MONO_API const char*    mono_method_get_name(void *method);
MONO_API void*          mono_method_desc_new(const char *methodString, gboolean useNamespace);
MONO_API void*          mono_method_desc_free(void *desc);
MONO_API void*          mono_method_desc_search_in_image(void *methodDesc, void *image);
MONO_API void*          mono_method_signature(void *m);
MONO_API void*          mono_runtime_invoke(void *method, void *obj, void **params, void **exc);

MONO_API guint32        mono_signature_get_param_count(void *sig);
MONO_API void*          mono_signature_get_return_type(void *sig);
MONO_API void*          mono_signature_get_params(void *sig, gpointer *iter);

MONO_API void*          mono_class_from_name(void *image, const char *namespaceString, const char *classnameString);
MONO_API const char*    mono_class_get_name(void *klass);
MONO_API void*          mono_class_get_type(void *klass);
MONO_API void*          mono_class_get_parent(void *klass);
MONO_API void*          mono_class_get_methods(void*, gpointer* iter);
MONO_API void*          mono_class_get_method_from_name(void *klass, const char *name, int param_count);
MONO_API void*          mono_class_get_fields(void* klass, gpointer *iter);
MONO_API void*          mono_class_get_field_from_name(void *klass, const char *name);
MONO_API void*          mono_class_get_properties(void* klass, gpointer *iter);
MONO_API void*          mono_class_get_property_from_name(void *klass, const char *name);
MONO_API void*          mono_class_get_events(void* klass, gpointer *iter);
MONO_API void*          mono_class_get_interfaces(void* klass, gpointer *iter);
MONO_API void*          mono_class_get_nested_types(void* klass, gpointer *iter);

MONO_API void*          mono_object_get_domain(void *obj);
MONO_API void*          mono_object_get_class(void *obj);


} // extern "C"
#endif // monoAPI_h
