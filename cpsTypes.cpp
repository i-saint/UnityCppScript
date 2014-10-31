#include "cpsInternal.h"
#include "cpsTypes.h"
#include "cpsUtils.h"
#include <vector>
#include <map>
#include <algorithm>


cpsImage cpsImage::findImage(const char *name)
{
    return mono_assembly_get_image(mono_domain_assembly_open(mono_domain_get(), name));
}

cpsClass cpsImage::findClass(const char *namespace_, const char *class_name)
{
    return mono_class_from_name(mimage, namespace_, class_name);
}


const char* cpsType::getName() const
{
    if (!mtype) { return nullptr; }
    return mono_type_get_name(mtype);
}

cpsClass cpsType::getClass() const
{
    return mono_type_get_class(mtype);
}



const char* cpsField::getName() const
{
    if (!mfield) { return nullptr; }
    return mono_field_get_name(mfield);
}

cpsType cpsField::getType() const
{
    return mono_field_get_type(mfield);
}

int cpsField::getOffset() const
{
    return mono_field_get_offset(mfield);
}

void cpsField::getValueImpl(cpsObject obj, void *p) const
{
    if (!mfield) { return; }
    mono_field_get_value(obj, mfield, p);
}

void cpsField::setValueImpl(cpsObject obj, const void *p)
{
    if (!mfield) { return; }
    mono_field_set_value(obj, mfield, (void*)p);
}


const char* cpsProperty::getName() const
{
    if (!mproperty) { return nullptr; }
    return mono_property_get_name(mproperty);
}

cpsMethod cpsProperty::getGetter() const
{
    if (!mproperty) { return nullptr; }
    return mono_property_get_get_method(mproperty);
}

cpsMethod cpsProperty::getSetter() const
{
    if (!mproperty) { return nullptr; }
    return mono_property_get_set_method(mproperty);
}



#define METHOD_ATTRIBUTE_MEMBER_ACCESS_MASK        0x0007
#define METHOD_ATTRIBUTE_COMPILER_CONTROLLED       0x0000
#define METHOD_ATTRIBUTE_PRIVATE                   0x0001
#define METHOD_ATTRIBUTE_FAM_AND_ASSEM             0x0002
#define METHOD_ATTRIBUTE_ASSEM                     0x0003
#define METHOD_ATTRIBUTE_FAMILY                    0x0004
#define METHOD_ATTRIBUTE_FAM_OR_ASSEM              0x0005
#define METHOD_ATTRIBUTE_PUBLIC                    0x0006
#define METHOD_ATTRIBUTE_STATIC                    0x0010
#define METHOD_ATTRIBUTE_FINAL                     0x0020
#define METHOD_ATTRIBUTE_VIRTUAL                   0x0040
#define METHOD_ATTRIBUTE_HIDE_BY_SIG               0x0080
#define METHOD_ATTRIBUTE_VTABLE_LAYOUT_MASK        0x0100
#define METHOD_ATTRIBUTE_REUSE_SLOT                0x0000
#define METHOD_ATTRIBUTE_NEW_SLOT                  0x0100
#define METHOD_ATTRIBUTE_STRICT                    0x0200
#define METHOD_ATTRIBUTE_ABSTRACT                  0x0400
#define METHOD_ATTRIBUTE_SPECIAL_NAME              0x0800
#define METHOD_ATTRIBUTE_PINVOKE_IMPL              0x2000
#define METHOD_ATTRIBUTE_UNMANAGED_EXPORT          0x0008


const char* cpsMethod::getName() const
{
    if (!mmethod) { return nullptr; }
    return mono_method_get_name(mmethod);
}

bool cpsMethod::isGeneric() const
{
    return ((mmethod)->is_generic) != 0;
}

bool cpsMethod::isInflated() const
{
    return ((mmethod)->is_inflated) != 0;
}

bool cpsMethod::isStatic() const
{
    return ((mmethod)->flags & METHOD_ATTRIBUTE_STATIC) != 0;
}

