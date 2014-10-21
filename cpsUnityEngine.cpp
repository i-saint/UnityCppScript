﻿#include "cpsInternal.h"
#include "cpsUtils.h"
#include "cpsUnityEngine.h"


#define cpsBindMethod(...)\
    static cpsCachedMethod s_method;\
    if (!s_method) { s_method = getClass().findMethod(__VA_ARGS__); }


namespace cpsUnityEngine
{

const Vector3 Vector3::up = Vector3(0.0f, 1.0f, 0.0f);



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


void Transform::Translate(const Vector3& v, Space s)
{
    static const char *typenames[] = {"UnityEngine.Vector3", "UnityEngine.Space"};
    cpsBindMethod("Translate", 2, typenames);
    void *args[] = { (void*)&v, &s };
    s_method.invoke(mobj, args);
}
void Transform::Translate(const Vector3& v, Transform relative)
{
    static const char *typenames[] = { "UnityEngine.Vector3", "UnityEngine.Transform" };
    cpsBindMethod("Translate", 2, typenames);
    void *args[] = { (void*)&v, relative.mobj };
    s_method.invoke(mobj, args);
}

void Transform::Rotate(const Vector3& eulerAngles, Space s)
{
    static const char *typenames[] = { "UnityEngine.Vector3", "UnityEngine.Space" };
    cpsBindMethod("Rotate", 2, typenames);
    void *args[] = { (void*)&eulerAngles, &s };
    s_method.invoke(mobj, args);
}
void Transform::Rotate(const Vector3& axis, float angle, Space s)
{
    static const char *typenames[] = { "UnityEngine.Vector3", "System.Single", "UnityEngine.Space" };
    cpsBindMethod("Rotate", 3, typenames);
    void *args[] = { (void*)&axis, &angle, &s };
    s_method.invoke(mobj, args);
}
void Transform::RotateAround(const Vector3& point, const Vector3& axis, float angle)
{
    static const char *typenames[] = { "UnityEngine.Vector3", "UnityEngine.Vector3", "System.Single" };
    cpsBindMethod("RotateAround", 3, typenames);
    void *args[] = { (void*)&point, (void*)&axis, &angle };
    s_method.invoke(mobj, args);
}

void Transform::LookAt(Transform t, const Vector3& up)
{
    static const char *typenames[] = { "UnityEngine.Transform", "UnityEngine.Vector3" };
    cpsBindMethod("LookAt", 2, typenames);
    void *args[] = { t.mobj, (void*)&up };
    s_method.invoke(mobj, args);
}
void Transform::LookAt(const Vector3& worldPos, const Vector3&up)
{
    static const char *typenames[] = { "UnityEngine.Vector3", "UnityEngine.Vector3" };
    cpsBindMethod("LookAt", 2, typenames);
    void *args[] = { (void*)&worldPos, (void*)&up };
    s_method.invoke(mobj, args);
}

Vector3 Transform::TransformDirection(const Vector3& v)
{
    cpsBindMethod("TransformDirection", 1);
    void *args[] = { (void*)&v };
    return s_method.invoke(mobj, args).getData<Vector3>();
}

Vector3 Transform::InverseTransformDirection(const Vector3& v)
{
    cpsBindMethod("InverseTransformDirection", 1);
    void *args[] = { (void*)&v };
    return s_method.invoke(mobj, args).getData<Vector3>();
}

Vector3 Transform::TransformPoint(const Vector3& v)
{
    cpsBindMethod("TransformPoint", 1);
    void *args[] = { (void*)&v };
    return s_method.invoke(mobj, args).getData<Vector3>();
}

Vector3 Transform::InverseTransformPoint(const Vector3& v)
{
    cpsBindMethod("InverseTransformPoint", 1);
    void *args[] = { (void*)&v };
    return s_method.invoke(mobj, args).getData<Vector3>();
}

void Transform::DetachChildren()
{
    cpsBindMethod("DetachChildren", 0);
    s_method.invoke(mobj);
}

void Transform::SetAsFirstSibling()
{
    cpsBindMethod("SetAsFirstSibling", 0);
    s_method.invoke(mobj);
}

void Transform::SetAsLastSibling()
{
    cpsBindMethod("SetAsLastSibling", 0);
    s_method.invoke(mobj);
}

void Transform::SetSiblingIndex(int i)
{
    cpsBindMethod("SetAsLastSibling", 1);
    void *args[] = { (void*)&i };
    s_method.invoke(mobj, args);
}

int Transform::GetSiblingIndex()
{
    cpsBindMethod("GetSiblingIndex", 0);
    return s_method.invoke(mobj).getData<int>();;
}

Transform Transform::Find(const char *name)
{
    cpsBindMethod("Find", 1);
    void *args[] = { mono_string_new(mono_domain_get(), name) };
    return s_method.invoke(mobj, args).getData<void*>();
}

void Transform::SendTransformChangedScale()
{
    cpsBindMethod("SendTransformChangedScale", 0);
    s_method.invoke(mobj);
}

bool Transform::IsChildOf(Transform t)
{
    cpsBindMethod("IsChildOf", 1);
    void *args[] = { t.mobj };
    return s_method.invoke(mobj, args).getData<gboolean>()!=0;
}

Transform Transform::FindChild(const char *name)
{
    cpsBindMethod("FindChild", 1);
    void *args[] = { mono_string_new(mono_domain_get(), name) };
    return s_method.invoke(mobj, args).getData<void*>();
}

void Transform::RotateAround(const Vector3& axis, float a)
{
    cpsBindMethod("RotateAround", 2);
    void *args[] = { (void*)&axis, &a };
    s_method.invoke(mobj, args);
}

void Transform::RotateAroundLocal(const Vector3& axis, float a)
{
    cpsBindMethod("RotateAroundLocal", 2);
    void *args[] = { (void*)&axis, &a };
    s_method.invoke(mobj, args);
}

Transform Transform::GetChild(int i)
{
    cpsBindMethod("GetChild", 1);
    void *args[] = { &i };
    return s_method.invoke(mobj, args).getData<void*>();
}

int Transform::GetChildCount()
{
    cpsBindMethod("GetChildCount", 0);
    return s_method.invoke(mobj).getData<int>();
}

bool Transform::IsNonUniformScaleTransform()
{
    cpsBindMethod("IsNonUniformScaleTransform", 0);
    return s_method.invoke(mobj).getData<gboolean>()!=0;
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
