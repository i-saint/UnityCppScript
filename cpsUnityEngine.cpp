#include "cpsInternal.h"
#include "cpsUtils.h"
#include "cpsUnityEngine.h"


#define cpsBindClass(...)\
    static cpsCachedClass s_class;\
    if (!s_class) { s_class = GetImage().findClass(__VA_ARGS__); }\
    return s_class;

#define cpsBindMethod(...)\
    static cpsCachedMethod s_method;\
    if (!s_method) { s_method = getClass().findMethod(__VA_ARGS__); }


namespace UnityEngine
{

const Vector2 Vector2::zero = Vector2(0.0f, 0.0f);
const Vector2 Vector2::one = Vector2(1.0f, 1.0f);

const Vector3 Vector3::zero = Vector3(0.0f, 0.0f, 0.0f);
const Vector3 Vector3::one = Vector3(1.0f, 1.0f, 1.0f);
const Vector3 Vector3::up = Vector3(0.0f, 1.0f, 0.0f);

const Vector4 Vector4::zero = Vector4(0.0f, 0.0f, 0.0f, 0.0f);
const Vector4 Vector4::one = Vector4(1.0f, 1.0f, 1.0f, 1.0f);



cpsAPI cpsImage& GetImage()
{
    static cpsCachedImage s_image;
    if (!s_image) { s_image = cpsImage::findImage("UnityEngine"); }
    return s_image;
}


cpsImplTraits(UnityEngine, Vector2);
cpsImplTraits(UnityEngine, Vector3);
cpsImplTraits(UnityEngine, Vector4);
cpsImplTraits(UnityEngine, Color);
cpsImplTraits(UnityEngine, Color32);
cpsImplTraits(UnityEngine, Quaternion);
cpsImplTraits(UnityEngine, Matrix4x4);

cpsImplTraits(UnityEngine, Rect);
cpsImplTraits(UnityEngine, Bounds);
cpsImplTraits(UnityEngine, Ray);
cpsImplTraits(UnityEngine, Ray2D);
cpsImplTraits(UnityEngine, RaycastHit);
cpsImplTraits(UnityEngine, RaycastHit2D);

cpsImplTraits(UnityEngine, RenderBuffer);



cpsImplTraits(UnityEngine, Object);

Object::Object(cpsObject v) : super(v) {}

cpsString Object::get_name() const
{
    cpsBindMethod("get_name");
    return cpsString(s_method.invoke(*this));
}
void Object::set_name(cpsString name)
{
    cpsBindMethod("set_name");
    void *args[] = { name };
    s_method.invoke(*this, args);
}
HideFlags Object::get_hideFlags() const
{
    cpsBindMethod("get_hideFlags");
    return s_method.invoke(*this).getData<HideFlags>();
}
void Object::set_hideFlags(HideFlags flags)
{
    cpsBindMethod("set_hideFlags");
    void *args[] = { &flags };
    s_method.invoke(*this, args);
}
void* Object::obj_address() const
{
    cpsBindMethod("obj_address");
    return s_method.invoke(*this).getData<void*>();
}

int Object::GetInstanceID() const
{
    cpsBindMethod("GetInstanceID");
    return s_method.invoke(*this).getData<int>();
}
cpsString Object::ToString() const
{
    cpsBindMethod("ToString");
    return cpsString(s_method.invoke(*this));
}

/*static*/ Object Object::Instantiate(Object original, const Vector3 &position, const Quaternion &rotation)
{
    cpsBindMethod("Instantiate", 3);
    void *args[] = { original, (void*)&position, (void*)&rotation };
    return s_method.invoke(nullptr, args).getData<MonoObject*>();
}
/*static*/ Object Object::Instantiate(Object original)
{
    cpsBindMethod("Instantiate", 1);
    void *args[] = { original };
    return s_method.invoke(nullptr, args).getData<MonoObject*>();
}
/*static*/ void Object::Destroy(cpsObject obj, float delay)
{
    cpsBindMethod("Destroy", 2);
    void *args[] = { obj, &delay };
    s_method.invoke(nullptr, args);
}
/*static*/ void Object::DestroyImmediate(Object obj, bool allowDestroyingAssets)
{
    cpsBindMethod("DestroyImmediate", 2);
    gboolean b = allowDestroyingAssets;
    void *args[] = { obj, &b };
    s_method.invoke(nullptr, args);
}
/*static*/ void Object::DontDestroyOnLoad(Object obj)
{
    cpsBindMethod("DontDestroyOnLoad", 1);
    void *args[] = { obj };
    s_method.invoke(nullptr, args);
}
/*static*/ void Object::DestroyObject(Object obj, float delay)
{
    cpsBindMethod("DestroyObject", 2);
    void *args[] = { obj, &delay };
    s_method.invoke(nullptr, args);
}



cpsImplTraits(UnityEngine, Mesh);
Mesh::Mesh(cpsObject v) : super(v) {}

cpsImplTraits(UnityEngine, Material);
Material::Material(cpsObject v) : super(v) {}

cpsImplTraits(UnityEngine, MaterialPropertyBlock);
MaterialPropertyBlock::MaterialPropertyBlock(cpsObject v) : super(v) {}

cpsImplTraits(UnityEngine, Shader);
Shader::Shader(cpsObject v) : super(v) {}

cpsImplTraits(UnityEngine, Texture);
Texture::Texture(cpsObject v) : super(v) {}

cpsImplTraits(UnityEngine, Texture2D);
Texture2D::Texture2D(cpsObject v) : super(v) {}

cpsImplTraits(UnityEngine, RenderTexture);
RenderTexture::RenderTexture(cpsObject v) : super(v) {}



cpsImplTraits(UnityEngine, ComputeBuffer);
/*static*/ ComputeBuffer ComputeBuffer::create(int count, int stride)
{
    cpsBindMethod(".ctor", 2);
    ComputeBuffer ret(cpsObject::create(getClass()));
    void *args[] = { &count, &stride };
    s_method.invoke(ret, args);
    return ret;

}
/*static*/ ComputeBuffer ComputeBuffer::create(int count, int stride, ComputeBufferType type)
{
    cpsBindMethod(".ctor", 3);
    ComputeBuffer ret(cpsObject::create(getClass()));
    void *args[] = { &count, &stride, &type };
    s_method.invoke(ret, args);
    return ret;
}

ComputeBuffer::ComputeBuffer(cpsObject v) : super(v) {}
int ComputeBuffer::get_count()
{
    cpsBindMethod("get_count", 0);
    cpsObject ret = s_method.invoke(*this);
    return ret.getData<int>();
}
int ComputeBuffer::get_stride()
{
    cpsBindMethod("get_stride", 0);
    cpsObject ret = s_method.invoke(*this);
    return ret.getData<int>();
}
void ComputeBuffer::Dispose()
{
    cpsBindMethod("Dispose", 0);
    s_method.invoke(*this);
}
void ComputeBuffer::Release()
{
    cpsBindMethod("Release", 0);
    s_method.invoke(*this);
}
void ComputeBuffer::SetData(cpsArray a)
{
    cpsBindMethod("SetData", 1);
    void *args[] = { a };
    s_method.invoke(*this, args);
}
void ComputeBuffer::GetData(cpsArray a)
{
    cpsBindMethod("GetData", 1);
    void *args[] = { a };
    s_method.invoke(*this, args);
}

/*static*/ void ComputeBuffer::CopyCount(ComputeBuffer src, ComputeBuffer dst, int count)
{
    cpsBindMethod("CopyCount", 3);
    void *args[] = { src, dst, &count };
    s_method.invoke(nullptr, args);
}




cpsImplTraits(UnityEngine, PhysicMaterial);
PhysicMaterial::PhysicMaterial(cpsObject v) : super(v) {}



cpsImplTraits(UnityEngine, PhysicMaterial2D);
PhysicMaterial2D::PhysicMaterial2D(cpsObject v) : super(v) {}



cpsImplTraits(UnityEngine, GameObject);
GameObject::GameObject(cpsObject v) : super(v) {}



cpsImplTraits(UnityEngine, Behaviour);
Behaviour::Behaviour(cpsObject obj) : super(obj) {}

bool Behaviour::get_enabled() const
{
    cpsBindMethod("get_enabled");
    return s_method.invoke(*this).getData<gboolean>() != 0;
}
void Behaviour::set_enabled(bool v)
{
    cpsBindMethod("set_enabled");
    gboolean b = v;
    void *args[] = { &b };
    s_method.invoke(*this, args);
}



cpsImplTraits(UnityEngine, Component);
Component::Component(cpsObject obj) : super(obj) {}

GameObject Component::get_gameObject() const
{
    cpsBindMethod("get_gameObject");
    return s_method.invoke(*this).getData<MonoObject*>();
}
bool Component::get_active() const
{
    cpsBindMethod("get_active");
    return s_method.invoke(*this).getData<gboolean>()!=0;
}
void Component::set_active(bool v)
{
    cpsBindMethod("set_active");
    gboolean b = v;
    void *args[] = { &b };
    s_method.invoke(*this, args);
}
cpsString Component::get_tag() const
{
    cpsBindMethod("get_tag");
    return cpsString(s_method.invoke(*this));
}
void Component::set_tag(cpsString v)
{
    cpsBindMethod("set_tag");
    void *args[] = { v };
    s_method.invoke(*this, args);
}

bool Component::CompareTag(cpsString v)
{
    cpsBindMethod("CompareTag", 1);
    void *args[] = { v };
    return s_method.invoke(*this, args).getData<gboolean>()!=0;
}

void Component::SendMessageUpwards(cpsString method_name, cpsObject obj, SendMessageOptions opt)
{
    cpsBindMethod("SendMessageUpwards", 3);
    void *args[] = { method_name, obj, &opt };
    s_method.invoke(*this, args);
}

void Component::SendMessage(cpsString method_name, cpsObject obj, SendMessageOptions opt)
{
    cpsBindMethod("SendMessage", 3);
    void *args[] = { method_name, obj, &opt };
    s_method.invoke(*this, args);
}

void Component::BroadcastMessage(cpsString method_name, cpsObject obj, SendMessageOptions opt)
{
    cpsBindMethod("BroadcastMessage", 3);
    void *args[] = { method_name, obj, &opt };
    s_method.invoke(*this, args);
}




cpsImplTraits(UnityEngine, Transform);
Transform::Transform(cpsObject obj) : super(obj) {}

Vector3 Transform::get_position() const
{
    cpsBindMethod("get_position");
    return s_method.invoke(*this).getData<Vector3>();
}
void Transform::set_position(const Vector3& v)
{
    cpsBindMethod("set_position");
    void *args[] = { (void*)&v };
    s_method.invoke(*this, args);
}

Vector3 Transform::get_localPosition() const
{
    cpsBindMethod("get_localPosition");
    return s_method.invoke(*this).getData<Vector3>();
}
void Transform::set_localPosition(const Vector3& v)
{
    cpsBindMethod("set_localPosition");
    void *args[] = { (void*)&v };
    s_method.invoke(*this, args);
}

Vector3 Transform::get_eulerAngles() const
{
    cpsBindMethod("get_eulerAngles");
    return s_method.invoke(*this).getData<Vector3>();
}
void Transform::set_eulerAngles(const Vector3& v)
{
    cpsBindMethod("set_eulerAngles");
    void *args[] = { (void*)&v };
    s_method.invoke(*this, args);
}

Vector3 Transform::get_right() const
{
    cpsBindMethod("get_right");
    return s_method.invoke(*this).getData<Vector3>();
}
void Transform::set_right(const Vector3& v)
{
    cpsBindMethod("set_right");
    void *args[] = { (void*)&v };
    s_method.invoke(*this, args);
}

Vector3 Transform::get_up() const
{
    cpsBindMethod("get_up");
    return s_method.invoke(*this).getData<Vector3>();
}
void Transform::set_up(const Vector3& v)
{
    cpsBindMethod("set_up");
    void *args[] = { (void*)&v };
    s_method.invoke(*this, args);
}

Vector3 Transform::get_forward() const
{
    cpsBindMethod("get_forward");
    return s_method.invoke(*this).getData<Vector3>();
}
void Transform::set_forward(const Vector3& v)
{
    cpsBindMethod("set_forward");
    void *args[] = { (void*)&v };
    s_method.invoke(*this, args);
}

Quaternion Transform::get_rotation() const
{
    cpsBindMethod("get_rotation");
    return s_method.invoke(*this).getData<Quaternion>();
}
void Transform::set_rotation(const Quaternion &v)
{
    cpsBindMethod("set_rotation");
    void *args[] = { (void*)&v };
    s_method.invoke(*this, args);
}

Quaternion Transform::get_localRotation() const
{
    cpsBindMethod("get_localRotation");
    return s_method.invoke(*this).getData<Quaternion>();
}
void Transform::set_localRotation(const Quaternion &v)
{
    cpsBindMethod("set_localRotation");
    void *args[] = { (void*)&v };
    s_method.invoke(*this, args);
}

Vector3 Transform::get_localScale() const
{
    cpsBindMethod("get_localScale");
    return s_method.invoke(*this).getData<Vector3>();
}
void Transform::set_localScale(const Vector3& v)
{
    cpsBindMethod("set_localScale");
    void *args[] = { (void*)&v };
    s_method.invoke(*this, args);
}

Transform Transform::get_parent() const
{
    cpsBindMethod("get_parent");
    return s_method.invoke(*this);
}
void Transform::set_parent(const Transform &v)
{
    cpsBindMethod("set_parent");
    void *args[] = { (void*)v };
    s_method.invoke(*this, args);
}

Matrix4x4 Transform::get_worldToLocalMatrix() const
{
    cpsBindMethod("get_worldToLocalMatrix");
    return s_method.invoke(*this).getData<Matrix4x4>();
}
Matrix4x4 Transform::get_localToWorldMatrix() const
{
    cpsBindMethod("get_localToWorldMatrix");
    return s_method.invoke(*this).getData<Matrix4x4>();
}

Transform Transform::get_root()
{
    cpsBindMethod("get_root");
    return s_method.invoke(*this);
}
int Transform::get_childCount()
{
    cpsBindMethod("get_childCount");
    return s_method.invoke(*this).getData<int>();
}
Vector3 Transform::get_lossyScale()
{
    cpsBindMethod("get_lossyScale");
    return s_method.invoke(*this).getData<Vector3>();
}

bool Transform::get_hasChanged()
{
    cpsBindMethod("get_hasChanged");
    return s_method.invoke(*this).getData<gboolean>()!=0;
}
void Transform::set_hasChanged(bool v)
{
    cpsBindMethod("set_hasChanged");
    gboolean b = v;
    void *args[] = {&b};
    s_method.invoke(*this, args);
}


void Transform::Translate(const Vector3& v, Space s)
{
    static const char *typenames[] = { cpsTypename<Vector3>(), cpsTypename<Space>() };
    cpsBindMethod("Translate", 2, typenames);
    void *args[] = { (void*)&v, &s };
    s_method.invoke(*this, args);
}
void Transform::Translate(const Vector3& v, Transform relative)
{
    static const char *typenames[] = { cpsTypename<Vector3>(), cpsTypename<Transform>() };
    cpsBindMethod("Translate", 2, typenames);
    void *args[] = { (void*)&v, relative.mobj };
    s_method.invoke(*this, args);
}

void Transform::Rotate(const Vector3& eulerAngles, Space s)
{
    static const char *typenames[] = { cpsTypename<Vector3>(), cpsTypename<Space>() };
    cpsBindMethod("Rotate", 2, typenames);
    void *args[] = { (void*)&eulerAngles, &s };
    s_method.invoke(*this, args);
}
void Transform::Rotate(const Vector3& axis, float angle, Space s)
{
    static const char *typenames[] = { cpsTypename<Vector3>(), cpsTypename<float>(), cpsTypename<Space>() };
    cpsBindMethod("Rotate", 3, typenames);
    void *args[] = { (void*)&axis, &angle, &s };
    s_method.invoke(*this, args);
}
void Transform::RotateAround(const Vector3& point, const Vector3& axis, float angle)
{
    static const char *typenames[] = { cpsTypename<Vector3>(), cpsTypename<Vector3>(), cpsTypename<float>() };
    cpsBindMethod("RotateAround", 3, typenames);
    void *args[] = { (void*)&point, (void*)&axis, &angle };
    s_method.invoke(*this, args);
}

void Transform::LookAt(Transform t, const Vector3& up)
{
    static const char *typenames[] = { cpsTypename<Transform>(), cpsTypename<Vector3>() };
    cpsBindMethod("LookAt", 2, typenames);
    void *args[] = { t.mobj, (void*)&up };
    s_method.invoke(*this, args);
}
void Transform::LookAt(const Vector3& worldPos, const Vector3&up)
{
    static const char *typenames[] = { cpsTypename<Vector3>(), cpsTypename<Vector3>() };
    cpsBindMethod("LookAt", 2, typenames);
    void *args[] = { (void*)&worldPos, (void*)&up };
    s_method.invoke(*this, args);
}

Vector3 Transform::TransformDirection(const Vector3& v)
{
    cpsBindMethod("TransformDirection", 1);
    void *args[] = { (void*)&v };
    return s_method.invoke(*this, args).getData<Vector3>();
}

Vector3 Transform::InverseTransformDirection(const Vector3& v)
{
    cpsBindMethod("InverseTransformDirection", 1);
    void *args[] = { (void*)&v };
    return s_method.invoke(*this, args).getData<Vector3>();
}

Vector3 Transform::TransformPoint(const Vector3& v)
{
    cpsBindMethod("TransformPoint", 1);
    void *args[] = { (void*)&v };
    return s_method.invoke(*this, args).getData<Vector3>();
}

Vector3 Transform::InverseTransformPoint(const Vector3& v)
{
    cpsBindMethod("InverseTransformPoint", 1);
    void *args[] = { (void*)&v };
    return s_method.invoke(*this, args).getData<Vector3>();
}

void Transform::DetachChildren()
{
    cpsBindMethod("DetachChildren", 0);
    s_method.invoke(*this);
}

void Transform::SetAsFirstSibling()
{
    cpsBindMethod("SetAsFirstSibling", 0);
    s_method.invoke(*this);
}

void Transform::SetAsLastSibling()
{
    cpsBindMethod("SetAsLastSibling", 0);
    s_method.invoke(*this);
}

void Transform::SetSiblingIndex(int i)
{
    cpsBindMethod("SetAsLastSibling", 1);
    void *args[] = { (void*)&i };
    s_method.invoke(*this, args);
}

int Transform::GetSiblingIndex()
{
    cpsBindMethod("GetSiblingIndex", 0);
    return s_method.invoke(*this).getData<int>();;
}

Transform Transform::Find(cpsString name)
{
    cpsBindMethod("Find", 1);
    void *args[] = { name };
    return s_method.invoke(*this, args).getData<MonoObject*>();
}

void Transform::SendTransformChangedScale()
{
    cpsBindMethod("SendTransformChangedScale", 0);
    s_method.invoke(*this);
}

bool Transform::IsChildOf(Transform t)
{
    cpsBindMethod("IsChildOf", 1);
    void *args[] = { t.mobj };
    return s_method.invoke(*this, args).getData<gboolean>()!=0;
}

Transform Transform::FindChild(cpsString name)
{
    cpsBindMethod("FindChild", 1);
    void *args[] = { name };
    return s_method.invoke(*this, args).getData<MonoObject*>();
}

void Transform::RotateAround(const Vector3& axis, float a)
{
    cpsBindMethod("RotateAround", 2);
    void *args[] = { (void*)&axis, &a };
    s_method.invoke(*this, args);
}

void Transform::RotateAroundLocal(const Vector3& axis, float a)
{
    cpsBindMethod("RotateAroundLocal", 2);
    void *args[] = { (void*)&axis, &a };
    s_method.invoke(*this, args);
}

Transform Transform::GetChild(int i)
{
    cpsBindMethod("GetChild", 1);
    void *args[] = { &i };
    return s_method.invoke(*this, args).getData<MonoObject*>();
}

int Transform::GetChildCount()
{
    cpsBindMethod("GetChildCount", 0);
    return s_method.invoke(*this).getData<int>();
}

bool Transform::IsNonUniformScaleTransform()
{
    cpsBindMethod("IsNonUniformScaleTransform", 0);
    return s_method.invoke(*this).getData<gboolean>()!=0;
}



cpsImplTraits(UnityEngine, Rigidbody);
Rigidbody::Rigidbody(cpsObject obj) : super(obj) {}

float Rigidbody::get_angularDrag()
{
    cpsBindMethod("get_angularDrag");
    return s_method.invoke(*this).getData<float>();
}
void Rigidbody::set_angularDrag(float v)
{
    cpsBindMethod("set_angularDrag");
    void *args[] = { (void*)&v };
    s_method.invoke(*this, args);
}
Vector3 Rigidbody::get_angularVelocity()
{
    cpsBindMethod("get_angularVelocity");
    return s_method.invoke(*this).getData<Vector3>();
}
void Rigidbody::set_angularVelocity(const Vector3 &v)
{
    cpsBindMethod("set_angularVelocity");
    void *args[] = { (void*)&v };
    s_method.invoke(*this, args);
}
Vector3 Rigidbody::get_centerOfMass()
{
    cpsBindMethod("get_centerOfMass");
    return s_method.invoke(*this).getData<Vector3>();
}
void Rigidbody::set_centerOfMass(const Vector3 &v)
{
    cpsBindMethod("set_centerOfMass");
    void *args[] = { (void*)&v };
    s_method.invoke(*this, args);
}
CollisionDetectionMode Rigidbody::get_collisionDetectionMode()
{
    cpsBindMethod("get_collisionDetectionMode");
    return s_method.invoke(*this).getData<CollisionDetectionMode>();
}
void Rigidbody::set_collisionDetectionMode(CollisionDetectionMode v)
{
    cpsBindMethod("set_collisionDetectionMode");
    void *args[] = { (void*)&v };
    s_method.invoke(*this, args);
}
RigidbodyConstraints Rigidbody::get_constraints()
{
    cpsBindMethod("get_constraints");
    return s_method.invoke(*this).getData<RigidbodyConstraints>();
}
void Rigidbody::set_constraints(RigidbodyConstraints v)
{
    cpsBindMethod("set_constraints");
    void *args[] = { (void*)&v };
    s_method.invoke(*this, args);
}
bool Rigidbody::get_detectCollisions()
{
    cpsBindMethod("get_detectCollisions");
    return s_method.invoke(*this).getData<gboolean>() != 0;
}
void Rigidbody::set_detectCollisions(bool v_)
{
    cpsBindMethod("set_detectCollisions");
    gboolean v = v_;
    void *args[] = { (void*)&v };
    s_method.invoke(*this, args);
}
float Rigidbody::get_drag()
{
    cpsBindMethod("get_drag");
    return s_method.invoke(*this).getData<float>();
}
void Rigidbody::set_drag(float v)
{
    cpsBindMethod("set_drag");
    void *args[] = { (void*)&v };
    s_method.invoke(*this, args);
}
bool Rigidbody::get_freezeRotation()
{
    cpsBindMethod("get_freezeRotation");
    return s_method.invoke(*this).getData<gboolean>() != 0;
}
void Rigidbody::set_freezeRotation(bool v_)
{
    cpsBindMethod("set_freezeRotation");
    gboolean v = v_;
    void *args[] = { (void*)&v };
    s_method.invoke(*this, args);
}
Vector3 Rigidbody::get_inertiaTensor()
{
    cpsBindMethod("get_inertiaTensor");
    return s_method.invoke(*this).getData<Vector3>();
}
void Rigidbody::set_inertiaTensor(const Vector3 &v)
{
    cpsBindMethod("set_inertiaTensor");
    void *args[] = { (void*)&v };
    s_method.invoke(*this, args);
}
Quaternion Rigidbody::get_inertiaTensorRotation()
{
    cpsBindMethod("get_inertiaTensorRotation");
    return s_method.invoke(*this).getData<Quaternion>();
}
void Rigidbody::set_inertiaTensorRotation(const Quaternion &v)
{
    cpsBindMethod("set_inertiaTensorRotation");
    void *args[] = { (void*)&v };
    s_method.invoke(*this, args);
}
RigidbodyInterpolation Rigidbody::get_interpolation()
{
    cpsBindMethod("get_interpolation");
    return s_method.invoke(*this).getData<RigidbodyInterpolation>();
}
void Rigidbody::set_interpolation(RigidbodyInterpolation v)
{
    cpsBindMethod("set_interpolation");
    void *args[] = { (void*)&v };
    s_method.invoke(*this, args);
}
bool Rigidbody::get_isKinematic()
{
    cpsBindMethod("get_isKinematic");
    return s_method.invoke(*this).getData<gboolean>() != 0;
}
void Rigidbody::set_isKinematic(bool v_)
{
    cpsBindMethod("set_isKinematic");
    gboolean v = v_;
    void *args[] = { (void*)&v };
    s_method.invoke(*this, args);
}
float Rigidbody::get_mass()
{
    cpsBindMethod("get_mass");
    return s_method.invoke(*this).getData<float>();
}
void Rigidbody::set_mass(float v)
{
    cpsBindMethod("set_mass");
    void *args[] = { (void*)&v };
    s_method.invoke(*this, args);
}
float Rigidbody::get_maxAngularVelocity()
{
    cpsBindMethod("get_maxAngularVelocity");
    return s_method.invoke(*this).getData<float>();
}
void Rigidbody::set_maxAngularVelocity(float v)
{
    cpsBindMethod("set_maxAngularVelocity");
    void *args[] = { (void*)&v };
    s_method.invoke(*this, args);
}
Vector3 Rigidbody::get_position()
{
    cpsBindMethod("get_position");
    return s_method.invoke(*this).getData<Vector3>();
}
void Rigidbody::set_position(const Vector3 &v)
{
    cpsBindMethod("set_position");
    void *args[] = { (void*)&v };
    s_method.invoke(*this, args);
}
Quaternion Rigidbody::get_rotation()
{
    cpsBindMethod("get_rotation");
    return s_method.invoke(*this).getData<Quaternion>();
}
void Rigidbody::set_rotation(const Quaternion &v)
{
    cpsBindMethod("set_rotation");
    void *args[] = { (void*)&v };
    s_method.invoke(*this, args);
}
float Rigidbody::get_sleepAngularVelocity()
{
    cpsBindMethod("get_sleepAngularVelocity");
    return s_method.invoke(*this).getData<float>();
}
void Rigidbody::set_sleepAngularVelocity(float v)
{
    cpsBindMethod("set_sleepAngularVelocity");
    void *args[] = { (void*)&v };
    s_method.invoke(*this, args);
}
float Rigidbody::get_sleepVelocity()
{
    cpsBindMethod("get_sleepVelocity");
    return s_method.invoke(*this).getData<float>();
}
void Rigidbody::set_sleepVelocity(float v)
{
    cpsBindMethod("set_sleepVelocity");
    void *args[] = { (void*)&v };
    s_method.invoke(*this, args);
}
int Rigidbody::get_solverIterationCount()
{
    cpsBindMethod("get_solverIterationCount");
    return s_method.invoke(*this).getData<int>();
}
void Rigidbody::set_solverIterationCount(int v)
{
    cpsBindMethod("set_solverIterationCount");
    void *args[] = { (void*)&v };
    s_method.invoke(*this, args);
}
bool Rigidbody::get_useConeFriction()
{
    cpsBindMethod("get_useConeFriction");
    return s_method.invoke(*this).getData<gboolean>() != 0;
}
void Rigidbody::set_useConeFriction(bool v_)
{
    cpsBindMethod("set_useConeFriction");
    gboolean v = v_;
    void *args[] = { (void*)&v };
    s_method.invoke(*this, args);
}
bool Rigidbody::get_useGravity()
{
    cpsBindMethod("get_useGravity");
    return s_method.invoke(*this).getData<gboolean>() != 0;
}
void Rigidbody::set_useGravity(bool v_)
{
    cpsBindMethod("set_useGravity");
    gboolean v = v_;
    void *args[] = { (void*)&v };
    s_method.invoke(*this, args);
}
Vector3 Rigidbody::get_velocity()
{
    cpsBindMethod("get_velocity");
    return s_method.invoke(*this).getData<Vector3>();
}
void Rigidbody::set_velocity(const Vector3 &v)
{
    cpsBindMethod("set_velocity");
    void *args[] = { (void*)&v };
    s_method.invoke(*this, args);
}
Vector3 Rigidbody::get_worldCenterOfMass()
{
    cpsBindMethod("get_worldCenterOfMass");
    return s_method.invoke(*this).getData<Vector3>();
}




cpsImplTraits(UnityEngine, Rigidbody2D);
Rigidbody2D::Rigidbody2D(cpsObject obj) : super(obj) {}



cpsImplTraits(UnityEngine, Collider);
Collider::Collider(cpsObject obj) : super(obj) {}

bool Collider::get_enabled()
{
    cpsBindMethod("get_enabled");
    return s_method.invoke(*this).getData<gboolean>() != 0;
}
void Collider::set_enabled(bool v)
{
    cpsBindMethod("set_enabled");
    gboolean b = v;
    void *args[] = {&b};
    s_method.invoke(*this, args);
}

Rigidbody Collider::get_attachedRigidbody()
{
    cpsBindMethod("get_attachedRigidbody");
    return s_method.invoke(*this).getData<MonoObject*>();
}
bool Collider::get_isTrigger()
{
    cpsBindMethod("get_isTrigger");
    return s_method.invoke(*this).getData<gboolean>() != 0;
}
void Collider::set_isTrigger(bool v)
{
    cpsBindMethod("set_isTrigger");
    gboolean b = v;
    void *args[] = { &b };
    s_method.invoke(*this, args);
}

PhysicMaterial Collider::get_material()
{
    cpsBindMethod("get_material");
    return s_method.invoke(*this).getData<MonoObject*>();
}
void Collider::set_material(PhysicMaterial v)
{
    cpsBindMethod("set_material");
    void *args[] = { v.mobj };
    s_method.invoke(*this, args);
}
PhysicMaterial Collider::get_sharedMaterial()
{
    cpsBindMethod("get_sharedMaterial");
    return s_method.invoke(*this).getData<MonoObject*>();
}
void Collider::set_sharedMaterial(PhysicMaterial v)
{
    cpsBindMethod("set_sharedMaterial");
    void *args[] = { v.mobj };
    s_method.invoke(*this, args);
}
Bounds Collider::get_bounds()
{
    cpsBindMethod("get_bounds");
    return s_method.invoke(*this).getData<Bounds>();
}

Vector3 Collider::ClosestPointOnBounds(const Vector3 &v)
{
    cpsBindMethod("ClosestPointOnBounds");
    void *args[] = { (void*)&v };
    return s_method.invoke(*this, args).getData<Vector3>();
}

bool Collider::Raycast(const Ray &ray, RaycastHit &hit, float dist)
{
    cpsBindMethod("Raycast");
    void *args[] = { (void*)&ray, (void*)&hit, &dist };
    return s_method.invoke(*this, args).getData<gboolean>() != 0;
}



cpsImplTraits(UnityEngine, Collider2D);
Collider2D::Collider2D(cpsObject obj) : super(obj) {}



cpsImplTraits(UnityEngine, Camera);
Camera::Camera(cpsObject obj) : super(obj) {}



cpsImplTraits(UnityEngine, Light);
Light::Light(cpsObject obj) : super(obj) {}







cpsImplTraits(UnityEngine, Application);

/*static*/ cpsString Application::get_dataPath()
{
    cpsBindMethod("get_dataPath");
    return cpsString(s_method.invoke(nullptr, nullptr));
}

/*static*/ bool Application::get_isEditor()
{
    cpsBindMethod("get_isEditor");
    cpsObject ret = s_method.invoke(nullptr, nullptr);
    return *((gboolean*)ret.getDataPtr()) != 0;
}



cpsImplTraits(UnityEngine, Debug);

/*static*/ void Debug::Log(cpsString message)
{
    cpsBindMethod("Log", 1);

    void *args[] = { message };
    s_method.invoke(nullptr, args);
}

/*static*/ void Debug::Log(cpsString message, cpsObject obj)
{
    cpsBindMethod("Log", 2);

    void *args[] = { message, obj };
    s_method.invoke(nullptr, args);
}


cpsImplTraits(UnityEngine, GL);


cpsImplTraits(UnityEngine, GUI);



cpsImplTraits(UnityEngine, Graphics);

/*static*/ RenderBuffer Graphics::get_activeColorBuffer()
{
    cpsBindMethod("get_activeColorBuffer");
    cpsObject ret = s_method.invoke(nullptr);
    return ret.getData<RenderBuffer>();
}
/*static*/ RenderBuffer Graphics::get_activeDepthBuffer()
{
    cpsBindMethod("get_activeDepthBuffer");
    cpsObject ret = s_method.invoke(nullptr);
    return ret.getData<RenderBuffer>();
}
/*static*/ cpsString Graphics::get_deviceName()
{
    cpsBindMethod("get_deviceName");
    cpsObject ret = s_method.invoke(nullptr);
    return cpsString(ret);
}
/*static*/ cpsString Graphics::get_deviceVendor()
{
    cpsBindMethod("get_deviceVendor");
    cpsObject ret = s_method.invoke(nullptr);
    return cpsString(ret);
}
/*static*/ cpsString Graphics::get_deviceVersion()
{
    cpsBindMethod("get_deviceVersion");
    cpsObject ret = s_method.invoke(nullptr);
    return cpsString(ret);
}
/*static*/ bool Graphics::get_supportsVertexProgram()
{
    cpsBindMethod("get_supportsVertexProgram");
    cpsObject ret = s_method.invoke(nullptr);
    return ret.getData<gboolean>()!=0;
}

/*static*/ void Graphics::Blit(Texture source, RenderTexture dest)
{
    static const char *names[] = { cpsTypename<Texture>(), cpsTypename<RenderTexture>() };
    cpsBindMethod("Blit", _countof(names), names);
    void *args[] = { source, dest };
    s_method.invoke(nullptr, args);
}
/*static*/ void Graphics::Blit(Texture source, RenderTexture dest, Material mat, int pass)
{
    static const char *names[] = { cpsTypename<Texture>(), cpsTypename<RenderTexture>(), cpsTypename<Material>(), cpsTypename<int>() };
    cpsBindMethod("Blit", _countof(names), names);
    void *args[] = { source, dest, mat, &pass };
    s_method.invoke(nullptr, args);
}
/*static*/ void Graphics::Blit(Texture source, Material mat, int pass)
{
    static const char *names[] = { cpsTypename<Texture>(), cpsTypename<Material>(), cpsTypename<int>() };
    cpsBindMethod("Blit", _countof(names), names);
    void *args[] = { source, mat, &pass };
    s_method.invoke(nullptr, args);
}
/*static*/ void Graphics::BlitMultiTap(Texture source, RenderTexture dest, Material mat, cpsTArray<Vector2> offsets)
{
    static const char *names[] = { cpsTypename<Texture>(), cpsTypename<RenderTexture>(), cpsTypename<Material>(), cpsTypenameArray<Vector2>() };
    cpsBindMethod("BlitMultiTap", _countof(names), names);
    void *args[] = { source, dest, mat, (cpsArray)offsets };
    s_method.invoke(nullptr, args);
}
/*static*/ void Graphics::ClearRandomWriteTargets()
{
    cpsBindMethod("ClearRandomWriteTargets", 0);
    s_method.invoke(nullptr);
}
/*static*/ void Graphics::DrawMesh(Mesh mesh, const Vector3 &position, const Quaternion &rotation, Material material, int layer, Camera camera, int submeshIndex, MaterialPropertyBlock properties)
{
    static const char *names[] = { cpsTypename<Mesh>(), cpsTypename<Vector3>(), cpsTypename<Quaternion>(), cpsTypename<Material>(), cpsTypename<int>(), cpsTypename<Camera>(), cpsTypename<int>(), cpsTypename<MaterialPropertyBlock>() };
    cpsBindMethod("DrawMesh", _countof(names), names);
    void *args[] = { mesh, (void*)&position, (void*)&rotation, material, &layer, camera, &submeshIndex, properties };
    s_method.invoke(nullptr, args);
}
/*static*/ void Graphics::DrawMesh(Mesh mesh, const Vector3 &position, const Quaternion &rotation, Material material, int layer, Camera camera, int submeshIndex, MaterialPropertyBlock properties, bool castShadows, bool receiveShadows)
{
    static const char *names[] = { cpsTypename<Mesh>(), cpsTypename<Vector3>(), cpsTypename<Quaternion>(), cpsTypename<Material>(), cpsTypename<int>(), cpsTypename<Camera>(), cpsTypename<int>(), cpsTypename<MaterialPropertyBlock>(), cpsTypename<bool>(), cpsTypename<bool>() };
    cpsBindMethod("DrawMesh", _countof(names), names);
    gboolean castShadows_ = castShadows;
    gboolean receiveShadows_ = receiveShadows;
    void *args[] = { mesh, (void*)&position, (void*)&rotation, material, &layer, camera, &submeshIndex, properties, &castShadows_, &receiveShadows_ };
    s_method.invoke(nullptr, args);
}
/*static*/ void Graphics::DrawMesh(Mesh mesh, const Matrix4x4 &matrix, Material material, int layer, Camera camera, int submeshIndex, MaterialPropertyBlock properties)
{
    static const char *names[] = { cpsTypename<Mesh>(), cpsTypename<Matrix4x4>(), cpsTypename<Material>(), cpsTypename<int>(), cpsTypename<Camera>(), cpsTypename<int>(), cpsTypename<MaterialPropertyBlock>() };
    cpsBindMethod("DrawMesh", _countof(names), names);
    void *args[] = { mesh, (void*)&matrix, material, &layer, camera, &submeshIndex, properties };
    s_method.invoke(nullptr, args);
}
/*static*/ void Graphics::DrawMesh(Mesh mesh, const Matrix4x4 &matrix, Material material, int layer, Camera camera, int submeshIndex, MaterialPropertyBlock properties, bool castShadows, bool receiveShadows)
{
    static const char *names[] = { cpsTypename<Mesh>(), cpsTypename<Matrix4x4>(), cpsTypename<Material>(), cpsTypename<int>(), cpsTypename<int>(), cpsTypename<MaterialPropertyBlock>(), cpsTypename<bool>(), cpsTypename<bool>() };
    cpsBindMethod("DrawMesh", _countof(names), names);
    gboolean castShadows_ = castShadows;
    gboolean receiveShadows_ = receiveShadows;
    void *args[] = { mesh, (void*)&matrix, material, &layer, camera, &submeshIndex, properties, &castShadows_, &receiveShadows_ };
    s_method.invoke(nullptr, args);
}
/*static*/ void Graphics::DrawMeshNow(Mesh mesh, const Vector3 &position, const Quaternion &rotation)
{
    static const char *names[] = { cpsTypename<Mesh>(), cpsTypename<Vector3>(), cpsTypename<Quaternion>() };
    cpsBindMethod("DrawMeshNow", _countof(names), names);
    void *args[] = { mesh, (void*)&position, (void*)&rotation };
    s_method.invoke(nullptr, args);
}
/*static*/ void Graphics::DrawMeshNow(Mesh mesh, const Vector3 &position, const Quaternion &rotation, int materialIndex)
{
    static const char *names[] = { cpsTypename<Mesh>(), cpsTypename<Vector3>(), cpsTypename<Quaternion>(), cpsTypename<int>() };
    cpsBindMethod("DrawMeshNow", _countof(names), names);
    void *args[] = { mesh, (void*)&position, (void*)&rotation, (void*)&materialIndex };
    s_method.invoke(nullptr, args);
}
/*static*/ void Graphics::DrawMeshNow(Mesh mesh, const Matrix4x4 &matrix)
{
    static const char *names[] = { cpsTypename<Mesh>(), cpsTypename<Matrix4x4>() };
    cpsBindMethod("DrawMeshNow", _countof(names), names);
    void *args[] = { mesh, (void*)&matrix };
    s_method.invoke(nullptr, args);
}
/*static*/ void Graphics::DrawMeshNow(Mesh mesh, const Matrix4x4 &matrix, int materialIndex)
{
    static const char *names[] = { cpsTypename<Mesh>(), cpsTypename<Matrix4x4>(), cpsTypename<int>() };
    cpsBindMethod("DrawMeshNow", _countof(names), names);
    void *args[] = { mesh, (void*)&matrix, (void*)&materialIndex };
    s_method.invoke(nullptr, args);
}
/*static*/ void Graphics::DrawProcedural(MeshTopology topology, int vertexCount, int instanceCount)
{
    static const char *names[] = { cpsTypename<MeshTopology>(), cpsTypename<int>(), cpsTypename<int>() };
    cpsBindMethod("DrawProcedural", _countof(names), names);
    void *args[] = { (void*)&topology, (void*)&vertexCount, (void*)&instanceCount };
    s_method.invoke(nullptr, args);
}
/*static*/ void Graphics::DrawProceduralIndirect(MeshTopology topology, ComputeBuffer bufferWithArgs, int argsOffset)
{
    static const char *names[] = { cpsTypename<MeshTopology>(), cpsTypename<ComputeBuffer>(), cpsTypename<int>() };
    cpsBindMethod("DrawProceduralIndirect", _countof(names), names);
    void *args[] = { (void*)&topology, bufferWithArgs, (void*)&argsOffset };
    s_method.invoke(nullptr, args);
}
/*static*/ void Graphics::DrawTexture(const Rect &screenRect, Texture texture, Material mat)
{
    static const char *names[] = { cpsTypename<Rect>(), cpsTypename<Texture>(), cpsTypename<Material>() };
    cpsBindMethod("DrawTexture", _countof(names), names);
    void *args[] = { (void*)&screenRect, texture, mat };
    s_method.invoke(nullptr, args);
}
/*static*/ void Graphics::DrawTexture(const Rect &screenRect, Texture texture, int leftBorder, int rightBorder, int topBorder, int bottomBorder, Material mat)
{
    static const char *names[] = { cpsTypename<Rect>(), cpsTypename<Texture>(), cpsTypename<int>(), cpsTypename<int>(), cpsTypename<int>(), cpsTypename<int>(), cpsTypename<Material>() };
    cpsBindMethod("DrawTexture", _countof(names), names);
    void *args[] = { (void*)&screenRect, texture, (void*)&leftBorder, (void*)&rightBorder, (void*)&topBorder, (void*)&bottomBorder, mat };
    s_method.invoke(nullptr, args);
}
/*static*/ void Graphics::DrawTexture(const Rect &screenRect, Texture texture, const Rect &sourceRect, int leftBorder, int rightBorder, int topBorder, int bottomBorder, Material mat)
{
    static const char *names[] = { cpsTypename<Rect>(), cpsTypename<Texture>(), cpsTypename<Rect>(), cpsTypename<int>(), cpsTypename<int>(), cpsTypename<int>(), cpsTypename<int>(), cpsTypename<Material>() };
    cpsBindMethod("DrawTexture", _countof(names), names);
    void *args[] = { (void*)&screenRect, texture, (void*)&sourceRect, (void*)&leftBorder, (void*)&rightBorder, (void*)&topBorder, (void*)&bottomBorder, mat };
    s_method.invoke(nullptr, args);
}
/*static*/ void Graphics::DrawTexture(const Rect &screenRect, Texture texture, const Rect &sourceRect, int leftBorder, int rightBorder, int topBorder, int bottomBorder, const Color &color, Material mat)
{
    static const char *names[] = { cpsTypename<Rect>(), cpsTypename<Texture>(), cpsTypename<Rect>(), cpsTypename<int>(), cpsTypename<int>(), cpsTypename<int>(), cpsTypename<int>(), cpsTypename<Color>(), cpsTypename<Material>() };
    cpsBindMethod("DrawTexture", _countof(names), names);
    void *args[] = { (void*)&screenRect, texture, (void*)&sourceRect, (void*)&leftBorder, (void*)&rightBorder, (void*)&topBorder, (void*)&bottomBorder, (void*)&color, mat };
    s_method.invoke(nullptr, args);
}
/*static*/ void Graphics::SetRandomWriteTarget(int index, RenderTexture uav)
{
    static const char *names[] = { cpsTypename<int>(), cpsTypename<RenderTexture>() };
    cpsBindMethod("SetRandomWriteTarget", _countof(names), names);
    void *args[] = { (void*)&index, uav };
    s_method.invoke(nullptr, args);
}
/*static*/ void Graphics::SetRandomWriteTarget(int index, ComputeBuffer uav)
{
    static const char *names[] = { cpsTypename<int>(), cpsTypename<ComputeBuffer>() };
    cpsBindMethod("SetRandomWriteTarget", _countof(names), names);
    void *args[] = { (void*)&index, uav };
    s_method.invoke(nullptr, args);
}
/*static*/ void Graphics::SetRenderTarget(RenderTexture rt)
{
    static const char *names[] = { cpsTypename<RenderTexture>() };
    cpsBindMethod("SetRenderTarget", _countof(names), names);
    void *args[] = { rt };
    s_method.invoke(nullptr, args);
}
/*static*/ void Graphics::SetRenderTarget(RenderTexture rt, int mipLevel)
{
    static const char *names[] = { cpsTypename<RenderTexture>(), cpsTypename<int>() };
    cpsBindMethod("SetRenderTarget", _countof(names), names);
    void *args[] = { rt, (void*)&mipLevel };
    s_method.invoke(nullptr, args);
}
/*static*/ void Graphics::SetRenderTarget(RenderTexture rt, int mipLevel, CubemapFace face)
{
    static const char *names[] = { cpsTypename<RenderTexture>(), cpsTypename<int>(), cpsTypename<CubemapFace>() };
    cpsBindMethod("SetRenderTarget", _countof(names), names);
    void *args[] = { rt, (void*)&mipLevel, (void*)&face };
    s_method.invoke(nullptr, args);
}
/*static*/ void Graphics::SetRenderTarget(RenderBuffer colorBuffer, RenderBuffer depthBuffer)
{
    static const char *names[] = { cpsTypename<RenderBuffer>(), cpsTypename<RenderBuffer>() };
    cpsBindMethod("SetRenderTarget", _countof(names), names);
    void *args[] = { &colorBuffer, &depthBuffer };
    s_method.invoke(nullptr, args);
}
/*static*/ void Graphics::SetRenderTarget(cpsTArray<RenderBuffer> colorBuffers, RenderBuffer depthBuffer)
{
    static const char *names[] = { cpsTypenameArray<RenderBuffer>(), cpsTypename<RenderBuffer>() };
    cpsBindMethod("SetRenderTarget", _countof(names), names);
    void *args[] = { (cpsArray)colorBuffers, &depthBuffer };
    s_method.invoke(nullptr, args);
}





cpsImplTraits(UnityEngine, Physics);
/*static*/ Vector3 Physics::get_gravity()
{
    cpsBindMethod("get_gravity");
    cpsObject ret = s_method.invoke(nullptr);
    return ret.getData<Vector3>();
}
/*static*/ void Physics::set_gravity(const Vector3 v)
{
    cpsBindMethod("set_gravity");
    void *args[] = { (void*)&v };
    s_method.invoke(nullptr, args);
}
/*static*/ float Physics::get_minPenetrationForPenalty()
{
    cpsBindMethod("get_minPenetrationForPenalty");
    cpsObject ret = s_method.invoke(nullptr);
    return ret.getData<float>();
}
/*static*/ void Physics::set_minPenetrationForPenalty(float v)
{
    cpsBindMethod("set_minPenetrationForPenalty");
    void *args[] = { (void*)&v };
    s_method.invoke(nullptr, args);
}
/*static*/ float Physics::get_bounceThreshold()
{
    cpsBindMethod("get_bounceThreshold");
    cpsObject ret = s_method.invoke(nullptr);
    return ret.getData<float>();
}
/*static*/ void Physics::set_bounceThreshold(float v)
{
    cpsBindMethod("set_bounceThreshold");
    void *args[] = { (void*)&v };
    s_method.invoke(nullptr, args);
}
/*static*/ float Physics::get_sleepVelocity()
{
    cpsBindMethod("get_sleepVelocity");
    cpsObject ret = s_method.invoke(nullptr);
    return ret.getData<float>();
}
/*static*/ void Physics::set_sleepVelocity(float v)
{
    cpsBindMethod("set_sleepVelocity");
    void *args[] = { (void*)&v };
    s_method.invoke(nullptr, args);
}
/*static*/ float Physics::get_sleepAngularVelocity()
{
    cpsBindMethod("get_sleepAngularVelocity");
    cpsObject ret = s_method.invoke(nullptr);
    return ret.getData<float>();
}
/*static*/ void Physics::set_sleepAngularVelocity(float v)
{
    cpsBindMethod("set_sleepAngularVelocity");
    void *args[] = { (void*)&v };
    s_method.invoke(nullptr, args);
}
/*static*/ float Physics::get_maxAngularVelocity()
{
    cpsBindMethod("get_maxAngularVelocity");
    cpsObject ret = s_method.invoke(nullptr);
    return ret.getData<float>();
}
/*static*/ void Physics::set_maxAngularVelocity(float v)
{
    cpsBindMethod("set_maxAngularVelocity");
    void *args[] = { (void*)&v };
    s_method.invoke(nullptr, args);
}
/*static*/ int Physics::get_solverIterationCount()
{
    cpsBindMethod("get_solverIterationCount");
    cpsObject ret = s_method.invoke(nullptr);
    return ret.getData<int>();
}
/*static*/ void Physics::set_solverIterationCount(int v)
{
    cpsBindMethod("set_solverIterationCount");
    void *args[] = { (void*)&v };
    s_method.invoke(nullptr, args);
}

/*static*/ bool Physics::CheckCapsule(const Vector3 &start, const Vector3 &end, float radius, int layermask)
{
    static const char *names[] = { cpsTypename<Vector3>(), cpsTypename<Vector3>(), cpsTypename<float>(), cpsTypename<int>() };
    cpsBindMethod("CheckCapsule", _countof(names), names);
    void *args[] = { (void*)&start, (void*)&end, &radius, &layermask };
    cpsObject ret = s_method.invoke(nullptr, args);
    return ret.getData<gboolean>() != 0;
}
/*static*/ bool Physics::CheckSphere(const Vector3 &position, float radius, int layerMask)
{
    static const char *names[] = { cpsTypename<Vector3>(), cpsTypename<float>(), cpsTypename<int>() };
    cpsBindMethod("CheckSphere", _countof(names), names);
    void *args[] = { (void*)&position, &radius, &layerMask };
    cpsObject ret = s_method.invoke(nullptr, args);
    return ret.getData<gboolean>() != 0;
}
/*static*/ bool Physics::Raycast(const Ray &ray, RaycastHit &hitInfo, float distance, int layerMask)
{
    static const char *names[] = { cpsTypename<Ray>(), cpsTypenameRef<RaycastHit>(), cpsTypename<float>(), cpsTypename<int>() };
    cpsBindMethod("Raycast", _countof(names), names);
    void *args[] = { (void*)&ray, &hitInfo, &distance, &layerMask };
    cpsObject ret = s_method.invoke(nullptr, args);
    return ret.getData<gboolean>() != 0;
}
/*static*/ bool Physics::CapsuleCast(const Vector3 &point1, const Vector3 &point2, float radius, const Vector3 &direction, RaycastHit &hitInfo, float distance, int layerMask)
{
    static const char *names[] = { cpsTypename<Vector3>(), cpsTypename<Vector3>(), cpsTypename<float>(), cpsTypename<Vector3>(), cpsTypenameRef<RaycastHit>(), cpsTypename<float>(), cpsTypename<int>() };
    cpsBindMethod("CapsuleCast", _countof(names), names);
    void *args[] = { (void*)&point1, (void*)&point2, (void*)&radius, (void*)&direction, (void*)&hitInfo, (void*)&distance, (void*)&layerMask };
    cpsObject ret = s_method.invoke(nullptr, args);
    return ret.getData<gboolean>() != 0;
}
/*static*/ bool Physics::Linecast(const Vector3 &start, const Vector3 &end, RaycastHit &hitInfo, int layerMask)
{
    static const char *names[] = { cpsTypename<Vector3>(), cpsTypename<Vector3>(), cpsTypenameRef<RaycastHit>(), cpsTypename<int>() };
    cpsBindMethod("Linecast", _countof(names), names);
    void *args[] = { (void*)&start, (void*)&end, (void*)&hitInfo, (void*)&layerMask };
    cpsObject ret = s_method.invoke(nullptr, args);
    return ret.getData<gboolean>() != 0;
}
/*static*/ bool Physics::SphereCast(const Ray &ray, float radius, RaycastHit &hitInfo, float distance, int layerMask)
{
    static const char *names[] = { cpsTypename<Ray>(), cpsTypename<float>(), cpsTypenameRef<RaycastHit>(), cpsTypename<float>(), cpsTypename<int>() };
    cpsBindMethod("SphereCast", _countof(names), names);
    void *args[] = { (void*)&ray, (void*)&radius, (void*)&hitInfo, (void*)&distance, (void*)&layerMask };
    cpsObject ret = s_method.invoke(nullptr, args);
    return ret.getData<gboolean>() != 0;
}
/*static*/ cpsTArray<Collider> Physics::OverlapSphere(const Vector3 &position, float radius, int layerMask)
{
    static const char *names[] = { cpsTypename<Vector3>(), cpsTypename<float>(), cpsTypename<int>() };
    cpsBindMethod("OverlapSphere", _countof(names), names);
    void *args[] = { (void*)&position, (void*)&radius, (void*)&layerMask };
    cpsObject ret = s_method.invoke(nullptr, args);
    return cpsTArray<Collider>(ret);
}
/*static*/ cpsTArray<RaycastHit> Physics::RaycastAll(const Ray &ray, float distance, int layerMask)
{
    static const char *names[] = { cpsTypename<Ray>(), cpsTypename<float>(), cpsTypename<int>() };
    cpsBindMethod("RaycastAll", _countof(names), names);
    void *args[] = { (void*)&ray, (void*)&distance, (void*)&layerMask };
    cpsObject ret = s_method.invoke(nullptr, args);
    return cpsTArray<RaycastHit>(ret);
}
/*static*/ cpsTArray<RaycastHit> Physics::SphereCastAll(const Ray &ray, float radius, float distance, int layerMask)
{
    static const char *names[] = { cpsTypename<Ray>(), cpsTypename<float>(), cpsTypename<float>(), cpsTypename<int>() };
    cpsBindMethod("SphereCastAll", _countof(names), names);
    void *args[] = { (void*)&ray, (void*)&radius, (void*)&distance, (void*)&layerMask };
    cpsObject ret = s_method.invoke(nullptr, args);
    return cpsTArray<RaycastHit>(ret);
}
/*static*/ cpsTArray<RaycastHit> Physics::CapsuleCastAll(const Vector3 &point1, const Vector3 &point2, float radius, const Vector3 &direction, float distance, int layerMask)
{
    static const char *names[] = { cpsTypename<Vector3>(), cpsTypename<Vector3>(), cpsTypename<float>(), cpsTypename<Vector3>(), cpsTypename<float>(), cpsTypename<int>() };
    cpsBindMethod("CapsuleCastAll", _countof(names), names);
    void *args[] = { (void*)&point1, (void*)&point2, (void*)&radius, (void*)&direction, (void*)&distance, (void*)&layerMask };
    cpsObject ret = s_method.invoke(nullptr, args);
    return cpsTArray<RaycastHit>(ret);
}
/*static*/ bool Physics::GetIgnoreLayerCollision(int layer1, int layer2)
{
    static const char *names[] = { cpsTypename<int>(), cpsTypename<int>() };
    cpsBindMethod("GetIgnoreLayerCollision", _countof(names), names);
    void *args[] = { &layer1, &layer2 };
    cpsObject ret = s_method.invoke(nullptr, args);
    return ret.getData<gboolean>() != 0;
}
/*static*/ void Physics::IgnoreCollision(Collider collider1, Collider collider2, bool ignore)
{
    static const char *names[] = { cpsTypename<Collider>(), cpsTypename<Collider>(), cpsTypename<bool>() };
    cpsBindMethod("IgnoreCollision", _countof(names), names);
    gboolean ignore_ = ignore;
    void *args[] = { collider1, collider2, &ignore_ };
    cpsObject ret = s_method.invoke(nullptr, args);
}
/*static*/ void Physics::IgnoreLayerCollision(int layer1, int layer2, bool ignore)
{
    static const char *names[] = { cpsTypename<int>(), cpsTypename<int>(), cpsTypename<bool>() };
    cpsBindMethod("IgnoreLayerCollision", _countof(names), names);
    gboolean ignore_ = ignore;
    void *args[] = { &layer1, &layer2, &ignore_ };
    cpsObject ret = s_method.invoke(nullptr, args);
}


cpsImplTraits(UnityEngine, Physics2D);




} // namespace cpsUnityEngine


cpsImplTraitsF(UnityEngine, Space)
cpsImplTraitsF(UnityEngine, SendMessageOptions)
cpsImplTraitsF(UnityEngine, HideFlags)
cpsImplTraitsF(UnityEngine, MeshTopology)
cpsImplTraitsF(UnityEngine, CubemapFace)
cpsImplTraitsF(UnityEngine, ComputeBufferType)
cpsImplTraitsF(UnityEngine, CollisionDetectionMode)
cpsImplTraitsF(UnityEngine, RigidbodyConstraints)
cpsImplTraitsF(UnityEngine, RigidbodyInterpolation)
cpsImplTraitsF(UnityEngine, ForceMode)
