#ifndef cpsUnityEngine_h
#define cpsUnityEngine_h

#include "cpsFoundation.h"

#ifdef max
#   undef max
#endif // max
#ifdef min
#   undef min
#endif // min

namespace UnityEngine
{

class cpsAPI Collider;
class cpsAPI Collider2D;
class cpsAPI Shader;
class cpsAPI Material;
class cpsAPI MaterialPropertyBlock;
class cpsAPI Texture;
class cpsAPI Texture2D;
class cpsAPI RenderTexture;
class cpsAPI ComputeBuffer;
class cpsAPI Mesh;
class cpsAPI Camera;

class cpsAPI Component;



cpsAPI cpsImage& GetImage();

enum Space {
    Space_World = 0,
    Space_Self = 1,
};

enum SendMessageOptions
{
    SendMessageOptions_RequireReceiver,
    SendMessageOptions_DontRequireReceiver
};

enum HideFlags
{
    HideFlags_None = 0,
    HideFlags_HideInHierarchy = 1,
    HideFlags_HideInInspector = 2,
    HideFlags_DontSaveInScene = 4,
    HideFlags_NotEditable = 8,
    HideFlags_DontUnload = 16,
    HideFlags_DontSaveInBuild = 32,
    HideFlags_DontSave = 52,
    HideFlags_HideAndDontSave = 61
};

enum MeshTopology
{
    MeshTopology_Triangles,
    MeshTopology_Quads = 2,
    MeshTopology_Lines,
    MeshTopology_LineStrip,
    MeshTopology_Points
};

enum CubemapFace
{
    CubemapFace_PositiveX,
    CubemapFace_NegativeX,
    CubemapFace_PositiveY,
    CubemapFace_NegativeY,
    CubemapFace_PositiveZ,
    CubemapFace_NegativeZ
};

enum ComputeBufferType
{
    ComputeBufferType_Default = 0,
    ComputeBufferType_Raw = 1,
    ComputeBufferType_Append = 2,
    ComputeBufferType_Counter = 4,
    ComputeBufferType_DrawIndirect = 256
};

enum CollisionDetectionMode
{
    CollisionDetectionMode_Discrete,
    CollisionDetectionMode_Continuous,
    CollisionDetectionMode_ContinuousDynamic
};

enum RigidbodyConstraints
{
    RigidbodyConstraints_None,
    RigidbodyConstraints_FreezePositionX = 2,
    RigidbodyConstraints_FreezePositionY = 4,
    RigidbodyConstraints_FreezePositionZ = 8,
    RigidbodyConstraints_FreezeRotationX = 16,
    RigidbodyConstraints_FreezeRotationY = 32,
    RigidbodyConstraints_FreezeRotationZ = 64,
    RigidbodyConstraints_FreezePosition = 14,
    RigidbodyConstraints_FreezeRotation = 112,
    RigidbodyConstraints_FreezeAll = 126
};

enum RigidbodyInterpolation
{
    RigidbodyInterpolation_None,
    RigidbodyInterpolation_Interpolate,
    RigidbodyInterpolation_Extrapolate
};

enum ForceMode
{
    ForceMode_Force,
    ForceMode_Acceleration = 5,
    ForceMode_Impulse = 1,
    ForceMode_VelocityChange
};

enum UserAuthorization
{
    UserAuthorization_WebCam = 1,
    UserAuthorization_Microphone
};

enum PrimitiveType
{
    PrimitiveType_Sphere,
    PrimitiveType_Capsule,
    PrimitiveType_Cylinder,
    PrimitiveType_Cube,
    PrimitiveType_Plane,
    PrimitiveType_Quad
};

enum RenderingPath
{
    RenderingPath_UsePlayerSettings = -1,
    RenderingPath_VertexLit,
    RenderingPath_Forward,
    RenderingPath_DeferredLighting
};

enum CameraClearFlags
{
    CameraClearFlags_Skybox = 1,
    CameraClearFlags_Color,
    CameraClearFlags_SolidColor = 2,
    CameraClearFlags_Depth,
    CameraClearFlags_Nothing
};
enum DepthTextureMode
{
    DepthTextureMode_None = 0,
    DepthTextureMode_Depth = 1,
    DepthTextureMode_DepthNormals = 2
};

enum TransparencySortMode
{
    TransparencySortMode_Default,
    TransparencySortMode_Perspective,
    TransparencySortMode_Orthographic
};


template<class T>
inline float clamp(T v, T minv, T maxv) { return std::min<T>(std::max<T>(v, minv), maxv); }

template<class T>
inline float clamp01(T v) { return std::min<T>(std::max<T>(v, T(0)), T(1)); }


struct cpsAPI Vector2
{
    cpsDeclTraits();
    static const float kEpsilon;
    static const Vector2 zero;
    static const Vector2 right;
    static const Vector2 up;
    static const Vector2 one;

    union {
        struct { float x, y; };
        float v[2];
    };
    Vector2(float x_ = 0.0f, float y_ = 0.0f) : x(x_), y(y_){}

    float&          operator[](int i)                   { return v[i]; }
    const float&    operator[](int i) const             { return v[i]; }
    inline Vector2  operator-() const                   { return Vector2(   -x,    -y); }
    inline Vector2  operator+(const Vector2 &v) const   { return Vector2(x+v.x, y+v.y); }
    inline Vector2  operator-(const Vector2 &v) const   { return Vector2(x-v.x, y-v.y); }
    inline Vector2  operator*(const Vector2 &v) const   { return Vector2(x*v.x, y*v.y); }
    inline Vector2  operator/(const Vector2 &v) const   { return Vector2(x/v.x, y/v.y); }
    inline Vector2  operator*(float v) const            { return Vector2(x*v, y*v); }
    inline Vector2  operator/(float v) const            { return Vector2(x / v, y / v); }
    inline bool     operator==(const Vector2 &v) const  { return x==v.x && y==v.y; }
    inline bool     operator!=(const Vector2 &v) const  { return x!=v.x || y!=v.y; }
    inline Vector2& operator+=(const Vector2 &v)        { x+=v.x; y+=v.y; return *this; }
    inline Vector2& operator-=(const Vector2 &v)        { x-=v.x; y-=v.y; return *this; }
    inline Vector2& operator*=(const Vector2 &v)        { x*=v.x; y*=v.y; return *this; }
    inline Vector2& operator/=(const Vector2 &v)        { x/=v.x; y/=v.y; return *this; }
    inline Vector2& operator*=(float v)                 { x*=v;   y*=v;   return *this; }
    inline Vector2& operator/=(float v)                 { x/=v;   y/=v;   return *this; }

    float get_magnitude() const
    {
        return std::sqrt(x*x + y*y);
    }
    Vector2 get_normalized() const
    {
        Vector2 r = *this;
        r.Normalize();
        return r;
    }
    float get_sqrMagnitude() const
    {
        return x*x + y*y;
    }

    void Normalize()
    {
        float mag = get_magnitude();
        if (mag > kEpsilon)
        {
            *this /= mag;
        }
        else
        {
            *this = Vector2::zero;
        }
    }
    void Scale(const Vector2 &scale)
    {
        *this *= scale;
    }
    void Set(float x_, float y_)
    {
        *this = Vector2(x_, y_);
    }
    float SqrMagnitude() const
    {
        return x*x + y*y;
    }


    static float Angle(const Vector2 &from, const Vector2 &to)
    {
        return std::acos(clamp(Dot(from.get_normalized(), to.get_normalized()), -1.0f, 1.0f)) * 57.29578f;
    }
    static Vector2 ClampMagnitude(const Vector2 &vector, float maxLength)
    {
        if (vector.get_sqrMagnitude() > maxLength * maxLength)
        {
            return vector.get_normalized() * maxLength;
        }
        return vector;
    }
    static float Distance(const Vector2 &a, const Vector2 &b)
    {
        return (a - b).get_magnitude();
    }
    static float Dot(Vector2 lhs, Vector2 rhs)
    {
        return lhs.x * rhs.x + lhs.y * rhs.y;
    }
    static Vector2 Lerp(const Vector2 &from, const Vector2 &to, float t)
    {
        t = clamp01(t);
        return Vector2(from.x + (to.x - from.x) * t, from.y + (to.y - from.y) * t);
    }
    static Vector2 Max(const Vector2 &lhs, const Vector2 &rhs)
    {
        return Vector2(std::max(lhs.x, rhs.x), std::max(lhs.y, rhs.y));
    }
    static Vector2 Min(const Vector2 &lhs, const Vector2 &rhs)
    {
        return Vector2(std::min(lhs.x, rhs.x), std::min(lhs.y, rhs.y));
    }
    static Vector2 MoveTowards(const Vector2 &current, const Vector2 &target, float maxDistanceDelta)
    {
        Vector2 a = target - current;
        float mag = a.get_magnitude();
        if (mag <= maxDistanceDelta || mag == 0.0f)
        {
            return target;
        }
        return current + a / mag * maxDistanceDelta;
    }
    static Vector2 Scale(const Vector2 &a, const Vector2 &b)
    {
        return Vector2(a.x * b.x, a.y * b.y);
    }
    static float SqrMagnitude(const Vector2 &a)
    {
        return a.x*a.x + a.y*a.y;
    }
};
inline Vector2  operator*(float t, const Vector2 &v) { return Vector2(t*v.x, t*v.y); }
inline Vector2  operator/(float t, const Vector2 &v) { return Vector2(t / v.x, t / v.y); }


struct cpsAPI Vector3
{
    cpsDeclTraits();
    static const float kEpsilon;
    static const Vector3 back;
    static const Vector3 down;
    static const Vector3 forward;
    static const Vector3 left;
    static const Vector3 one;
    static const Vector3 right;
    static const Vector3 up;
    static const Vector3 zero;

