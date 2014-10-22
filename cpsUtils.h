#ifndef cpsUtils_h
#define cpsUtils_h

#include "cpsTypes.h"

#define cpsMaxSymName 2500

cpsAPI void cpsDumpClassStructure(cpsClass cpsc);
cpsAPI void cpsAddressToSymbolName(void *addr, char *out_name, size_t out_len);
cpsAPI void cpsDebugPrint(const char *format, ...);
cpsAPI void cpsGetArraySizeAndData(void *cs_array, size_t &size, void *& data);

cpsAPI void* cpsNewString(const cps_char8 *str, int len = -1); // len=-1: strlen(str) 
cpsAPI void* cpsNewString(const cps_char16 *str, int len = -1); // len=-1: strlen(str) 
cpsAPI const cps_char8*  cpsToUTF8(void *cs_string);
cpsAPI const cps_char16* cpsToUTF16(void *cs_string);

template<class T>
class cpsArray
{
public:
    typedef T*          iterator;
    typedef const T*    const_iterator;

    cpsArray(void *cs_array) : m_size(0), m_data(nullptr) { cpsGetArraySizeAndData(cs_array, m_size, (void*&)m_data); }
    size_t          size() const                { return m_size;  }
    T&              operator[](size_t i)        { return m_data[i]; }
    const T&        operator[](size_t i) const  { return m_data[i]; }
    iterator        begin()                     { return m_data; }
    iterator        end()                       { return m_data + m_size; }
    const_iterator  begin() const               { return m_data; }
    const_iterator  end() const                 { return m_data + m_size; }

private:
    size_t m_size;
    T *m_data;
};

class cpsAPI cpsCachedImage : public cpsImage
{
public:
    cpsCachedImage();
    void operator=(const cpsImage &v) { mimage = v.mimage; }
};

class cpsAPI cpsCachedClass : public cpsClass
{
public:
    cpsCachedClass();
    void operator=(const cpsClass &v) { mclass = v.mclass; }
};

class cpsAPI cpsCachedField : public cpsField
{
public:
    cpsCachedField();
    void operator=(const cpsField &v) { mfield = v.mfield; }
};

class cpsAPI cpsCachedMethod : public cpsMethod
{
public:
    cpsCachedMethod();
    void operator=(const cpsMethod &v) { mmethod = v.mmethod; }
};

class cpsAPI cpsCachedProperty : public cpsProperty
{
public:
    cpsCachedProperty();
    void operator=(const cpsProperty &v) { mproperty = v.mproperty; }
};

#endif // cpsUtils_h
