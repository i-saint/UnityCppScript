#ifndef cpsUnityEngine_h
#define cpsUnityEngine_h

#include "cpsTypes.h"
#include <vector>

namespace cpsUnityEngine
{

cpsAPI cpsImage& GetImage();

enum Space {
    World = 0,
    Self = 1,
};

enum SendMessageOptions
{
    RequireReceiver,
    DontRequireReceiver
};

enum HideFlags
{
    None = 0,
    HideInHierarchy = 1,
    HideInInspector = 2,
    DontSaveInScene = 4,
    NotEditable = 8,
    DontUnload = 16,
    DontSaveInBuild = 32,
    DontSave = 52,
    HideAndDontSave = 61
};



struct cpsAPI Vector2
{
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
    static const Vector4 zero;
    static const Vector4 one;

    union {
        struct { float x, y, z, w; };
        float v[4];
    };
    Vector4(float a = 0.0f, float b = 0.0f, float c = 0.0f, float d = 0.0f) : x(a), y(b), z(c), w(d){}
};

struct cpsAPI Quaternion
{
    static const Quaternion identity;

    union {
        struct { float x, y, z, w; };
        float v[4];
    };
    Quaternion(float a = 0.0f, float b = 0.0f, float c = 0.0f, float d = 0.0f) : x(a), y(b), z(c), w(d){}
};

struct cpsAPI Matrix4x4
{
    static const Matrix4x4 identity;

    union {
        float v[16];
    };
    Matrix4x4() {}
};



struct cpsAPI Bounds
{
    Vector3 center;
    Vector3 extents;
};

struct cpsAPI Ray
{
    Vector3 direction;
    Vector3 origin;
};

struct cpsAPI Ray2D
{
    Vector2 direction;
    Vector2 origin;
};

struct cpsAPI RaycastHit
{
    float       distance;
    Vector2     uv;
    cpsObject   collider; // Collider
    Vector3     point;
    Vector3     normal;
    int         faceID;
};

struct cpsAPI RaycastHit2D
{
    float       distance;
    float       fraction;
    cpsObject   collider; // Collider2D
    Vector2     centroid;
    Vector2     point;
    Vector2     normal;
};




class cpsAPI Application
{
public:
    static cpsClass     getClass();
    static cpsString    get_dataPath();
    static bool         get_isEditor();
};


class cpsAPI Debug
{
public:
    static cpsClass getClass();
    static void Log(cpsString message);
    static void Log(cpsString message, cpsObject obj);
};


class cpsAPI GL
{
public:
    static cpsClass getClass();
};


class cpsAPI GUI
{
public:
    static cpsClass getClass();
};


class cpsAPI Graphics
{
public:
    static cpsClass getClass();
};

class cpsAPI Physics
{
public:
    static cpsClass getClass();
};




class cpsAPI Object : public cpsObject
{
typedef cpsObject super;
public:
    static cpsClass getClass();

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


class cpsAPI Texture : public Object
{
typedef Object super;
public:
    static cpsClass getClass();
    Texture(cpsObject v = nullptr);
};


class cpsAPI RenderTexture : public Object
{
typedef Object super;
public:
    static cpsClass getClass();
    RenderTexture(cpsObject = nullptr);
};


class cpsAPI ComputeBuffer : public Object
{
typedef Object super;
public:
    static cpsClass getClass();
    ComputeBuffer(cpsObject = nullptr);
};

class cpsAPI PhysicMaterial : public Object
{
typedef Object super;
public:
    static cpsClass getClass();
    PhysicMaterial(cpsObject v = nullptr);
};

class cpsAPI PhysicMaterial2D : public Object
{
typedef Object super;
public:
    static cpsClass getClass();
    PhysicMaterial2D(cpsObject v = nullptr);
};





class cpsAPI GameObject : public Object
{
typedef Object super;
public:
    static cpsClass getClass();
    GameObject(cpsObject v = nullptr);
};

class cpsAPI Component : public Object
{
typedef Object super;
public:
    static cpsClass getClass();
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
            s_generics = mobj.getClass().findMethod("GetComponent", 0);
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
            s_generics = mobj.getClass().findMethod("GetComponents", 0);
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
            s_generics = mobj.getClass().findMethod("GetComponentInChildren", 0);
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
            s_generics = mobj.getClass().findMethod("GetComponentsInChildren", 0);
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
            s_generics = mobj.getClass().findMethod("GetComponentInParent", 0);
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
            s_generics = mobj.getClass().findMethod("GetComponentsInParent", 0);
            s_method = s_generics.instantiate(tparams, 1);
        }
        return cpsTArray<ComponentT>(s_method.invoke(mobj));
    }

    bool CompareTag(cpsString tag);
    void SendMessageUpwards(cpsString method_name, cpsObject obj = nullptr, SendMessageOptions opt = RequireReceiver);
    void SendMessage(cpsString method_name, cpsObject obj = nullptr, SendMessageOptions opt = RequireReceiver);
    void BroadcastMessage(cpsString method_name, cpsObject obj = nullptr, SendMessageOptions opt = RequireReceiver);
};

class cpsAPI Behaviour : public Component
{
typedef Component super;
public:
    static cpsClass getClass();
    Behaviour(cpsObject obj = nullptr);
    bool get_enabled() const;
    void set_enabled(bool v);
};


class cpsAPI Transform : public Component
{
typedef Component super;
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

    void        Translate(const Vector3& v, Space s = Self);
    void        Translate(const Vector3& v, Transform relative);
    void        Rotate(const Vector3& eulerAngles, Space s = Self);
    void        Rotate(const Vector3& axis, float angle, Space s = Self);
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
    static cpsClass getClass();
    Rigidbody(cpsObject obj = nullptr);
};


class cpsAPI Rigidbody2D : public Component
{
typedef Component super;
public:
    static cpsClass getClass();
    Rigidbody2D(cpsObject obj = nullptr);
};


class cpsAPI Collider : public Component
{
typedef Component super;
public:
    static cpsClass getClass();
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
    static cpsClass getClass();
    Collider2D(cpsObject obj = nullptr);
};


class cpsAPI Camera : public Component
{
typedef Component super;
public:
    static cpsClass getClass();
    Camera(cpsObject obj = nullptr);
};


class cpsAPI Light : public Component
{
typedef Component super;
public:
    static cpsClass getClass();
    Light(cpsObject obj = nullptr);
};


} // namespace cpsUnityEngine
#endif // cpsUnityEngine_h