    union {
        struct { float x, y, z; };
        float v[3];
    };
    Vector3(float x_ = 0.0f, float y_ = 0.0f, float z_ = 0.0f) : x(x_), y(y_), z(z_){}

    float&          operator[](int i)                   { return v[i]; }
    const float&    operator[](int i) const             { return v[i]; }
    inline Vector3  operator-() const                   { return Vector3(-x, -y, -z); }
    inline Vector3  operator+(const Vector3 &v) const   { return Vector3(x+v.x, y+v.y, z+v.z); }
    inline Vector3  operator-(const Vector3 &v) const   { return Vector3(x-v.x, y-v.y, z-v.z); }
    inline Vector3  operator*(const Vector3 &v) const   { return Vector3(x*v.x, y*v.y, z*v.z); }
    inline Vector3  operator/(const Vector3 &v) const   { return Vector3(x/v.x, y/v.y, z/v.z); }
    inline Vector3  operator*(float v) const            { return Vector3(  x*v,   y*v,   z*v); }
    inline Vector3  operator/(float v) const            { return Vector3(  x/v,   y/v,   z/v); }
    inline bool     operator==(const Vector3 &v) const  { return x==v.x && y==v.y && z==v.z; }
    inline bool     operator!=(const Vector3 &v) const  { return x!=v.x || y!=v.y || z!=v.z; }
    inline Vector3& operator+=(const Vector3 &v)        { x+=v.x; y+=v.y; z+=v.z; return *this; }
    inline Vector3& operator-=(const Vector3 &v)        { x-=v.x; y-=v.y; z-=v.z; return *this; }
    inline Vector3& operator*=(const Vector3 &v)        { x*=v.x; y*=v.y; z*=v.z; return *this; }
    inline Vector3& operator/=(const Vector3 &v)        { x/=v.x; y/=v.y; z/=v.z; return *this; }
    inline Vector3& operator*=(float v)                 { x*=v;   y*=v;   z*=v;   return *this; }
    inline Vector3& operator/=(float v)                 { x/=v;   y/=v;   z/=v;   return *this; }


    float get_magnitude() const
    {
        return std::sqrt(x*x + y*y + z*z);
    }
    Vector3 get_normalized() const
    {
        Vector3 r = *this;
        r.Normalize();
        return r;
    }
    float get_sqrMagnitude() const
    {
        return x*x + y*y + z*z;
    }


    void Normalize()
    {
        float num = Magnitude(*this);
        if (num > kEpsilon)
        {
            *this /= num;
        }
        else
        {
            *this = zero;
        }
    }
    void Scale(Vector3 scale)
    {
        *this *= scale;
    }

    void Set(float new_x, float new_y, float new_z)
    {
        *this = Vector3(new_x, new_y, new_z);
    }


    static float Angle(const Vector3 &from, const Vector3 &to)
    {
        return std::acos(clamp(Dot(from.get_normalized(), to.get_normalized()), -1.0f, 1.0f)) * 57.29578f;
    }
    static Vector3 ClampMagnitude(const Vector3 &vector, float maxLength)
    {
        if (vector.get_sqrMagnitude() > maxLength * maxLength)
        {
            return vector.get_normalized() * maxLength;
        }
        return vector;
    }
    static Vector3 Cross(Vector3 lhs, Vector3 rhs)
    {
        return Vector3(lhs.y*rhs.z - lhs.z*rhs.y, lhs.z*rhs.x - lhs.x*rhs.z, lhs.x*rhs.y - lhs.y*rhs.x);
    }
    static float Distance(Vector3 a, Vector3 b)
    {
        Vector3 vector = Vector3(a.x - b.x, a.y - b.y, a.z - b.z);
        return std::sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
    }
    static float Dot(Vector3 lhs, Vector3 rhs)
    {
        return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
    }
    static Vector3 Exclude(Vector3 excludeThis, Vector3 fromThat)
    {
        return fromThat - Project(fromThat, excludeThis);
    }
    static Vector3 Lerp(Vector3 from, Vector3 to, float t)
    {
        t = clamp01(t);
        return Vector3(from.x + (to.x - from.x) * t, from.y + (to.y - from.y) * t, from.z + (to.z - from.z) * t);
    }
    static float Magnitude(Vector3 a)
    {
        return std::sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
    }
    static Vector3 Max(Vector3 lhs, Vector3 rhs)
    {
        return Vector3(std::max(lhs.x, rhs.x), std::max(lhs.y, rhs.y), std::max(lhs.z, rhs.z));
    }
    static Vector3 Min(Vector3 lhs, Vector3 rhs)
    {
        return Vector3(std::min(lhs.x, rhs.x), std::min(lhs.y, rhs.y), std::min(lhs.z, rhs.z));
    }
    static Vector3 MoveTowards(Vector3 current, Vector3 target, float maxDistanceDelta)
    {
        Vector3 a = target - current;
        float magnitude = a.get_magnitude();
        if (magnitude <= maxDistanceDelta || magnitude == 0.0f)
        {
            return target;
        }
        return current + a / magnitude * maxDistanceDelta;
    }
    static Vector3 Normalize(Vector3 value)
    {
        float num = Magnitude(value);
        if (num > kEpsilon)
        {
            return value / num;
        }
        return zero;
    }
    static void OrthoNormalize(Vector3 &normal, Vector3 &tangent, Vector3 &binormal);
    static void OrthoNormalize(Vector3 &normal, Vector3 &tangent);
    static Vector3 Project(const Vector3 &vector, const Vector3 &onNormal)
    {
        float num = Dot(onNormal, onNormal);
        if (num < 1.401298E-45f)
        {
            return zero;
        }
        return onNormal * Dot(vector, onNormal) / num;
    }
    static Vector3 Reflect(const Vector3 &inDirection, const Vector3 &inNormal)
    {
        return inNormal * (- 2.0f * Dot(inNormal, inDirection)) + inDirection;
    }
    static Vector3 RotateTowards(Vector3 &current, Vector3 &target, float maxRadiansDelta, float maxMagnitudeDelta);
    static Vector3 Scale(const Vector3 &a, const Vector3 &b)
    {
        return Vector3(a.x*b.x, a.y*b.y, a.z*b.z);
    }
    static Vector3 Slerp(Vector3 &from, Vector3 &to, float t);
    static Vector3 SmoothDamp(const Vector3 &current, Vector3 &target, Vector3 &currentVelocity, float smoothTime);
    static Vector3 SmoothDamp(const Vector3 &current, Vector3 &target, Vector3 &currentVelocity, float smoothTime, float maxSpeed);
    static Vector3 SmoothDamp(const Vector3 &current, Vector3 &target, Vector3 &currentVelocity, float smoothTime, float maxSpeed, float deltaTime);
    static float SqrMagnitude(Vector3 a)
    {
        return a.x*a.x + a.y*a.y + a.z*a.z;
    }
};
inline Vector3 operator*(float t, const Vector3 &v) { return Vector3( t*v.x, t*v.y, t*v.z); }
inline Vector3 operator/(float t, const Vector3 &v) { return Vector3( t/v.x, t/v.y, t/v.z); }


struct cpsAPI Vector4
{
    cpsDeclTraits();
    static const float kEpsilon;
    static const Vector4 zero;
    static const Vector4 one;

    union {
        struct { float x, y, z, w; };
        float v[4];
    };
    Vector4(float x_ = 0.0f, float y_ = 0.0f, float z_ = 0.0f, float w_ = 0.0f) : x(x_), y(y_), z(z_), w(w_){}

