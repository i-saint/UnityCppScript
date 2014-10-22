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

typedef guint32 mono_array_size_t;
typedef gint32 mono_array_lower_bound_t;

#define MONO_ZERO_LEN_ARRAY 1
#if defined(_MSC_VER) && defined(PLATFORM_IPHONE_XCOMP)
#   define USE_UINT8_BIT_FIELD(type, field) guint8 field 
#else
#   define USE_UINT8_BIT_FIELD(type, field) type field
#endif

struct MonoDomain;
struct MonoAssembly;
struct MonoImage;

struct MonoMethodSignature;
struct MonoMethodDesc;
struct MonoClassField;
struct MonoProperty;
struct MonoEvent;
struct MonoThreadsSync;
struct MonoRuntimeGenericContext;
struct MonoMarshalType;
struct MonoGenericClass;
struct MonoGenericContainer;
struct MonoClassRuntimeInfo;
struct MonoClassExt;
struct MonoArrayType;
struct MonoGenericParam;
enum MonoTypeEnum;

struct MonoCustomMod;
struct MonoClass;
struct MonoType;
struct MonoMethod;
struct MonoVTable;

struct MonoCustomMod {
    unsigned int required : 1;
    unsigned int token : 31;
} ;



struct MonoType {
    union {
        MonoClass *klass; /* for VALUETYPE and CLASS */
        MonoType *type;   /* for PTR */
        MonoArrayType *array; /* for ARRAY */
        MonoMethodSignature *method;
        MonoGenericParam *generic_param; /* for VAR and MVAR */
        MonoGenericClass *generic_class; /* for GENERICINST */
    } data;
    unsigned int attrs : 16; /* param attributes or field flags */
    MonoTypeEnum type : 8;
    unsigned int num_mods : 6;  /* max 64 modifiers follow at the end */
    unsigned int byref : 1;
    unsigned int pinned : 1;  /* valid when included in a local var signature */
    MonoCustomMod modifiers[MONO_ZERO_LEN_ARRAY]; /* this may grow */
};

struct MonoClass {
    /* element class for arrays and enum basetype for enums */
    MonoClass *element_class;
    /* used for subtype checks */
    MonoClass *cast_class;

    /* for fast subtype checks */
    MonoClass **supertypes;
    guint16     idepth;

    /* array dimension */
    guint8     rank;

    int        instance_size; /* object instance size */

    USE_UINT8_BIT_FIELD(guint, inited          : 1);
    /* We use init_pending to detect cyclic calls to mono_class_init */
    USE_UINT8_BIT_FIELD(guint, init_pending    : 1);

    /* A class contains static and non static data. Static data can be
    * of the same type as the class itselfs, but it does not influence
    * the instance size of the class. To avoid cyclic calls to
    * mono_class_init (from mono_class_instance_size ()) we first
    * initialise all non static fields. After that we set size_inited
    * to 1, because we know the instance size now. After that we
    * initialise all static fields.
    */
    USE_UINT8_BIT_FIELD(guint, size_inited     : 1);
    USE_UINT8_BIT_FIELD(guint, valuetype       : 1); /* derives from System.ValueType */
    USE_UINT8_BIT_FIELD(guint, enumtype        : 1); /* derives from System.Enum */
    USE_UINT8_BIT_FIELD(guint, blittable       : 1); /* class is blittable */
    USE_UINT8_BIT_FIELD(guint, unicode         : 1); /* class uses unicode char when marshalled */
    USE_UINT8_BIT_FIELD(guint, wastypebuilder  : 1); /* class was created at runtime from a TypeBuilder */
    /* next byte */
    guint8 min_align;
    /* next byte */
    USE_UINT8_BIT_FIELD(guint, packing_size    : 4);
    USE_UINT8_BIT_FIELD(guint, has_unity_native_intptr : 1); // This class has a IntPtr that points to a native class with an asset reference
    /* still 3 bits free */
    /* next byte */
    USE_UINT8_BIT_FIELD(guint, ghcimpl         : 1); /* class has its own GetHashCode impl */
    USE_UINT8_BIT_FIELD(guint, has_finalize    : 1); /* class has its own Finalize impl */
    USE_UINT8_BIT_FIELD(guint, marshalbyref    : 1); /* class is a MarshalByRefObject */
    USE_UINT8_BIT_FIELD(guint, contextbound    : 1); /* class is a ContextBoundObject */
    USE_UINT8_BIT_FIELD(guint, delegate        : 1); /* class is a Delegate */
    USE_UINT8_BIT_FIELD(guint, gc_descr_inited : 1); /* gc_descr is initialized */
    USE_UINT8_BIT_FIELD(guint, has_cctor       : 1); /* class has a cctor */
    USE_UINT8_BIT_FIELD(guint, has_references  : 1); /* it has GC-tracked references in the instance */
    /* next byte */
    USE_UINT8_BIT_FIELD(guint, has_static_refs : 1); /* it has static fields that are GC-tracked */
    USE_UINT8_BIT_FIELD(guint, no_special_static_fields : 1); /* has no thread/context static fields */
    /* directly or indirectly derives from ComImport attributed class.
    * this means we need to create a proxy for instances of this class
    * for COM Interop. set this flag on loading so all we need is a quick check
    * during object creation rather than having to traverse supertypes
    */
    USE_UINT8_BIT_FIELD(guint, is_com_object   : 1);
    USE_UINT8_BIT_FIELD(guint, nested_classes_inited : 1); /* Whenever nested_class is initialized */
    USE_UINT8_BIT_FIELD(guint, interfaces_inited : 1); /* interfaces is initialized */
    USE_UINT8_BIT_FIELD(guint, simd_type       : 1); /* class is a simd intrinsic type */
    USE_UINT8_BIT_FIELD(guint, is_generic      : 1); /* class is a generic type definition */
    USE_UINT8_BIT_FIELD(guint, is_inflated     : 1); /* class is a generic instance */

