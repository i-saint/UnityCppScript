#include "AsyncBehaviour.h"
#include "CubeDrawer.h"


class TestAsyncBehaviour : public AsyncBehaviour
{
typedef AsyncBehaviour super;
public:
    TestAsyncBehaviour(cpsObject o);
    virtual ~TestAsyncBehaviour();

    void BeforeAsyncUpdate();
    void AsyncUpdate();
    void AfterAsyncUpdate();

private:
    Transform trans;
};

#define cpsCurrentClass TestAsyncBehaviour
cpsExportClass()
cpsExportMethod(BeforeAsyncUpdate)
cpsExportMethod(AsyncUpdate)
cpsExportMethod(AfterAsyncUpdate)
#undef cpsCurrentClass




TestAsyncBehaviour::TestAsyncBehaviour(cpsObject o)
: super(o)
{
    trans = GetComponent<Transform>();
}

TestAsyncBehaviour::~TestAsyncBehaviour()
{
}

void TestAsyncBehaviour::BeforeAsyncUpdate()
{
}

void TestAsyncBehaviour::AsyncUpdate()
{
}

void TestAsyncBehaviour::AfterAsyncUpdate()
{
}
