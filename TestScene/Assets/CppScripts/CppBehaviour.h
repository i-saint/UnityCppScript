#ifndef CppBehaviour_h
#define CppBehaviour_h

#include "cpsBinder.h"
#include "cpsUtils.h"
#include "cpsUnityEngine.h"
using namespace cpsUnityEngine;


class CppBehaviour : public Behaviour
{
typedef Behaviour super;
public:
    CppBehaviour(cpsObject o=nullptr) : super(o) {}
    virtual ~CppBehaviour() {}
};

#endif // CppBehaviour_h
