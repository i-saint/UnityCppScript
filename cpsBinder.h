#ifndef cpsBinder_h
#define cpsBinder_h

#include "cpsFoundation.h"
#include <type_traits>
#define cpsUnRefConst(T) typename std::remove_const<typename std::remove_reference<T>::type>::type

#pragma region cps_function_binder_detail

template<class R>
struct cpsFB_Fn0
{
    typedef R (*F)();
    R invoke(F f, va_list args)
    {
        return f();
    }
};
template<>
struct cpsFB_Fn0<void>
{
    typedef void (*F)();
    void* invoke(F f, va_list args)
    {
        f();
        return nullptr;
    }
};

template<class R, class C>
struct cpsFB_MemFn0
{
    typedef R (C::*F)();
    R invoke(F f, C &o, va_list args)
    {
        return (o.*f)();
    }
};
template<class C>
struct cpsFB_MemFn0<void, C>
{
    typedef void (C::*F)();
    void* invoke(F f, C &o, va_list args)
    {
        (o.*f)();
        return nullptr;
    }
};

template<class R, class C>
struct cpsFB_ConstMemFn0
{
    typedef R (C::*F)() const;
    R invoke(F f, const C &o, va_list args)
    {
        return (o.*f)();
    }
};
template<class C>
struct cpsFB_ConstMemFn0<void, C>
{
    typedef void (C::*F)() const;
    void* invoke(F f, const C &o, va_list args)
    {
        (o.*f)();
        return nullptr;
    }
};



template<class R, class A0>
struct cpsFB_Fn1
{
    typedef R (*F)(A0);
    R invoke(F f, va_list args)
    {
        typedef cpsUnRefConst(A0) A0V;
        A0V &a0 = va_arg(args, A0V);
        return f(a0);
    }
};
template<class A0>
struct cpsFB_Fn1 < void, A0 >
{
    typedef void (*F)(A0);
    void* invoke(F f, va_list args)
    {
        typedef cpsUnRefConst(A0) A0V;
        A0V &a0 = va_arg(args, A0V);
        f(a0);
        return nullptr;
    }
};

template<class R, class C, class A0>
struct cpsFB_MemFn1
{
    typedef R (C::*F)(A0);
    R invoke(F f, C &o, va_list args)
    {
        typedef cpsUnRefConst(A0) A0V;
        A0V &a0 = va_arg(args, A0V);
        return (o.*f)(a0);
    }
};
template<class C, class A0>
struct cpsFB_MemFn1 < void, C, A0 >
{
    typedef void (C::*F)(A0);
    void* invoke(F f, C &o, va_list args)
    {
        typedef cpsUnRefConst(A0) A0V;
        A0V &a0 = va_arg(args, A0V);
        (o.*f)(a0);
        return nullptr;
    }
};

template<class R, class C, class A0>
struct cpsFB_ConstMemFn1
{
    typedef R (C::*F)(A0) const;
    R invoke(F f, const C &o, va_list args)
    {
        typedef cpsUnRefConst(A0) A0V;
        A0V &a0 = va_arg(args, A0V);
        return (o.*f)(a0);
    }
};
template<class C, class A0>
struct cpsFB_ConstMemFn1 < void, C, A0 >
{
    typedef void (C::*F)(A0) const;
    void* invoke(F f, const C &o, va_list args)
    {
        typedef cpsUnRefConst(A0) A0V;
        A0V &a0 = va_arg(args, A0V);
        (o.*f)(a0);
        return nullptr;
    }
};



template<class R, class A0, class A1>
struct cpsFB_Fn2
{
    typedef R(*F)(A0, A1);
    R invoke(F f, va_list args)
    {
        typedef cpsUnRefConst(A0) A0V;
        typedef cpsUnRefConst(A1) A1V;
        A0V &a0 = va_arg(args, A0V);
        A1V &a1 = va_arg(args, A1V);
        return f(a0, a1);
    }
};
template<class A0, class A1>
struct cpsFB_Fn2 < void, A0, A1 >
{
    typedef void(*F)(A0, A1);
    void* invoke(F f, va_list args)
    {
        typedef cpsUnRefConst(A0) A0V;
        typedef cpsUnRefConst(A1) A1V;
        A0V &a0 = va_arg(args, A0V);
        A1V &a1 = va_arg(args, A1V);
        f(a0, a1);
        return nullptr;
    }
};

