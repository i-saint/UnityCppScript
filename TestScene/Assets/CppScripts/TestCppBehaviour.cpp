#include "CppBehaviour.h"
#include "monoAPI.h"
#include <string>
#include <vector>


class TestCppBehaviour : public CppBehaviour
{
typedef CppBehaviour super;
public:
    TestCppBehaviour(void *o);
    virtual ~TestCppBehaviour();
    void Start();
    void Update();

    int test1(int a1, int a2, int a3, int a4);
    int test2(float a1, Vector2 a2);

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



inline std::string StringizeArgTypes(cpsMethod mt)
{
    std::string ret;
    bool first = true;
    mt.eachArgTypes([&](cpsType &t){
        if (!first) { ret += ", "; }
        first = false;
        ret += t.getName();
    });
    return ret;
}


void DumpClassStructure(cpsClass cpsc)
{
    cpsDebugPrint("class %s\n", cpsc.getName());

    cpsDebugPrint("methods:\n");
    cpsc.eachMethodsUpwards([&](cpsMethod &m, cpsClass &c){
        cpsDebugPrint("    %s::%s(%s) : %s\n", c.getName(), m.getName(), StringizeArgTypes(m).c_str(), m.getReturnType().getName());
    });

    cpsDebugPrint("properties:\n");
    cpsc.eachPropertiesUpwards([&](cpsProperty &m, cpsClass &c){
        cpsDebugPrint("    %s::%s\n", c.getName(), m.getName());
        if (cpsMethod getter = m.getGetter()) {
            cpsDebugPrint("        getter(%s) : %s\n", StringizeArgTypes(getter).c_str(), getter.getReturnType().getName());
        }
        if (cpsMethod setter = m.getSetter()) {
            cpsDebugPrint("        setter(%s) : %s\n", StringizeArgTypes(setter).c_str(), setter.getReturnType().getName());
        }
    });

    cpsDebugPrint("fields:\n");
    cpsc.eachFieldsUpwards([&](cpsField &m, cpsClass &c){
        cpsDebugPrint("    %s::%s : %s\n", c.getName(), m.getName(), m.getType().getName());
    });
}


TestCppBehaviour::TestCppBehaviour(void *o)
: super(o)
, m_frame(0)
, m_v3v(cpsGetFieldValuePtr<Vector3>(o, "v3value"))
{
    cpsDebugPrint("TestCppBehaviour::TestCppBehaviour()\n");
    DumpClassStructure(this_cs.getClass());
}

TestCppBehaviour::~TestCppBehaviour()
{
    cpsDebugPrint("TestCppBehaviour:~TestCppBehaviour()\n");
}

void TestCppBehaviour::Start()
{
    cpsDebugPrint("TestCppBehaviour::Start()\n");


    MonoDomain *domain = mono_domain_get();
    MonoAssembly *as = mono_domain_assembly_open(domain, "UnityEngine");
    MonoImage    *img = mono_assembly_get_image(as);

    cpsClass ctransform = mono_class_from_name(img, "UnityEngine", "Transform");

    cpsMethod gmethod = this_cs.getClass().findMethod("GetComponent", 0);
    cpsMethod imethod = gmethod.instantiate(&ctransform, 1);
    cpsObject obj = imethod.invoke(this_cs, nullptr);
    DumpClassStructure(obj.getClass());

    cpsMethod get_position = obj.getClass().findMethod("get_position");
    Vector3 pos = *(Vector3*)get_position.invoke(obj, nullptr).getData();
    cpsDebugPrint("%.2f, %.2f, %.2f\n", pos.x, pos.y, pos.z);
}

void TestCppBehaviour::Update()
{
    if (++m_frame % 180 == 0) {
        // crash test
        //*(int*)nullptr = 0;

        cpsDebugPrint("TestCppBehaviour::Update()\n");
        if (cpsMethod method = findMethod("ThisFunctionWillBeCalledFromCpp")) {
            method.invoke(this_cs, nullptr);
        }

        {
            cpsDebugPrint("    v3value: %.2f, %.2f, %.2f\n", m_v3v->x, m_v3v->y, m_v3v->z);
            m_v3v->x += 1.0f;
            m_v3v->y += 2.0f;
            m_v3v->z += 3.0f;
        }
    }
}


int TestCppBehaviour::test1(int a1, int a2, int a3, int a4)
{
    cpsDebugPrint("TestCppBehaviour::test1(%d, %d, %d, %d)\n", a1, a2, a3, a4);
    return 1;
}

int TestCppBehaviour::test2(float a1, Vector2 a2)
{
    cpsDebugPrint("TestCppBehaviour::test2({%f, %f})\n", a2.x, a2.y);
    return 2;
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
