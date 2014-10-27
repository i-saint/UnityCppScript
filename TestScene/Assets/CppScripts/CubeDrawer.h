#ifndef CubeDrawer_h
#define CubeDrawer_h
#include "CppBehaviour.h"
#include "AsyncBehaviour.h"

struct CubeInstanceData
{
    Vector3 position;
    float scale;
    Vector4 diffuse;
    Vector4 emission;
};
typedef std::vector<CubeInstanceData> CubeCont;


class CubeDrawer : public CppBehaviour
{
typedef CppBehaviour super;
public:
    static CubeDrawer* getInstance();

    CubeDrawer(cpsObject o);
    ~CubeDrawer();
    void OnPreRender();
    void OnPostRender();

    CubeCont& getInstanceBuffer();

private:
    static CubeDrawer *s_inst;
    ComputeBuffer m_buffer;
    std::vector<CubeInstanceData> m_data;
};

#endif // CubeDrawer_h