template<class R, class C, class A0, class A1>
struct cpsFB_MemFn2
{
    typedef R(C::*F)(A0, A1);
    R invoke(F f, C &o, va_list args)
    {
        typedef cpsUnRefConst(A0) A0V;
        typedef cpsUnRefConst(A1) A1V;
        A0V &a0 = va_arg(args, A0V);
        A1V &a1 = va_arg(args, A1V);
        return (o.*f)(a0, a1);
    }
};
template<class C, class A0, class A1>
struct cpsFB_MemFn2 < void, C, A0, A1 >
{
    typedef void (C::*F)(A0, A1);
    void* invoke(F f, C &o, va_list args)
    {
        typedef cpsUnRefConst(A0) A0V;
        typedef cpsUnRefConst(A1) A1V;
        A0V &a0 = va_arg(args, A0V);
        A1V &a1 = va_arg(args, A1V);
        (o.*f)(a0, a1);
        return nullptr;
    }
};

template<class R, class C, class A0, class A1>
struct cpsFB_ConstMemFn2
{
    typedef R(C::*F)(A0, A1) const;
    R invoke(F f, const C &o, va_list args)
    {
        typedef cpsUnRefConst(A0) A0V;
        typedef cpsUnRefConst(A1) A1V;
        A0V &a0 = va_arg(args, A0V);
        A1V &a1 = va_arg(args, A1V);
        return (o.*f)(a0, a1);
    }
};
template<class C, class A0, class A1>
struct cpsFB_ConstMemFn2 < void, C, A0, A1 >
{
    typedef void (C::*F)(A0, A1) const;
    void* invoke(F f, const C &o, va_list args)
    {
        typedef cpsUnRefConst(A0) A0V;
        typedef cpsUnRefConst(A1) A1V;
        A0V &a0 = va_arg(args, A0V);
        A1V &a1 = va_arg(args, A1V);
        (o.*f)(a0, a1);
        return nullptr;
    }
};



template<class R, class A0, class A1, class A2>
struct cpsFB_Fn3
{
    typedef R(*F)(A0, A1, A2);
    R invoke(F f, va_list args)
    {
        typedef cpsUnRefConst(A0) A0V;
        typedef cpsUnRefConst(A1) A1V;
        typedef cpsUnRefConst(A2) A2V;
        A0V &a0 = va_arg(args, A0V);
        A1V &a1 = va_arg(args, A1V);
        A2V &a2 = va_arg(args, A2V);
        return f(a0, a1, a2);
    }
};
template<class A0, class A1, class A2>
struct cpsFB_Fn3 < void, A0, A1, A2 >
{
    typedef void(*F)(A0, A1, A2);
    void* invoke(F f, va_list args)
    {
        typedef cpsUnRefConst(A0) A0V;
        typedef cpsUnRefConst(A1) A1V;
        typedef cpsUnRefConst(A2) A2V;
        A0V &a0 = va_arg(args, A0V);
        A1V &a1 = va_arg(args, A1V);
        A2V &a2 = va_arg(args, A2V);
        f(a0, a1, a2);
        return nullptr;
    }
};

