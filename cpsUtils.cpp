#include "cpsInternal.h"
#include "cpsUtils.h"
#include "cpsUnityEngine.h"
#include <vector>
#include <algorithm>

#if defined(_WIN32) && !defined(cpsWithoutDbgHelp)


std::string cpsExceptionToSymbolNames(EXCEPTION_POINTERS *ep)
{
    EXCEPTION_RECORD &er = *ep->ExceptionRecord;
    CONTEXT &context = *ep->ContextRecord;
    HANDLE hProcess = GetCurrentProcess();
    HANDLE hThread = GetCurrentThread();

    STACKFRAME64 stackFrame;
    memset(&stackFrame, 0, sizeof(stackFrame));

#if defined(_M_IX86)
    DWORD machineType = IMAGE_FILE_MACHINE_I386;
    stackFrame.AddrPC.Offset = context.Eip;
    stackFrame.AddrPC.Mode = AddrModeFlat;
    stackFrame.AddrFrame.Offset = context.Ebp;
    stackFrame.AddrFrame.Mode = AddrModeFlat;
    stackFrame.AddrStack.Offset = context.Esp;
    stackFrame.AddrStack.Mode = AddrModeFlat;
#elif defined(_M_X64)
    DWORD machineType = IMAGE_FILE_MACHINE_AMD64;
    stackFrame.AddrPC.Offset = context.Rip;
    stackFrame.AddrPC.Mode = AddrModeFlat;
    stackFrame.AddrFrame.Offset = context.Rbp;
    stackFrame.AddrFrame.Mode = AddrModeFlat;
    stackFrame.AddrStack.Offset = context.Rsp;
    stackFrame.AddrStack.Mode = AddrModeFlat;
#endif

    std::string ret;
    char buf[cpsMaxSymName];
    {
        cpsAddressToSymbolName(er.ExceptionAddress, buf, sizeof(buf));
        ret += buf;
    }
    for (;;)
    {
        if (StackWalk64(machineType, hProcess, hThread, &stackFrame, &context, NULL, NULL, NULL, NULL) == FALSE ||
            stackFrame.AddrPC.Offset == stackFrame.AddrReturn.Offset ||
            stackFrame.AddrPC.Offset == 0 ||
            stackFrame.AddrReturn.Offset == 0)
        {
            break;
        }
        cpsAddressToSymbolName((void*)stackFrame.AddrReturn.Offset, buf, sizeof(buf));
        ret += buf;
    }

    return ret;
}

cpsAPI DWORD cpsSEHHandler(EXCEPTION_POINTERS *ep)
{
    std::string message;
    message += "CppScript: crash!!!\n";
    message += cpsExceptionToSymbolNames(ep);
    cpsDebugPrint(message.c_str());
    return EXCEPTION_EXECUTE_HANDLER;
}
#endif

cpsAPI void cpsAddressToSymbolName(void *addr, char *out_name, size_t out_len)
{
    // currently windows only
#ifdef _WIN32

#if defined(_M_IX86)
    typedef DWORD DWORDX;
    typedef PDWORD PDWORDX;
#elif defined(_M_X64)
    typedef DWORD64 DWORDX;
    typedef PDWORD64 PDWORDX;
#endif

    HANDLE process = ::GetCurrentProcess();
    IMAGEHLP_MODULE imageModule = { sizeof(IMAGEHLP_MODULE) };
    IMAGEHLP_LINE line = { sizeof(IMAGEHLP_LINE) };
    DWORDX dispSym = 0;
    DWORD dispLine = 0;

    char symbolBuffer[sizeof(IMAGEHLP_SYMBOL) + cpsMaxSymName] = { 0 };
    IMAGEHLP_SYMBOL * imageSymbol = (IMAGEHLP_SYMBOL*)symbolBuffer;
    imageSymbol->SizeOfStruct = sizeof(IMAGEHLP_SYMBOL);
    imageSymbol->MaxNameLength = MAX_PATH;

    if (!::SymGetModuleInfo(process, (DWORDX)addr, &imageModule)) {
        _snprintf(out_name, out_len, "[0x%p]\n", addr);
    }
    else if (!::SymGetSymFromAddr(process, (DWORDX)addr, &dispSym, imageSymbol)) {
        _snprintf(out_name, out_len, "%s + 0x%x [0x%p]\n", imageModule.ModuleName, ((size_t)addr - (size_t)imageModule.BaseOfImage), addr);
    }
    else if (!::SymGetLineFromAddr(process, (DWORDX)addr, &dispLine, &line)) {
        _snprintf(out_name, out_len, "%s!%s + 0x%x [0x%p]\n", imageModule.ModuleName, imageSymbol->Name, ((size_t)addr - (size_t)imageSymbol->Address), addr);
    }
    else {
        _snprintf(out_name, out_len, "%s(%d): %s!%s + 0x%x [0x%p]\n", line.FileName, line.LineNumber,
            imageModule.ModuleName, imageSymbol->Name, ((size_t)addr - (size_t)imageSymbol->Address), addr);
    }

#else

    snprintf(out_name, out_len, "[0x%p]\n", addr);

#endif
}



