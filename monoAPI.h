#ifndef monoAPI_h
#define monoAPI_h

#pragma comment(lib,"mono.lib")
#define MONO_API __declspec(dllimport)

extern "C" {

typedef int            gboolean;
typedef int            gint;
typedef unsigned int   guint;
typedef short          gshort;
typedef unsigned short gushort;
typedef long           glong;
typedef unsigned long  gulong;
typedef void *         gpointer;
typedef const void *   gconstpointer;
typedef char           gchar;
typedef unsigned char  guchar;

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

#define MONO_ZERO_LEN_ARRAY 1

typedef void MonoDomain;
typedef void MonoAssembly;
typedef void MonoImage;

typedef void MonoMethodSignature;
typedef void MonoMethodDesc;
typedef void MonoType;
typedef void MonoClass;
typedef void MonoClassField;
typedef void MonoProperty;
typedef void MonoEvent;
typedef void MonoVTable;
typedef void MonoThreadsSync;

struct MonoObject {
    MonoVTable *vtable;
    MonoThreadsSync *synchronisation;
};
struct MonoString {
    MonoObject object;
    gint32 length;
    gunichar2 chars[MONO_ZERO_LEN_ARRAY];
};

struct MonoMethod {
    guint16 flags;  /* method flags */
    guint16 iflags; /* method implementation flags */
    guint32 token;
    MonoClass *klass;
    MonoMethodSignature *signature;
    /* name is useful mostly for debugging */
    const char *name;
    /* this is used by the inlining algorithm */
    unsigned int inline_info : 1;
    unsigned int inline_failure : 1;
    unsigned int wrapper_type : 5;
    unsigned int string_ctor : 1;
    unsigned int save_lmf : 1;
    unsigned int dynamic : 1; /* created & destroyed during runtime */
    unsigned int is_generic : 1; /* whenever this is a generic method definition */
    unsigned int is_inflated : 1; /* whether we're a MonoMethodInflated */
    unsigned int skip_visibility : 1; /* whenever to skip JIT visibility checks */
    unsigned int verification_success : 1; /* whether this method has been verified successfully.*/
    /* TODO we MUST get rid of this field, it's an ugly hack nobody is proud of. */
    unsigned int is_mb_open : 1;		/* This is the fully open instantiation of a generic method_builder. Worse than is_tb_open, but it's temporary */
    signed int slot : 17;

    /*
    * If is_generic is TRUE, the generic_container is stored in image->property_hash,
    * using the key MONO_METHOD_PROP_GENERIC_CONTAINER.
    */
};

typedef void MonoMethodHeader;

struct MonoMethodNormal {
    MonoMethod method;
    MonoMethodHeader *header;
};

struct MonoMethodPInvoke {
    MonoMethod method;
    gpointer addr;
    /* add marshal info */
    guint16 piflags;  /* pinvoke flags */
    guint16 implmap_idx;  /* index into IMPLMAP */
};


struct MonoGenericInst {
    guint id;			/* unique ID for debugging */
    guint type_argc : 22;	/* number of type arguments */
    guint is_open : 1;	/* if this is an open type */
    MonoType *type_argv[MONO_ZERO_LEN_ARRAY];
};

struct MonoGenericContext {
    MonoGenericInst *class_inst;
    MonoGenericInst *method_inst;
};

struct MonoMethodInflated {
    union {
        MonoMethod method;
        MonoMethodNormal normal;
        MonoMethodPInvoke pinvoke;
    } method;
    MonoMethod *declaring;		/* the generic method definition. */
    MonoGenericContext context;	/* The current instantiation */
};

MONO_API MonoDomain*    mono_domain_get();
MONO_API MonoAssembly*  mono_domain_assembly_open(MonoDomain *domain, const char *assemblyName);
MONO_API MonoImage*     mono_assembly_get_image(MonoAssembly *assembly);
MONO_API MonoString*    mono_string_new(MonoDomain *domain, const char *text);
MONO_API void           mono_add_internal_call(const char *name, gconstpointer method);

MONO_API const char*    mono_type_get_name(MonoType *type);
MONO_API MonoClass*     mono_type_get_class(MonoType *type);

MONO_API const char*    mono_field_get_name(MonoClassField *field);
MONO_API MonoType*      mono_field_get_type(MonoClassField *field);
MONO_API guint32        mono_field_get_offset(MonoClassField *field);
MONO_API void           mono_field_get_value(MonoObject *obj, MonoClassField *field, void *value);
MONO_API void           mono_field_set_value(MonoObject *obj, MonoClassField *field, void *value);

MONO_API const char*    mono_property_get_name(MonoProperty *prop);
MONO_API MonoMethod*    mono_property_get_set_method(MonoProperty *prop);
MONO_API MonoMethod*    mono_property_get_get_method(MonoProperty *prop);

MONO_API const char*            mono_method_get_name(MonoMethod *method);
MONO_API MonoMethodHeader*      mono_method_get_header(MonoMethod *method);
MONO_API MonoMethodDesc*        mono_method_desc_new(const char *methodString, gboolean useNamespace);
MONO_API void                   mono_method_desc_free(MonoMethodDesc *desc);
MONO_API MonoMethodDesc*        mono_method_desc_search_in_image(MonoMethodDesc *methodDesc, MonoImage *image);
MONO_API MonoMethodSignature*   mono_method_signature(MonoMethod *m);
MONO_API void*                  mono_method_get_unmanaged_thunk(MonoMethod *method);
MONO_API MonoObject*            mono_runtime_invoke(MonoMethod *method, MonoObject *obj, void **params, void **exc);

MONO_API MonoMethod*            mono_class_inflate_generic_method(MonoMethod *method, MonoGenericContext *context);
MONO_API MonoMethod*            mono_class_inflate_generic_method_full(MonoMethod *method, MonoClass *klass_hint, MonoGenericContext *context);


MONO_API guint32                mono_signature_get_param_count(MonoMethodSignature *sig);
MONO_API MonoType*              mono_signature_get_return_type(MonoMethodSignature *sig);
MONO_API MonoType*              mono_signature_get_params(MonoMethodSignature *sig, gpointer *iter);

MONO_API MonoClass*             mono_class_from_name(MonoImage *image, const char *namespaceString, const char *classnameString);
MONO_API const char*            mono_class_get_name(MonoClass *klass);
MONO_API MonoType*              mono_class_get_type(MonoClass *klass);
MONO_API MonoClass*             mono_class_get_parent(MonoClass *klass);
MONO_API MonoMethod*            mono_class_get_methods(MonoClass*, gpointer* iter);
MONO_API MonoMethod*            mono_class_get_method_from_name(MonoClass *klass, const char *name, int param_count);
MONO_API MonoClassField*        mono_class_get_fields(MonoClass* klass, gpointer *iter);
MONO_API MonoClassField*        mono_class_get_field_from_name(MonoClass *klass, const char *name);
MONO_API MonoProperty*          mono_class_get_properties(MonoClass* klass, gpointer *iter);
MONO_API MonoProperty*          mono_class_get_property_from_name(MonoClass *klass, const char *name);
MONO_API MonoEvent*             mono_class_get_events(MonoClass* klass, gpointer *iter);
MONO_API MonoClass*             mono_class_get_interfaces(MonoClass* klass, gpointer *iter);
MONO_API MonoClass*             mono_class_get_nested_types(MonoClass* klass, gpointer *iter);
MONO_API MonoGenericContext*    mono_class_get_context(MonoClass *klass);

MONO_API MonoDomain*        mono_object_get_domain(MonoObject *obj);
MONO_API MonoClass*         mono_object_get_class(MonoObject *obj);


MONO_API MonoClass* mono_get_object_class();
MONO_API MonoClass* mono_get_byte_class();
MONO_API MonoClass* mono_get_void_class();
MONO_API MonoClass* mono_get_boolean_class();
MONO_API MonoClass* mono_get_sbyte_class();
MONO_API MonoClass* mono_get_int16_class();
MONO_API MonoClass* mono_get_uint16_class();
MONO_API MonoClass* mono_get_int32_class();
MONO_API MonoClass* mono_get_uint32_class();
MONO_API MonoClass* mono_get_intptr_class();
MONO_API MonoClass* mono_get_uintptr_class();
MONO_API MonoClass* mono_get_int64_class();
MONO_API MonoClass* mono_get_uint64_class();
MONO_API MonoClass* mono_get_single_class();
MONO_API MonoClass* mono_get_double_class();
MONO_API MonoClass* mono_get_char_class();
MONO_API MonoClass* mono_get_string_class();
MONO_API MonoClass* mono_get_enum_class();
MONO_API MonoClass* mono_get_array_class();
MONO_API MonoClass* mono_get_thread_class(); 
MONO_API MonoClass* mono_get_exception_class();

} // extern "C"
#endif // monoAPI_h
