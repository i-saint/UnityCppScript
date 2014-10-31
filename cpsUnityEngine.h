#ifndef cpsUnityEngine_h
#define cpsUnityEngine_h

#include "cpsTypes.h"
#include <vector>

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



struct cpsAPI Vector2
{
    cpsDeclTraits();
    static const Vector2 zero;
    static const Vector2 one;

    union {
        struct { float x, y; };
        float v[2];
    };
    Vector2(float a = 0.0f, float b = 0.0f) : x(a), y(b){}
};

struct cpsAPI Vector3
{
    cpsDeclTraits();
    static const Vector3 zero;
    static const Vector3 one;
    static const Vector3 up;

    union {
        struct { float x, y, z; };
        float v[3];
    };
    Vector3(float a = 0.0f, float b = 0.0f, float c = 0.0f) : x(a), y(b), z(c){}
};

struct cpsAPI Vector4
{
    cpsDeclTraits();
    static const Vector4 zero;
    static const Vector4 one;

    union {
        struct { float x, y, z, w; };
        float v[4];
    };
    Vector4(float a = 0.0f, float b = 0.0f, float c = 0.0f, float d = 0.0f) : x(a), y(b), z(c), w(d){}
};

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

class cpsAPI PhysicMaterial2D : public Object
{
typedef Object super;
public:
    cpsDeclTraits();
    PhysicMaterial2D(cpsObject v = nullptr);
};





class cpsAPI GameObject : public Object
{
typedef Object super;
public:
    cpsDeclTraits();
    GameObject(cpsObject v = nullptr);
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


class cpsAPI Collider2D : public Behaviour
{
typedef Behaviour super;
public:
    cpsDeclTraits();
    Collider2D(cpsObject obj = nullptr);
};


class cpsAPI Camera : public Component
{
typedef Component super;
public:
    cpsDeclTraits();
    Camera(cpsObject obj = nullptr);
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
