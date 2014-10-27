#ifndef CubeDrawer_h
#define CubeDrawer_h
#include "CppBehaviour.h"

struct CubeInstanceData
{
    Vector3 position;
    float scale;
    Vector4 diffuse;
    Vector4 emission;
};

class CubeDrawerManager : public CppBehaviour
{
typedef CppBehaviour super;
public:
    CubeDrawerManager(cpsObject o) : super(o) {}
    void Awake();
    void OnDestroy();
    void OnPreRender();
    void OnPostRender();
};


class CubeDrawer : public CppBehaviour
{
typedef CppBehaviour super;
public:
    CubeDrawer(cpsObject o) : super(o) {}
    void Awake();
    void OnDestroy();
    void OnPreRender();
    void OnPostRender();
};

#endif // CubeDrawer_h
