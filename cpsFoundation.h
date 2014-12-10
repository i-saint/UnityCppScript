#ifndef cpsFoundation_h
#define cpsFoundation_h

#define _ITERATOR_DEBUG_LEVEL 0

#include <cstdio>
#include <cstdarg>
#include <cstdint>
#include <cmath>
#include <algorithm>
#include <functional>


#define cpsCLinkage extern "C"
#define cpsExport __declspec(dllexport)
#ifndef cpsAPI
#   pragma comment(lib, "CppScriptCore.lib")
#   define cpsAPI __declspec(dllimport)

struct MonoDomain;
struct MonoImage;
struct MonoType;
struct MonoClassField;
struct MonoProperty;
struct MonoMethod;
struct MonoClass;
struct MonoObject;
struct MonoString;
struct MonoArray;
#endif

class cpsType;
class cpsClass;
class cpsMethod;
class cpsField;
class cpsProperty;
class cpsObject;
class cpsArray;
class cpsString;

typedef char        cps_char8;
typedef uint16_t    cps_char16;

bool cpsAPI cpsIsSubclassOf(cpsClass parent, cpsClass child);
template<class T> const char* cpsTypename();
template<class T> const char* cpsTypenameRef();
template<class T> const char* cpsTypenameArray();
template<class T> cpsClass    cpsTypeinfo();


class cpsAPI cpsImage
{
public:
    static cpsImage findImage(const char *name); // name: not includes extensions. ex: "UnityEngine"

    cpsImage(MonoImage *m) : mimage(m) {}
    operator void*() const { return mimage; }
    operator bool() const { return mimage != nullptr; }

    cpsClass findClass(const char *namespace_, const char *class_name);

public:
    MonoImage *mimage;
};

class cpsAPI cpsType
{
public:
    cpsType(MonoType *m) : mtype(m) {}
    operator MonoType*() const { return mtype; }
    operator bool() const { return mtype != nullptr; }
    const char* getName() const;
    cpsClass getClass() const;

public:
    MonoType *mtype;
};


class cpsAPI cpsField
{
public:
    cpsField(MonoClassField *mc) : mfield(mc) {}
    operator MonoClassField*() const { return mfield; }
    operator bool() const { return mfield != nullptr; }
    const char* getName() const;

    cpsType getType() const;
    int getOffset() const;
    template<class T> void getValue(cpsObject obj, T &o) const { getValueImpl(obj, &o); }
    template<class T> void setValue(cpsObject obj, const T &o) { setValueImpl(obj, &o); }
    template<class T> void setValueRef(cpsObject obj, T *o) { setValueImpl(obj, o); }

    void getValueImpl(cpsObject obj, void *p) const;
    void setValueImpl(cpsObject obj, const void *p);

public:
    MonoClassField *mfield;
};


class cpsAPI cpsProperty
{
public:
    cpsProperty(MonoProperty *mc) : mproperty(mc) {}
    operator MonoProperty*() const { return mproperty; }
    operator bool() const { return mproperty != nullptr; }
    const char* getName() const;

    cpsMethod getGetter() const;
    cpsMethod getSetter() const;

public:
    MonoProperty *mproperty;
};


class cpsAPI cpsMethod
{
public:
    cpsMethod(MonoMethod *mm) : mmethod(mm) {}
    operator MonoMethod*() const { return mmethod; }
    operator bool() const { return mmethod != nullptr; }
    const char* getName() const;

    int getParamCount() const;
    cpsType getReturnType() const;
    void eachArgTypes(const std::function<void(cpsType&)>&) const;
    bool isGeneric() const;
    bool isInflated() const;
    bool isStatic() const;
    bool isVirtual() const;

    cpsObject invoke(cpsObject obj, void **args=nullptr);
    cpsMethod instantiate(cpsClass *params, int num_params);

public:
    MonoMethod *mmethod;
};


class cpsAPI cpsClass
{
public:
    cpsClass(MonoClass *mc) : mclass(mc) {}
    operator MonoClass*() const { return mclass; }
    operator bool() const { return mclass != nullptr; }
    const char* getName() const;
    cpsType     getType() const;
    cpsClass    getParent() const;

    cpsField    findField(const char *name) const;
    cpsProperty findProperty(const char *name) const;
    cpsMethod   findMethod(const char *name, int num_args=-1, const char **arg_typenames=nullptr) const; // num_args: -1=don't care

    // enumerate members (not include parent class members)
    void eachFields(const std::function<void(cpsField&)> &f);
    void eachProperties(const std::function<void(cpsProperty&)> &f);
    void eachMethods(const std::function<void(cpsMethod&)> &f);
    // include parent classes
    void eachFieldsUpwards(const std::function<void(cpsField&, cpsClass&)> &f);
    void eachPropertiesUpwards(const std::function<void(cpsProperty&, cpsClass&)> &f);
    void eachMethodsUpwards(const std::function<void(cpsMethod&, cpsClass&)> &f);

    //cpsClass insantiate(cpsClass *template_params);

    template<class T>
    T as() const { return cpsIsSubclassOf(*this, cpsTypeinfo<T>()) ? T(*this) : nullptr; }

public:
    MonoClass *mclass;
};


class cpsAPI cpsObject
{
public:
    static cpsObject create(cpsClass mclass);

    cpsObject(MonoObject *o) : mobj(o) {}
    operator MonoObject*() const { return mobj; }
    operator bool() const { return mobj != nullptr; }

