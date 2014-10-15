#include "CppBehaviour.h"
#include <string>
#include <vector>

struct Vector3
{
    union {
        struct { float x, y, z; };
        float v[3];
    };
};



class TestCppBehaviour : public CppBehaviour
{
typedef CppBehaviour super;
public:
    TestCppBehaviour(void *o);
    virtual ~TestCppBehaviour();
    void Start();
    void Update();

    int memfn1(int a1);
    int memfn2(int a1, int a2);
    int memfn3(int a1, int a2, int a3);
    int memfn4(int a1, int a2, int a3, int a4);
    int cmemfn1(int a1) const;
    int cmemfn2(int a1, int a2) const;
    int cmemfn3(int a1, int a2, int a3) const;
    int cmemfn4(int a1, int a2, int a3, int a4) const;
    static int smemfn1(int a1);
    static int smemfn2(int a1, int a2);
    static int smemfn3(int a1, int a2, int a3);
    static int smemfn4(int a1, int a2, int a3, int a4);

private:
    int m_frame;
    Vector3 *m_v3v;
};



cpsDefineEntryPoint()

#define cpsCurrentClass TestCppBehaviour
cpsExportClass()
cpsExportMethod(Start)
cpsExportMethod(Update)
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


TestCppBehaviour::TestCppBehaviour(void *o)
: super(o)
, m_frame(0)
, m_v3v(cpsGetFieldValuePtr<Vector3>(o, "v3value"))
{
    cpsDebugPrint("TestCppBehaviour::TestCppBehaviour()\n");

    cpsDebugPrint("methods:\n");
    this_cs.getClass().eachMethodsUpwards([&](cpsMethod &m, cpsClass &c){
        cpsDebugPrint("    %s::%s(%s) : %s\n", c.getName(), m.getName(), StringizeArgTypes(m).c_str(), m.getReturnType().getName());
    });

    cpsDebugPrint("properties:\n");
    this_cs.getClass().eachPropertiesUpwards([&](cpsProperty &m, cpsClass &c){
        cpsDebugPrint("    %s::%s\n", c.getName(), m.getName());
        if (cpsMethod getter = m.getGetter()) {
            cpsDebugPrint("        getter(%s) : %s\n", StringizeArgTypes(getter).c_str(), getter.getReturnType().getName());
        }
        if (cpsMethod setter = m.getSetter()) {
            cpsDebugPrint("        setter(%s) : %s\n", StringizeArgTypes(setter).c_str(), setter.getReturnType().getName());
        }
    });

    cpsDebugPrint("fields:\n");
    this_cs.getClass().eachFieldsUpwards([&](cpsField &m, cpsClass &c){
        cpsDebugPrint("    %s::%s : %s\n", c.getName(), m.getName(), m.getType().getName());
    });
}

TestCppBehaviour::~TestCppBehaviour()
{
    cpsDebugPrint("TestCppBehaviour:~TestCppBehaviour()\n");
}

void TestCppBehaviour::Start()
{
    cpsDebugPrint("TestCppBehaviour::Start()\n");
}

void TestCppBehaviour::Update()
{
    if (++m_frame % 60 == 0) {
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


int TestCppBehaviour::memfn1(int a1)
{
    cpsDebugPrint("TestCppBehaviour::memfn1(%d) : %d\n", a1, m_frame);
    return m_frame;
}

int TestCppBehaviour::memfn2(int a1, int a2)
{
    cpsDebugPrint("TestCppBehaviour::memfn2(%d, %d) : %d\n", a1, a2, m_frame);
    return m_frame;
}

int TestCppBehaviour::memfn3(int a1, int a2, int a3)
{
    cpsDebugPrint("TestCppBehaviour::memfn3(%d, %d, %d) : %d\n", a1, a2, a3, m_frame);
    return m_frame;
}

int TestCppBehaviour::memfn4(int a1, int a2, int a3, int a4)
{
    cpsDebugPrint("TestCppBehaviour::memfn4(%d, %d, %d, %d) : %d\n", a1, a2, a3, a4, m_frame);
    return m_frame;
}


int TestCppBehaviour::cmemfn1(int a1) const
{
    cpsDebugPrint("TestCppBehaviour::cmemfn1(%d) : %d\n", a1, m_frame);
    return m_frame;
}

int TestCppBehaviour::cmemfn2(int a1, int a2) const
{
    cpsDebugPrint("TestCppBehaviour::cmemfn2(%d, %d) : %d\n", a1, a2, m_frame);
    return m_frame;
}

int TestCppBehaviour::cmemfn3(int a1, int a2, int a3) const
{
    cpsDebugPrint("TestCppBehaviour::cmemfn3(%d, %d, %d) : %d\n", a1, a2, a3, m_frame);
    return m_frame;
}

int TestCppBehaviour::cmemfn4(int a1, int a2, int a3, int a4) const
{
    cpsDebugPrint("TestCppBehaviour::cmemfn4(%d, %d, %d, %d) : %d\n", a1, a2, a3, a4, m_frame);
    return m_frame;
}


int TestCppBehaviour::smemfn1(int a1)
{
    cpsDebugPrint("TestCppBehaviour::smemfn1(%d) : %d\n", a1, 1);
    return 1;
}

int TestCppBehaviour::smemfn2(int a1, int a2)
{
    cpsDebugPrint("TestCppBehaviour::smemfn2(%d, %d) : %d\n", a1, a2, 2);
    return 2;
}

int TestCppBehaviour::smemfn3(int a1, int a2, int a3)
{
    cpsDebugPrint("TestCppBehaviour::smemfn3(%d, %d, %d) : %d\n", a1, a2, a3, 3);
    return 3;
}

int TestCppBehaviour::smemfn4(int a1, int a2, int a3, int a4)
{
    cpsDebugPrint("TestCppBehaviour::smemfn4(%d, %d, %d, %d) : %d\n", a1, a2, a3, a4, 4);
    return 4;
}