template<class R, class C, class A0, class A1, class A2>
struct cpsFB_MemFn3
{
    typedef R(C::*F)(A0, A1, A2);
    R invoke(F f, C &o, va_list args)
    {
        typedef cpsUnRefConst(A0) A0V;
        typedef cpsUnRefConst(A1) A1V;
        typedef cpsUnRefConst(A2) A2V;
        A0V &a0 = va_arg(args, A0V);
        A1V &a1 = va_arg(args, A1V);
        A2V &a2 = va_arg(args, A2V);
        return (o.*f)(a0, a1, a2);
    }
};
template<class C, class A0, class A1, class A2>
struct cpsFB_MemFn3 < void, C, A0, A1, A2 >
{
    typedef void (C::*F)(A0, A1, A2);
    void* invoke(F f, C &o, va_list args)
    {
        typedef cpsUnRefConst(A0) A0V;
        typedef cpsUnRefConst(A1) A1V;
        typedef cpsUnRefConst(A2) A2V;
        A0V &a0 = va_arg(args, A0V);
        A1V &a1 = va_arg(args, A1V);
        A2V &a2 = va_arg(args, A2V);
        (o.*f)(a0, a1, a2);
        return nullptr;
    }
};

template<class R, class C, class A0, class A1, class A2>
struct cpsFB_ConstMemFn3
{
    typedef R(C::*F)(A0, A1, A2) const;
    R invoke(F f, const C &o, va_list args)
    {
        typedef cpsUnRefConst(A0) A0V;
        typedef cpsUnRefConst(A1) A1V;
        typedef cpsUnRefConst(A2) A2V;
        A0V &a0 = va_arg(args, A0V);
        A1V &a1 = va_arg(args, A1V);
        A2V &a2 = va_arg(args, A2V);
        return (o.*f)(a0, a1, a2);
    }
};
template<class C, class A0, class A1, class A2>
struct cpsFB_ConstMemFn3 < void, C, A0, A1, A2 >
{
    typedef void (C::*F)(A0, A1, A2) const;
    void* invoke(F f, const C &o, va_list args)
    {
        typedef cpsUnRefConst(A0) A0V;
        typedef cpsUnRefConst(A1) A1V;
        typedef cpsUnRefConst(A2) A2V;
        A0V &a0 = va_arg(args, A0V);
        A1V &a1 = va_arg(args, A1V);
        A2V &a2 = va_arg(args, A2V);
        (o.*f)(a0, a1, a2);
        return nullptr;
    }
};



template<class R, class A0, class A1, class A2, class A3>
struct cpsFB_Fn4
{
    typedef R(*F)(A0, A1, A2, A3);
    R invoke(F f, va_list args)
    {
        typedef cpsUnRefConst(A0) A0V;
        typedef cpsUnRefConst(A1) A1V;
        typedef cpsUnRefConst(A2) A2V;
        typedef cpsUnRefConst(A3) A3V;
        A0V &a0 = va_arg(args, A0V);
        A1V &a1 = va_arg(args, A1V);
        A2V &a2 = va_arg(args, A2V);
        A3V &a3 = va_arg(args, A3V);
        return f(a0, a1, a2, a3);
    }
};
template<class A0, class A1, class A2, class A3>
struct cpsFB_Fn4 < void, A0, A1, A2, A3 >
{
    typedef void(*F)(A0, A1, A2, A3);
    void* invoke(F f, va_list args)
    {
        typedef cpsUnRefConst(A0) A0V;
        typedef cpsUnRefConst(A1) A1V;
        typedef cpsUnRefConst(A2) A2V;
        typedef cpsUnRefConst(A3) A3V;
        A0V &a0 = va_arg(args, A0V);
        A1V &a1 = va_arg(args, A1V);
        A2V &a2 = va_arg(args, A2V);
        A3V &a3 = va_arg(args, A3V);
        f(a0, a1, a2, a3);
        return nullptr;
    }
};