bool cpsMethod::isVirtual() const
{
    return ((mmethod)->flags & METHOD_ATTRIBUTE_VIRTUAL) != 0;
}


cpsObject cpsMethod::invoke(cpsObject obj, void **args)
{
    if (!mmethod) { return nullptr; }
    return mono_runtime_invoke(mmethod, obj, args, nullptr);
}

int cpsMethod::getParamCount() const
{
    if (!mmethod) { return -1; }
    MonoMethodSignature *sig = mono_method_signature(mmethod);
    return mono_signature_get_param_count(sig);
}

cpsType cpsMethod::getReturnType() const
{
    if (!mmethod) { return nullptr; }
    MonoMethodSignature *sig = mono_method_signature(mmethod);
    return mono_signature_get_return_type(sig);
}

void cpsMethod::eachArgTypes(const std::function<void(cpsType&)>& f) const
{
    if (!mmethod) { return; }
    MonoMethodSignature *sig = mono_method_signature(mmethod);
    MonoType *mt = nullptr;
    gpointer iter = nullptr;
    while (mt = mono_signature_get_params(sig, &iter)) {
        cpsType miot = mt;
        f(miot);
    }
}

cpsMethod cpsMethod::instantiate(cpsClass *params, int num_params)
{
    // todo: fix this leak
    void *buf = malloc(sizeof(MonoGenericInst)+(sizeof(void*)*(num_params-1)));
    MonoGenericInst *gi = (MonoGenericInst*)buf;
    gi->id = -1;
    gi->is_open = 0; // must be zero!
    gi->type_argc = num_params;
    for (int i = 0; i < num_params; ++i) {
        gi->type_argv[i] = params[i].getType().mtype;
    }
    MonoGenericContext ctx = { nullptr, gi };
    return mono_class_inflate_generic_method(mmethod, &ctx);
}


const char* cpsClass::getName() const
{
    if (!mclass) { return nullptr; }
    return mono_class_get_name(mclass);
}

cpsType cpsClass::getType() const
{
    if (!mclass) { return nullptr; }
    return mono_class_get_type(mclass);
}

cpsField cpsClass::findField(const char *name) const
{
    if (!mclass) { return nullptr; }
    return mono_class_get_field_from_name(mclass, name);
}

cpsProperty cpsClass::findProperty(const char *name) const
{
    if (!mclass) { return nullptr; }
    return mono_class_get_property_from_name(mclass, name);
}

cpsMethod cpsClass::findMethod(const char *name, int num_args, const char **arg_typenames) const
{
    if (!mclass) { return nullptr; }
    if (arg_typenames != nullptr) {
        for (cpsClass mc = mclass; mc; mc = mc.getParent()) {
            MonoMethod *method;
            gpointer iter = nullptr;
            while ((method = mono_class_get_methods(mclass, &iter))) {
                if (strcmp(mono_method_get_name(method), name) != 0) { continue; }
                MonoMethodSignature *sig = mono_method_signature(method);
                if (mono_signature_get_param_count(sig) != num_args) { continue; }
                MonoType *mt = nullptr;
                gpointer iter = nullptr;
                for (int ia = 0; ia < num_args; ++ia) {
                    mt = mono_signature_get_params(sig, &iter);
                    if (strcmp(mono_type_get_name(mt), arg_typenames[ia]) != 0) {
                        goto next_method;
                    }
                }
                return method;
            next_method:;
            }
        }
    }
    else {
        for (cpsClass mc = mclass; mc; mc = mc.getParent()) {
            if (MonoMethod *ret = mono_class_get_method_from_name(mc.mclass, name, num_args)) {
                return ret;
            }
        }
    }
    return nullptr;
}

void cpsClass::eachFields(const std::function<void(cpsField&)> &f)
{
    MonoClassField *field = nullptr;
    gpointer iter = nullptr;
    while ((field = mono_class_get_fields(mclass, &iter))) {
        cpsField mf = field;
        f(mf);
    }
}