    float&          operator[](int i)                   { return v[i]; }
    const float&    operator[](int i) const             { return v[i]; }
    inline Vector4  operator-() const                   { return Vector4(   -x,    -y,    -z,    -w); }
    inline Vector4  operator+(const Vector4 &v) const   { return Vector4(x+v.x, y+v.y, z+v.z, w+v.w); }
    inline Vector4  operator-(const Vector4 &v) const   { return Vector4(x-v.x, y-v.y, z-v.z, w-v.w); }
    inline Vector4  operator*(const Vector4 &v) const   { return Vector4(x*v.x, y*v.y, z*v.z, w*v.w); }
    inline Vector4  operator/(const Vector4 &v) const   { return Vector4(x/v.x, y/v.y, z/v.z, w/v.w); }
    inline Vector4  operator*(float v)  const           { return Vector4(  x*v,   y*v,   z*v,   w*v); }
    inline Vector4  operator/(float v)  const           { return Vector4(  x/v,   y/v,   z/v,   w/v); }
    inline bool     operator==(const Vector4 &v) const  { return x==v.x && y==v.y && z==v.z && w==v.w; }
    inline bool     operator!=(const Vector4 &v) const  { return x!=v.x || y!=v.y || z!=v.z || w!=v.w; }
    inline Vector4& operator+=(const Vector4 &v)        { x+=v.x; y+=v.y; z+=v.z; w+=v.w; return *this; }
    inline Vector4& operator-=(const Vector4 &v)        { x-=v.x; y-=v.y; z-=v.z; w-=v.w; return *this; }
    inline Vector4& operator*=(const Vector4 &v)        { x*=v.x; y*=v.y; z*=v.z; w*=v.w; return *this; }
    inline Vector4& operator/=(const Vector4 &v)        { x/=v.x; y/=v.y; z/=v.z; w/=v.w; return *this; }
    inline Vector4& operator*=(float v)                 { x*=v;   y*=v;   z*=v;   w*=v;   return *this; }
    inline Vector4& operator/=(float v)                 { x/=v;   y/=v;   z/=v;   w/=v;   return *this; }
};
inline Vector4 operator*(float t, const Vector4 &v) { return Vector4( t*v.x, t*v.y, t*v.z, t*v.w); }
inline Vector4 operator/(float t, const Vector4 &v) { return Vector4( t/v.x, t/v.y, t/v.z, t/v.w); }



struct Color
{
    cpsDeclTraits();
    static const Color black;
    static const Color blue;
    static const Color clear;
    static const Color cyan;
    static const Color gray;
    static const Color green;
    static const Color grey;
    static const Color magenta;
    static const Color red;
    static const Color white;
    static const Color yellow;

    union {
        struct { float b,a,r,g; };
        float v[4];
    };
};

struct Color32
{
    cpsDeclTraits();
    union {
        struct { uint8_t b, a, r, g; };
        uint8_t v[4];
    };
};

struct cpsAPI Quaternion
{
    cpsDeclTraits();
    static const Quaternion identity;

    union {
        struct { float x, y, z, w; };
        float v[4];
    };
    Quaternion(float a = 0.0f, float b = 0.0f, float c = 0.0f, float d = 0.0f) : x(a), y(b), z(c), w(d){}
};

struct cpsAPI Matrix4x4
{
    cpsDeclTraits();
    static const Matrix4x4 identity;

    union {
        float v[16];
    };
    Matrix4x4();
};



struct Rect
{
    cpsDeclTraits();

    float width;
    float height;
    float xmin;
    float ymin;
};

struct cpsAPI Bounds
{
    cpsDeclTraits();

    Vector3 center;
    Vector3 extents;
};

struct cpsAPI Ray
{
    cpsDeclTraits();

    Vector3 direction;
    Vector3 origin;
};

struct cpsAPI Ray2D
{
    cpsDeclTraits();

    Vector2 direction;
    Vector2 origin;
};

struct cpsAPI RaycastHit
{
    cpsDeclTraits();

    float       distance;
    Vector2     uv;
    cpsObject   collider; // Collider
    Vector3     point;
    Vector3     normal;
    int         faceID;
};

struct cpsAPI RaycastHit2D
{
    cpsDeclTraits();

    float       distance;
    float       fraction;
    cpsObject   collider; // Collider2D
    Vector2     centroid;
    Vector2     point;
    Vector2     normal;
};

struct cpsAPI RenderBuffer
{
    cpsDeclTraits();

    void *buffer_ptr;
    int rendertexture_instanceID;
};


struct cpsAPI BoneWeight
{
    cpsDeclTraits();

    int bone_indices[4];
    float weight[4];
};


class cpsAPI Collision : public cpsObject
{
typedef cpsObject super;
public:
    cpsDeclTraits();
    Collision(cpsObject = nullptr);
};

class cpsAPI Collision2D : public cpsObject
{
typedef cpsObject super;
public:
    cpsDeclTraits();
    Collision2D(cpsObject = nullptr);
};



class cpsAPI Object : public cpsObject
{
typedef cpsObject super;
public:
    cpsDeclTraits();

    Object(cpsObject = nullptr);
    cpsString   get_name() const;
    void        set_name(cpsString name);
    HideFlags   get_hideFlags() const;
    void        set_hideFlags(HideFlags flags);
    void*       obj_address() const;

    int         GetInstanceID() const;
    cpsString   ToString() const;

    template<class T>
    static T FindObjectOfType()
    {
        static cpsCachedMethod s_generics;
        static cpsCachedMethod s_method;
        if (!s_generics) {
            cpsClass tparams[] = { ComponentT::getClass() };
            s_generics = mobj.getClass().findMethod("FindObjectOfType", 0);
            s_method = s_generics.instantiate(tparams, 1);
        }
        return T(s_method.invoke(mobj));
    }

    template<class T>
    static cpsTArray<T> FindObjectsOfType()
    {
        static cpsCachedMethod s_generics;
        static cpsCachedMethod s_method;
        if (!s_generics) {
            cpsClass tparams[] = { ComponentT::getClass() };
            s_generics = mobj.getClass().findMethod("FindObjectsOfType", 0);
            s_method = s_generics.instantiate(tparams, 1);
        }
        return cpsTArray<T>(s_method.invoke(mobj));
    }

    static Object   Instantiate(Object original, const Vector3 &position, const Quaternion &rotation);
    static Object   Instantiate(Object original);
    static void     Destroy(cpsObject obj, float delay = 0.0f);
    static void     DestroyImmediate(Object obj, bool allowDestroyingAssets = false);
    static void     DontDestroyOnLoad(Object obj);
    static void     DestroyObject(Object obj, float delay = 0.0f);
};

class cpsAPI AsyncOperation : public Object
{
typedef Object super;
public:
    cpsDeclTraits();
    AsyncOperation(cpsObject v = nullptr);
    bool    get_isDone();
    float   get_progress();
    int     get_priority();
    void    set_priority(int v);
    bool    get_allowSceneActivation();
    void    set_allowSceneActivation(bool v);
};

class cpsAPI ResourceRequest : public AsyncOperation
{
typedef AsyncOperation super;
public:
    cpsDeclTraits();
    ResourceRequest(cpsObject v = nullptr);
    Object get_asset();
};


class cpsAPI Mesh : public Object
{
typedef Object super;
public:
    cpsDeclTraits();
    static Mesh create();
    Mesh(cpsObject v = nullptr);

    Matrix4x4               get_bindposes();
    void                    set_bindposes(const Matrix4x4 &v);
    int                     get_blendShapeCount();
    cpsTArray<BoneWeight>   get_boneWeights();
    void                    set_boneWeights(cpsTArray<BoneWeight> v);
    Bounds                  get_bounds();
    void                    set_bounds(const Bounds &v);
    cpsTArray<Color>        get_colors();
    void                    set_colors(cpsTArray<Color> v);
    cpsTArray<Color32>      get_colors32();
    void                    set_colors32(cpsTArray<Color32> v);
    bool                    get_isReadable();
    cpsTArray<Vector3>      get_normals();
    void                    set_normals(cpsTArray<Vector3> v);
    int                     get_subMeshCount();
    void                    set_subMeshCount(int v);
    cpsTArray<Vector4>      get_tangents();
    void                    set_tangents(cpsTArray<Vector4> v);
    cpsTArray<int>          get_triangles();
    void                    set_triangles(cpsTArray<int> v);
    cpsTArray<Vector2>      get_uv();
    void                    set_uv(cpsTArray<Vector2> v);
    cpsTArray<Vector2>      get_uv2();
    void                    set_uv2(cpsTArray<Vector2> v);
    int                     get_vertexCount();
    cpsTArray<Vector3>      get_vertices();
    void                    set_vertices(cpsTArray<Vector3> v);

