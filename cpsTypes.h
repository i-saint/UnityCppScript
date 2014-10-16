#ifndef cpsTypes_h
#define cpsTypes_h

#include <functional>
#include <cstdio>
#include <cstdarg>

#define cpsCLinkage extern "C"
#define cpsExport __declspec(dllexport)
#ifndef cpsAPI
#   pragma comment(lib, "CppScriptCore.lib")
#   define cpsAPI __declspec(dllimport)
#endif

class cpsObject;
class cpsType;
class cpsClass;
class cpsMethod;
class cpsField;
class cpsProperty;


class cpsAPI cpsImage
{
public:
    static cpsImage findImage(const char *name); // name: not includes extensions. ex: "UnityEngine"

    cpsImage(void *m) : mimage(m) {}
    operator void*() const { return mimage; }
    operator bool() const { return mimage != nullptr; }

    cpsClass findClass(const char *namespace_, const char *class_name);

private:
    void *mimage;
};

class cpsAPI cpsType
{
public:
    cpsType(void *m) : mtype(m) {}
    operator void*() const { return mtype; }
    operator bool() const { return mtype != nullptr; }
    const char* getName() const;
    cpsClass getClass() const;

private:
    void *mtype;
};


class cpsAPI cpsField
{
public:
    cpsField(void *mc) : mfield(mc) {}
    operator void*() const { return mfield; }
    operator bool() const { return mfield != nullptr; }
    const char* getName() const;

    cpsType getType() const;
    int getOffset() const;
    template<class T> void getValue(cpsObject obj, T &o) const { getValueImpl(obj, &o); }
    template<class T> void setValue(cpsObject obj, const T &o) { setValueImpl(obj, &o); }

    void getValueImpl(cpsObject obj, void *p) const;
    void setValueImpl(cpsObject obj, const void *p);

private:
    void *mfield;
};


class cpsAPI cpsProperty
{
public:
    cpsProperty(void *mc) : mproperty(mc) {}
    operator void*() const { return mproperty; }
    operator bool() const { return mproperty != nullptr; }
    const char* getName() const;

    cpsMethod getGetter() const;
    cpsMethod getSetter() const;

private:
    void *mproperty;
};


class cpsAPI cpsMethod
{
public:
    cpsMethod(void *mm) : mmethod(mm) {}
    operator void*() const { return mmethod; }
    operator bool() const { return mmethod != nullptr; }
    const char* getName() const;

    int getParamCount() const;
    cpsType getReturnType() const;
    void eachArgTypes(const std::function<void(cpsType&)>&) const;
    
    cpsObject invoke(cpsObject obj, void **args);
    cpsMethod instantiate(cpsClass *params, int num_params);

private:
    void *mmethod;
};


class cpsAPI cpsClass
{
public:
    cpsClass(void *mc) : mclass(mc) {}
    operator void*() const { return mclass; }
    operator bool() const { return mclass != nullptr; }
    const char* getName() const;
    cpsType     getType() const;
    cpsClass    getParent() const;

    cpsField    findField(const char *name) const;
    cpsProperty findProperty(const char *name) const;
    cpsMethod   findMethod(const char *name, int num_args=-1) const; // num_args: -1=don't care

    // enumerate members (not include parent class members)
    void eachFields(const std::function<void(cpsField&)> &f);
    void eachProperties(const std::function<void(cpsProperty&)> &f);
    void eachMethods(const std::function<void(cpsMethod&)> &f);
    // include parent classes
    void eachFieldsUpwards(const std::function<void(cpsField&, cpsClass&)> &f);
    void eachPropertiesUpwards(const std::function<void(cpsProperty&, cpsClass&)> &f);
    void eachMethodsUpwards(const std::function<void(cpsMethod&, cpsClass&)> &f);

    //cpsClass insantiate(cpsClass *template_params);

private:
    void *mclass;
};


class cpsAPI cpsObject
{
public:
    cpsObject(void *o) : mobj(o) {}
    operator void*() const { return mobj; }
    operator bool() const { return mobj != nullptr; }

    void*       getDomain() const;
    cpsClass    getClass() const;
    void*       getData();

private:
    void *mobj;
};


#endif // cpsTypes_h
