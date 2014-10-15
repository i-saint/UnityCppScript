#ifndef cpsObjectTranslator_h
#define cpsObjectTranslator_h
#include "cpsTypes.h"


template<class T> struct mioObjctTranslatorImpl;

template<class T> inline const T& mioToCppObject(cpsObject &o) { return mioObjctTranslatorImpl<T>().toCpp(o); }
template<class T> inline cpsObject cpsToCsObject(const T &o) { return mioObjctTranslatorImpl<T>().toCs(o); }


// pointers
template<class T> struct mioObjctTranslatorImpl < T* >
{
    T*& toCpp(cpsObject &o) { return (T*&)o; }
    cpsObject toCs(const T *&o) { return (cpsObject&)o; }
};

// int
template<> struct mioObjctTranslatorImpl <int>
{
    int& toCpp(cpsObject &o) { return (int&)o; }
    cpsObject toCs(const int &o) { return (cpsObject&)o; }
};

#endif // cpsObjectTranslator_h
