#include "CubeDrawer.h"

#define cpsCurrentClass CubeDrawer
cpsExportClass()
cpsExportMethod(OnPreRender)
cpsExportMethod(OnPostRender)
#undef cpsCurrentClass


CubeDrawer* CubeDrawer::s_inst;


CubeDrawer* CubeDrawer::getInstance()
{
    return s_inst;
}

CubeDrawer::CubeDrawer(cpsObject o)
    : super(o)
{
    if (s_inst != nullptr) {
        cpsDebugPrint("CubeDrawer::s_inst is not null!\n");
    }
    s_inst = this;

    m_data.reserve(1024 * 16);
    findField("instance_buffer").getValue(*this, m_buffer);
}

CubeDrawer::~CubeDrawer()
{
    if (s_inst != this) {
        cpsDebugPrint("CubeDrawer::s_inst is not this!\n");
    }
    s_inst = nullptr;
}

void CubeDrawer::OnPreRender()
{
    // todo
    //m_buffer.SetData(m_data);
    m_data.clear();

}

void CubeDrawer::OnPostRender()
{
}

CubeCont& CubeDrawer::getInstanceBuffer()
{
    return m_data;
}