void cpsClass::eachProperties(const std::function<void(cpsProperty&)> &f)
{
    MonoProperty *prop = nullptr;
    gpointer iter = nullptr;
    while ((prop = mono_class_get_properties(mclass, &iter))) {
        cpsProperty mp = prop;
        f(mp);
    }
}

void cpsClass::eachMethods(const std::function<void(cpsMethod&)> &f)
{
    MonoMethod *method = nullptr;
    gpointer iter = nullptr;
    while ((method = mono_class_get_methods(mclass, &iter))) {
        cpsMethod mm = method;
        f(mm);
    }
}

void cpsClass::eachFieldsUpwards(const std::function<void(cpsField&, cpsClass&)> &f)
{
    cpsClass c = mclass;
    do {
        MonoClassField *field = nullptr;
        gpointer iter = nullptr;
        while (field = mono_class_get_fields(c.mclass, &iter)) {
            cpsField m = field;
            f(m, c);
        }
        c = c.getParent();
    } while (c);
}

void cpsClass::eachPropertiesUpwards(const std::function<void(cpsProperty&, cpsClass&)> &f)
{
    cpsClass c = mclass;
    do {
        MonoProperty *prop = nullptr;
        gpointer iter = nullptr;
        while (prop = mono_class_get_properties(c.mclass, &iter)) {
            cpsProperty m = prop;
            f(m, c);
        }
        c = c.getParent();
    } while (c);
}

void cpsClass::eachMethodsUpwards(const std::function<void(cpsMethod&, cpsClass&)> &f)
{
    cpsClass c = mclass;
    do {
        MonoMethod *method = nullptr;
        gpointer iter = nullptr;
        while (method = mono_class_get_methods(c.mclass, &iter)) {
            cpsMethod m = method;
            f(m, c);
        }
        c = c.getParent();
    } while (c);
}


cpsClass cpsClass::getParent() const
{
    return mono_class_get_parent(mclass);
}


cpsClass cpsObject::getClass() const
{
    return mono_object_get_class(mobj);
}

MonoDomain* cpsObject::getDomain() const
{
    return mono_object_get_domain(mobj);
}

/*static*/ cpsObject cpsObject::create(cpsClass mclass)
{
    return mono_object_new(mono_domain_get(), mclass);
}


void* cpsObject::getDataPtr()
{
    return (char*)mobj + sizeof(MonoObject);
}

cpsField cpsObject::findField(const char *name) const
{
    return getClass().findField(name);
}
cpsProperty cpsObject::findProperty(const char *name) const
{
    return getClass().findProperty(name);
}
cpsMethod cpsObject::findMethod(const char *name, int num_args, const char **arg_typenames) const
{
    return getClass().findMethod(name, num_args, arg_typenames);
}


struct cpsLessCString
{
    bool operator()(const char *a, const char *b) const
    {
        return strcmp(a,b)<0;
    }
};

class cpsMethodManager
{
public:
    typedef std::map<const char*, void*, cpsLessCString> MethodTable;
    static cpsMethodManager* getInstance();
    void addMethod(const char * name, void *method);
    void registerAll();

private:
    static cpsMethodManager *s_inst;
    MethodTable m_methods;
};

/*static*/ cpsMethodManager* cpsMethodManager::s_inst;
/*static*/ cpsMethodManager* cpsMethodManager::getInstance()
{
    if (!s_inst) {
        s_inst = new cpsMethodManager();
    }
    return s_inst;
}

void cpsMethodManager::addMethod(const char * name, void *method)
{
    m_methods[name] = method;
}

void cpsMethodManager::registerAll()
{
    for (auto m : m_methods) {
        mono_add_internal_call(m.first, m.second);
    }
}


cpsAPI void cpsAddMethod(const char *name, void *addr)
{
    mono_add_internal_call(name, addr);
}

/*static*/ cpsString cpsString::create(const cps_char8 *str, int len)
{
    return cpsString(mono_string_new_len(mono_domain_get(), str, len == -1 ? (int)strlen(str) : len));
}

