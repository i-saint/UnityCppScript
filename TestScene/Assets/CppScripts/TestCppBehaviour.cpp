#include "CppBehaviour.h"
#include "monoAPI.h"
#include <string>
#include <vector>


class TestCppBehaviour : public CppBehaviour
{
typedef CppBehaviour super;
public:
    TestCppBehaviour(cpsObject o);
    virtual ~TestCppBehaviour();

    void Start();
    void Update();

    void test1(cpsArray a);
    void test2(cpsString str);

    int memfn1(float a1);
    int memfn2(float a1, Vector2 a2);
    int memfn3(float a1, Vector2 a2, Vector3 a3);
    int memfn4(float a1, Vector2 a2, Vector3 a3, Vector4 a4);
    int cmemfn1(float a1) const;
    int cmemfn2(float a1, Vector2 a2) const;
    int cmemfn3(float a1, Vector2 a2, Vector3 a3) const;
    int cmemfn4(float a1, Vector2 a2, Vector3 a3, Vector4 a4) const;
    static int smemfn1(float a1);
    static int smemfn2(float a1, Vector2 a2);
    static int smemfn3(float a1, Vector2 a2, Vector3 a3);
    static int smemfn4(float a1, Vector2 a2, Vector3 a3, Vector4 a4);

private:
    Transform trans;
    int m_frame;
    Vector3 *m_v3v;
};



cpsDefineEntryPoint()

#define cpsCurrentClass TestCppBehaviour
cpsExportClass()
cpsExportMethod(Start)
cpsExportMethod(Update)
cpsExportMethod(test1)
cpsExportMethod(test2)
cpsExportMethod(memfn1)
cpsExportMethod(memfn2)
cpsExportMethod(memfn3)
cpsExportMethod(memfn4)
cpsExportMethod(cmemfn1)
cpsExportMethod(cmemfn2)
cpsExportMethod(cmemfn3)
cpsExportMethod(cmemfn4)
cpsExportMethod(smemfn1)
cpsExportMethod(smemfn2)
cpsExportMethod(smemfn3)
cpsExportMethod(smemfn4)
#undef cpsCurrentClass




TestCppBehaviour::TestCppBehaviour(cpsObject o)
: super(o)
, m_frame(0)
, m_v3v(cpsGetFieldValuePtr<Vector3>(o, "v3value"))
{
    cpsDebugPrint("TestCppBehaviour::TestCppBehaviour()\n");
}

TestCppBehaviour::~TestCppBehaviour()
{
    cpsDebugPrint("TestCppBehaviour:~TestCppBehaviour()\n");
}


void TestCppBehaviour::Start()
{
    cpsDebugPrint("TestCppBehaviour::Start()\n");
    trans = GetComponent<Transform>();

    cpsDumpClassStructure(cpsTypeinfo<Rigidbody2D>());
    cpsDumpClassStructure(cpsTypeinfo<Rigidbody2D>());
    cpsDumpClassStructure(cpsTypeinfo<Texture2D>());
    cpsDumpClassStructure(cpsTypeinfo<RenderTexture>());
    cpsDumpClassStructure(cpsTypeinfo<GL>());
    cpsDumpClassStructure(cpsTypeinfo<GUI>());
}

void TestCppBehaviour::Update()
{
    if (++m_frame % 120 == 0) {
        //// crash test
        //*(int*)nullptr = 0;

        cpsDebugPrint("TestCppBehaviour::Update()\n");
        cpsDebugPrint("name: %s\n", trans.get_name().toUTF8());
        if (cpsMethod method = findMethod("ThisFunctionWillBeCalledFromCpp")) {
            method.invoke(*this, nullptr);
        }

        {
            m_v3v->x += 1.0f;
            m_v3v->y += 2.0f;
            m_v3v->z += 3.0f;
        }
        {
            Vector3 pos = trans.get_position();
            pos.x += 0.1f;
            pos.y += 0.1f;
            pos.z += 0.1f;
            trans.set_position(pos);
            trans.Translate(Vector3(0.0f, 0.1f, 0.2f));
        }
    }
    {
        trans.Rotate(Vector3(0.0f, 1.0f, 0.0f), 1.0f);
    }
}


