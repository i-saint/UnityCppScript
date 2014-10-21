#ifndef CppBehaviour_h
#define CppBehaviour_h

#include "cpsBinder.h"
#include "cpsUtils.h"
#include "cpsUnityEngine.h"
using namespace cpsUnityEngine;


class CppBehaviour
{
public:
    CppBehaviour(void *o) : this_cs(o) {}
    virtual ~CppBehaviour() {}

    template <class T>
    T GetComponent() const
    {
        static cpsCachedMethod gmethod;
        static cpsCachedMethod imethod;
        if (!gmethod) {
            gmethod = this_cs.getClass().findMethod("GetComponent", 0);
        }
        if (!imethod) {
            cpsClass tparams[] = { T::getClass() };
            imethod = gmethod.instantiate(tparams, 1);
        }
        return T(imethod.invoke(this_cs));
    }

    cpsField    findField(const char *name) const       { return this_cs.getClass().findField(name); }
    cpsProperty findProperty(const char *name) const    { return this_cs.getClass().findProperty(name); }
    cpsMethod   findMethod(const char *name, int num_args = -1) const { return this_cs.getClass().findMethod(name, num_args); }

protected:
    cpsObject this_cs;
};

#endif // CppBehaviour_h