    void                    Clear(bool keepVertexLayout = true);
    //void                    CombineMeshes(CombineInstance[] combine, bool mergeSubMeshes = true, bool useMatrices = true);
    cpsString               GetBlendShapeName(int index);
    cpsTArray<int>          GetIndices(int submesh);
    MeshTopology            GetTopology(int submesh);
    cpsTArray<int>          GetTriangles(int submesh);
    void                    MarkDynamic();
    void                    Optimize();
    void                    RecalculateBounds();
    void                    RecalculateNormals();
    void                    SetIndices(cpsTArray<int> indices, MeshTopology topology, int submesh);
    void                    SetTriangles(cpsTArray<int> triangles, int submesh);
};


class cpsAPI Material : public Object
{
typedef Object super;
public:
    cpsDeclTraits();
    static Material create(cpsString v);
    static Material create(Shader v);
    static Material create(Material v);
    Material(cpsObject v = nullptr);

    Color                   get_color();
    void                    set_color(const Color &v);
    Texture                 get_mainTexture();
    void                    set_mainTexture(Texture v);
    Vector2                 get_mainTextureOffset();
    void                    set_mainTextureOffset(const Vector2 &v);
    Vector2                 get_mainTextureScale();
    void                    set_mainTextureScale(const Vector2 &v);
    int                     get_passCount();
    int                     get_renderQueue();
    void                    set_renderQueue(int v);
    Shader                  get_shader();
    void                    set_shader(Shader v);
    cpsTArray<cpsString>    get_shaderKeywords();
    void                    set_shaderKeywords(cpsTArray<cpsString> v);

    void        CopyPropertiesFromMaterial(Material mat);
    void        DisableKeyword(cpsString keyword);
    void        EnableKeyword(cpsString keyword);
    Color       GetColor(cpsString propertyName);
    Color       GetColor(int nameID);
    float       GetFloat(cpsString propertyName);
    float       GetFloat(int nameID);
    int         GetInt(cpsString propertyName);
    int         GetInt(int nameID);
    Matrix4x4   GetMatrix(cpsString propertyName);
    Matrix4x4   GetMatrix(int nameID);
    cpsString   GetTag(cpsString tag, bool searchFallbacks, cpsString defaultValue);
    Texture     GetTexture(cpsString propertyName);
    Texture     GetTexture(int nameID);
    Vector2     GetTextureOffset(cpsString propertyName);
    Vector2     GetTextureScale(cpsString propertyName);
    Vector4     GetVector(cpsString propertyName);
    Vector4     GetVector(int nameID);
    bool        HasProperty(cpsString propertyName);
    bool        HasProperty(int nameID);
    void        Lerp(Material start, Material end, float t);
    void        SetBuffer(cpsString propertyName, ComputeBuffer buffer);
    void        SetColor(cpsString propertyName, const Color &color);
    void        SetColor(int nameID, const Color &color);
    void        SetFloat(cpsString propertyName, float value);
    void        SetFloat(int nameID, float value);
    void        SetInt(cpsString propertyName, int value);
    void        SetInt(int nameID, int value);
    void        SetMatrix(cpsString propertyName, const Matrix4x4 &matrix);
    void        SetMatrix(int nameID, const Matrix4x4 &matrix);
    bool        SetPass(int pass);
    void        SetTexture(cpsString propertyName, Texture texture);
    void        SetTexture(int nameID, Texture texture);
    void        SetTextureOffset(cpsString propertyName, const Vector2 &offset);
    void        SetTextureScale(cpsString propertyName, const Vector2 &scale);
    void        SetVector(cpsString propertyName, const Vector4 &vector);
    void        SetVector(int nameID, const Vector4 &vector);
};

class cpsAPI MaterialPropertyBlock : public Object
{
typedef Object super;
public:
    cpsDeclTraits();
    MaterialPropertyBlock(cpsObject v = nullptr);
};

class cpsAPI Shader : public Object
{
typedef Object super;
public:
    cpsDeclTraits();
    Shader(cpsObject v = nullptr);
    
    bool            get_isSupported();
    int             get_maximumLOD();
    void            set_maximumLOD(int v);
    int             get_renderQueue();
    cpsString       get_customEditor();

    static int      get_globalMaximumLOD();
    static void     set_globalMaximumLOD(int v);

    static Shader   Find(cpsString name);
    static int      PropertyToID(cpsString name);
    static void     SetGlobalBuffer(cpsString propertyName, ComputeBuffer buffer);
    static void     SetGlobalColor(cpsString propertyName, const Color &color);
    static void     SetGlobalColor(int nameID, const Color &color);
    static void     SetGlobalFloat(cpsString propertyName, float value);
    static void     SetGlobalFloat(int nameID, float value);
    static void     SetGlobalInt(cpsString propertyName, int value);
    static void     SetGlobalInt(int nameID, int value);
    static void     SetGlobalMatrix(cpsString propertyName, const Matrix4x4 &mat);
    static void     SetGlobalMatrix(int nameID, const Matrix4x4 &mat);
    static void     SetGlobalTexture(cpsString propertyName, Texture tex);
    static void     SetGlobalTexture(int nameID, Texture tex);
    static void     SetGlobalVector(cpsString propertyName, const Vector4 &vec);
    static void     SetGlobalVector(int nameID, const Vector4 &vec);
    static void     WarmupAllShaders();
};

class cpsAPI Texture : public Object
{
typedef Object super;
public:
    cpsDeclTraits();
    Texture(cpsObject v = nullptr);
};

class cpsAPI Texture2D : public Texture
{
typedef Texture super;
public:
    cpsDeclTraits();
    Texture2D(cpsObject v = nullptr);
};

class cpsAPI RenderTexture : public Texture
{
typedef Texture super;
public:
    cpsDeclTraits();
    RenderTexture(cpsObject = nullptr);
};

class cpsAPI Cubemap : public Texture
{
typedef Texture super;
public:
    cpsDeclTraits();
    Cubemap(cpsObject = nullptr);
};


class cpsAPI ComputeBuffer : public Object
{
typedef Object super;
public:
    cpsDeclTraits();
    static ComputeBuffer create(int count, int stride);
    static ComputeBuffer create(int count, int stride, ComputeBufferType type);

    ComputeBuffer(cpsObject = nullptr);
    int get_count();
    int get_stride();
    void Dispose();
    void Release();
    void SetData(cpsArray a);
    void GetData(cpsArray a);

    static void CopyCount(ComputeBuffer src, ComputeBuffer dst, int count);
};


class cpsAPI PhysicMaterial : public Object
{
typedef Object super;
public:
    cpsDeclTraits();
    PhysicMaterial(cpsObject v = nullptr);
};

class cpsAPI PhysicsMaterial2D : public Object
{
typedef Object super;
public:
    cpsDeclTraits();
    PhysicsMaterial2D(cpsObject v = nullptr);
};


class Motion : public Object
{
typedef Object super;
public:
    cpsDeclTraits();
    Motion(cpsObject v = nullptr);
};

class AnimationClip : public Motion
{
typedef Motion super;
public:
    cpsDeclTraits();
    AnimationClip(cpsObject v = nullptr);
};



class cpsAPI GameObject : public Object
{
typedef Object super;
public:
    cpsDeclTraits();
    GameObject(cpsObject v = nullptr);

    template<class ComponentT>
    ComponentT AddComponent()
    {
        static cpsCachedMethod s_generics;
        static cpsCachedMethod s_method;
        if (!s_generics) {
            cpsClass tparams[] = { ComponentT::getClass() };
            s_generics = cpsObject(mobj).getClass().findMethod("AddComponent", 0);
            s_method = s_generics.instantiate(tparams, 1);
        }
        return ComponentT(s_method.invoke(mobj));
    }

    template<class ComponentT>
    ComponentT GetComponent()
    {
        static cpsCachedMethod s_generics;
        static cpsCachedMethod s_method;
        if (!s_generics) {
            cpsClass tparams[] = { ComponentT::getClass() };
            s_generics = cpsObject(mobj).getClass().findMethod("GetComponent", 0);
            s_method = s_generics.instantiate(tparams, 1);
        }
        return ComponentT(s_method.invoke(mobj));
    }

    template<class ComponentT>
    cpsTArray<ComponentT> GetComponents()
    {
        static cpsCachedMethod s_generics;
        static cpsCachedMethod s_method;
        if (!s_generics) {
            cpsClass tparams[] = { ComponentT::getClass() };
            s_generics = cpsObject(mobj).getClass().findMethod("GetComponents", 0);
            s_method = s_generics.instantiate(tparams, 1);
        }
        return cpsTArray<ComponentT>(s_method.invoke(mobj));
    }

    template<class ComponentT>
    ComponentT GetComponentInChildren()
    {
        static cpsCachedMethod s_generics;
        static cpsCachedMethod s_method;
        if (!s_generics) {
            cpsClass tparams[] = { ComponentT::getClass() };
            s_generics = cpsObject(mobj).getClass().findMethod("GetComponentInChildren", 0);
            s_method = s_generics.instantiate(tparams, 1);
        }
        return ComponentT(s_method.invoke(mobj));
    }

