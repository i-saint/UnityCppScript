#ifndef cpsUnityEngine_h
#define cpsUnityEngine_h

#include "cpsTypes.h"

namespace cpsUnityEngine
{
    struct Vector2;
    struct Vector3;
    struct Vector4;

    class Debug;
    class Transform;
    class Collider;
    class Camera;
    class Graphics;
    class Texture;
    class RenderTexture;
    class Mesh;
    class MeshFilter;
    class Shader;
    class ComputeShader;
    class ComputeBuffer;


    struct Vector2
    {
        union {
            struct { float x, y; };
            float v[2];
        };
        Vector2(float a = 0.0f, float b = 0.0f) : x(a), y(b){}
    };

    struct Vector3
    {
        union {
            struct { float x, y, z; };
            float v[3];
        };
        Vector3(float a = 0.0f, float b = 0.0f, float c = 0.0f) : x(a), y(b), z(c){}
    };

    struct Vector4
    {
        union {
            struct { float x, y, z, w; };
            float v[4];
        };
        Vector4(float a = 0.0f, float b = 0.0f, float c = 0.0f, float d = 0.0f) : x(a), y(b), z(c), w(d){}
    };

    struct Quaternion
    {
        union {
            struct { float x, y, z, w; };
            float v[4];
        };
        Quaternion(float a = 0.0f, float b = 0.0f, float c = 0.0f, float d = 0.0f) : x(a), y(b), z(c), w(d){}
    };

    struct Matrix4x4
    {
        union {
            float v[16];
        };
        Matrix4x4() {}
    };

    enum Space {
        World = 0,
        Seld = 1,
    };


    class cpsAPI Application
    {
    public:
        static cpsClass getClass();
        static std::string  get_dataPath();
        static bool         get_isEditor();
    };

    class cpsAPI Debug
    {
    public:
        static cpsClass getClass();
        static void Log(const char *message);
        static void Log(const char *message, cpsObject obj);
    };


    class cpsAPI Component : public cpsObject
    {
    public:
        static cpsClass getClass();

        Component(cpsObject obj);
    };

    class cpsAPI Transform : public Component
    {
    public:
        static cpsClass getClass();

        Transform(cpsObject obj=nullptr);

        Vector3     get_position() const;
        void        set_position(const Vector3& v);

        Vector3     get_localPosition() const;
        void        set_localPosition(const Vector3& v);

        Vector3     get_eulerAngles() const;
        void        set_eulerAngles(const Vector3& v);

        Vector3     get_right() const;
        void        set_right(const Vector3& v);

        Vector3     get_up() const;
        void        set_up(const Vector3& v);

        Vector3     get_forward() const;
        void        set_forward(const Vector3& v);

        Quaternion  get_rotation() const;
        void        set_rotation(const Quaternion &v);

        Quaternion  get_localRotation() const;
        void        set_localRotation(const Quaternion &v);

        Vector3     get_localScale() const;
        void        set_localScale(const Vector3& v);

        Transform   get_parent() const;
        void        set_parent(const Transform &v);

        Matrix4x4   get_worldToLocalMatrix() const;
        Matrix4x4   get_localToWorldMatrix() const;

        Transform   get_root();
        int         get_childCount();
        Vector3     get_lossyScale();

        bool        get_hasChanged();
        void        set_hasChanged(bool v);

        void Translate(const Vector3& v);
        void Translate(const Vector3& v, Space s);
        void Translate(float x, float y, float z);
        void Translate(float x, float y, float z, Space s);
        void Translate(const Vector3& v, Transform t);
        void Translate(float x, float y, float z, Transform t);

        void Rotate(const Vector3& v);
        void Rotate(const Vector3& v, Space s);
        void Rotate(float x, float y, float z);
        void Rotate(float x, float y, float z, Space s);
        void Rotate(const Vector3& v, float a);
        void Rotate(const Vector3& v, float a, Space s);

        void RotateAround(const Vector3& point, const Vector3& axis, float angle);

        void LookAt(Transform t);
        void LookAt(Transform t, const Vector3& v);
        void LookAt(const Vector3& v1, const Vector3& v);
        void LookAt(const Vector3& v);

        Vector3 TransformDirection(const Vector3& v);
        Vector3 TransformDirection(float x, float y, float z);

        Vector3 InverseTransformDirection(const Vector3& v);
        Vector3 InverseTransformDirection(float x, float y, float z);

        Vector3 TransformPoint(const Vector3& v);
        Vector3 TransformPoint(float x, float y, float z);

        Vector3 InverseTransformPoint(const Vector3& v);
        Vector3 InverseTransformPoint(float x, float y, float z);

        void DetachChildren();
        void SetAsFirstSibling();
        void SetAsLastSibling();
        void SetSiblingIndex(int i);
        int GetSiblingIndex();
        Transform Find(const char *name);
        void SendTransformChangedScale();
        bool IsChildOf(Transform t);
        Transform FindChild(const char *name);
        // System.Collections.IEnumerator GetEnumerator();
        void RotateAround(const Vector3& axis, float a);
        void RotateAroundLocal(const Vector3& axis, float a);
        Transform GetChild(int i);
        int GetChildCount();
        bool IsNonUniformScaleTransform();
    };

    class cpsAPI Camera
    {
    public:
        static cpsClass getClass();
    };

    class cpsAPI Graphics
    {
    public:
        static cpsClass getClass();
    };

    class cpsAPI ComputeBuffer
    {
    public:
        static cpsClass getClass();
    };
} // namespace cpsUnityEngine

#endif // cpsUnityEngine_h