    MonoDomain* getDomain() const;
    cpsClass    getClass() const;
    void*       getDataPtr();
    template<class T> T& getValue(int offset=0) { return *(T*)((size_t)getDataPtr()+offset); }

    // redirect to cpsClass
    cpsField    findField(const char *name) const;
    cpsProperty findProperty(const char *name) const;
    cpsMethod   findMethod(const char *name, int num_args = -1, const char **arg_typenames = nullptr) const;

public:
    MonoObject *mobj;
};


class cpsAPI cpsString : public cpsObject
{
public:
    static cpsString create(const cps_char8 *str, int len = -1);
    static cpsString create(const cps_char16 *str, int len = -1);

    cpsString(MonoObject *o) : cpsObject(o) {}
    cpsString(MonoString *o) : cpsObject((MonoObject*)o) {}

    const cps_char8*    toUTF8();
    const cps_char16*   toUTF16();
};

class cpsAPI cpsArray : public cpsObject
{
public:
    static cpsArray create(cpsClass klass, size_t size);

    cpsArray(MonoObject *o) : cpsObject(o) {}
    cpsArray(MonoArray *o) : cpsObject((MonoObject*)o) {}

    size_t getSize() const;
    void* getDataPtr();
};

template<class T>
class cpsTArray
{
public:
    typedef T           value_type;
    typedef T&          reference;
    typedef const T&    const_reference;
    typedef T*          pointer;
    typedef const T*    const_pointer;
    typedef T*          iterator;
    typedef const T*    const_iterator;

    cpsTArray(cpsObject cs_array) : m_array(cs_array), m_size(m_array.getSize()), m_data((pointer)m_array.getDataPtr()) {}
    cpsTArray(cpsArray cs_array) : m_array(cs_array), m_size(m_array.getSize()), m_data((pointer)m_array.getDataPtr()) {}
    size_t          size() const                { return m_size; }
    reference       operator[](size_t i)        { return m_data[i]; }
    const_reference operator[](size_t i) const  { return m_data[i]; }
    iterator        begin()                     { return m_data; }
    iterator        end()                       { return m_data + m_size; }
    const_iterator  begin() const               { return m_data; }
    const_iterator  end() const                 { return m_data + m_size; }
    operator bool() const { return m_array; }
    operator cpsArray() const { return m_array; }

private:
    cpsArray m_array;
    size_t m_size;
    pointer m_data;
};




#define cpsDeclTraits()\
    static cpsClass getClass();\
    static const char* getTypename();\
    static const char* getTypenameRef();\
    static const char* getTypenameArray();


#define cpsImplTraits(Namespace, Type)\
    cpsClass Type::getClass()\
    {\
        static cpsCachedClass s_class;\
        if (!s_class) { s_class = GetImage().findClass(#Namespace, #Type); }\
        return s_class;\
    }\
    const char* Type::getTypename()\
    {\
        return #Namespace "." #Type;\
    }\
    const char* Type::getTypenameRef()\
    {\
        return #Namespace "." #Type "&";\
    }\
    const char* Type::getTypenameArray()\
    {\
        return #Namespace "." #Type "[]";\
    }

#define cpsDeclTraitsF(Namespace, Type)\
    template<> cpsAPI cpsClass    cpsTypeinfo<Namespace##::##Type>();\
    template<> cpsAPI const char* cpsTypename<Namespace##::##Type>();\
    template<> cpsAPI const char* cpsTypenameRef<Namespace##::##Type>();\
    template<> cpsAPI const char* cpsTypenameArray<Namespace##::##Type>();

#define cpsImplTraitsF(Namespace, Type)\
    template<> cpsAPI cpsClass cpsTypeinfo<Namespace##::##Type>()\
    {\
        static cpsCachedClass s_class;\
        if (!s_class) { s_class = Namespace::GetImage().findClass(#Namespace, #Type); }\
        return s_class;\
    }\
    template<> cpsAPI const char* cpsTypename<Namespace##::##Type>()\
    {\
        return #Namespace "." #Type;\
    }\
    template<> cpsAPI const char* cpsTypenameRef<Namespace##::##Type>()\
    {\
        return #Namespace "." #Type "&";\
    }\
    template<> cpsAPI const char* cpsTypenameArray<Namespace##::##Type&>()\
    {\
        return #Namespace "." #Type "[]";\
    }



template<class T> const char* cpsTypename()     { return T::getTypename(); }
template<class T> const char* cpsTypenameRef()  { return T::getTypenameRef(); }
template<class T> const char* cpsTypenameArray(){ return T::getTypenameArray(); }
template<class T> cpsClass    cpsTypeinfo() { return T::getClass(); }

template<> cpsAPI cpsClass    cpsTypeinfo<bool>();
template<> cpsAPI const char* cpsTypename<bool>();
template<> cpsAPI cpsClass    cpsTypeinfo<uint8_t>();
template<> cpsAPI const char* cpsTypename<uint8_t>();
template<> cpsAPI cpsClass    cpsTypeinfo<int>();
template<> cpsAPI const char* cpsTypename<int>();
template<> cpsAPI cpsClass    cpsTypeinfo<float>();
template<> cpsAPI const char* cpsTypename<float>();
template<> cpsAPI cpsClass    cpsTypeinfo<cpsString>();
template<> cpsAPI const char* cpsTypename<cpsString>();

cpsAPI uint32_t cpsPin(cpsObject obj);
cpsAPI void cpsUnpin(uint32_t handle);

cpsAPI void cpsClearCache();


#endif // cpsFoundation_h