/*static*/ cpsString cpsString::create(const cps_char16 *str, int len)
{
    if (len == -1) {
        for (len = 0;; ++len) {
            if (str[len] == 0) { break; }
        }
    }
    return cpsString(mono_string_new_utf16(mono_domain_get(), str, len));
}

const cps_char8* cpsString::toUTF8()
{
    return mono_string_to_utf8((MonoString*)mobj);
}

const cps_char16* cpsString::toUTF16()
{
    return mono_string_to_utf16((MonoString*)mobj);
}


/*static*/ cpsArray cpsArray::create(cpsClass klass, size_t size)
{
    MonoArray *ret = mono_array_new(mono_domain_get(), klass, size);
    return ret;
}

size_t cpsArray::getSize() const
{
    return ((MonoArray*)mobj)->max_length;
}
void* cpsArray::getData()
{
    return ((MonoArray*)mobj)->vector;
}


template<> cpsAPI cpsClass    cpsTypeinfo<bool>()
{
    static cpsCachedClass s_class;
    if (!s_class) { s_class = mono_get_boolean_class(); }
    return s_class;
}
template<> cpsAPI const char* cpsTypename<bool>()
{
    return "System.Boolean";
}

template<> cpsAPI cpsClass    cpsTypeinfo<int>()
{
    static cpsCachedClass s_class;
    if (!s_class) { s_class = mono_get_int32_class(); }
    return s_class;
}
template<> cpsAPI const char* cpsTypename<int>()
{
    return "System.Int32";
}

template<> cpsAPI cpsClass cpsTypeinfo<float>()
{
    static cpsCachedClass s_class;
    if (!s_class) { s_class = mono_get_single_class(); }
    return s_class;
}
template<> cpsAPI const char* cpsTypename<float>()
{
    return "System.Single";
}

template<> cpsAPI cpsClass cpsTypeinfo<cpsString>()
{
    static cpsCachedClass s_class;
    if (!s_class) { s_class = mono_get_string_class(); }
    return s_class;
}
template<> cpsAPI const char* cpsTypename<cpsString>()
{
    return "System.String";
}



void cpsClearCache();

cpsCLinkage cpsExport void cpsCoreInitialize()
{
    static bool s_is_first = true;

    if (s_is_first) {
        s_is_first = false;

#ifdef _WIN32
        char path_to_this_module[MAX_PATH + 1];
        {
            HMODULE mod = 0;
            ::GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS, (LPCSTR)&cpsCoreInitialize, &mod);
            DWORD size = ::GetModuleFileNameA(mod, path_to_this_module, sizeof(path_to_this_module));
            for (int i = size - 1; i >= 0; --i) {
                if (path_to_this_module[i] == '\\') {
                    path_to_this_module[i] = '\0';
                    break;
                }
            }
        }


        // add plugin directory to PATH environment variable to load dependent dlls 
        std::string path;
        path.resize(1024 * 64);

        DWORD ret = ::GetEnvironmentVariableA("PATH", &path[0], (DWORD)path.size());
        path.resize(ret);
        path += ";";
        path += path_to_this_module;
        ::SetEnvironmentVariableA("PATH", path.c_str());

        std::string cppscript_dll = path_to_this_module;
        cppscript_dll += "\\CppScript.dll";
        HMODULE cppscript = ::LoadLibraryA(cppscript_dll.c_str());
        if (cppscript) {
            typedef void(*proc_t)();
            if (proc_t p = (proc_t)::GetProcAddress(cppscript, "cpsInitialize()")) {
                p();
            }
        }

#if !defined(cpsWithoutDbgHelp)
        ::SymSetOptions(SYMOPT_DEFERRED_LOADS | SYMOPT_DEBUG);
        ::SymInitialize(::GetCurrentProcess(), NULL, TRUE);
#endif

#elif defined(__APPLE__)

#endif
    }
    cpsClearCache();
}
