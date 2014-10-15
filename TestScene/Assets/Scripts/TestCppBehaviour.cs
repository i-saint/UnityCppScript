using UnityEngine;
using System;
using System.Collections;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;


public class CppBehaviour : MonoBehaviour
{
    [DllImport("CppScriptCore")]
    public static extern void cpsCoreInitialize();

    [DllImport("CppScript")]
    public static extern void cpsInitialize();

    internal IntPtr this_cpp;

    public CppBehaviour()
    {
        cpsCoreInitialize();
        cpsInitialize();
    }

    ~CppBehaviour()
    {}
}


public class TestCppBehaviour : CppBehaviour
{
    [MethodImplAttribute(MethodImplOptions.InternalCall)]
    public extern void ctor();

    [MethodImplAttribute(MethodImplOptions.InternalCall)]
    public extern void dtor();




    Vector3 v3value;

    TestCppBehaviour()
    {

    }

    ~TestCppBehaviour()
    { }

    void Awake()
    {
        ctor();
        v3value = new Vector3(1.0f, 2.0f, 3.0f);
    }

    void OnDestroy()
    {
        dtor();
    }


    [MethodImplAttribute(MethodImplOptions.InternalCall)]
    public extern void Start();

    [MethodImplAttribute(MethodImplOptions.InternalCall)]
    public extern void Update();




    [MethodImplAttribute(MethodImplOptions.InternalCall)]
    public extern int memfn1(int a1);

    [MethodImplAttribute(MethodImplOptions.InternalCall)]
    public extern int memfn2(int a1, int a2);

    [MethodImplAttribute(MethodImplOptions.InternalCall)]
    public extern int memfn3(int a1, int a2, int a3);

    [MethodImplAttribute(MethodImplOptions.InternalCall)]
    public extern int memfn4(int a1, int a2, int a3, int a4);


    [MethodImplAttribute(MethodImplOptions.InternalCall)]
    public extern int cmemfn1(int a1);

    [MethodImplAttribute(MethodImplOptions.InternalCall)]
    public extern int cmemfn2(int a1, int a2);

    [MethodImplAttribute(MethodImplOptions.InternalCall)]
    public extern int cmemfn3(int a1, int a2, int a3);

    [MethodImplAttribute(MethodImplOptions.InternalCall)]
    public extern int cmemfn4(int a1, int a2, int a3, int a4);


    [MethodImplAttribute(MethodImplOptions.InternalCall)]
    public extern int smemfn1(int a1);

    [MethodImplAttribute(MethodImplOptions.InternalCall)]
    public extern int smemfn2(int a1, int a2);

    [MethodImplAttribute(MethodImplOptions.InternalCall)]
    public extern int smemfn3(int a1, int a2, int a3);

    [MethodImplAttribute(MethodImplOptions.InternalCall)]
    public extern int smemfn4(int a1, int a2, int a3, int a4);


    void ThisFunctionWillBeCalledFromCpp()
    {
        Debug.Log("ThisFunctionWillBeCalledFromCpp()");
        memfn1(1);
        memfn2(1, 2);
        memfn3(1, 2, 3);
        memfn4(1, 2, 3, 4);
        cmemfn1(1);
        cmemfn2(1, 2);
        cmemfn3(1, 2, 3);
        cmemfn4(1, 2, 3, 4);
        smemfn1(1);
        smemfn2(1, 2);
        smemfn3(1, 2, 3);
        smemfn4(1, 2, 3, 4);
   }
}