    template<class ComponentT>
    cpsTArray<ComponentT> GetComponentsInChildren()
    {
        static cpsCachedMethod s_generics;
        static cpsCachedMethod s_method;
        if (!s_generics) {
            cpsClass tparams[] = { ComponentT::getClass() };
            s_generics = cpsObject(mobj).getClass().findMethod("GetComponentsInChildren", 0);
            s_method = s_generics.instantiate(tparams, 1);
        }
        return cpsTArray<ComponentT>(s_method.invoke(mobj));
    }

    template<class ComponentT>
    ComponentT GetComponentInParent()
    {
        static cpsCachedMethod s_generics;
        static cpsCachedMethod s_method;
        if (!s_generics) {
            cpsClass tparams[] = { ComponentT::getClass() };
            s_generics = cpsObject(mobj).getClass().findMethod("GetComponentInParent", 0);
            s_method = s_generics.instantiate(tparams, 1);
        }
        return ComponentT(s_method.invoke(mobj));
    }

    template<class ComponentT>
    cpsTArray<ComponentT> GetComponentsInParent()
    {
        static cpsCachedMethod s_generics;
        static cpsCachedMethod s_method;
        if (!s_generics) {
            cpsClass tparams[] = { ComponentT::getClass() };
            s_generics = cpsObject(mobj).getClass().findMethod("GetComponentsInParent", 0);
            s_method = s_generics.instantiate(tparams, 1);
        }
        return cpsTArray<ComponentT>(s_method.invoke(mobj));
    }

    void BroadcastMessage(cpsString methodName, Object parameter = Object(), SendMessageOptions options = SendMessageOptions_RequireReceiver);
    bool CompareTag(cpsString tag);
    void SampleAnimation(AnimationClip animation, float time);
    void SendMessage(cpsString methodName, Object value = Object(), SendMessageOptions options = SendMessageOptions_RequireReceiver);
    void SendMessageUpwards(cpsString methodName, Object value = Object(), SendMessageOptions options = SendMessageOptions_RequireReceiver);
    void SetActive(bool value);

    static GameObject               CreatePrimitive(PrimitiveType type);
    static GameObject               Find(cpsString name);
    static cpsTArray<GameObject>    FindGameObjectsWithTag(cpsString tag);
    static GameObject               FindWithTag(cpsString tag);
};

class cpsAPI Component : public Object
{
typedef Object super;
public:
    cpsDeclTraits();
    Component(cpsObject obj=nullptr);

    //// obsolete in Unity5. use GetComponent<T>() instead
    //get_transform() : Transform
    //InternalGetTransform() : Transform
    //get_rigidbody() : Rigidbody
    //get_rigidbody2D() : Rigidbody2D
    //get_camera() : Camera
    //get_light() : Light
    //get_animation() : Animation
    //get_constantForce() : ConstantForce
    //get_renderer() : Renderer
    //get_audio() : AudioSource
    //get_guiText() : GUIText
    //get_networkView() : NetworkView
    //get_guiElement() : GUIElement
    //get_guiTexture() : GUITexture
    //get_collider() : Collider
    //get_collider2D() : Collider2D
    //get_hingeJoint() : HingeJoint
    //get_particleEmitter() : ParticleEmitter
    //get_particleSystem() : ParticleSystem

    GameObject  get_gameObject() const;
    bool        get_active() const;
    void        set_active(bool v);
    cpsString   get_tag() const;
    void        set_tag(cpsString tag);

    template<class ComponentT>
    ComponentT GetComponent()
    {
        static cpsCachedMethod s_generics;
        static cpsCachedMethod s_method;
        if (!s_generics) {
            cpsClass tparams[] = { ComponentT::getClass() };
            s_generics = cpsObject(mobj).getClass().findMethod("GetComponent", 0);
            s_method = s_generics.instantiate(tparams, 1);
        }
        return ComponentT(s_method.invoke(mobj));
    }

    template<class ComponentT>
    cpsTArray<ComponentT> GetComponents()
    {
        static cpsCachedMethod s_generics;
        static cpsCachedMethod s_method;
        if (!s_generics) {
            cpsClass tparams[] = { ComponentT::getClass() };
            s_generics = cpsObject(mobj).getClass().findMethod("GetComponents", 0);
            s_method = s_generics.instantiate(tparams, 1);
        }
        return cpsTArray<ComponentT>(s_method.invoke(mobj));
    }

    template<class ComponentT>
    ComponentT GetComponentInChildren()
    {
        static cpsCachedMethod s_generics;
        static cpsCachedMethod s_method;
        if (!s_generics) {
            cpsClass tparams[] = { ComponentT::getClass() };
            s_generics = cpsObject(mobj).getClass().findMethod("GetComponentInChildren", 0);
            s_method = s_generics.instantiate(tparams, 1);
        }
        return ComponentT(s_method.invoke(mobj));
    }

    template<class ComponentT>
    cpsTArray<ComponentT> GetComponentsInChildren()
    {
        static cpsCachedMethod s_generics;
        static cpsCachedMethod s_method;
        if (!s_generics) {
            cpsClass tparams[] = { ComponentT::getClass() };
            s_generics = cpsObject(mobj).getClass().findMethod("GetComponentsInChildren", 0);
            s_method = s_generics.instantiate(tparams, 1);
        }
        return cpsTArray<ComponentT>(s_method.invoke(mobj));
    }

    template<class ComponentT>
    ComponentT GetComponentInParent()
    {
        static cpsCachedMethod s_generics;
        static cpsCachedMethod s_method;
        if (!s_generics) {
            cpsClass tparams[] = { ComponentT::getClass() };
            s_generics = cpsObject(mobj).getClass().findMethod("GetComponentInParent", 0);
            s_method = s_generics.instantiate(tparams, 1);
        }
        return ComponentT(s_method.invoke(mobj));
    }

    template<class ComponentT>
    cpsTArray<ComponentT> GetComponentsInParent()
    {
        static cpsCachedMethod s_generics;
        static cpsCachedMethod s_method;
        if (!s_generics) {
            cpsClass tparams[] = { ComponentT::getClass() };
            s_generics = cpsObject(mobj).getClass().findMethod("GetComponentsInParent", 0);
            s_method = s_generics.instantiate(tparams, 1);
        }
        return cpsTArray<ComponentT>(s_method.invoke(mobj));
    }

    bool CompareTag(cpsString tag);
    void SendMessageUpwards(cpsString method_name, cpsObject obj = nullptr, SendMessageOptions opt = SendMessageOptions_RequireReceiver);
    void SendMessage(cpsString method_name, cpsObject obj = nullptr, SendMessageOptions opt = SendMessageOptions_RequireReceiver);
    void BroadcastMessage(cpsString method_name, cpsObject obj = nullptr, SendMessageOptions opt = SendMessageOptions_RequireReceiver);
};

class cpsAPI Behaviour : public Component
{
typedef Component super;
public:
    cpsDeclTraits();
    Behaviour(cpsObject obj = nullptr);
    bool get_enabled() const;
    void set_enabled(bool v);
};


class cpsAPI Transform : public Component
{
typedef Component super;
public:
    cpsDeclTraits();

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

    void        Translate(const Vector3& v, Space s = Space_Self);
    void        Translate(const Vector3& v, Transform relative);
    void        Rotate(const Vector3& eulerAngles, Space s = Space_Self);
    void        Rotate(const Vector3& axis, float angle, Space s = Space_Self);
    void        RotateAround(const Vector3& point, const Vector3& axis, float angle);
    void        LookAt(Transform t, const Vector3& v = Vector3::up);
    void        LookAt(const Vector3& worldPos, const Vector3& v = Vector3::up);
    Vector3     TransformDirection(const Vector3& v);
    Vector3     InverseTransformDirection(const Vector3& v);
    Vector3     TransformPoint(const Vector3& v);
    Vector3     InverseTransformPoint(const Vector3& v);
    void        DetachChildren();
    void        SetAsFirstSibling();
    void        SetAsLastSibling();
    void        SetSiblingIndex(int i);
    int         GetSiblingIndex();
    Transform   Find(cpsString name);
    void        SendTransformChangedScale();
    bool        IsChildOf(Transform t);
    Transform   FindChild(cpsString name);
    void        RotateAround(const Vector3& axis, float a);
    void        RotateAroundLocal(const Vector3& axis, float a);
    Transform   GetChild(int i);
    int         GetChildCount();
    bool        IsNonUniformScaleTransform();
    // System.Collections.IEnumerator GetEnumerator();
};


class cpsAPI Rigidbody : public Component
{
typedef Component super;
public:
    cpsDeclTraits();
    Rigidbody(cpsObject obj = nullptr);

