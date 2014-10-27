using UnityEngine;
using UnityEditor;
using System;
using System.Collections;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;
using System.Diagnostics;


public class CppBehaviour : MonoBehaviour
{
    [DllImport("CppScriptCore")]
    public static extern void cpsCoreInitialize();

    internal IntPtr this_cpp;

    public CppBehaviour()
    {
        cpsCoreInitialize();
    }


#if UNITY_EDITOR
    [MenuItem ("Assets/Reload DLL")]
    static void ReloadDll()
    {
#if UNITY_EDITOR_WIN
        System.Diagnostics.Process p = new Process();
        p.StartInfo.FileName = "build.bat";
        p.Start();
#endif
    }
#endif // UNITY_EDITOR
}


public class TestCppBehaviour : CppBehaviour
{
    [MethodImplAttribute(MethodImplOptions.InternalCall)]
    public extern void ctor();

    [MethodImplAttribute(MethodImplOptions.InternalCall)]
    public extern void dtor();



    Vector3 v3value;


    void Awake()
    {
        v3value = new Vector3(1.0f, 2.0f, 3.0f);
        ctor();
    }

    void OnDestroy()
    {
        dtor();
    }


    [MethodImplAttribute(MethodImplOptions.InternalCall)]
    public extern void Start();

    [MethodImplAttribute(MethodImplOptions.InternalCall)]
    public extern void Update();


    //[MethodImplAttribute(MethodImplOptions.InternalCall)]
    //public extern void BeforeAsyncUpdate();

    //[MethodImplAttribute(MethodImplOptions.InternalCall)]
    //public extern void AsyncUpdate();

    //[MethodImplAttribute(MethodImplOptions.InternalCall)]
    //public extern void AfterAsyncUpdate();



    [MethodImplAttribute(MethodImplOptions.InternalCall)]
    public extern void test1(Vector3[] a);
    [MethodImplAttribute(MethodImplOptions.InternalCall)]
    public extern void test2(string s);


    [MethodImplAttribute(MethodImplOptions.InternalCall)]
    public extern int memfn1(float a1);

    [MethodImplAttribute(MethodImplOptions.InternalCall)]
    public extern int memfn2(float a1, Vector2 a2);

    [MethodImplAttribute(MethodImplOptions.InternalCall)]
    public extern int memfn3(float a1, Vector2 a2, Vector3 a3);

    [MethodImplAttribute(MethodImplOptions.InternalCall)]
    public extern int memfn4(float a1, Vector2 a2, Vector3 a3, Vector4 a4);


    [MethodImplAttribute(MethodImplOptions.InternalCall)]
    public extern int cmemfn1(float a1);

    [MethodImplAttribute(MethodImplOptions.InternalCall)]
    public extern int cmemfn2(float a1, Vector2 a2);

    [MethodImplAttribute(MethodImplOptions.InternalCall)]
    public extern int cmemfn3(float a1, Vector2 a2, Vector3 a3);

    [MethodImplAttribute(MethodImplOptions.InternalCall)]
    public extern int cmemfn4(float a1, Vector2 a2, Vector3 a3, Vector4 a4);


    [MethodImplAttribute(MethodImplOptions.InternalCall)]
    public extern int smemfn1(float a1);

    [MethodImplAttribute(MethodImplOptions.InternalCall)]
    public extern int smemfn2(float a1, Vector2 a2);

    [MethodImplAttribute(MethodImplOptions.InternalCall)]
    public extern int smemfn3(float a1, Vector2 a2, Vector3 a3);

    [MethodImplAttribute(MethodImplOptions.InternalCall)]
    public extern int smemfn4(float a1, Vector2 a2, Vector3 a3, Vector4 a4);


    T TestTemplateMethod<T>() where T : struct
    {
        UnityEngine.Debug.Log("TestTemplateMethod()");
        return new T();
    }

    void ThisFunctionWillBeCalledFromCpp()
    {
        UnityEngine.Debug.Log("ThisFunctionWillBeCalledFromCpp()");

        Vector3[] v3array = new Vector3[] {
            Vector3.one * 1.0f,
            Vector3.one * 2.0f,
            Vector3.one * 3.0f,
        };
        test1(v3array);
        test2("hogehoge");

        //Vector3 v3 = ReturnVector3();
        //UnityEngine.Debug.Log("v3: "+v3.x+", "+v3.y+", "+v3.z);

        float f = 1.0f;
        Vector2 v2 = new Vector2(0.0f, 1.0f);
        Vector3 v3 = new Vector3(0.0f, 1.0f, 2.0f);
        Vector4 v4 = new Vector4(0.0f, 1.0f, 2.0f, 3.0f);

        //test1(10, 20, 30, 40);
        //test2(1.0f, v2);

        memfn1(f);
        //UnityEngine.Debug.Log("memfn1: " + f);
        memfn2(f, v2);
        //UnityEngine.Debug.Log("memfn2: " + v2.x + ", " + v2.y);
        memfn3(f, v2, v3);
        //UnityEngine.Debug.Log("memfn3: " + v3.x + ", " + v3.y + ", " + v3.z);
        memfn4(f, v2, v3, v4);
        //UnityEngine.Debug.Log("memfn4: " + v4.x + ", " + v4.y + ", " + v4.z + ", " + v4.w);

        cmemfn1(f);
        //UnityEngine.Debug.Log("cmemfn1: " + f);
        cmemfn2(f, v2);
        //UnityEngine.Debug.Log("cmemfn2: " + v2.x + ", " + v2.y);
        cmemfn3(f, v2, v3);
        //UnityEngine.Debug.Log("cmemfn3: " + v3.x + ", " + v3.y + ", " + v3.z);
        cmemfn4(f, v2, v3, v4);
        //UnityEngine.Debug.Log("cmemfn4: " + v4.x + ", " + v4.y + ", " + v4.z + ", " + v4.w);

        smemfn1(f);
        //UnityEngine.Debug.Log("smemfn1: " + f);
        smemfn2(f, v2);
        //UnityEngine.Debug.Log("smemfn2: " + v2.x + ", " + v2.y);
        smemfn3(f, v2, v3);
        //UnityEngine.Debug.Log("smemfn3: " + v3.x + ", " + v3.y + ", " + v3.z);
        smemfn4(f, v2, v3, v4);
        //UnityEngine.Debug.Log("smemfn4: " + v4.x + ", " + v4.y + ", " + v4.z + ", " + v4.w);
    }
}
