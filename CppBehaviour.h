#ifndef CppBehaviour_h
#define CppBehaviour_h

#include "cpsBinder.h"
#include "cpsUtils.h"

class CppBehaviour
{
public:
    CppBehaviour(void *o) : this_cs(o) {}
    virtual ~CppBehaviour() {}

    cpsField    findField(const char *name) const       { return this_cs.findField(name); }
    cpsProperty findProperty(const char *name) const    { return this_cs.findProperty(name); }
    cpsMethod   findMethod(const char *name) const      { return this_cs.findMethod(name); }

protected:
    cpsObject this_cs;
};

#endif // CppBehaviour_h