    float                   get_angularDrag();
    void                    set_angularDrag(float v);
    Vector3                 get_angularVelocity();
    void                    set_angularVelocity(const Vector3 &v);
    Vector3                 get_centerOfMass();
    void                    set_centerOfMass(const Vector3 &v);
    CollisionDetectionMode  get_collisionDetectionMode();
    void                    set_collisionDetectionMode(CollisionDetectionMode v);
    RigidbodyConstraints    get_constraints();
    void                    set_constraints(RigidbodyConstraints v);
    bool                    get_detectCollisions();
    void                    set_detectCollisions(bool v);
    float                   get_drag();
    void                    set_drag(float v);
    bool                    get_freezeRotation();
    void                    set_freezeRotation(bool v);
    Vector3                 get_inertiaTensor();
    void                    set_inertiaTensor(const Vector3 &v);
    Quaternion              get_inertiaTensorRotation();
    void                    set_inertiaTensorRotation(const Quaternion &v);
    RigidbodyInterpolation  get_interpolation();
    void                    set_interpolation(RigidbodyInterpolation v);
    bool                    get_isKinematic();
    void                    set_isKinematic(bool v);
    float                   get_mass();
    void                    set_mass(float v);
    float                   get_maxAngularVelocity();
    void                    set_maxAngularVelocity(float v);
    Vector3                 get_position();
    void                    set_position(const Vector3 &v);
    Quaternion              get_rotation();
    void                    set_rotation(const Quaternion &v);
    float                   get_sleepAngularVelocity();
    void                    set_sleepAngularVelocity(float v);
    float                   get_sleepVelocity();
    void                    set_sleepVelocity(float v);
    int                     get_solverIterationCount();
    void                    set_solverIterationCount(int v);
    bool                    get_useConeFriction();
    void                    set_useConeFriction(bool v);
    bool                    get_useGravity();
    void                    set_useGravity(bool v);
    Vector3                 get_velocity();
    void                    set_velocity(const Vector3 &v);
    Vector3                 get_worldCenterOfMass();

    void                    AddExplosionForce(float explosionForce, const Vector3 &explosionPosition, float explosionRadius, float upwardsModifier = 0.0f, ForceMode mode = ForceMode_Force);
    void                    AddForce(const Vector3 &force, ForceMode mode = ForceMode_Force);
    void                    AddForceAtPosition(const Vector3 &force, const Vector3 &position, ForceMode mode = ForceMode_Force);
    void                    AddRelativeForce(const Vector3 &force, ForceMode mode = ForceMode_Force);
    void                    AddRelativeTorque(const Vector3 &torque, ForceMode mode = ForceMode_Force);
    void                    AddTorque(const Vector3 &torque, ForceMode mode = ForceMode_Force);
    Vector3                 ClosestPointOnBounds(const Vector3 &position);
    Vector3                 GetPointVelocity(const Vector3 &worldPoint);
    Vector3                 GetRelativePointVelocity(const Vector3 &relativePoint);
    bool                    IsSleeping();
    void                    MovePosition(const Vector3 &position);
    void                    MoveRotation(const Quaternion &rot);
    void                    SetDensity(float density);
    void                    Sleep();
    bool                    SweepTest(const Vector3 &direction, RaycastHit &hitInfo, float distance = FLT_MAX);
    cpsTArray<RaycastHit>   SweepTestAll(const Vector3 &direction, float distance = FLT_MAX);
    void                    WakeUp();
};


class cpsAPI Rigidbody2D : public Component
{
typedef Component super;
public:
    cpsDeclTraits();
    Rigidbody2D(cpsObject obj = nullptr);
};


class cpsAPI Collider : public Component
{
typedef Component super;
public:
    cpsDeclTraits();
    Collider(cpsObject obj = nullptr);

    bool            get_enabled();
    void            set_enabled(bool v);
    Rigidbody       get_attachedRigidbody();
    bool            get_isTrigger();
    void            set_isTrigger(bool v);
    PhysicMaterial  get_material();
    void            set_material(PhysicMaterial v);
    PhysicMaterial  get_sharedMaterial();
    void            set_sharedMaterial(PhysicMaterial v);
    Bounds          get_bounds();

    Vector3         ClosestPointOnBounds(const Vector3 &v);
    bool            Raycast(const Ray &ray, RaycastHit &hit, float dist);
};

class cpsAPI BoxCollider : public Collider
{
typedef Collider super;
public:
    cpsDeclTraits();
    BoxCollider(cpsObject obj = nullptr);

    Vector3 get_center();
    void    set_center(const Vector3 &v);
    Vector3 get_size();
    void    set_size(const Vector3 &v);
};

class cpsAPI SphereCollider : public Collider
{
typedef Collider super;
public:
    cpsDeclTraits();
    SphereCollider(cpsObject obj = nullptr);

    Vector3 get_center();
    void    set_center(const Vector3 &v);
    float   get_radius();
    void    set_radius(float v);
};

class cpsAPI CapsuleCollider : public Collider
{
typedef Collider super;
public:
    enum Direction {
        Direction_X,
        Direction_Y,
        Direction_Z,
    };

    cpsDeclTraits();
    CapsuleCollider(cpsObject obj = nullptr);

    Vector3     get_center();
    void        set_center(const Vector3 &v);
    Direction   get_direction();
    void        set_direction(Direction v);
    float       get_height();
    void        set_height(float v);
    float       get_radius();
    void        set_radius(float v);
};

class cpsAPI MeshCollider : public Collider
{
typedef Collider super;
public:
    cpsDeclTraits();
    MeshCollider(cpsObject obj = nullptr);

    bool get_convex();
    void set_convex(bool v);
    Mesh get_sharedMesh();
    void set_sharedMesh(Mesh v);
    bool get_smoothSphereCollisions();
    void set_smoothSphereCollisions(bool v);
};


class cpsAPI Collider2D : public Behaviour
{
typedef Behaviour super;
public:
    cpsDeclTraits();
    Collider2D(cpsObject obj = nullptr);

    Rigidbody2D         get_attachedRigidbody();
    Bounds              get_bounds();
    bool                get_isTrigger();
    void                set_isTrigger(bool v);
    int                 get_shapeCount();
    PhysicsMaterial2D   get_sharedMaterial();
    void                set_sharedMaterial(PhysicsMaterial2D v);

    bool OverlapPoint(const Vector2 &v);
};

class cpsAPI BoxCollider2D : public Collider2D
{
typedef Collider2D super;
public:
    cpsDeclTraits();
    BoxCollider2D(cpsObject obj = nullptr);
    Vector2 get_center();
    void    set_center(const Vector2 &v);
    Vector2 get_size();
    void    set_size(const Vector2 &v);
};

class cpsAPI CircleCollider2D : public Collider2D
{
typedef Collider2D super;
public:
    cpsDeclTraits();
    CircleCollider2D(cpsObject obj = nullptr);
    Vector2 get_center();
    void    set_center(const Vector2 &v);
    float   get_radius();
    void    set_radius(float v);
};

class cpsAPI PolygonCollider2D : public Collider2D
{
typedef Collider2D super;
public:
    cpsDeclTraits();
    PolygonCollider2D(cpsObject obj = nullptr);

    int                 get_pathCount();
    void                set_pathCount(int v);
    cpsTArray<Vector2>  get_points();
    void                set_points(cpsTArray<Vector2> v);
};



class cpsAPI Camera : public Component
{
typedef Component super;
public:
    cpsDeclTraits();
    Camera(cpsObject obj = nullptr);

    static cpsTArray<Camera>    get_allCameras();
    static int                  get_allCamerasCount();
    static Camera               get_current();
    static Camera               get_main();
    static int                  GetAllCameras(cpsTArray<Camera> &v);
    static void                 SetupCurrent(Camera cur);