template<class R, class C, class A0, class A1, class A2, class A3>
struct cpsFB_MemFn4
{
    typedef R(C::*F)(A0, A1, A2, A3);
    R invoke(F f, C &o, va_list args)
    {
        typedef cpsUnRefConst(A0) A0V;
        typedef cpsUnRefConst(A1) A1V;
        typedef cpsUnRefConst(A2) A2V;
        typedef cpsUnRefConst(A3) A3V;
        A0V &a0 = va_arg(args, A0V);
        A1V &a1 = va_arg(args, A1V);
        A2V &a2 = va_arg(args, A2V);
        A3V &a3 = va_arg(args, A3V);
        return (o.*f)(a0, a1, a2, a3);
    }
};
template<class C, class A0, class A1, class A2, class A3>
struct cpsFB_MemFn4 < void, C, A0, A1, A2, A3 >
{
    typedef void (C::*F)(A0, A1, A2, A3);
    void* invoke(F f, C &o, va_list args)
    {
        typedef cpsUnRefConst(A0) A0V;
        typedef cpsUnRefConst(A1) A1V;
        typedef cpsUnRefConst(A2) A2V;
        typedef cpsUnRefConst(A3) A3V;
        A0V &a0 = va_arg(args, A0V);
        A1V &a1 = va_arg(args, A1V);
        A2V &a2 = va_arg(args, A2V);
        A3V &a3 = va_arg(args, A3V);
        (o.*f)(a0, a1, a2, a3);
        return nullptr;
    }
};

template<class R, class C, class A0, class A1, class A2, class A3>
struct cpsFB_ConstMemFn4
{
    typedef R(C::*F)(A0, A1, A2, A3) const;
    R invoke(F f, const C &o, va_list args)
    {
        typedef cpsUnRefConst(A0) A0V;
        typedef cpsUnRefConst(A1) A1V;
        typedef cpsUnRefConst(A2) A2V;
        typedef cpsUnRefConst(A3) A3V;
        A0V &a0 = va_arg(args, A0V);
        A1V &a1 = va_arg(args, A1V);
        A2V &a2 = va_arg(args, A2V);
        A3V &a3 = va_arg(args, A3V);
        return (o.*f)(a0, a1, a2, a3);
    }
};
template<class C, class A0, class A1, class A2, class A3>
struct cpsFB_ConstMemFn4 < void, C, A0, A1, A2, A3 >
{
    typedef void (C::*F)(A0, A1, A2, A3) const;
    void* invoke(F f, const C &o, va_list args)
    {
        typedef cpsUnRefConst(A0) A0V;
        typedef cpsUnRefConst(A1) A1V;
        typedef cpsUnRefConst(A2) A2V;
        typedef cpsUnRefConst(A3) A3V;
        A0V &a0 = va_arg(args, A0V);
        A1V &a1 = va_arg(args, A1V);
        A2V &a2 = va_arg(args, A2V);
        A3V &a3 = va_arg(args, A3V);
        (o.*f)(a0, a1, a2, a3);
        return nullptr;
    }
};



template<class T> struct cpsReturnType { typedef cpsUnRefConst(T) type; };
template<> struct cpsReturnType<void> { typedef void* type; };


template<class R, class C>
inline typename cpsReturnType<R>::type cpsCSCall(R(*f)(), C *o, va_list args)
{
    return cpsFB_Fn0<R>().invoke(f, args);
}
template<class R, class C>
inline typename cpsReturnType<R>::type cpsCSCall(R(C::*f)(), C *o, va_list args)
{
    return cpsFB_MemFn0<R, C>().invoke(f, *o, args);
}
template<class R, class C>
inline typename cpsReturnType<R>::type cpsCSCall(R(C::*f)() const, const C o, va_list args)
{
    return cpsFB_ConstMemFn0<R, C>().invoke(f, *o, args);
}


template<class R, class C, class A0>
inline typename cpsReturnType<R>::type cpsCSCall(R(*f)(A0), C *o, va_list args)
{
    return cpsFB_Fn1<R, A0>().invoke(f, args);
}
template<class R, class C, class A0>
inline typename cpsReturnType<R>::type cpsCSCall(R(C::*f)(A0), C *o, va_list args)
{
    return cpsFB_MemFn1<R, C, A0>().invoke(f, *o, args);
}
template<class R, class C, class A0>
inline typename cpsReturnType<R>::type cpsCSCall(R(C::*f)(A0) const, const C *o, va_list args)
{
    return cpsFB_ConstMemFn1<R, C, A0>().invoke(f, *o, args);
}