    guint8     exception_type;	/* MONO_EXCEPTION_* */

    /* Additional information about the exception */
    /* Stored as property MONO_CLASS_PROP_EXCEPTION_DATA */
    //void       *exception_data;

    MonoClass  *parent;
    MonoClass  *nested_in;

    MonoImage *image;
    const char *name;
    const char *name_space;

    guint32    type_token;
    int        vtable_size; /* number of slots */

    guint16     interface_count;
    guint16     interface_id;        /* unique inderface id (for interfaces) */
    guint16     max_interface_id;

    guint16     interface_offsets_count;
    MonoClass **interfaces_packed;
    guint16    *interface_offsets_packed;
    guint8     *interface_bitmap;

    MonoClass **interfaces;

    union {
        int class_size; /* size of area for static fields */
        int element_size; /* for array types */
        int generic_param_token; /* for generic param types, both var and mvar */
    } sizes;

    /*
    * From the TypeDef table
    */
    guint32    flags;
    struct {
        guint32 first, count;
    } field, method;

    /* loaded on demand */
    MonoMarshalType *marshal_info;

    /*
    * Field information: Type and location from object base
    */
    MonoClassField *fields;

    MonoMethod **methods;

    /* used as the type of the this argument and when passing the arg by value */
    MonoType this_arg;
    MonoType byval_arg;

    MonoGenericClass *generic_class;
    MonoGenericContainer *generic_container;

    void *reflection_info;

    void *gc_descr;

    MonoClassRuntimeInfo *runtime_info;

    /* next element in the class_cache hash list (in MonoImage) */
    MonoClass *next_class_cache;

    /* Generic vtable. Initialized by a call to mono_class_setup_vtable () */
    MonoMethod **vtable;

    /* Rarely used fields of classes */
    MonoClassExt *ext;
};

struct MonoVTable {
    MonoClass  *klass;
    /*
    * According to comments in gc_gcj.h, this should be the second word in
    * the vtable.
    */
    void *gc_descr;
    MonoDomain *domain;  /* each object/vtable belongs to exactly one domain */
    gpointer    data; /* to store static class data */
    gpointer    type; /* System.Type type for klass */
    guint8     *interface_bitmap;
    guint16     max_interface_id;
    guint8      rank;
    USE_UINT8_BIT_FIELD(guint, remote      : 1); /* class is remotely activated */
    USE_UINT8_BIT_FIELD(guint, initialized : 1); /* cctor has been run */
    USE_UINT8_BIT_FIELD(guint, init_failed : 1); /* cctor execution failed */
    guint32     imt_collisions_bitmap;
    MonoRuntimeGenericContext *runtime_generic_context;
    /* do not add any fields after vtable, the structure is dynamically extended */
    gpointer    vtable[MONO_ZERO_LEN_ARRAY];
};


struct MonoObject {
    MonoVTable *vtable;
    MonoThreadsSync *synchronisation;
};
struct MonoString {
    MonoObject object;
    gint32 length;
    gunichar2 chars[MONO_ZERO_LEN_ARRAY];
};

struct MonoArrayBounds {
    mono_array_size_t length;
    mono_array_lower_bound_t lower_bound;
};

struct MonoArray{
    MonoObject obj;
    /* bounds is NULL for szarrays */
    MonoArrayBounds *bounds;
    /* total number of elements of the array */
    mono_array_size_t max_length;
    double vector[MONO_ZERO_LEN_ARRAY];
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
MONO_API void           mono_add_internal_call(const char *name, gconstpointer method);

MONO_API MonoString*    mono_string_new(MonoDomain *domain, const char *text);
MONO_API MonoString*    mono_string_new_len(MonoDomain *domain, const char *text, guint length);
MONO_API MonoString *   mono_string_new_utf16(MonoDomain *domain, const guint16 *text, gint32 len);
MONO_API char*          mono_string_to_utf8(MonoString *string_obj);
MONO_API gunichar2*     mono_string_to_utf16(MonoString *string_obj);

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
