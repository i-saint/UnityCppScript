#ifndef cpsUtils_h
#define cpsUtils_h

#include "cpsTypes.h"

#define cpsMaxSymName 2500

cpsAPI void cpsAddressToSymbolName(void *addr, char *out_name, size_t out_len);
cpsAPI void cpsDebugPrint(const char *format, ...);

#endif // cpsUtils_h