template<class R, class C, class A0, class A1>
inline typename cpsReturnType<R>::type cpsCSCall(R(*f)(A0, A1), C *o, va_list args)
{
    return cpsFB_Fn2<R, A0, A1>().invoke(f, args);
}
template<class R, class C, class A0, class A1>
inline typename cpsReturnType<R>::type cpsCSCall(R(C::*f)(A0, A1), C *o, va_list args)
{
    return cpsFB_MemFn2<R, C, A0, A1>().invoke(f, *o, args);
}
template<class R, class C, class A0, class A1>
inline typename cpsReturnType<R>::type cpsCSCall(R(C::*f)(A0, A1) const, const C *o, va_list args)
{
    return cpsFB_ConstMemFn2<R, C, A0, A1>().invoke(f, *o, args);
}


template<class R, class C, class A0, class A1, class A2>
inline typename cpsReturnType<R>::type cpsCSCall(R(*f)(A0, A1, A2), C *o, va_list args)
{
    return cpsFB_Fn3<R, A0, A1, A2>().invoke(f, args);
}
template<class R, class C, class A0, class A1, class A2>
inline typename cpsReturnType<R>::type cpsCSCall(R(C::*f)(A0, A1, A2), C *o, va_list args)
{
    return cpsFB_MemFn3<R, C, A0, A1, A2>().invoke(f, *o, args);
}
template<class R, class C, class A0, class A1, class A2>
inline typename cpsReturnType<R>::type cpsCSCall(R(C::*f)(A0, A1, A2) const, const C *o, va_list args)
{
    return cpsFB_ConstMemFn3<R, C, A0, A1, A2>().invoke(f, *o, args);
}


template<class R, class C, class A0, class A1, class A2, class A3>
inline typename cpsReturnType<R>::type cpsCSCall(R(*f)(A0, A1, A2, A3), C *o, va_list args)
{
    return cpsFB_Fn4<R, A0, A1, A2, A3>().invoke(f, args);
}
template<class R, class C, class A0, class A1, class A2, class A3>
inline typename cpsReturnType<R>::type cpsCSCall(R(C::*f)(A0, A1, A2, A3), C *o, va_list args)
{
    return cpsFB_MemFn4<R, C, A0, A1, A2, A3>().invoke(f, *o, args);
}
template<class R, class C, class A0, class A1, class A2, class A3>
inline typename cpsReturnType<R>::type cpsCSCall(R(C::*f)(A0, A1, A2, A3) const, const C *o, va_list args)
{
    return cpsFB_ConstMemFn4<R, C, A0, A1, A2, A3>().invoke(f, *o, args);
}



#pragma endregion


cpsAPI void cpsAddMethod(const char *name, void *addr);
struct cpsAddMethodHelper { cpsAddMethodHelper(const char *name, void *addr) { cpsAddMethod(name, addr); } };


template<class T>
inline cpsField cpsGetCppThisField(cpsObject o)
{
    static cpsCachedField s_field;
    if (!s_field) {
        s_field = o.getClass().findField("this_cpp");
    }
    return s_field;
}
template<class T>
inline T* cpsGetCppThis(cpsObject o)
{
    T *ret = nullptr;
    cpsGetCppThisField<T>(o).getValue<T*>(o, ret);
    return ret;
}
template<class T>
inline void cpsSetCppThis(cpsObject o)
{
    cpsGetCppThisField<T>(o).setValue<T*>(o, new T(o));
}
template<class T>
inline void cpsDeleteCppThis(cpsObject o)
{
    delete cpsGetCppThis<T>(o);
    cpsGetCppThisField<T>(o).setValue<T*>(o, nullptr);
}
template<class T>
inline void cpsSetCppThisSingleton(cpsObject o)
{
    cpsGetCppThisField<T>(o).setValue<T*>(o, T::getInstance());
}



template<class T>
inline T* cpsGetFieldValuePtr(cpsObject parent, const char *field_name)
{
    int offset = parent.getClass().findField(field_name).getOffset();
    return (T*)((size_t&)parent + offset);
}

