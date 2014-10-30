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

class cpsAPI Mesh : public Object
{
typedef Object super;
public:
    cpsDeclTraits();
    Mesh(cpsObject v = nullptr);
};

class cpsAPI Material : public Object
{
typedef Object super;
public:
    cpsDeclTraits();
    Material(cpsObject v = nullptr);
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

    //Rigidbody::SetDensity(System.Single) : System.Void
    //Rigidbody::AddForce(UnityEngine.Vector3, UnityEngine.ForceMode) : System.Void
    //Rigidbody::AddForce(UnityEngine.Vector3) : System.Void
    //Rigidbody::AddForce(System.Single, System.Single, System.Single) : System.Void
    //Rigidbody::AddForce(System.Single, System.Single, System.Single, UnityEngine.ForceMode) : System.Void
    //Rigidbody::AddRelativeForce(UnityEngine.Vector3, UnityEngine.ForceMode) : System.Void
    //Rigidbody::AddRelativeForce(UnityEngine.Vector3) : System.Void
    //Rigidbody::AddRelativeForce(System.Single, System.Single, System.Single) : System.Void
    //Rigidbody::AddRelativeForce(System.Single, System.Single, System.Single, UnityEngine.ForceMode) : System.Void
    //Rigidbody::AddTorque(UnityEngine.Vector3, UnityEngine.ForceMode) : System.Void
    //Rigidbody::AddTorque(UnityEngine.Vector3) : System.Void
    //Rigidbody::AddTorque(System.Single, System.Single, System.Single) : System.Void
    //Rigidbody::AddTorque(System.Single, System.Single, System.Single, UnityEngine.ForceMode) : System.Void
    //Rigidbody::AddRelativeTorque(UnityEngine.Vector3, UnityEngine.ForceMode) : System.Void
    //Rigidbody::AddRelativeTorque(UnityEngine.Vector3) : System.Void
    //Rigidbody::AddRelativeTorque(System.Single, System.Single, System.Single) : System.Void
    //Rigidbody::AddRelativeTorque(System.Single, System.Single, System.Single, UnityEngine.ForceMode) : System.Void
    //Rigidbody::AddForceAtPosition(UnityEngine.Vector3, UnityEngine.Vector3, UnityEngine.ForceMode) : System.Void
    //Rigidbody::AddForceAtPosition(UnityEngine.Vector3, UnityEngine.Vector3) : System.Void
    //Rigidbody::AddExplosionForce(System.Single, UnityEngine.Vector3, System.Single, System.Single, UnityEngine.ForceMode) : System.Void
    //Rigidbody::AddExplosionForce(System.Single, UnityEngine.Vector3, System.Single, System.Single) : System.Void
    //Rigidbody::AddExplosionForce(System.Single, UnityEngine.Vector3, System.Single) : System.Void
    //Rigidbody::ClosestPointOnBounds(UnityEngine.Vector3) : UnityEngine.Vector3
    //Rigidbody::GetRelativePointVelocity(UnityEngine.Vector3) : UnityEngine.Vector3
    //Rigidbody::GetPointVelocity(UnityEngine.Vector3) : UnityEngine.Vector3
    //Rigidbody::MovePosition(UnityEngine.Vector3) : System.Void
    //Rigidbody::MoveRotation(UnityEngine.Quaternion) : System.Void
    //Rigidbody::Sleep() : System.Void
    //Rigidbody::IsSleeping() : System.Boolean
    //Rigidbody::WakeUp() : System.Void
    //Rigidbody::SweepTest(UnityEngine.Vector3, UnityEngine.RaycastHit&, System.Single) : System.Boolean
    //Rigidbody::SweepTest(UnityEngine.Vector3, UnityEngine.RaycastHit&) : System.Boolean
    //Rigidbody::SweepTestAll(UnityEngine.Vector3, System.Single) : UnityEngine.RaycastHit[]
    //Rigidbody::SweepTestAll(UnityEngine.Vector3) : UnityEngine.RaycastHit[]
    //Rigidbody::SetMaxAngularVelocity(System.Single) : System.Void
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







class cpsAPI Application
{
public:
    cpsDeclTraits();
    static cpsString    get_dataPath();
    static bool         get_isEditor();
};


class cpsAPI Debug
{
public:
    cpsDeclTraits();
    static void Log(cpsString message);
    static void Log(cpsString message, cpsObject obj);
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


} // namespace cpsUnityEngine


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
