#ifndef cpsUtils_h
#define cpsUtils_h

#include "cpsFoundation.h"

#define cpsMaxSymName 2500

cpsAPI void cpsDumpClassStructure(cpsClass cpsc);
cpsAPI void cpsAddressToSymbolName(void *addr, char *out_name, size_t out_len);
cpsAPI void cpsDebugPrint(const char *format, ...);


class cpsAPI cpsCachedImage : public cpsImage
{
public:
    cpsCachedImage();
    ~cpsCachedImage();
    void operator=(const cpsImage &v) { mimage = v.mimage; }
};

class cpsAPI cpsCachedClass : public cpsClass
{
public:
    cpsCachedClass();
    ~cpsCachedClass();
    void operator=(const cpsClass &v) { mclass = v.mclass; }
};

class cpsAPI cpsCachedField : public cpsField
{
public:
    cpsCachedField();
    ~cpsCachedField();
    void operator=(const cpsField &v) { mfield = v.mfield; }
};

class cpsAPI cpsCachedMethod : public cpsMethod
{
public:
    cpsCachedMethod();
    ~cpsCachedMethod();
    void operator=(const cpsMethod &v) { mmethod = v.mmethod; }
};

class cpsAPI cpsCachedProperty : public cpsProperty
{
public:
    cpsCachedProperty();
    ~cpsCachedProperty();
    void operator=(const cpsProperty &v) { mproperty = v.mproperty; }
};

#endif // cpsUtils_h