    RenderingPath           get_actualRenderingPath();
    float                   get_aspect();
    void                    set_aspect(float v);
    Color                   get_backgroundColor();
    void                    set_backgroundColor(const Color &v);
    Matrix4x4               get_cameraToWorldMatrix();
    CameraClearFlags        get_clearFlags();
    void                    set_clearFlags(CameraClearFlags v);
    bool                    get_clearStencilAfterLightingPass();
    void                    set_clearStencilAfterLightingPass(bool v);
    int                     get_cullingMask();
    void                    set_cullingMask(int v);
    float                   get_depth();
    void                    set_depth(float v);
    DepthTextureMode        get_depthTextureMode();
    void                    set_depthTextureMode(DepthTextureMode v);
    int                     get_eventMask();
    void                    set_eventMask(int v);
    float                   get_farClipPlane();
    void                    set_farClipPlane(float v);
    float                   get_fieldOfView();
    void                    set_fieldOfView(float v);
    bool                    get_hdr();
    void                    set_hdr(bool v);
    bool                    get_isOrthoGraphic();
    void                    set_isOrthoGraphic(bool v);
    cpsTArray<float>        get_layerCullDistances();
    void                    set_layerCullDistances(cpsTArray<float> v);
    bool                    get_layerCullSpherical();
    void                    set_layerCullSpherical(bool v);
    float                   get_nearClipPlane();
    void                    set_nearClipPlane(float v);
    bool                    get_orthographic();
    void                    set_orthographic(bool v);
    float                   get_orthographicSize();
    void                    set_orthographicSize(float v);
    float                   get_pixelHeight();
    Rect                    get_pixelRect();
    void                    set_pixelRect(const Rect &v);
    float                   get_pixelWidth();
    Matrix4x4               get_projectionMatrix();
    void                    set_projectionMatrix(const Matrix4x4 &v);
    Rect                    get_rect();
    void                    set_rect(const Rect &v);
    RenderingPath           get_renderingPath();
    void                    set_renderingPath(RenderingPath v);
    float                   get_stereoConvergence();
    void                    set_stereoConvergence(float v);
    bool                    get_stereoEnabled();
    void                    set_stereoEnabled(bool v);
    float                   get_stereoSeparation();
    void                    set_stereoSeparation(float v);
    RenderTexture           get_targetTexture();
    void                    set_targetTexture(RenderTexture v);
    TransparencySortMode    get_transparencySortMode();
    void                    set_transparencySortMode(TransparencySortMode v);
    bool                    get_useOcclusionCulling();
    void                    set_useOcclusionCulling(bool v);
    Vector3                 get_velocity();
    void                    set_velocity(const Vector3 &v);
    Matrix4x4               get_worldToCameraMatrix();
    void                    set_worldToCameraMatrix(const Matrix4x4 &v);

    Matrix4x4               CalculateObliqueMatrix(const Vector4 &clipPlane);
    void                    CopyFrom(Camera other);
    void                    Render();
    bool                    RenderToCubemap(Cubemap cubemap, int faceMask = 63);
    void                    RenderWithShader(Shader shader, cpsString replacementTag);
    void                    ResetAspect();
    void                    ResetProjectionMatrix();
    void                    ResetReplacementShader();
    void                    ResetWorldToCameraMatrix();
    Ray                     ScreenPointToRay(const Vector3 &position);
    Vector3                 ScreenToViewportPoint(const Vector3 &position);
    Vector3                 ScreenToWorldPoint(const Vector3 &position);
    void                    SetReplacementShader(Shader shader, cpsString replacementTag);
    void                    SetTargetBuffers(RenderBuffer colorBuffer, RenderBuffer depthBuffer);
    void                    SetTargetBuffers(cpsTArray<RenderBuffer> colorBuffer, RenderBuffer depthBuffer);
    Ray                     ViewportPointToRay(const Vector3 &position);
    Vector3                 ViewportToScreenPoint(const Vector3 &position);
    Vector3                 ViewportToWorldPoint(const Vector3 &position);
    Vector3                 WorldToScreenPoint(const Vector3 &position);
    Vector3                 WorldToViewportPoint(const Vector3 &position);
};


class cpsAPI Light : public Component
{
typedef Component super;
public:
    cpsDeclTraits();
    Light(cpsObject obj = nullptr);
};


class cpsAPI Renderer : public Component
{
typedef Component super;
public:
    cpsDeclTraits();
    Renderer(cpsObject obj = nullptr);
};


class cpsAPI MeshRenderer : public Renderer
{
typedef Renderer super;
public:
    cpsDeclTraits();
    MeshRenderer(cpsObject obj = nullptr);
};


class cpsAPI SpriteRenderer : public Renderer
{
typedef Renderer super;
public:
    cpsDeclTraits();
    SpriteRenderer(cpsObject obj = nullptr);
};




class cpsAPI Application
{
public:
    cpsDeclTraits();
    static cpsString    get_dataPath();
    static bool         get_isEditor();

    static void CancelQuit();
    static bool CanStreamedLevelBeLoaded(int levelIndex);
    static void CaptureScreenshot(cpsString filename, int superSize = 0);
    //static void ExternalCall(cpsString functionName, cpsArray args);  // Web Player only
    //static void ExternalEval(cpsString script);                       // 
    static float GetStreamProgressForLevel(int levelIndex);
    static bool HasProLicense();
    static bool HasUserAuthorization(UserAuthorization mode);
    static void LoadLevel(int index);
    static void LoadLevel(cpsString name);
    static void LoadLevelAdditive(int index);
    static void LoadLevelAdditive(cpsString name);
    static AsyncOperation LoadLevelAdditiveAsync(int index);
    static AsyncOperation LoadLevelAdditiveAsync(cpsString levelName);
    static AsyncOperation LoadLevelAsync(int index);
    static AsyncOperation LoadLevelAsync(cpsString levelName);
    static void OpenURL(cpsString url);
    static void Quit();
    //static void RegisterLogCallback(LogCallback handler);
    //static void RegisterLogCallbackThreaded(LogCallback handler);
    static AsyncOperation RequestUserAuthorization(UserAuthorization mode);
};


class cpsAPI Debug
{
public:
    cpsDeclTraits();

    static bool get_developerConsoleVisible();
    static void set_developerConsoleVisible(bool v);
    static bool get_isDebugBuild();

    static void Break();
    static void ClearDeveloperConsole();
    static void DrawLine(const Vector3 &start, const Vector3 &end, const Color &color = Color::white, float duration = 0.0f, bool depthTest = true);
    static void DrawRay(const Vector3 &start, const Vector3 &dir, const Color &color = Color::white, float duration = 0.0f, bool depthTest = true);
    static void Log(cpsString message);
    static void Log(cpsString message, cpsObject obj);
    static void LogError(cpsString message);
    static void LogError(cpsString message, cpsObject context);
    //static void LogException(Exception exception);
    //static void LogException(Exception exception, Object context);
    static void LogWarning(cpsString message);
    static void LogWarning(cpsString message, cpsObject context);
};


class cpsAPI GL
{
public:
    cpsDeclTraits();
    static const int QUADS = 7;
    static const int LINES = 1;
    static const int TRIANGLES = 4;
    static const int TRIANGLE_STRIP = 5;

    static void         Begin(int mode);
    static void         Clear(bool clearDepth, bool clearColor, const Color &backgroundColor, float depth = 1.0f);
    static void         ClearWithSkybox(bool clearDepth, Camera camera);
    static void         Color_(const Color &c);
    static void         End();
    static Matrix4x4    GetGPUProjectionMatrix(const Matrix4x4 &proj, bool renderIntoTexture);
    static void         InvalidateState();
    static void         IssuePluginEvent(int eventID);
    static void         LoadIdentity();
    static void         LoadOrtho();
    static void         LoadPixelMatrix();
    static void         LoadProjectionMatrix(const Matrix4x4 &mat);
    static void         MultiTexCoord(int unit, const Vector3 &v);
    static void         MultiTexCoord2(int unit, float x, float y);
    static void         MultiTexCoord3(int unit, float x, float y, float z);
    static void         MultMatrix(const Matrix4x4 &mat);
    static void         PopMatrix();
    static void         PushMatrix();
    static void         SetRevertBackfacing(bool revertBackFaces);
    static void         TexCoord(const Vector3 &v);
    static void         TexCoord2(float x, float y);
    static void         TexCoord3(float x, float y, float z);
    static void         Vertex(const Vector3 &v);
    static void         Vertex3(float x, float y, float z);
    static void         Viewport(const Rect &pixelRect);
};


class cpsAPI GUI
{
public:
    cpsDeclTraits();
};


class cpsAPI Graphics
{
public:
    cpsDeclTraits();
    static RenderBuffer get_activeColorBuffer();
    static RenderBuffer get_activeDepthBuffer();
    static cpsString    get_deviceName();
    static cpsString    get_deviceVendor();
    static cpsString    get_deviceVersion();
    static bool         get_supportsVertexProgram();

