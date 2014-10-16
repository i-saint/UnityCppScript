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


    class Debug
    {
    public:
        static cpsClass getClass();
        static void Log(const char *message);
        static void Log(const char *message, cpsObject obj);
    };
} // namespace cpsUnityEngine

#endif // cpsUnityEngine_h