static inline std::string cpsStringizeArgTypes(cpsMethod mt)
{
    std::string ret;
    bool first = true;
    mt.eachArgTypes([&](cpsType &t){
        if (!first) { ret += ", "; }
        first = false;
        ret += t.getName();
    });
    return ret;
}

static inline std::string cpsStringizeMethodAttributes(cpsMethod mt)
{
    std::string ret;
    if (mt.isVirtual()) { ret += "virtual "; }
    if (mt.isStatic()) { ret += "static "; }
    return ret;
}


cpsAPI void cpsDumpClassStructure(cpsClass cpsc)
{
    cpsDebugPrint("class %s\n", cpsc.getName());

    cpsDebugPrint("methods:\n");
    cpsc.eachMethodsUpwards([&](cpsMethod &m, cpsClass &c){
        cpsDebugPrint("    %s%s::%s(%s) : %s\n", cpsStringizeMethodAttributes(m).c_str(), c.getName(), m.getName(), cpsStringizeArgTypes(m).c_str(), m.getReturnType().getName());
    });

    cpsDebugPrint("properties:\n");
    cpsc.eachPropertiesUpwards([&](cpsProperty &m, cpsClass &c){
        cpsDebugPrint("    %s::%s\n", c.getName(), m.getName());
        if (cpsMethod getter = m.getGetter()) {
            cpsDebugPrint("        getter(%s) : %s\n", cpsStringizeArgTypes(getter).c_str(), getter.getReturnType().getName());
        }
        if (cpsMethod setter = m.getSetter()) {
            cpsDebugPrint("        setter(%s) : %s\n", cpsStringizeArgTypes(setter).c_str(), setter.getReturnType().getName());
        }
    });

    cpsDebugPrint("fields:\n");
    cpsc.eachFieldsUpwards([&](cpsField &m, cpsClass &c){
        cpsDebugPrint("    %s::%s : %s\n", c.getName(), m.getName(), m.getType().getName());
    });
}

cpsAPI void cpsDebugPrint(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    char buf[1024 * 8];
    vsprintf(buf, format, args);

    cpsUnityEngine::Debug::Log(buf);

#ifdef WIN32
    ::OutputDebugStringA(buf);
#else  // WIN32
    puts(buf);
#endif // WIN32

    va_end(args);
}


struct cpsCaches
{
    std::vector<cpsCachedImage*>    images;
    std::vector<cpsCachedClass*>    classes;
    std::vector<cpsCachedField*>    fields;
    std::vector<cpsCachedMethod*>   methods;
    std::vector<cpsCachedProperty*> properties;
} g_cpsCaches;

void cpsClearCache()
{
    for (auto o : g_cpsCaches.images)      { o->mimage = nullptr; }
    for (auto o : g_cpsCaches.classes)     { o->mclass = nullptr; }
    for (auto o : g_cpsCaches.fields)      { o->mfield = nullptr; }
    for (auto o : g_cpsCaches.methods)     { o->mmethod = nullptr; }
    for (auto o : g_cpsCaches.properties)  { o->mproperty = nullptr; }
}

cpsAPI void cpsGetArraySizeAndData(void *cs_array, size_t &size, void *& data)
{
    if (cs_array == nullptr) { return; }
    MonoArray *ma = (MonoArray*)cs_array;
    size = ma->max_length;
    data = ma->vector;
}

cpsAPI void* cpsNewString(const cps_char8 *str, int len)
{
    return mono_string_new_len(mono_domain_get(), str, len==-1 ? (int)strlen(str) : len);
}

cpsAPI void* cpsNewString(const cps_char16 *str, int len)
{
    if (len == -1) {
        for (len = 0;; ++len) {
            if (str[len] == 0) { break; }
        }
    }
    return mono_string_new_utf16(mono_domain_get(), str, len);
}

cpsAPI const cps_char8*  cpsToUTF8(void *cs_string)
{
    return mono_string_to_utf8((MonoString*)cs_string);
}

cpsAPI const cps_char16* cpsToUTF16(void *cs_string)
{
    return mono_string_to_utf16((MonoString*)cs_string);
}

cpsCachedImage::cpsCachedImage() : cpsImage(nullptr)
{
    g_cpsCaches.images.push_back(this);
}

cpsCachedClass::cpsCachedClass() : cpsClass(nullptr)
{
    g_cpsCaches.classes.push_back(this);
}

cpsCachedField::cpsCachedField() : cpsField(nullptr)
{
    g_cpsCaches.fields.push_back(this);
}

cpsCachedMethod::cpsCachedMethod() : cpsMethod(nullptr)
{
    g_cpsCaches.methods.push_back(this);
}

cpsCachedProperty::cpsCachedProperty() : cpsProperty(nullptr)
{
    g_cpsCaches.properties.push_back(this);
}