    static void Blit(Texture source, RenderTexture dest);
    static void Blit(Texture source, RenderTexture dest, Material mat, int pass = -1);
    static void Blit(Texture source, Material mat, int pass = -1);
    static void BlitMultiTap(Texture source, RenderTexture dest, Material mat, cpsTArray<Vector2> offsets);
    static void ClearRandomWriteTargets();
    static void DrawMesh(Mesh mesh, const Vector3 &position, const Quaternion &rotation, Material material, int layer, Camera camera = Camera(), int submeshIndex = 0, MaterialPropertyBlock properties = MaterialPropertyBlock());
    static void DrawMesh(Mesh mesh, const Vector3 &position, const Quaternion &rotation, Material material, int layer, Camera camera, int submeshIndex, MaterialPropertyBlock properties, bool castShadows, bool receiveShadows);
    static void DrawMesh(Mesh mesh, const Matrix4x4 &matrix, Material material, int layer, Camera camera = Camera(), int submeshIndex = 0, MaterialPropertyBlock properties = MaterialPropertyBlock());
    static void DrawMesh(Mesh mesh, const Matrix4x4 &matrix, Material material, int layer, Camera camera, int submeshIndex, MaterialPropertyBlock properties, bool castShadows, bool receiveShadows);
    static void DrawMeshNow(Mesh mesh, const Vector3 &position, const Quaternion &rotation);
    static void DrawMeshNow(Mesh mesh, const Vector3 &position, const Quaternion &rotation, int materialIndex);
    static void DrawMeshNow(Mesh mesh, const Matrix4x4 &matrix);
    static void DrawMeshNow(Mesh mesh, const Matrix4x4 &matrix, int materialIndex);
    static void DrawProcedural(MeshTopology topology, int vertexCount, int instanceCount = 1);
    static void DrawProceduralIndirect(MeshTopology topology, ComputeBuffer bufferWithArgs, int argsOffset = 0);
    static void DrawTexture(const Rect &screenRect, Texture texture, Material mat = Material());
    static void DrawTexture(const Rect &screenRect, Texture texture, int leftBorder, int rightBorder, int topBorder, int bottomBorder, Material mat = Material());
    static void DrawTexture(const Rect &screenRect, Texture texture, const Rect &sourceRect, int leftBorder, int rightBorder, int topBorder, int bottomBorder, Material mat = Material());
    static void DrawTexture(const Rect &screenRect, Texture texture, const Rect &sourceRect, int leftBorder, int rightBorder, int topBorder, int bottomBorder, const Color &color, Material mat = Material());
    static void SetRandomWriteTarget(int index, RenderTexture uav);
    static void SetRandomWriteTarget(int index, ComputeBuffer uav);
    static void SetRenderTarget(RenderTexture rt);
    static void SetRenderTarget(RenderTexture rt, int mipLevel);
    static void SetRenderTarget(RenderTexture rt, int mipLevel, CubemapFace face);
    static void SetRenderTarget(RenderBuffer colorBuffer, RenderBuffer depthBuffer);
    static void SetRenderTarget(cpsTArray<RenderBuffer> colorBuffers, RenderBuffer depthBuffer);

};

class cpsAPI Physics
{
public:
    cpsDeclTraits();

    static const int IgnoreRaycastLayer = 4;
    static const int DefaultRaycastLayers = -5;
    static const int AllLayers = -1;
    static const int kIgnoreRaycastLayer = 4;
    static const int kDefaultRaycastLayers = -5;
    static const int kAllLayers = -1;

    static Vector3  get_gravity();
    static void     set_gravity(const Vector3 v);
    static float    get_minPenetrationForPenalty();
    static void     set_minPenetrationForPenalty(float v);
    static float    get_bounceThreshold();
    static void     set_bounceThreshold(float v);
    static float    get_sleepVelocity();
    static void     set_sleepVelocity(float v);
    static float    get_sleepAngularVelocity();
    static void     set_sleepAngularVelocity(float v);
    static float    get_maxAngularVelocity();
    static void     set_maxAngularVelocity(float v);
    static int      get_solverIterationCount();
    static void     set_solverIterationCount(int v);

    static bool CheckCapsule(const Vector3 &start, const Vector3 &end, float radius, int layermask = DefaultRaycastLayers);
    static bool CheckSphere(const Vector3 &position, float radius, int layerMask = DefaultRaycastLayers);
    static bool Raycast(const Ray &ray, RaycastHit &hitInfo, float distance = FLT_MAX, int layerMask = DefaultRaycastLayers);
    static bool CapsuleCast(const Vector3 &point1, const Vector3 &point2, float radius, const Vector3 &direction, RaycastHit &hitInfo, float distance = FLT_MAX, int layerMask = DefaultRaycastLayers);
    static bool Linecast(const Vector3 &start, const Vector3 &end, RaycastHit &hitInfo, int layerMask = DefaultRaycastLayers);
    static bool SphereCast(const Ray &ray, float radius, RaycastHit &hitInfo, float distance = FLT_MAX, int layerMask = DefaultRaycastLayers);
    static cpsTArray<Collider>   OverlapSphere(const Vector3 &position, float radius, int layerMask = AllLayers);
    static cpsTArray<RaycastHit> RaycastAll(const Ray &ray, float distance = FLT_MAX, int layerMask = DefaultRaycastLayers);
    static cpsTArray<RaycastHit> SphereCastAll(const Ray &ray, float radius, float distance = FLT_MAX, int layerMask = DefaultRaycastLayers);
    static cpsTArray<RaycastHit> CapsuleCastAll(const Vector3 &point1, const Vector3 &point2, float radius, const Vector3 &direction, float distance = FLT_MAX, int layermask = DefaultRaycastLayers);
    static bool GetIgnoreLayerCollision(int layer1, int layer2);
    static void IgnoreCollision(Collider collider1, Collider collider2, bool ignore = true);
    static void IgnoreLayerCollision(int layer1, int layer2, bool ignore = true);
};

class cpsAPI Physics2D
{
public:
    cpsDeclTraits();
};


class cpsAPI Resources
{
public:
    cpsDeclTraits();

    template<class T>
    static cpsTArray<T> FindObjectsOfTypeAll()
    {
        static cpsCachedMethod s_generics;
        static cpsCachedMethod s_method;
        if (!s_generics) {
            cpsClass tparams[] = { cpsTypeinfo<T>() };
            s_generics = cpsTypeinfo<Resources>().getClass().findMethod("FindObjectsOfTypeAll", 0);
            s_method = s_generics.instantiate(tparams, 1);
        }
        return cpsTArray<T>(s_method.invoke(nullptr));
    }

    static cpsObject Load(cpsString path);
    static cpsTArray<cpsObject> LoadAll(cpsString path);
    //static Object LoadAssetAtPath(cpsString assetPath, Type type);
    static ResourceRequest LoadAsync(cpsString path);
    static void UnloadAsset(Object assetToUnload);
    static AsyncOperation UnloadUnusedAssets();
};

class cpsAPI Time
{
public:
    cpsDeclTraits();
    static int      get_captureFramerate();
    static void     set_captureFramerate(int v);
    static float    get_deltaTime();
    static float    get_fixedDeltaTime();
    static void     set_fixedDeltaTime(float v);
    static float    get_fixedTime();
    static int      get_frameCount();
    static float    get_maximumDeltaTime();
    static void     set_maximumDeltaTime(float v);
    static float    get_realtimeSinceStartup();
    static int      get_renderedFrameCount();
    static float    get_smoothDeltaTime();
    static float    get_time();
    static float    get_timeScale();
    static void     set_timeScale(float v);
    static float    get_timeSinceLevelLoad();
    static float    get_unscaledDeltaTime();
    static float    get_unscaledTime();
};

class Profiler
{

public:
    cpsDeclTraits();

    static bool         get_enableBinaryLog();
    static void         set_enableBinaryLog(bool v);
    static bool         get_enabled();
    static void         set_enabled(bool v);
    static cpsString    get_logFile();
    static void         set_logFile(cpsString v);
    static bool         get_supported();
    static void         set_supported(bool v);
    static uint32_t     get_usedHeapSize();

    static void         AddFramesFromFile(cpsString file);
    static void         BeginSample(cpsString name, Object targetObject);
    static void         BeginSample(cpsString name);
    static void         EndSample();
    static uint32_t     GetMonoHeapSize();
    static uint32_t     GetMonoUsedSize();
    static int          GetRuntimeMemorySize(Object o);
    static uint32_t     GetTotalAllocatedMemory();
    static uint32_t     GetTotalReservedMemory();
    static uint32_t     GetTotalUnusedReservedMemory();
};

} // namespace UnityEngine


cpsDeclTraitsF(UnityEngine, Space)
cpsDeclTraitsF(UnityEngine, SendMessageOptions)
cpsDeclTraitsF(UnityEngine, HideFlags)
cpsDeclTraitsF(UnityEngine, MeshTopology)
cpsDeclTraitsF(UnityEngine, CubemapFace)
cpsDeclTraitsF(UnityEngine, ComputeBufferType)
cpsDeclTraitsF(UnityEngine, CollisionDetectionMode)
cpsDeclTraitsF(UnityEngine, RigidbodyConstraints)
cpsDeclTraitsF(UnityEngine, RigidbodyInterpolation)
cpsDeclTraitsF(UnityEngine, ForceMode)

#endif // cpsUnityEngine_h