template<class T>
inline T* cpsGetFieldValuePtr(cpsObject parent, cpsField field)
{
    int offset = field.getOffset();
    return (T*)((size_t&)parent + offset);
}




#if defined(_WIN32) && !defined(cpsWithoutDbgHelp)

#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
cpsAPI DWORD cpsSEHHandler(EXCEPTION_POINTERS *ep);
#define cpsGuard(...)     __try { __VA_ARGS__ } __except( cpsSEHHandler(GetExceptionInformation()) ) {  }

#else 

#define cpsGuard(...)     { __VA_ARGS__ }

#endif // 


#define cpsS2(...) #__VA_ARGS__
#define cpsS(...) cpsS2(__VA_ARGS__)
#define cpsP(...) __VA_ARGS__

#define cpsExportClass()\
    cpsExport void cpsP(cpsCurrentClass)##_ctor(MonoObject *o)\
    {\
        typedef cpsP(cpsCurrentClass) this_t;\
        cpsGuard(\
            cpsSetCppThis<this_t>(o); \
        )\
    }\
    cpsExport void cpsP(cpsCurrentClass)##_dtor(MonoObject *o)\
    {\
        typedef cpsP(cpsCurrentClass) this_t;\
        cpsGuard(\
            delete cpsGetCppThis<this_t>(o);\
        )\
    }\
    cpsAddMethodHelper cpsP(cpsCurrentClass)##_ctor_(cpsS(cpsCurrentClass) "::ctor", &cpsP(cpsCurrentClass)##_ctor);\
    cpsAddMethodHelper cpsP(cpsCurrentClass)##_dtor_(cpsS(cpsCurrentClass) "::dtor", &cpsP(cpsCurrentClass)##_dtor);

#define cpsExportSingletonClass()\
    cpsExport void cpsP(cpsCurrentClass)##_ctor(MonoObject *o)\
    {\
        typedef cpsP(cpsCurrentClass) this_t;\
        cpsGuard(\
            cpsSetCppThisSingleton<this_t>(o); \
        )\
    }\
    cpsExport void cpsP(cpsCurrentClass)##_dtor(MonoObject *o)\
    {\
    }\
    cpsAddMethodHelper cpsP(cpsCurrentClass)##_ctor_(cpsS(cpsCurrentClass) "::ctor", &cpsP(cpsCurrentClass)##_ctor);\
    cpsAddMethodHelper cpsP(cpsCurrentClass)##_dtor_(cpsS(cpsCurrentClass) "::dtor", &cpsP(cpsCurrentClass)##_dtor);


#define cpsExportMethod(MethodName)\
    cpsExport auto cpsP(cpsCurrentClass)##_##MethodName(MonoObject *o, ...) -> decltype(cpsCSCall(&cpsP(cpsCurrentClass)::##MethodName, (cpsP(cpsCurrentClass)*)nullptr, nullptr))\
    {\
        typedef cpsP(cpsCurrentClass) this_t;\
        typedef decltype(cpsCSCall(&this_t::##MethodName, (this_t*)nullptr, nullptr)) ret_t;\
        ret_t ret = ret_t();\
        va_list args;\
        va_start(args, o);\
        cpsGuard(\
            this_t *this_cpp = cpsGetCppThis<this_t>(o);\
            if(this_cpp) {\
                ret = cpsCSCall(&this_t::##MethodName, this_cpp, args);\
            }\
            else{\
                cpsDebugPrint("%p " cpsS(cpsCurrentClass) "::" #MethodName "(): this_cpp is null\n", o);\
            }\
        )\
        va_end(args);\
        return ret;\
    }\
    cpsAddMethodHelper cpsP(cpsCurrentClass)##_##MethodName##_(cpsS(cpsCurrentClass) "::" #MethodName, &cpsP(cpsCurrentClass)##_##MethodName);


#define cpsDefineEntryPoint()\
    cpsCLinkage cpsExport void cpsInitialize() {}

#endif // cpsBinder_h