void TestCppBehaviour::test1(cpsArray a)
{
    cpsTArray<Vector3> v3a(a);
    cpsDebugPrint("TestCppBehaviour::test1()\n");
    for (auto &v : v3a) {
        cpsDebugPrint("    {%.2f, %.2f, %.2f}\n", v.x, v.y, v.z);
    }
}

void TestCppBehaviour::test2(cpsString str)
{
    cpsDebugPrint("TestCppBehaviour::test2()\n");
    cpsDebugPrint("%s\n", str.toUTF8());
}



int TestCppBehaviour::memfn1(float a1)
{
    cpsDebugPrint("TestCppBehaviour::memfn1(%f)\n", a1);
    float f = (float)m_frame;
    return 1;
}

int TestCppBehaviour::memfn2(float a1, Vector2 a2)
{
    cpsDebugPrint("TestCppBehaviour::memfn2(..., {%f, %f})\n", a2.x, a2.y);
    float f = (float)m_frame;
    return 2;
}

int TestCppBehaviour::memfn3(float a1, Vector2 a2, Vector3 a3)
{
    cpsDebugPrint("TestCppBehaviour::memfn3(..., {%f, %f, %f})\n", a3.x, a3.y, a3.z);
    float f = (float)m_frame;
    return 3;
}

int TestCppBehaviour::memfn4(float a1, Vector2 a2, Vector3 a3, Vector4 a4)
{
    cpsDebugPrint("TestCppBehaviour::memfn4((..., {%f, %f, %f, %f})\n", a4.x, a4.y, a4.z, a4.w);
    float f = (float)m_frame;
    return 4;
}


int TestCppBehaviour::cmemfn1(float a1) const
{
    cpsDebugPrint("TestCppBehaviour::cmemfn1(%f)\n", a1);
    float f = (float)m_frame;
    return 5;
}

int TestCppBehaviour::cmemfn2(float a1, Vector2 a2) const
{
    cpsDebugPrint("TestCppBehaviour::cmemfn2(..., {%f, %f})\n", a2.x, a2.y);
    float f = (float)m_frame;
    return 6;
}

int TestCppBehaviour::cmemfn3(float a1, Vector2 a2, Vector3 a3) const
{
    cpsDebugPrint("TestCppBehaviour::cmemfn3(..., {%f, %f, %f})\n", a3.x, a3.y, a3.z);
    float f = (float)m_frame;
    return 7;
}

int TestCppBehaviour::cmemfn4(float a1, Vector2 a2, Vector3 a3, Vector4 a4) const
{
    cpsDebugPrint("TestCppBehaviour::cmemfn4((..., {%f, %f, %f, %f})\n", a4.x, a4.y, a4.z, a4.w);
    float f = (float)m_frame;
    return 8;
}


int TestCppBehaviour::smemfn1(float a1)
{
    cpsDebugPrint("TestCppBehaviour::smemfn1(%f)\n", a1);
    return 9;
}

int TestCppBehaviour::smemfn2(float a1, Vector2 a2)
{
    cpsDebugPrint("TestCppBehaviour::smemfn2(..., {%f, %f})\n", a2.x, a2.y);
    return 10;
}

int TestCppBehaviour::smemfn3(float a1, Vector2 a2, Vector3 a3)
{
    cpsDebugPrint("TestCppBehaviour::smemfn3(..., {%f, %f, %f})\n", a3.x, a3.y, a3.z);
    return 11;
}

int TestCppBehaviour::smemfn4(float a1, Vector2 a2, Vector3 a3, Vector4 a4)
{
    cpsDebugPrint("TestCppBehaviour::smemfn4((..., {%f, %f, %f, %f})\n", a4.x, a4.y, a4.z, a4.w);
    return 12;
}
