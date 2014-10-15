#include "cpsInternal.h"
#include "cpsUtils.h"
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

cpsAPI void cpsDebugPrint(const char *format, ...)
{
    va_list args;
    va_start(args, format);
#ifdef WIN32
    char buf[1024 * 2];
    vsprintf(buf, format, args);
    ::OutputDebugStringA(buf);
#else  // WIN32
    vprintf(format, args);
#endif // WIN32
    va_end(args);
}

