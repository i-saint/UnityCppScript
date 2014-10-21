#include "cpsInternal.h"
#include "cpsTypes.h"
#include "cpsUtils.h"
#include <vector>
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
    mono_field_get_value((MonoObject*)(void*)obj, mfield, p);
}

void cpsField::setValueImpl(cpsObject obj, const void *p)
{
    if (!mfield) { return; }
    mono_field_set_value((MonoObject*)(void*)obj, mfield, (void*)p);
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
    return mono_method_get_name((MonoMethod*)mmethod);
}

bool cpsMethod::isGeneric() const
{
    return (((MonoMethod*)mmethod)->is_generic) != 0;
}

bool cpsMethod::isInflated() const
{
    return (((MonoMethod*)mmethod)->is_inflated) != 0;
}

bool cpsMethod::isStatic() const
{
    return (((MonoMethod*)mmethod)->flags & METHOD_ATTRIBUTE_STATIC) != 0;
}

bool cpsMethod::isVirtual() const
{
    return (((MonoMethod*)mmethod)->flags & METHOD_ATTRIBUTE_VIRTUAL) != 0;
}


cpsObject cpsMethod::invoke(cpsObject obj, void **args)
{
    if (!mmethod) { return nullptr; }
    return mono_runtime_invoke((MonoMethod*)mmethod, (MonoObject*)(void*)obj, args, nullptr);
}

int cpsMethod::getParamCount() const
{
    if (!mmethod) { return -1; }
    void *sig = mono_method_signature((MonoMethod*)mmethod);
    return mono_signature_get_param_count(sig);
}

cpsType cpsMethod::getReturnType() const
{
    if (!mmethod) { return nullptr; }
    void *sig = mono_method_signature((MonoMethod*)mmethod);
    return mono_signature_get_return_type(sig);
}

void cpsMethod::eachArgTypes(const std::function<void(cpsType&)>& f) const
{
    if (!mmethod) { return; }
    void *sig = mono_method_signature((MonoMethod*)mmethod);
    void *mt = nullptr;
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
        gi->type_argv[i] = params[i].getType();
    }
    MonoGenericContext ctx = { nullptr, gi };
    return mono_class_inflate_generic_method((MonoMethod*)mmethod, &ctx);
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
            void *method;
            gpointer iter = nullptr;
            while ((method = mono_class_get_methods(mclass, &iter))) {
                if (strcmp(mono_method_get_name((MonoMethod*)method), name) != 0) { continue; }
                MonoMethodSignature *sig = mono_method_signature((MonoMethod*)method);
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
            if (MonoMethod *ret = mono_class_get_method_from_name(mc, name, num_args)) {
                return ret;
            }
        }
    }
    return nullptr;
}

void cpsClass::eachFields(const std::function<void(cpsField&)> &f)
{
    void *field;
    gpointer iter = nullptr;
    while ((field = mono_class_get_fields(mclass, &iter))) {
        cpsField mf = field;
        f(mf);
    }
}

void cpsClass::eachProperties(const std::function<void(cpsProperty&)> &f)
{
    void *prop;
    gpointer iter = nullptr;
    while ((prop = mono_class_get_properties(mclass, &iter))) {
        cpsProperty mp = prop;
        f(mp);
    }
}

void cpsClass::eachMethods(const std::function<void(cpsMethod&)> &f)
{
    void *method;
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
        void *field;
        gpointer iter = nullptr;
        while (field = mono_class_get_fields(c, &iter)) {
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
        void *prop;
        gpointer iter = nullptr;
        while (prop = mono_class_get_properties(c, &iter)) {
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
        void *method;
        gpointer iter = nullptr;
        while (method = mono_class_get_methods(c, &iter)) {
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
    return mono_object_get_class((MonoObject*)mobj);
}

void* cpsObject::getDomain() const
{
    return mono_object_get_domain((MonoObject*)mobj);
}

void* cpsObject::getDataPtr() const
{
    return (char*)mobj + sizeof(void*)*2;
}


void cpsClearCache();

cpsAPI void cpsAddMethod(const char *name, void *addr)
{
    mono_add_internal_call(name, addr);
}

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

#if !defined(cpsWithoutDbgHelp)
        ::SymSetOptions(SYMOPT_DEFERRED_LOADS | SYMOPT_DEBUG);
        ::SymInitialize(::GetCurrentProcess(), NULL, TRUE);
#endif

#elif defined(__APPLE__)

#endif
    }
    cpsClearCache();
}
