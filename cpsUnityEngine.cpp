#include "cpsInternal.h"
#include "cpsUtils.h"
#include "cpsUnityEngine.h"


#define cpsBindMethod(...)\
    static cpsCachedMethod s_method;\
    if (!s_method) { s_method = getClass().findMethod(__VA_ARGS__); }


namespace cpsUnityEngine
{

cpsImage& GetImage()
{
    static cpsCachedImage s_image;
    if (!s_image) { s_image = cpsImage::findImage("UnityEngine"); }
    return s_image;
}



cpsClass Application::getClass()
{
    static cpsCachedClass s_class;
    if (!s_class) { s_class = GetImage().findClass("UnityEngine", "Application"); }
    return s_class;
}

std::string Application::get_dataPath()
{
    cpsBindMethod("get_dataPath");

    cpsObject ret = s_method.invoke(nullptr, nullptr);
    return std::string((char*)((MonoString*)ret.mobj)->chars);
}

bool Application::get_isEditor()
{
    cpsBindMethod("get_isEditor");
    cpsObject ret = s_method.invoke(nullptr, nullptr);
    return *((gboolean*)ret.getDataPtr()) != 0;
}



cpsClass Debug::getClass()
{
    static cpsCachedClass s_class;
    if (!s_class) { s_class = GetImage().findClass("UnityEngine", "Debug"); }
    return s_class;
}

void Debug::Log(const char *message)
{
    cpsBindMethod("Log", 1);

    MonoString *str = mono_string_new(mono_domain_get(), message);
    void *args[] = { str };
    s_method.invoke(nullptr, args);
}

void Debug::Log(const char *message, cpsObject obj)
{
    cpsBindMethod("Log", 2);

    MonoString *str = mono_string_new(mono_domain_get(), message);
    void *args[] = { str, obj };
    s_method.invoke(nullptr, args);
}



Component::Component(cpsObject obj)
    : cpsObject(obj)
{

}


Transform::Transform(cpsObject obj)
    : Component(obj)
{

}

cpsClass Transform::getClass()
{
    static cpsCachedClass s_class;
    if (!s_class) { s_class = GetImage().findClass("UnityEngine", "Transform"); }
    return s_class;
}

Vector3 Transform::get_position() const
{
    cpsBindMethod("get_position");
    return s_method.invoke(mobj).getData<Vector3>();
}
void Transform::set_position(const Vector3& v)
{
    cpsBindMethod("set_position");
    void *args[] = { (void*)&v };
    s_method.invoke(mobj, args);
}

Vector3 Transform::get_localPosition() const
{
    cpsBindMethod("get_localPosition");
    return s_method.invoke(mobj).getData<Vector3>();
}
void Transform::set_localPosition(const Vector3& v)
{
    cpsBindMethod("set_localPosition");
    void *args[] = { (void*)&v };
    s_method.invoke(mobj, args);
}

Vector3 Transform::get_eulerAngles() const
{
    cpsBindMethod("get_eulerAngles");
    return s_method.invoke(mobj).getData<Vector3>();
}
void Transform::set_eulerAngles(const Vector3& v)
{
    cpsBindMethod("set_eulerAngles");
    void *args[] = { (void*)&v };
    s_method.invoke(mobj, args);
}

Vector3 Transform::get_right() const
{
    cpsBindMethod("get_right");
    return s_method.invoke(mobj).getData<Vector3>();
}
void Transform::set_right(const Vector3& v)
{
    cpsBindMethod("set_right");
    void *args[] = { (void*)&v };
    s_method.invoke(mobj, args);
}

Vector3 Transform::get_up() const
{
    cpsBindMethod("get_up");
    return s_method.invoke(mobj).getData<Vector3>();
}
void Transform::set_up(const Vector3& v)
{
    cpsBindMethod("set_up");
    void *args[] = { (void*)&v };
    s_method.invoke(mobj, args);
}

Vector3 Transform::get_forward() const
{
    cpsBindMethod("get_forward");
    return s_method.invoke(mobj).getData<Vector3>();
}
void Transform::set_forward(const Vector3& v)
{
    cpsBindMethod("set_forward");
    void *args[] = { (void*)&v };
    s_method.invoke(mobj, args);
}

Quaternion Transform::get_rotation() const
{
    cpsBindMethod("get_rotation");
    return s_method.invoke(mobj).getData<Quaternion>();
}
void Transform::set_rotation(const Quaternion &v)
{
    cpsBindMethod("set_rotation");
    void *args[] = { (void*)&v };
    s_method.invoke(mobj, args);
}

Quaternion Transform::get_localRotation() const
{
    cpsBindMethod("get_localRotation");
    return s_method.invoke(mobj).getData<Quaternion>();
}
void Transform::set_localRotation(const Quaternion &v)
{
    cpsBindMethod("set_localRotation");
    void *args[] = { (void*)&v };
    s_method.invoke(mobj, args);
}

Vector3 Transform::get_localScale() const
{
    cpsBindMethod("get_localScale");
    return s_method.invoke(mobj).getData<Vector3>();
}
void Transform::set_localScale(const Vector3& v)
{
    cpsBindMethod("set_localScale");
    void *args[] = { (void*)&v };
    s_method.invoke(mobj, args);
}

Transform Transform::get_parent() const
{
    cpsBindMethod("get_parent");
    return s_method.invoke(mobj);
}
void Transform::set_parent(const Transform &v)
{
    cpsBindMethod("set_parent");
    void *args[] = { (void*)v };
    s_method.invoke(mobj, args);
}

Matrix4x4 Transform::get_worldToLocalMatrix() const
{
    cpsBindMethod("get_worldToLocalMatrix");
    return s_method.invoke(mobj).getData<Matrix4x4>();
}
Matrix4x4 Transform::get_localToWorldMatrix() const
{
    cpsBindMethod("get_localToWorldMatrix");
    return s_method.invoke(mobj).getData<Matrix4x4>();
}

Transform Transform::get_root()
{
    cpsBindMethod("get_root");
    return s_method.invoke(mobj);
}
int Transform::get_childCount()
{
    cpsBindMethod("get_childCount");
    return s_method.invoke(mobj).getData<int>();
}
Vector3 Transform::get_lossyScale()
{
    cpsBindMethod("get_lossyScale");
    return s_method.invoke(mobj).getData<Vector3>();
}

bool Transform::get_hasChanged()
{
    cpsBindMethod("get_hasChanged");
    return s_method.invoke(mobj).getData<gboolean>()!=0;
}
void Transform::set_hasChanged(bool v)
{
    cpsBindMethod("set_hasChanged");
    gboolean b = v;
    void *args[] = {&b};
    s_method.invoke(mobj, args);
}



cpsClass Camera::getClass()
{
    static cpsCachedClass s_class;
    if (!s_class) { s_class = GetImage().findClass("UnityEngine", "Camera"); }
    return s_class;
}



cpsClass Graphics::getClass()
{
    static cpsCachedClass s_class;
    if (!s_class) { s_class = GetImage().findClass("UnityEngine", "Graphics"); }
    return s_class;
}



cpsClass ComputeBuffer::getClass()
{
    static cpsCachedClass s_class;
    if (!s_class) { s_class = GetImage().findClass("UnityEngine", "ComputeBuffer"); }
    return s_class;
}


} // namespace cpsUnityEngine
