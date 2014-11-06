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

cpsAPI cpsImage& GetImage()
{
    static cpsCachedImage s_image;
    if (!s_image) { s_image = cpsImage::findImage("UnityEngine"); }
    return s_image;
}


cpsImplTraits(UnityEngine, Vector2);
const float Vector2::kEpsilon = 1E-05f;
const Vector2 Vector2::one = Vector2(1.0f, 1.0f);
const Vector2 Vector2::right = Vector2(1.0f, 0.0f);
const Vector2 Vector2::up = Vector2(0.0f, 1.0f);
const Vector2 Vector2::zero = Vector2(0.0f, 0.0f);


cpsImplTraits(UnityEngine, Vector3);
const float Vector3::kEpsilon = 1E-05f;
const Vector3 Vector3::back = Vector3(0.0f, 0.0f, -1.0f);
const Vector3 Vector3::down = Vector3(0.0f, -1.0f, 0.0f);
const Vector3 Vector3::forward = Vector3(0.0f, 0.0f, 1.0f);
const Vector3 Vector3::left = Vector3(-1.0f, 0.0f, 0.0f);
const Vector3 Vector3::one = Vector3(1.0f, 1.0f, 1.0f);
const Vector3 Vector3::right = Vector3(1.0f, 0.0f, 0.0f);
const Vector3 Vector3::up = Vector3(0.0f, 1.0f, 0.0f);
const Vector3 Vector3::zero = Vector3(0.0f, 0.0f, 0.0f);

/*static*/ void Vector3::OrthoNormalize(Vector3 &normal, Vector3 &tangent, Vector3 &binormal)
{
    cpsBindMethod("Internal_OrthoNormalize3");
    void *args[] = { (void*)&normal, (void*)&tangent, (void*)&binormal };
    s_method.invoke(nullptr, args);
}
/*static*/ void Vector3::OrthoNormalize(Vector3 &normal, Vector3 &tangent)
{
    cpsBindMethod("Internal_OrthoNormalize2");
    void *args[] = { (void*)&normal, (void*)&tangent };
    s_method.invoke(nullptr, args);
}
/*static*/ Vector3 Vector3::RotateTowards(Vector3 &current, Vector3 &target, float maxRadiansDelta, float maxMagnitudeDelta)
{
    cpsBindMethod("INTERNAL_CALL_RotateTowards");
    void *args[] = { (void*)&current, (void*)&target, (void*)&maxRadiansDelta, (void*)&maxMagnitudeDelta };
    return s_method.invoke(nullptr, args).getValue<Vector3>();
}
/*static*/ Vector3 Vector3::Slerp(Vector3 &from, Vector3 &to, float t)
{
    cpsBindMethod("INTERNAL_CALL_Slerp");
    void *args[] = { (void*)&from, (void*)&to, (void*)&t };
    return s_method.invoke(nullptr, args).getValue<Vector3>();
}
/*static*/ Vector3 Vector3::SmoothDamp(const Vector3 &current, Vector3 &target, Vector3 &currentVelocity, float smoothTime)
{
    float deltaTime = Time::get_deltaTime();
    float maxSpeed = FLT_MAX;
    return SmoothDamp(current, target, currentVelocity, smoothTime, maxSpeed, deltaTime);
}
/*static*/ Vector3 Vector3::SmoothDamp(const Vector3 &current, Vector3 &target, Vector3 &currentVelocity, float smoothTime, float maxSpeed)
{
    float deltaTime = Time::get_deltaTime();
    return SmoothDamp(current, target, currentVelocity, smoothTime, maxSpeed, deltaTime);
}
/*static*/ Vector3 Vector3::SmoothDamp(const Vector3 &current, Vector3 &target, Vector3 &currentVelocity, float smoothTime, float maxSpeed, float deltaTime)
{
    smoothTime = std::max(0.0001f, smoothTime);
    float num = 2.0f / smoothTime;
    float num2 = num * deltaTime;
    float d = 1.0f / (1.0f + num2 + 0.48f * num2 * num2 + 0.235f * num2 * num2 * num2);
    Vector3 vector = current - target;
    Vector3 vector2 = target;
    float maxLength = maxSpeed * smoothTime;
    vector = ClampMagnitude(vector, maxLength);
    target = current - vector;
    Vector3 vector3 = (currentVelocity + num * vector) * deltaTime;
    currentVelocity = (currentVelocity - num * vector3) * d;
    Vector3 vector4 = target + (vector + vector3) * d;
    if (Dot(vector2 - current, vector4 - vector2) > 0.0f)
    {
        vector4 = vector2;
        currentVelocity = (vector4 - vector2) / deltaTime;
    }
    return vector4;
}


cpsImplTraits(UnityEngine, Vector4);
const Vector4 Vector4::zero = Vector4(0.0f, 0.0f, 0.0f, 0.0f);
const Vector4 Vector4::one = Vector4(1.0f, 1.0f, 1.0f, 1.0f);

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
cpsImplTraits(UnityEngine, BoneWeight);


cpsImplTraits(UnityEngine, Collision);
Collision::Collision(cpsObject v) : super(v) {}

cpsImplTraits(UnityEngine, Collision2D);
Collision2D::Collision2D(cpsObject v) : super(v) {}


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
    return s_method.invoke(*this).getValue<HideFlags>();
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
    return s_method.invoke(*this).getValue<void*>();
}

int Object::GetInstanceID() const
{
    cpsBindMethod("GetInstanceID");
    return s_method.invoke(*this).getValue<int>();
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
    return s_method.invoke(nullptr, args).getValue<MonoObject*>();
}
/*static*/ Object Object::Instantiate(Object original)
{
    cpsBindMethod("Instantiate", 1);
    void *args[] = { original };
    return s_method.invoke(nullptr, args).getValue<MonoObject*>();
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


cpsImplTraits(UnityEngine, AsyncOperation);
AsyncOperation::AsyncOperation(cpsObject v) : super(v) {}
bool AsyncOperation::get_isDone()
{
    cpsBindMethod("get_isDone");
    return s_method.invoke(*this).getValue<gboolean>() != 0;
}
float AsyncOperation::get_progress()
{
    cpsBindMethod("get_progress");
    return s_method.invoke(*this).getValue<float>();
}
int AsyncOperation::get_priority()
{
    cpsBindMethod("get_priority");
    return s_method.invoke(*this).getValue<int>();
}
void AsyncOperation::set_priority(int v)
{
    cpsBindMethod("set_priority");
    void *args[] = {&v};
    s_method.invoke(*this, args);
}
bool AsyncOperation::get_allowSceneActivation()
{
    cpsBindMethod("get_allowSceneActivation");
    return s_method.invoke(*this).getValue<gboolean>() != 0;
}
void AsyncOperation::set_allowSceneActivation(bool v_)
{
    cpsBindMethod("set_allowSceneActivation");
    gboolean v = v_;
    void *args[] = { &v };
    s_method.invoke(*this, args);
}


cpsImplTraits(UnityEngine, ResourceRequest);
ResourceRequest::ResourceRequest(cpsObject v) : super(v) {}
Object ResourceRequest::get_asset()
{
    cpsBindMethod("get_priority");
    return Object(s_method.invoke(*this));
}



cpsImplTraits(UnityEngine, Mesh);
Mesh::Mesh(cpsObject v) : super(v) {}
Matrix4x4 Mesh::get_bindposes()
{
    cpsBindMethod("get_bindposes");
    return s_method.invoke(*this).getValue<Matrix4x4>();
}
void Mesh::set_bindposes(const Matrix4x4 &v)
{
    cpsBindMethod("set_bindposes");
    void *args[] = { (void*)&v };
    s_method.invoke(*this, args);
}
int Mesh::get_blendShapeCount()
{
    cpsBindMethod("get_blendShapeCount");
    return s_method.invoke(*this).getValue<int>();
}
cpsTArray<BoneWeight> Mesh::get_boneWeights()
{
    cpsBindMethod("get_boneWeights");
    return cpsTArray<BoneWeight>(s_method.invoke(*this));
}
void Mesh::set_boneWeights(cpsTArray<BoneWeight> v)
{
    cpsBindMethod("set_boneWeights");
    void *args[] = { (cpsArray)v };
    s_method.invoke(*this, args);
}
Bounds Mesh::get_bounds()
{
    cpsBindMethod("get_bounds");
    return s_method.invoke(*this).getValue<Bounds>();
}
void Mesh::set_bounds(const Bounds &v)
{
    cpsBindMethod("set_bounds");
    void *args[] = { (void*)&v };
    s_method.invoke(*this, args);
}
cpsTArray<Color> Mesh::get_colors()
{
    cpsBindMethod("get_colors");
    return cpsTArray<Color>(s_method.invoke(*this));
}
void Mesh::set_colors(cpsTArray<Color> v)
{
    cpsBindMethod("set_colors");
    void *args[] = { (cpsArray)v };
    s_method.invoke(*this, args);
}
cpsTArray<Color32> Mesh::get_colors32()
{
    cpsBindMethod("get_colors32");
    return cpsTArray<Color32>(s_method.invoke(*this));
}
void Mesh::set_colors32(cpsTArray<Color32> v)
{
    cpsBindMethod("set_colors32");
    void *args[] = { (cpsArray)v };
    s_method.invoke(*this, args);
}
bool Mesh::get_isReadable()
{
    cpsBindMethod("get_isReadable");
    return s_method.invoke(*this).getValue<gboolean>() != 0;
}
cpsTArray<Vector3> Mesh::get_normals()
{
    cpsBindMethod("get_normals");
    return cpsTArray<Vector3>(s_method.invoke(*this));
}
void Mesh::set_normals(cpsTArray<Vector3> v)
{
    cpsBindMethod("set_normals");
    void *args[] = { (cpsArray)v };
    s_method.invoke(*this, args);
}
int Mesh::get_subMeshCount()
{
    cpsBindMethod("get_subMeshCount");
    return s_method.invoke(*this).getValue<int>();
}
void Mesh::set_subMeshCount(int v)
{
    cpsBindMethod("set_subMeshCount");
    void *args[] = { (void*)&v };
    s_method.invoke(*this, args);
}
cpsTArray<Vector4> Mesh::get_tangents()
{
    cpsBindMethod("get_tangents");
    return cpsTArray<Vector4>(s_method.invoke(*this));
}
void Mesh::set_tangents(cpsTArray<Vector4> v)
{
    cpsBindMethod("set_tangents");
    void *args[] = { (cpsArray)v };
    s_method.invoke(*this, args);
}
cpsTArray<int> Mesh::get_triangles()
{
    cpsBindMethod("get_triangles");
    return cpsTArray<int>(s_method.invoke(*this));
}
void Mesh::set_triangles(cpsTArray<int> v)
{
    cpsBindMethod("set_triangles");
    void *args[] = { (cpsArray)v };
    s_method.invoke(*this, args);
}
cpsTArray<Vector2> Mesh::get_uv()
{
    cpsBindMethod("get_uv");
    return cpsTArray<Vector2>(s_method.invoke(*this));
}
void Mesh::set_uv(cpsTArray<Vector2> v)
{
    cpsBindMethod("set_uv");
    void *args[] = { (cpsArray)v };
    s_method.invoke(*this, args);
}
cpsTArray<Vector2> Mesh::get_uv2()
{
    cpsBindMethod("get_uv2");
    return cpsTArray<Vector2>(s_method.invoke(*this));
}
void Mesh::set_uv2(cpsTArray<Vector2> v)
{
    cpsBindMethod("set_uv2");
    void *args[] = { (cpsArray)v };
    s_method.invoke(*this, args);
}
int Mesh::get_vertexCount()
{
    cpsBindMethod("get_vertexCount");
    return s_method.invoke(*this).getValue<int>();
}
cpsTArray<Vector3> Mesh::get_vertices()
{
    cpsBindMethod("get_vertices");
    return cpsTArray<Vector3>(s_method.invoke(*this));
}
void Mesh::set_vertices(cpsTArray<Vector3> v)
{
    cpsBindMethod("set_vertices");
    void *args[] = { (cpsArray)v };
    s_method.invoke(*this, args);
}

void Mesh::Clear(bool keepVertexLayout_)
{
    cpsBindMethod("Clear");
    gboolean keepVertexLayout = keepVertexLayout_;
    void *args[] = { &keepVertexLayout };
    s_method.invoke(*this, args);
}
//void Mesh::CombineMeshes(CombineInstance[] combine, bool mergeSubMeshes = true, bool useMatrices = true);
cpsString Mesh::GetBlendShapeName(int index)
{
    cpsBindMethod("GetBlendShapeName");
    void *args[] = { &index };
    return cpsString(s_method.invoke(*this, args));
}
cpsTArray<int> Mesh::GetIndices(int submesh)
{
    cpsBindMethod("GetIndices");
    void *args[] = { &submesh };
    return cpsTArray<int>(s_method.invoke(*this, args));
}
MeshTopology Mesh::GetTopology(int submesh)
{
    cpsBindMethod("GetTopology");
    void *args[] = { &submesh };
    return s_method.invoke(*this, args).getValue<MeshTopology>();
}
cpsTArray<int> Mesh::GetTriangles(int submesh)
{
    cpsBindMethod("GetTriangles");
    void *args[] = { &submesh };
    return cpsTArray<int>(s_method.invoke(*this, args));
}
void Mesh::MarkDynamic()
{
    cpsBindMethod("MarkDynamic");
    s_method.invoke(*this);
}
void Mesh::Optimize()
{
    cpsBindMethod("Optimize");
    s_method.invoke(*this);
}
void Mesh::RecalculateBounds()
{
    cpsBindMethod("RecalculateBounds");
    s_method.invoke(*this);
}
void Mesh::RecalculateNormals()
{
    cpsBindMethod("RecalculateNormals");
    s_method.invoke(*this);
}
void Mesh::SetIndices(cpsTArray<int> indices, MeshTopology topology, int submesh)
{
    cpsBindMethod("SetIndices");
    void *args[] = { (cpsArray)indices, &topology, &submesh };
    s_method.invoke(*this, args);
}
void Mesh::SetTriangles(cpsTArray<int> triangles, int submesh)
{
    cpsBindMethod("SetTriangles");
    void *args[] = { (cpsArray)triangles, &submesh };
    s_method.invoke(*this, args);
}



cpsImplTraits(UnityEngine, Material);
Material::Material(cpsObject v) : super(v) {}

Color Material::get_color()
{
    cpsBindMethod("get_color");
    return s_method.invoke(*this).getValue<Color>();
}
void Material::set_color(const Color &v)
{
    cpsBindMethod("set_color");
    void *args[] = { (void*)&v };
    s_method.invoke(*this, args);

}
Texture Material::get_mainTexture()
{
    cpsBindMethod("get_mainTexture");
    return Texture(s_method.invoke(*this));
}
void Material::set_mainTexture(Texture v)
{
    cpsBindMethod("set_mainTexture");
    void *args[] = { &v };
    s_method.invoke(*this, args);
}
Vector2 Material::get_mainTextureOffset()
{
    cpsBindMethod("get_mainTextureOffset");
    return s_method.invoke(*this).getValue<Vector2>();
}
void Material::set_mainTextureOffset(const Vector2 &v)
{
    cpsBindMethod("set_mainTextureOffset");
    void *args[] = { (void*)&v };
    s_method.invoke(*this, args);
}
Vector2 Material::get_mainTextureScale()
{
    cpsBindMethod("get_mainTextureScale");
    return s_method.invoke(*this).getValue<Vector2>();
}
void Material::set_mainTextureScale(const Vector2 &v)
{
    cpsBindMethod("set_mainTextureScale");
    void *args[] = { (void*)&v };
    s_method.invoke(*this, args);
}
int Material::get_passCount()
{
    cpsBindMethod("get_passCount");
    return s_method.invoke(*this).getValue<int>();
}
int Material::get_renderQueue()
{
    cpsBindMethod("get_renderQueue");
    return s_method.invoke(*this).getValue<int>();
}
void Material::set_renderQueue(int v)
{
    cpsBindMethod("set_renderQueue");
    void *args[] = { (void*)&v };
    s_method.invoke(*this, args);
}
Shader Material::get_shader()
{
    cpsBindMethod("get_shader");
    return Shader(s_method.invoke(*this));
}
void Material::set_shader(Shader v)
{
    cpsBindMethod("set_shader");
    void *args[] = { v };
    s_method.invoke(*this, args);
}
cpsTArray<cpsString> Material::get_shaderKeywords()
{
    cpsBindMethod("get_shaderKeywords");
    return cpsTArray<cpsString>(s_method.invoke(*this));
}
void Material::set_shaderKeywords(cpsTArray<cpsString> v)
{
    cpsBindMethod("set_shaderKeywords");
    void *args[] = { (cpsArray)v };
    s_method.invoke(*this, args);
}

void Material::CopyPropertiesFromMaterial(Material mat)
{
    static const char *names[] = {cpsTypename<Material>()};
    cpsBindMethod("CopyPropertiesFromMaterial", _countof(names), names);
    void *args[] = { mat };
    s_method.invoke(*this, args);
}
void Material::DisableKeyword(cpsString keyword)
{
    static const char *names[] = { cpsTypename<cpsString>() };
    cpsBindMethod("DisableKeyword");
    void *args[] = { keyword };
    s_method.invoke(*this, args);
}
void Material::EnableKeyword(cpsString keyword)
{
    static const char *names[] = { cpsTypename<cpsString>() };
    cpsBindMethod("EnableKeyword", _countof(names), names);
    void *args[] = { keyword };
    s_method.invoke(*this, args);
}
Color Material::GetColor(cpsString propertyName)
{
    static const char *names[] = { cpsTypename<cpsString>() };
    cpsBindMethod("GetColor", _countof(names), names);
    void *args[] = { propertyName };
    return s_method.invoke(*this, args).getValue<Color>();
}
Color Material::GetColor(int nameID)
{
    static const char *names[] = { cpsTypename<int>() };
    cpsBindMethod("GetColor", _countof(names), names);
    void *args[] = { &nameID };
    return s_method.invoke(*this, args).getValue<Color>();
}
float Material::GetFloat(cpsString propertyName)
{
    static const char *names[] = { cpsTypename<cpsString>() };
    cpsBindMethod("GetFloat", _countof(names), names);
    void *args[] = { propertyName };
    return s_method.invoke(*this, args).getValue<float>();
}
float Material::GetFloat(int nameID)
{
    static const char *names[] = { cpsTypename<int>() };
    cpsBindMethod("GetFloat", _countof(names), names);
    void *args[] = { &nameID };
    return s_method.invoke(*this, args).getValue<float>();
}
int Material::GetInt(cpsString propertyName)
{
    static const char *names[] = { cpsTypename<cpsString>() };
    cpsBindMethod("GetInt", _countof(names), names);
    void *args[] = { propertyName };
    return s_method.invoke(*this, args).getValue<int>();
}
int Material::GetInt(int nameID)
{
    static const char *names[] = { cpsTypename<int>() };
    cpsBindMethod("GetInt", _countof(names), names);
    void *args[] = { &nameID };
    return s_method.invoke(*this, args).getValue<int>();
}
Matrix4x4 Material::GetMatrix(cpsString propertyName)
{
    static const char *names[] = { cpsTypename<cpsString>() };
    cpsBindMethod("GetMatrix", _countof(names), names);
    void *args[] = { propertyName };
    return s_method.invoke(*this, args).getValue<Matrix4x4>();
}
Matrix4x4 Material::GetMatrix(int nameID)
{
    static const char *names[] = { cpsTypename<int>() };
    cpsBindMethod("GetMatrix", _countof(names), names);
    void *args[] = { &nameID };
    return s_method.invoke(*this, args).getValue<Matrix4x4>();
}
cpsString Material::GetTag(cpsString tag, bool searchFallbacks_, cpsString defaultValue)
{
    static const char *names[] = { cpsTypename<cpsString>(), cpsTypename<bool>(), cpsTypename<cpsString>() };
    cpsBindMethod("GetTag", _countof(names), names);
    gboolean searchFallbacks = searchFallbacks_;
    void *args[] = { tag, &searchFallbacks, defaultValue };
    return cpsString(s_method.invoke(*this, args));
}
Texture Material::GetTexture(cpsString propertyName)
{
    static const char *names[] = { cpsTypename<cpsString>() };
    cpsBindMethod("GetTexture", _countof(names), names);
    void *args[] = { propertyName };
    return Texture(s_method.invoke(*this, args));
}
Texture Material::GetTexture(int nameID)
{
    static const char *names[] = { cpsTypename<int>() };
    cpsBindMethod("GetTexture", _countof(names), names);
    void *args[] = { &nameID };
    return Texture(s_method.invoke(*this, args));
}
Vector2 Material::GetTextureOffset(cpsString propertyName)
{
    static const char *names[] = { cpsTypename<cpsString>() };
    cpsBindMethod("GetTextureOffset", _countof(names), names);
    void *args[] = { propertyName };
    return s_method.invoke(*this, args).getValue<Vector2>();
}
Vector2 Material::GetTextureScale(cpsString propertyName)
{
    static const char *names[] = { cpsTypename<cpsString>() };
    cpsBindMethod("GetTextureScale", _countof(names), names);
    void *args[] = { propertyName };
    return s_method.invoke(*this, args).getValue<Vector2>();
}
Vector4 Material::GetVector(cpsString propertyName)
{
    static const char *names[] = { cpsTypename<cpsString>() };
    cpsBindMethod("GetVector", _countof(names), names);
    void *args[] = { propertyName };
    return s_method.invoke(*this, args).getValue<Vector4>();
}
Vector4 Material::GetVector(int nameID)
{
    static const char *names[] = { cpsTypename<int>() };
    cpsBindMethod("GetVector", _countof(names), names);
    void *args[] = { &nameID };
    return s_method.invoke(*this, args).getValue<Vector4>();
}
bool Material::HasProperty(cpsString propertyName)
{
    static const char *names[] = { cpsTypename<cpsString>() };
    cpsBindMethod("HasProperty", _countof(names), names);
    void *args[] = { propertyName };
    return s_method.invoke(*this, args).getValue<gboolean>() != 0;
}
bool Material::HasProperty(int nameID)
{
    static const char *names[] = { cpsTypename<int>() };
    cpsBindMethod("HasProperty", _countof(names), names);
    void *args[] = { &nameID };
    return s_method.invoke(*this, args).getValue<gboolean>() != 0;
}
void Material::Lerp(Material start, Material end, float t)
{
    static const char *names[] = { cpsTypename<Material>(), cpsTypename<Material>(), cpsTypename<float>() };
    cpsBindMethod("Lerp", _countof(names), names);
    void *args[] = { start, end, &t };
    s_method.invoke(*this, args);
}
void Material::SetBuffer(cpsString propertyName, ComputeBuffer buffer)
{
    static const char *names[] = { cpsTypename<cpsString>(), cpsTypename<ComputeBuffer>() };
    cpsBindMethod("SetBuffer", _countof(names), names);
    void *args[] = { propertyName, buffer };
    s_method.invoke(*this, args);
}
void Material::SetColor(cpsString propertyName, const Color &color)
{
    static const char *names[] = { cpsTypename<cpsString>(), cpsTypename<Color>() };
    cpsBindMethod("SetColor", _countof(names), names);
    void *args[] = { propertyName, (void*)&color };
    s_method.invoke(*this, args);
}
void Material::SetColor(int nameID, const Color &color)
{
    static const char *names[] = { cpsTypename<int>(), cpsTypename<Color>() };
    cpsBindMethod("SetColor", _countof(names), names);
    void *args[] = { &nameID, (void*)&color };
    s_method.invoke(*this, args);
}
void Material::SetFloat(cpsString propertyName, float value)
{
    static const char *names[] = { cpsTypename<cpsString>(), cpsTypename<float>() };
    cpsBindMethod("SetFloat", _countof(names), names);
    void *args[] = { propertyName, &value };
    s_method.invoke(*this, args);
}
void Material::SetFloat(int nameID, float value)
{
    static const char *names[] = { cpsTypename<int>(), cpsTypename<float>() };
    cpsBindMethod("SetFloat", _countof(names), names);
    void *args[] = { &nameID, &value };
    s_method.invoke(*this, args);
}
void Material::SetInt(cpsString propertyName, int value)
{
    static const char *names[] = { cpsTypename<cpsString>(), cpsTypename<int>() };
    cpsBindMethod("SetInt", _countof(names), names);
    void *args[] = { propertyName, &value };
    s_method.invoke(*this, args);
}
void Material::SetInt(int nameID, int value)
{
    static const char *names[] = { cpsTypename<int>(), cpsTypename<int>() };
    cpsBindMethod("SetInt", _countof(names), names);
    void *args[] = { &nameID, &value };
    s_method.invoke(*this, args);
}
void Material::SetMatrix(cpsString propertyName, const Matrix4x4 &matrix)
{
    static const char *names[] = { cpsTypename<cpsString>(), cpsTypename<Matrix4x4>() };
    cpsBindMethod("SetMatrix", _countof(names), names);
    void *args[] = { propertyName, (void*)&matrix };
    s_method.invoke(*this, args);
}
void Material::SetMatrix(int nameID, const Matrix4x4 &matrix)
{
    static const char *names[] = { cpsTypename<int>(), cpsTypename<Matrix4x4>() };
    cpsBindMethod("SetMatrix", _countof(names), names);
    void *args[] = { &nameID, (void*)&matrix };
    s_method.invoke(*this, args);
}
bool Material::SetPass(int pass)
{
    static const char *names[] = { cpsTypename<int>() };
    cpsBindMethod("SetPass", _countof(names), names);
    void *args[] = { &pass };
    return s_method.invoke(*this, args).getValue<gboolean>() != 0;
}
void Material::SetTexture(cpsString propertyName, Texture texture)
{
    static const char *names[] = { cpsTypename<cpsString>(), cpsTypename<Texture>() };
    cpsBindMethod("SetTexture", _countof(names), names);
    void *args[] = { propertyName, texture };
    s_method.invoke(*this, args);
}
void Material::SetTexture(int nameID, Texture texture)
{
    static const char *names[] = { cpsTypename<int>(), cpsTypename<Texture>() };
    cpsBindMethod("SetTexture", _countof(names), names);
    void *args[] = { &nameID, texture };
    s_method.invoke(*this, args);
}
void Material::SetTextureOffset(cpsString propertyName, const Vector2 &offset)
{
    static const char *names[] = { cpsTypename<cpsString>(), cpsTypename<Vector2>() };
    cpsBindMethod("SetTextureOffset", _countof(names), names);
    void *args[] = { propertyName, (void*)&offset };
    s_method.invoke(*this, args);
}
void Material::SetTextureScale(cpsString propertyName, const Vector2 &scale)
{
    static const char *names[] = { cpsTypename<cpsString>(), cpsTypename<Vector2>() };
    cpsBindMethod("SetTextureScale", _countof(names), names);
    void *args[] = { propertyName, (void*)&scale };
    s_method.invoke(*this, args);
}
void Material::SetVector(cpsString propertyName, const Vector4 &vector)
{
    static const char *names[] = { cpsTypename<cpsString>(), cpsTypename<Vector4>() };
    cpsBindMethod("SetVector", _countof(names), names);
    void *args[] = { propertyName, (void*)&vector };
    s_method.invoke(*this, args);
}
void Material::SetVector(int nameID, const Vector4 &vector)
{
    static const char *names[] = { cpsTypename<int>(), cpsTypename<Vector4>() };
    cpsBindMethod("SetVector", _countof(names), names);
    void *args[] = { &nameID, (void*)&vector };
    s_method.invoke(*this, args);
}



cpsImplTraits(UnityEngine, MaterialPropertyBlock);
MaterialPropertyBlock::MaterialPropertyBlock(cpsObject v) : super(v) {}


cpsImplTraits(UnityEngine, Shader);
Shader::Shader(cpsObject v) : super(v) {}

bool Shader::get_isSupported()
{
    cpsBindMethod("get_isSupported");
    return s_method.invoke(*this).getValue<gboolean>()!=0;
}
int Shader::get_maximumLOD()
{
    cpsBindMethod("get_maximumLOD");
    return s_method.invoke(*this).getValue<int>();
}
void Shader::set_maximumLOD(int v)
{
    cpsBindMethod("set_maximumLOD");
    void *args[] = {&v};
    s_method.invoke(*this, args);
}
int Shader::get_renderQueue()
{
    cpsBindMethod("get_renderQueue");
    return s_method.invoke(*this).getValue<int>();
}
cpsString Shader::get_customEditor()
{
    cpsBindMethod("get_customEditor");
    return cpsString(s_method.invoke(*this));
}

/*static*/ int Shader::get_globalMaximumLOD()
{
    cpsBindMethod("get_globalMaximumLOD");
    return s_method.invoke(nullptr).getValue<int>();
}
/*static*/ void Shader::set_globalMaximumLOD(int v)
{
    cpsBindMethod("set_globalMaximumLOD");
    void *args[] = { &v };
    s_method.invoke(nullptr, args);
}

/*static*/ Shader Shader::Find(cpsString name)
{
    static const char *names[] = { cpsTypename<cpsString>() };
    cpsBindMethod("Find", _countof(names), names);
    void *args[] = { name };
    return Shader(s_method.invoke(nullptr, args));
}
/*static*/ int Shader::PropertyToID(cpsString name)
{
    static const char *names[] = { cpsTypename<cpsString>() };
    cpsBindMethod("PropertyToID", _countof(names), names);
    void *args[] = { name };
    return s_method.invoke(nullptr, args).getValue<int>();
}
/*static*/ void Shader::SetGlobalBuffer(cpsString propertyName, ComputeBuffer buffer)
{
    static const char *names[] = { cpsTypename<cpsString>(), cpsTypename<ComputeBuffer>() };
    cpsBindMethod("SetGlobalBuffer", _countof(names), names);
    void *args[] = { propertyName, buffer };
    s_method.invoke(nullptr, args);
}
/*static*/ void Shader::SetGlobalColor(cpsString propertyName, const Color &color)
{
    static const char *names[] = { cpsTypename<cpsString>(), cpsTypename<Color>() };
    cpsBindMethod("SetGlobalColor", _countof(names), names);
    void *args[] = { propertyName, (void*)&color };
    s_method.invoke(nullptr, args);
}
/*static*/ void Shader::SetGlobalColor(int nameID, const Color &color)
{
    static const char *names[] = { cpsTypename<int>(), cpsTypename<Color>() };
    cpsBindMethod("SetGlobalColor", _countof(names), names);
    void *args[] = { &nameID, (void*)&color };
    s_method.invoke(nullptr, args);
}
/*static*/ void Shader::SetGlobalFloat(cpsString propertyName, float value)
{
    static const char *names[] = { cpsTypename<cpsString>(), cpsTypename<float>() };
    cpsBindMethod("SetGlobalFloat", _countof(names), names);
    void *args[] = { propertyName, &value };
    s_method.invoke(nullptr, args);
}
/*static*/ void Shader::SetGlobalFloat(int nameID, float value)
{
    static const char *names[] = { cpsTypename<int>(), cpsTypename<float>() };
    cpsBindMethod("SetGlobalFloat", _countof(names), names);
    void *args[] = { &nameID, &value };
    s_method.invoke(nullptr, args);
}
/*static*/ void Shader::SetGlobalInt(cpsString propertyName, int value)
{
    static const char *names[] = { cpsTypename<cpsString>(), cpsTypename<int>() };
    cpsBindMethod("SetGlobalInt", _countof(names), names);
    void *args[] = { propertyName, &value };
    s_method.invoke(nullptr, args);
}
/*static*/ void Shader::SetGlobalInt(int nameID, int value)
{
    static const char *names[] = { cpsTypename<int>(), cpsTypename<int>() };
    cpsBindMethod("SetGlobalInt", _countof(names), names);
    void *args[] = { &nameID, &value };
    s_method.invoke(nullptr, args);
}
/*static*/ void Shader::SetGlobalMatrix(cpsString propertyName, const Matrix4x4 &mat)
{
    static const char *names[] = { cpsTypename<cpsString>(), cpsTypename<Matrix4x4>() };
    cpsBindMethod("SetGlobalMatrix", _countof(names), names);
    void *args[] = { propertyName, (void*)&mat };
    s_method.invoke(nullptr, args);
}
/*static*/ void Shader::SetGlobalMatrix(int nameID, const Matrix4x4 &mat)
{
    static const char *names[] = { cpsTypename<int>(), cpsTypename<Matrix4x4>() };
    cpsBindMethod("SetGlobalMatrix", _countof(names), names);
    void *args[] = { &nameID, (void*)&mat };
    s_method.invoke(nullptr, args);
}
/*static*/ void Shader::SetGlobalTexture(cpsString propertyName, Texture tex)
{
    static const char *names[] = { cpsTypename<cpsString>(), cpsTypename<Texture>() };
    cpsBindMethod("SetGlobalTexture", _countof(names), names);
    void *args[] = { propertyName, tex };
    s_method.invoke(nullptr, args);
}
/*static*/ void Shader::SetGlobalTexture(int nameID, Texture tex)
{
    static const char *names[] = { cpsTypename<int>(), cpsTypename<Texture>() };
    cpsBindMethod("SetGlobalTexture", _countof(names), names);
    void *args[] = { &nameID, tex };
    s_method.invoke(nullptr, args);
}
/*static*/ void Shader::SetGlobalVector(cpsString propertyName, const Vector4 &vec)
{
    static const char *names[] = { cpsTypename<cpsString>(), cpsTypename<Vector4>() };
    cpsBindMethod("SetGlobalVector", _countof(names), names);
    void *args[] = { propertyName, (void*)&vec };
    s_method.invoke(nullptr, args);
}
/*static*/ void Shader::SetGlobalVector(int nameID, const Vector4 &vec)
{
    static const char *names[] = { cpsTypename<int>(), cpsTypename<Vector4>() };
    cpsBindMethod("SetGlobalVector", _countof(names), names);
    void *args[] = { &nameID, (void*)&vec };
    s_method.invoke(nullptr, args);
}
/*static*/ void Shader::WarmupAllShaders()
{
    cpsBindMethod("WarmupAllShaders", 0);
}



cpsImplTraits(UnityEngine, Texture);
Texture::Texture(cpsObject v) : super(v) {}

cpsImplTraits(UnityEngine, Texture2D);
Texture2D::Texture2D(cpsObject v) : super(v) {}

cpsImplTraits(UnityEngine, RenderTexture);
RenderTexture::RenderTexture(cpsObject v) : super(v) {}

cpsImplTraits(UnityEngine, Cubemap);
Cubemap::Cubemap(cpsObject v) : super(v) {}



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
    return ret.getValue<int>();
}
int ComputeBuffer::get_stride()
{
    cpsBindMethod("get_stride", 0);
    cpsObject ret = s_method.invoke(*this);
    return ret.getValue<int>();
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



cpsImplTraits(UnityEngine, PhysicsMaterial2D);
PhysicsMaterial2D::PhysicsMaterial2D(cpsObject v) : super(v) {}



cpsImplTraits(UnityEngine, Motion);
Motion::Motion(cpsObject v) : super(v) {}



cpsImplTraits(UnityEngine, AnimationClip);
AnimationClip::AnimationClip(cpsObject v) : super(v) {}



cpsImplTraits(UnityEngine, GameObject);
GameObject::GameObject(cpsObject v) : super(v) {}
void GameObject::BroadcastMessage(cpsString methodName, Object parameter, SendMessageOptions options)
{
    cpsBindMethod("BroadcastMessage");
    void *args[] = {methodName, parameter, &options};
    s_method.invoke(*this, args);
}
bool GameObject::CompareTag(cpsString tag)
{
    cpsBindMethod("CompareTag");
    void *args[] = { tag };
    return s_method.invoke(*this, args).getValue<gboolean>() != 0;
}
void GameObject::SampleAnimation(AnimationClip animation, float time)
{
    cpsBindMethod("SampleAnimation");
    void *args[] = { animation, &time };
    s_method.invoke(*this, args);
}
void GameObject::SendMessage(cpsString methodName, Object value, SendMessageOptions options)
{
    cpsBindMethod("SendMessage");
    void *args[] = { methodName, value, &options };
    s_method.invoke(*this, args);
}
void GameObject::SendMessageUpwards(cpsString methodName, Object value, SendMessageOptions options)
{
    cpsBindMethod("SendMessageUpwards");
    void *args[] = { methodName, value, &options };
    s_method.invoke(*this, args);
}
void GameObject::SetActive(bool value_)
{
    cpsBindMethod("SetActive");
    gboolean value = value_;
    void *args[] = { &value };
    s_method.invoke(*this, args);
}

/*static*/ GameObject GameObject::CreatePrimitive(PrimitiveType type)
{
    cpsBindMethod("CreatePrimitive");
    void *args[] = { &type };
    return GameObject(s_method.invoke(nullptr, args));
}
/*static*/ GameObject GameObject::Find(cpsString name)
{
    cpsBindMethod("Find");
    void *args[] = { name };
    return GameObject(s_method.invoke(nullptr, args));
}
/*static*/ cpsTArray<GameObject> GameObject::FindGameObjectsWithTag(cpsString tag)
{
    cpsBindMethod("FindGameObjectsWithTag");
    void *args[] = { tag };
    return cpsTArray<GameObject>(s_method.invoke(nullptr, args));
}
/*static*/ GameObject GameObject::FindWithTag(cpsString tag)
{
    cpsBindMethod("FindWithTag");
    void *args[] = { tag };
    return GameObject(s_method.invoke(nullptr, args));
}



cpsImplTraits(UnityEngine, Behaviour);
Behaviour::Behaviour(cpsObject obj) : super(obj) {}

bool Behaviour::get_enabled() const
{
    cpsBindMethod("get_enabled");
    return s_method.invoke(*this).getValue<gboolean>() != 0;
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
    return s_method.invoke(*this).getValue<MonoObject*>();
}
bool Component::get_active() const
{
    cpsBindMethod("get_active");
    return s_method.invoke(*this).getValue<gboolean>()!=0;
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
    return s_method.invoke(*this, args).getValue<gboolean>()!=0;
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
    return s_method.invoke(*this).getValue<Vector3>();
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
    return s_method.invoke(*this).getValue<Vector3>();
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
    return s_method.invoke(*this).getValue<Vector3>();
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
    return s_method.invoke(*this).getValue<Vector3>();
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
    return s_method.invoke(*this).getValue<Vector3>();
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
    return s_method.invoke(*this).getValue<Vector3>();
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
    return s_method.invoke(*this).getValue<Quaternion>();
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
    return s_method.invoke(*this).getValue<Quaternion>();
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
    return s_method.invoke(*this).getValue<Vector3>();
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
    return s_method.invoke(*this).getValue<Matrix4x4>();
}
Matrix4x4 Transform::get_localToWorldMatrix() const
{
    cpsBindMethod("get_localToWorldMatrix");
    return s_method.invoke(*this).getValue<Matrix4x4>();
}

Transform Transform::get_root()
{
    cpsBindMethod("get_root");
    return s_method.invoke(*this);
}
int Transform::get_childCount()
{
    cpsBindMethod("get_childCount");
    return s_method.invoke(*this).getValue<int>();
}
Vector3 Transform::get_lossyScale()
{
    cpsBindMethod("get_lossyScale");
    return s_method.invoke(*this).getValue<Vector3>();
}

bool Transform::get_hasChanged()
{
    cpsBindMethod("get_hasChanged");
    return s_method.invoke(*this).getValue<gboolean>()!=0;
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
    return s_method.invoke(*this, args).getValue<Vector3>();
}

Vector3 Transform::InverseTransformDirection(const Vector3& v)
{
    cpsBindMethod("InverseTransformDirection", 1);
    void *args[] = { (void*)&v };
    return s_method.invoke(*this, args).getValue<Vector3>();
}

Vector3 Transform::TransformPoint(const Vector3& v)
{
    cpsBindMethod("TransformPoint", 1);
    void *args[] = { (void*)&v };
    return s_method.invoke(*this, args).getValue<Vector3>();
}

Vector3 Transform::InverseTransformPoint(const Vector3& v)
{
    cpsBindMethod("InverseTransformPoint", 1);
    void *args[] = { (void*)&v };
    return s_method.invoke(*this, args).getValue<Vector3>();
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
    return s_method.invoke(*this).getValue<int>();;
}

Transform Transform::Find(cpsString name)
{
    cpsBindMethod("Find", 1);
    void *args[] = { name };
    return s_method.invoke(*this, args).getValue<MonoObject*>();
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
    return s_method.invoke(*this, args).getValue<gboolean>()!=0;
}

Transform Transform::FindChild(cpsString name)
{
    cpsBindMethod("FindChild", 1);
    void *args[] = { name };
    return s_method.invoke(*this, args).getValue<MonoObject*>();
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
    return s_method.invoke(*this, args).getValue<MonoObject*>();
}

int Transform::GetChildCount()
{
    cpsBindMethod("GetChildCount", 0);
    return s_method.invoke(*this).getValue<int>();
}

bool Transform::IsNonUniformScaleTransform()
{
    cpsBindMethod("IsNonUniformScaleTransform", 0);
    return s_method.invoke(*this).getValue<gboolean>()!=0;
}



cpsImplTraits(UnityEngine, Rigidbody);
Rigidbody::Rigidbody(cpsObject obj) : super(obj) {}

float Rigidbody::get_angularDrag()
{
    cpsBindMethod("get_angularDrag");
    return s_method.invoke(*this).getValue<float>();
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
    return s_method.invoke(*this).getValue<Vector3>();
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
    return s_method.invoke(*this).getValue<Vector3>();
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
    return s_method.invoke(*this).getValue<CollisionDetectionMode>();
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
    return s_method.invoke(*this).getValue<RigidbodyConstraints>();
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
    return s_method.invoke(*this).getValue<gboolean>() != 0;
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
    return s_method.invoke(*this).getValue<float>();
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
    return s_method.invoke(*this).getValue<gboolean>() != 0;
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
    return s_method.invoke(*this).getValue<Vector3>();
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
    return s_method.invoke(*this).getValue<Quaternion>();
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
    return s_method.invoke(*this).getValue<RigidbodyInterpolation>();
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
    return s_method.invoke(*this).getValue<gboolean>() != 0;
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
    return s_method.invoke(*this).getValue<float>();
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
    return s_method.invoke(*this).getValue<float>();
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
    return s_method.invoke(*this).getValue<Vector3>();
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
    return s_method.invoke(*this).getValue<Quaternion>();
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
    return s_method.invoke(*this).getValue<float>();
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
    return s_method.invoke(*this).getValue<float>();
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
    return s_method.invoke(*this).getValue<int>();
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
    return s_method.invoke(*this).getValue<gboolean>() != 0;
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
    return s_method.invoke(*this).getValue<gboolean>() != 0;
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
    return s_method.invoke(*this).getValue<Vector3>();
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
    return s_method.invoke(*this).getValue<Vector3>();
}

void Rigidbody::AddExplosionForce(float explosionForce, const Vector3 &explosionPosition, float explosionRadius, float upwardsModifier, ForceMode mode)
{
    static const char *names[] = { cpsTypename<float>(), cpsTypename<Vector3>(), cpsTypename<float>(), cpsTypename<float>(), cpsTypenameRef<ForceMode>() };
    cpsBindMethod("AddExplosionForce", _countof(names), names);
    void *args[] = { (void*)&explosionForce, (void*)&explosionPosition, (void*)&explosionRadius, (void*)&upwardsModifier, (void*)&mode };
    s_method.invoke(*this, args);
}
void Rigidbody::AddForce(const Vector3 &force, ForceMode mode)
{
    static const char *names[] = { cpsTypename<Vector3>(), cpsTypename<ForceMode>() };
    cpsBindMethod("AddForce", _countof(names), names);
    void *args[] = { (void*)&force, (void*)&mode };
    s_method.invoke(*this, args);
}
void Rigidbody::AddForceAtPosition(const Vector3 &force, const Vector3 &position, ForceMode mode)
{
    static const char *names[] = { cpsTypename<Vector3>(), cpsTypename<Vector3>(), cpsTypename<ForceMode>() };
    cpsBindMethod("AddForceAtPosition", _countof(names), names);
    void *args[] = { (void*)&force, (void*)&position, (void*)&mode };
    s_method.invoke(*this, args);
}
void Rigidbody::AddRelativeForce(const Vector3 &force, ForceMode mode)
{
    static const char *names[] = { cpsTypename<Vector3>(), cpsTypename<ForceMode>() };
    cpsBindMethod("AddRelativeForce", _countof(names), names);
    void *args[] = { (void*)&force, (void*)&mode };
    s_method.invoke(*this, args);
}
void Rigidbody::AddRelativeTorque(const Vector3 &torque, ForceMode mode)
{
    static const char *names[] = { cpsTypename<Vector3>(), cpsTypename<ForceMode>() };
    cpsBindMethod("AddRelativeTorque", _countof(names), names);
    void *args[] = { (void*)&torque, (void*)&mode };
    s_method.invoke(*this, args);
}
void Rigidbody::AddTorque(const Vector3 &torque, ForceMode mode)
{
    static const char *names[] = { cpsTypename<Vector3>(), cpsTypename<ForceMode>() };
    cpsBindMethod("AddTorque", _countof(names), names);
    void *args[] = { (void*)&torque, (void*)&mode };
    s_method.invoke(*this, args);
}
Vector3 Rigidbody::ClosestPointOnBounds(const Vector3 &position)
{
    static const char *names[] = { cpsTypename<Vector3>() };
    cpsBindMethod("ClosestPointOnBounds", _countof(names), names);
    void *args[] = { (void*)&position };
    return s_method.invoke(*this, args).getValue<Vector3>();
}
Vector3 Rigidbody::GetPointVelocity(const Vector3 &worldPoint)
{
    static const char *names[] = { cpsTypename<Vector3>() };
    cpsBindMethod("GetPointVelocity", _countof(names), names);
    void *args[] = { (void*)&worldPoint };
    return s_method.invoke(*this, args).getValue<Vector3>();
}
Vector3 Rigidbody::GetRelativePointVelocity(const Vector3 &relativePoint)
{
    static const char *names[] = { cpsTypename<Vector3>() };
    cpsBindMethod("GetRelativePointVelocity", _countof(names), names);
    void *args[] = { (void*)&relativePoint };
    return s_method.invoke(*this, args).getValue<Vector3>();
}
bool Rigidbody::IsSleeping()
{
    cpsBindMethod("IsSleeping", 0);
    return s_method.invoke(*this).getValue<gboolean>() != 0;
}
void Rigidbody::MovePosition(const Vector3 &position)
{
    static const char *names[] = { cpsTypename<Vector3>() };
    cpsBindMethod("MovePosition", _countof(names), names);
    void *args[] = { (void*)&position };
    s_method.invoke(*this, args);
}
void Rigidbody::MoveRotation(const Quaternion &rot)
{
    static const char *names[] = { cpsTypename<Quaternion>() };
    cpsBindMethod("MoveRotation", _countof(names), names);
    void *args[] = { (void*)&rot };
    s_method.invoke(*this, args);
}
void Rigidbody::SetDensity(float density)
{
    static const char *names[] = { cpsTypename<float>() };
    cpsBindMethod("SetDensity", _countof(names), names);
    void *args[] = { (void*)&density };
    s_method.invoke(*this, args);
}
void Rigidbody::Sleep()
{
    cpsBindMethod("Sleep", 0);
    s_method.invoke(*this);
}
bool Rigidbody::SweepTest(const Vector3 &direction, RaycastHit &hitInfo, float distance)
{
    static const char *names[] = { cpsTypename<Vector3>(), cpsTypenameRef<RaycastHit>(), cpsTypename<float>() };
    cpsBindMethod("SweepTest", _countof(names), names);
    void *args[] = { (void*)&direction, (void*)&hitInfo, (void*)&distance };
    cpsObject ret = s_method.invoke(*this, args);
    return ret.getValue<gboolean>()!=0;
}
cpsTArray<RaycastHit> Rigidbody::SweepTestAll(const Vector3 &direction, float distance)
{
    static const char *names[] = { cpsTypename<Vector3>(), cpsTypename<float>() };
    cpsBindMethod("SweepTestAll", _countof(names), names);
    void *args[] = { (void*)&direction, (void*)&distance };
    cpsObject ret = s_method.invoke(*this, args);
    return cpsTArray<RaycastHit>(ret);
}
void Rigidbody::WakeUp()
{
    cpsBindMethod("WakeUp", 0);
    s_method.invoke(*this);
}




cpsImplTraits(UnityEngine, Rigidbody2D);
Rigidbody2D::Rigidbody2D(cpsObject obj) : super(obj) {}



cpsImplTraits(UnityEngine, Collider);
Collider::Collider(cpsObject obj) : super(obj) {}

bool Collider::get_enabled()
{
    cpsBindMethod("get_enabled");
    return s_method.invoke(*this).getValue<gboolean>() != 0;
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
    return s_method.invoke(*this).getValue<MonoObject*>();
}
bool Collider::get_isTrigger()
{
    cpsBindMethod("get_isTrigger");
    return s_method.invoke(*this).getValue<gboolean>() != 0;
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
    return s_method.invoke(*this).getValue<MonoObject*>();
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
    return s_method.invoke(*this).getValue<MonoObject*>();
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
    return s_method.invoke(*this).getValue<Bounds>();
}

Vector3 Collider::ClosestPointOnBounds(const Vector3 &v)
{
    cpsBindMethod("ClosestPointOnBounds");
    void *args[] = { (void*)&v };
    return s_method.invoke(*this, args).getValue<Vector3>();
}

bool Collider::Raycast(const Ray &ray, RaycastHit &hit, float dist)
{
    cpsBindMethod("Raycast");
    void *args[] = { (void*)&ray, (void*)&hit, &dist };
    return s_method.invoke(*this, args).getValue<gboolean>() != 0;
}


cpsImplTraits(UnityEngine, BoxCollider);
BoxCollider::BoxCollider(cpsObject obj) : super(obj) {}
Vector3 BoxCollider::get_center()
{
    cpsBindMethod("get_bounds");
    return s_method.invoke(*this).getValue<Vector3>();
}
void BoxCollider::set_center(const Vector3 &v)
{
    cpsBindMethod("set_center");
    void *args[] = {(void*)&v};
    s_method.invoke(*this, args);
}
Vector3 BoxCollider::get_size()
{
    cpsBindMethod("get_size");
    return s_method.invoke(*this).getValue<Vector3>();
}
void BoxCollider::set_size(const Vector3 &v)
{
    cpsBindMethod("set_size");
    void *args[] = { (void*)&v };
    s_method.invoke(*this, args);
}


cpsImplTraits(UnityEngine, SphereCollider);
SphereCollider::SphereCollider(cpsObject obj) : super(obj) {}

Vector3 SphereCollider::get_center()
{
    cpsBindMethod("get_center");
    return s_method.invoke(*this).getValue<Vector3>();
}
void SphereCollider::set_center(const Vector3 &v)
{
    cpsBindMethod("set_center");
    void *args[] = { (void*)&v };
    s_method.invoke(*this, args);
}
float SphereCollider::get_radius()
{
    cpsBindMethod("get_radius");
    return s_method.invoke(*this).getValue<float>();
}
void SphereCollider::set_radius(float v)
{
    cpsBindMethod("set_radius");
    void *args[] = { (void*)&v };
    s_method.invoke(*this, args);
}


cpsImplTraits(UnityEngine, CapsuleCollider);
CapsuleCollider::CapsuleCollider(cpsObject obj) : super(obj) {}

Vector3 CapsuleCollider::get_center()
{
    cpsBindMethod("get_center");
    return s_method.invoke(*this).getValue<float>();
}
void CapsuleCollider::set_center(const Vector3 &v)
{
    cpsBindMethod("set_center");
    void *args[] = { (void*)&v };
    s_method.invoke(*this, args);
}
CapsuleCollider::Direction CapsuleCollider::get_direction()
{
    cpsBindMethod("get_direction");
    return s_method.invoke(*this).getValue<Direction>();
}
void CapsuleCollider::set_direction(Direction v)
{
    cpsBindMethod("set_direction");
    void *args[] = { (void*)&v };
    s_method.invoke(*this, args);
}
float CapsuleCollider::get_height()
{
    cpsBindMethod("get_height");
    return s_method.invoke(*this).getValue<float>();
}
void CapsuleCollider::set_height(float v)
{
    cpsBindMethod("set_height");
    void *args[] = { (void*)&v };
    s_method.invoke(*this, args);
}
float CapsuleCollider::get_radius()
{
    cpsBindMethod("get_radius");
    return s_method.invoke(*this).getValue<float>();
}
void CapsuleCollider::set_radius(float v)
{
    cpsBindMethod("set_radius");
    void *args[] = { (void*)&v };
    s_method.invoke(*this, args);
}

cpsImplTraits(UnityEngine, MeshCollider);
MeshCollider::MeshCollider(cpsObject obj) : super(obj) {}

bool MeshCollider::get_convex()
{
    cpsBindMethod("get_convex");
    return s_method.invoke(*this).getValue<gboolean>() != 0;
}
void MeshCollider::set_convex(bool v_)
{
    cpsBindMethod("set_convex");
    gboolean v = v_;
    void *args[] = { &v };
    s_method.invoke(*this, args);
}
Mesh MeshCollider::get_sharedMesh()
{
    cpsBindMethod("get_sharedMesh");
    return Mesh(s_method.invoke(*this));
}
void MeshCollider::set_sharedMesh(Mesh v)
{
    cpsBindMethod("set_sharedMesh");
    void *args[] = { v };
    s_method.invoke(*this, args);
}
bool MeshCollider::get_smoothSphereCollisions()
{
    cpsBindMethod("get_smoothSphereCollisions");
    return s_method.invoke(*this).getValue<gboolean>() != 0;
}
void MeshCollider::set_smoothSphereCollisions(bool v_)
{
    cpsBindMethod("set_smoothSphereCollisions");
    gboolean v = v_;
    void *args[] = { &v };
    s_method.invoke(*this, args);
}



cpsImplTraits(UnityEngine, Collider2D);
Collider2D::Collider2D(cpsObject obj) : super(obj) {}

Rigidbody2D Collider2D::get_attachedRigidbody()
{
    cpsBindMethod("get_attachedRigidbody");
    return Rigidbody2D(s_method.invoke(*this));
}
Bounds Collider2D::get_bounds()
{
    cpsBindMethod("get_bounds");
    return s_method.invoke(*this).getValue<Bounds>();
}
bool Collider2D::get_isTrigger()
{
    cpsBindMethod("get_isTrigger");
    return s_method.invoke(*this).getValue<gboolean>() != 0;
}
void Collider2D::set_isTrigger(bool v_)
{
    cpsBindMethod("set_isTrigger");
    gboolean v = v_;
    void *args[] = {&v};
    s_method.invoke(*this, args);
}
int Collider2D::get_shapeCount()
{
    cpsBindMethod("get_shapeCount");
    return s_method.invoke(*this).getValue<int>() != 0;
}
PhysicsMaterial2D Collider2D::get_sharedMaterial()
{
    cpsBindMethod("get_sharedMaterial");
    return PhysicsMaterial2D(s_method.invoke(*this));
}
void Collider2D::set_sharedMaterial(PhysicsMaterial2D v)
{
    cpsBindMethod("set_sharedMaterial");
    void *args[] = { v };
    s_method.invoke(*this, args);
}

bool Collider2D::OverlapPoint(const Vector2 &v)
{
    cpsBindMethod("OverlapPoint");
    void *args[] = { (void*)&v };
    return s_method.invoke(*this, args).getValue<gboolean>() != 0;
}


cpsImplTraits(UnityEngine, BoxCollider2D);
BoxCollider2D::BoxCollider2D(cpsObject obj) : super(obj) {}

Vector2 BoxCollider2D::get_center()
{
    cpsBindMethod("get_center");
    return s_method.invoke(*this).getValue<Vector2>();

}
void BoxCollider2D::set_center(const Vector2 &v)
{
    cpsBindMethod("set_center");
    void *args[] = { (void*)&v };
    s_method.invoke(*this, args);
}
Vector2 BoxCollider2D::get_size()
{
    cpsBindMethod("get_size");
    return s_method.invoke(*this).getValue<Vector2>();
}
void BoxCollider2D::set_size(const Vector2 &v)
{
    cpsBindMethod("set_size");
    void *args[] = { (void*)&v };
    s_method.invoke(*this, args);
}

cpsImplTraits(UnityEngine, CircleCollider2D);
CircleCollider2D::CircleCollider2D(cpsObject obj) : super(obj) {}

Vector2 CircleCollider2D::get_center()
{
    cpsBindMethod("get_center");
    return s_method.invoke(*this).getValue<Vector2>();
}
void CircleCollider2D::set_center(const Vector2 &v)
{
    cpsBindMethod("set_center");
    void *args[] = { (void*)&v };
    s_method.invoke(*this, args);
}
float CircleCollider2D::get_radius()
{
    cpsBindMethod("get_radius");
    return s_method.invoke(*this).getValue<float>();
}
void CircleCollider2D::set_radius(float v)
{
    cpsBindMethod("set_radius");
    void *args[] = { (void*)&v };
    s_method.invoke(*this, args);
}

cpsImplTraits(UnityEngine, PolygonCollider2D);
PolygonCollider2D::PolygonCollider2D(cpsObject obj) : super(obj) {}

int PolygonCollider2D::get_pathCount()
{
    cpsBindMethod("get_pathCount");
    return s_method.invoke(*this).getValue<int>();
}
void PolygonCollider2D::set_pathCount(int v)
{
    cpsBindMethod("set_pathCount");
    void *args[] = { (void*)&v };
    s_method.invoke(*this, args);
}
cpsTArray<Vector2> PolygonCollider2D::get_points()
{
    cpsBindMethod("get_points");
    return cpsTArray<Vector2>(s_method.invoke(*this));
}
void PolygonCollider2D::set_points(cpsTArray<Vector2> v)
{
    cpsBindMethod("set_points");
    void *args[] = { (cpsArray)v };
    s_method.invoke(*this, args);
}


cpsImplTraits(UnityEngine, Camera);
Camera::Camera(cpsObject obj) : super(obj) {}

/*static*/ cpsTArray<Camera> Camera::get_allCameras()
{
    cpsBindMethod("get_allCameras");
    return cpsTArray<Camera>(s_method.invoke(nullptr));
}
/*static*/ int Camera::get_allCamerasCount()
{
    cpsBindMethod("get_allCamerasCount");
    return s_method.invoke(nullptr).getValue<int>();
}
/*static*/ Camera Camera::get_current()
{
    cpsBindMethod("get_current");
    return Camera(s_method.invoke(nullptr));
}
/*static*/ Camera Camera::get_main()
{
    cpsBindMethod("get_main");
    return Camera(s_method.invoke(nullptr));
}
/*static*/ int Camera::GetAllCameras(cpsTArray<Camera> &v)
{
    cpsBindMethod("GetAllCameras");
    void *args[] = { (cpsArray)v };
    return s_method.invoke(nullptr, args).getValue<int>();
}
/*static*/ void Camera::SetupCurrent(Camera cur)
{
    cpsBindMethod("SetupCurrent");
    void *args[] = { cur };
    s_method.invoke(nullptr, args);
}

RenderingPath Camera::get_actualRenderingPath()
{
    cpsBindMethod("get_actualRenderingPath");
    return s_method.invoke(*this).getValue<RenderingPath>();
}
float Camera::get_aspect()
{
    cpsBindMethod("get_aspect");
    return s_method.invoke(*this).getValue<float>();
}
void Camera::set_aspect(float v)
{
    cpsBindMethod("set_aspect");
    void *args[] = { &v };
    s_method.invoke(*this, args);
}
Color Camera::get_backgroundColor()
{
    cpsBindMethod("get_backgroundColor");
    return s_method.invoke(*this).getValue<Color>();
}
void Camera::set_backgroundColor(const Color &v)
{
    cpsBindMethod("set_backgroundColor");
    void *args[] = { (void*)&v };
    s_method.invoke(*this, args);
}
Matrix4x4 Camera::get_cameraToWorldMatrix()
{
    cpsBindMethod("get_cameraToWorldMatrix");
    return s_method.invoke(*this).getValue<Matrix4x4>();
}
CameraClearFlags Camera::get_clearFlags()
{
    cpsBindMethod("get_clearFlags");
    return s_method.invoke(*this).getValue<CameraClearFlags>();
}
void Camera::set_clearFlags(CameraClearFlags v)
{
    cpsBindMethod("set_clearFlags");
    void *args[] = { (void*)&v };
    s_method.invoke(*this, args);
}
bool Camera::get_clearStencilAfterLightingPass()
{
    cpsBindMethod("get_clearStencilAfterLightingPass");
    return s_method.invoke(*this).getValue<gboolean>() != 0;
}
void Camera::set_clearStencilAfterLightingPass(bool v_)
{
    cpsBindMethod("set_clearStencilAfterLightingPass");
    gboolean v = v_;
    void *args[] = { (void*)&v };
    s_method.invoke(*this, args);
}
int Camera::get_cullingMask()
{
    cpsBindMethod("get_cullingMask");
    return s_method.invoke(*this).getValue<int>();
}
void Camera::set_cullingMask(int v)
{
    cpsBindMethod("set_cullingMask");
    void *args[] = { (void*)&v };
    s_method.invoke(*this, args);
}
float Camera::get_depth()
{
    cpsBindMethod("get_depth");
    return s_method.invoke(*this).getValue<float>();
}
void Camera::set_depth(float v)
{
    cpsBindMethod("set_depth");
    void *args[] = { (void*)&v };
    s_method.invoke(*this, args);
}
DepthTextureMode Camera::get_depthTextureMode()
{
    cpsBindMethod("get_depthTextureMode");
    return s_method.invoke(*this).getValue<DepthTextureMode>();
}
void Camera::set_depthTextureMode(DepthTextureMode v)
{
    cpsBindMethod("set_depthTextureMode");
    void *args[] = { (void*)&v };
    s_method.invoke(*this, args);
}
int Camera::get_eventMask()
{
    cpsBindMethod("get_eventMask");
    return s_method.invoke(*this).getValue<int>();
}
void Camera::set_eventMask(int v)
{
    cpsBindMethod("set_eventMask");
    void *args[] = { (void*)&v };
    s_method.invoke(*this, args);
}
float Camera::get_farClipPlane()
{
    cpsBindMethod("get_farClipPlane");
    return s_method.invoke(*this).getValue<float>();
}
void Camera::set_farClipPlane(float v)
{
    cpsBindMethod("set_farClipPlane");
    void *args[] = { (void*)&v };
    s_method.invoke(*this, args);
}
float Camera::get_fieldOfView()
{
    cpsBindMethod("get_fieldOfView");
    return s_method.invoke(*this).getValue<float>();
}
void Camera::set_fieldOfView(float v)
{
    cpsBindMethod("set_fieldOfView");
    void *args[] = { (void*)&v };
    s_method.invoke(*this, args);
}
bool Camera::get_hdr()
{
    cpsBindMethod("get_hdr");
    return s_method.invoke(*this).getValue<gboolean>() != 0;
}
void Camera::set_hdr(bool v_)
{
    cpsBindMethod("set_hdr");
    gboolean v = v_;
    void *args[] = { (void*)&v };
    s_method.invoke(*this, args);
}
bool Camera::get_isOrthoGraphic()
{
    cpsBindMethod("get_isOrthoGraphic");
    return s_method.invoke(*this).getValue<gboolean>() != 0;
}
void Camera::set_isOrthoGraphic(bool v_)
{
    cpsBindMethod("set_isOrthoGraphic");
    gboolean v = v_;
    void *args[] = { (void*)&v };
    s_method.invoke(*this, args);
}
cpsTArray<float> Camera::get_layerCullDistances()
{
    cpsBindMethod("get_layerCullDistances");
    return cpsTArray<float>(s_method.invoke(*this));
}
void Camera::set_layerCullDistances(cpsTArray<float> v)
{
    cpsBindMethod("set_layerCullDistances");
    void *args[] = { (cpsArray)v };
    s_method.invoke(*this, args);
}
bool Camera::get_layerCullSpherical()
{
    cpsBindMethod("get_layerCullSpherical");
    return s_method.invoke(*this).getValue<gboolean>() != 0;
}
void Camera::set_layerCullSpherical(bool v_)
{
    cpsBindMethod("set_layerCullSpherical");
    gboolean v = v_;
    void *args[] = { (void*)&v };
    s_method.invoke(*this, args);
}
float Camera::get_nearClipPlane()
{
    cpsBindMethod("get_nearClipPlane");
    return s_method.invoke(*this).getValue<float>();
}
void Camera::set_nearClipPlane(float v)
{
    cpsBindMethod("set_nearClipPlane");
    void *args[] = { (void*)&v };
    s_method.invoke(*this, args);
}
bool Camera::get_orthographic()
{
    cpsBindMethod("get_orthographic");
    return s_method.invoke(*this).getValue<gboolean>() != 0;
}
void Camera::set_orthographic(bool v_)
{
    cpsBindMethod("set_orthographic");
    gboolean v = v_;
    void *args[] = { (void*)&v };
    s_method.invoke(*this, args);
}
float Camera::get_orthographicSize()
{
    cpsBindMethod("get_orthographicSize");
    return s_method.invoke(*this).getValue<float>();
}
void Camera::set_orthographicSize(float v)
{
    cpsBindMethod("set_orthographicSize");
    void *args[] = { (void*)&v };
    s_method.invoke(*this, args);
}
float Camera::get_pixelHeight()
{
    cpsBindMethod("get_pixelHeight");
    return s_method.invoke(*this).getValue<float>();
}
Rect Camera::get_pixelRect()
{
    cpsBindMethod("get_pixelRect");
    return s_method.invoke(*this).getValue<Rect>();
}
void Camera::set_pixelRect(const Rect &v)
{
    cpsBindMethod("set_pixelRect");
    void *args[] = { (void*)&v };
    s_method.invoke(*this, args);
}
float Camera::get_pixelWidth()
{
    cpsBindMethod("get_pixelWidth");
    return s_method.invoke(*this).getValue<float>();
}
Matrix4x4 Camera::get_projectionMatrix()
{
    cpsBindMethod("get_projectionMatrix");
    return s_method.invoke(*this).getValue<Matrix4x4>();
}
void Camera::set_projectionMatrix(const Matrix4x4 &v)
{
    cpsBindMethod("set_projectionMatrix");
    void *args[] = { (void*)&v };
    s_method.invoke(*this, args);
}
Rect Camera::get_rect()
{
    cpsBindMethod("get_rect");
    return s_method.invoke(*this).getValue<Rect>();
}
void Camera::set_rect(const Rect &v)
{
    cpsBindMethod("set_rect");
    void *args[] = { (void*)&v };
    s_method.invoke(*this, args);
}
RenderingPath Camera::get_renderingPath()
{
    cpsBindMethod("get_renderingPath");
    return s_method.invoke(*this).getValue<RenderingPath>();
}
void Camera::set_renderingPath(RenderingPath v)
{
    cpsBindMethod("set_renderingPath");
    void *args[] = { (void*)&v };
    s_method.invoke(*this, args);
}
float Camera::get_stereoConvergence()
{
    cpsBindMethod("get_stereoConvergence");
    return s_method.invoke(*this).getValue<float>();
}
void Camera::set_stereoConvergence(float v)
{
    cpsBindMethod("set_stereoConvergence");
    void *args[] = { (void*)&v };
    s_method.invoke(*this, args);
}
bool Camera::get_stereoEnabled()
{
    cpsBindMethod("get_stereoEnabled");
    return s_method.invoke(*this).getValue<gboolean>() != 0;
}
void Camera::set_stereoEnabled(bool v_)
{
    cpsBindMethod("set_stereoEnabled");
    gboolean v = v_;
    void *args[] = { (void*)&v };
    s_method.invoke(*this, args);
}
float Camera::get_stereoSeparation()
{
    cpsBindMethod("get_stereoSeparation");
    return s_method.invoke(*this).getValue<float>();
}
void Camera::set_stereoSeparation(float v)
{
    cpsBindMethod("set_stereoSeparation");
    void *args[] = { (void*)&v };
    s_method.invoke(*this, args);
}
RenderTexture Camera::get_targetTexture()
{
    cpsBindMethod("get_targetTexture");
    return RenderTexture(s_method.invoke(*this));
}
void Camera::set_targetTexture(RenderTexture v)
{
    cpsBindMethod("set_targetTexture");
    void *args[] = { v };
    s_method.invoke(*this, args);
}
TransparencySortMode Camera::get_transparencySortMode()
{
    cpsBindMethod("get_transparencySortMode");
    return s_method.invoke(*this).getValue<TransparencySortMode>();
}
void Camera::set_transparencySortMode(TransparencySortMode v)
{
    cpsBindMethod("set_transparencySortMode");
    void *args[] = { &v };
    s_method.invoke(*this, args);
}
bool Camera::get_useOcclusionCulling()
{
    cpsBindMethod("get_useOcclusionCulling");
    return s_method.invoke(*this).getValue<gboolean>() != 0;
}
void Camera::set_useOcclusionCulling(bool v_)
{
    cpsBindMethod("set_useOcclusionCulling");
    gboolean v = v_;
    void *args[] = { (void*)&v };
    s_method.invoke(*this, args);
}
Vector3 Camera::get_velocity()
{
    cpsBindMethod("get_velocity");
    return s_method.invoke(*this).getValue<Vector3>();
}
void Camera::set_velocity(const Vector3 &v)
{
    cpsBindMethod("set_velocity");
    void *args[] = { (void*)&v };
    s_method.invoke(*this, args);
}
Matrix4x4 Camera::get_worldToCameraMatrix()
{
    cpsBindMethod("get_worldToCameraMatrix");
    return s_method.invoke(*this).getValue<Matrix4x4>();
}
void Camera::set_worldToCameraMatrix(const Matrix4x4 &v)
{
    cpsBindMethod("set_worldToCameraMatrix");
    void *args[] = { (void*)&v };
    s_method.invoke(*this, args);
}

Matrix4x4 Camera::CalculateObliqueMatrix(const Vector4 &clipPlane)
{
    cpsBindMethod("CalculateObliqueMatrix");
    void *args[] = { (void*)&clipPlane };
    return s_method.invoke(*this, args).getValue<Matrix4x4>();
}
void Camera::CopyFrom(Camera other)
{
    cpsBindMethod("CopyFrom");
    void *args[] = { (void*)&other };
    s_method.invoke(*this, args);
}
void Camera::Render()
{
    cpsBindMethod("Render");
    s_method.invoke(*this);
}
bool Camera::RenderToCubemap(Cubemap cubemap, int faceMask)
{
    cpsBindMethod("RenderToCubemap");
    void *args[] = { cubemap, &faceMask };
    return s_method.invoke(*this, args).getValue<gboolean>() != 0;
}
void Camera::RenderWithShader(Shader shader, cpsString replacementTag)
{
    cpsBindMethod("RenderWithShader");
    void *args[] = { shader, replacementTag };
    s_method.invoke(*this, args);
}
void Camera::ResetAspect()
{
    cpsBindMethod("ResetAspect");
    s_method.invoke(*this);
}
void Camera::ResetProjectionMatrix()
{
    cpsBindMethod("ResetProjectionMatrix");
    s_method.invoke(*this);
}
void Camera::ResetReplacementShader()
{
    cpsBindMethod("ResetReplacementShader");
    s_method.invoke(*this);
}
void Camera::ResetWorldToCameraMatrix()
{
    cpsBindMethod("ResetWorldToCameraMatrix");
    s_method.invoke(*this);
}
Ray Camera::ScreenPointToRay(const Vector3 &position)
{
    cpsBindMethod("ScreenPointToRay");
    void *args[] = { (void*)&position };
    return s_method.invoke(*this, args).getValue<Ray>();
}
Vector3 Camera::ScreenToViewportPoint(const Vector3 &position)
{
    cpsBindMethod("ScreenToViewportPoint");
    void *args[] = { (void*)&position };
    return s_method.invoke(*this, args).getValue<Vector3>();
}
Vector3 Camera::ScreenToWorldPoint(const Vector3 &position)
{
    cpsBindMethod("ScreenToWorldPoint");
    void *args[] = { (void*)&position };
    return s_method.invoke(*this, args).getValue<Vector3>();
}
void Camera::SetReplacementShader(Shader shader, cpsString replacementTag)
{
    cpsBindMethod("SetReplacementShader");
    void *args[] = { shader, replacementTag };
    s_method.invoke(*this, args);
}
void Camera::SetTargetBuffers(RenderBuffer colorBuffer, RenderBuffer depthBuffer)
{
    const char *typenames[] = { cpsTypename<RenderBuffer>(), cpsTypename<RenderBuffer>() };
    cpsBindMethod("SetTargetBuffers", _countof(typenames), typenames);
    void *args[] = { &colorBuffer, &depthBuffer };
    s_method.invoke(*this, args);
}
void Camera::SetTargetBuffers(cpsTArray<RenderBuffer> colorBuffer, RenderBuffer depthBuffer)
{
    const char *typenames[] = { cpsTypenameArray<RenderBuffer>(), cpsTypename<RenderBuffer>() };
    cpsBindMethod("SetTargetBuffers", _countof(typenames), typenames);
    void *args[] = { (cpsArray)colorBuffer, &depthBuffer };
    s_method.invoke(*this, args);
}
Ray Camera::ViewportPointToRay(const Vector3 &position)
{
    cpsBindMethod("ViewportPointToRay");
    void *args[] = { (void*)&position };
    return s_method.invoke(*this, args).getValue<Ray>();
}
Vector3 Camera::ViewportToScreenPoint(const Vector3 &position)
{
    cpsBindMethod("ViewportToScreenPoint");
    void *args[] = { (void*)&position };
    return s_method.invoke(*this, args).getValue<Vector3>();
}
Vector3 Camera::ViewportToWorldPoint(const Vector3 &position)
{
    cpsBindMethod("ViewportToWorldPoint");
    void *args[] = { (void*)&position };
    return s_method.invoke(*this, args).getValue<Vector3>();
}
Vector3 Camera::WorldToScreenPoint(const Vector3 &position)
{
    cpsBindMethod("WorldToScreenPoint");
    void *args[] = { (void*)&position };
    return s_method.invoke(*this, args).getValue<Vector3>();
}
Vector3 Camera::WorldToViewportPoint(const Vector3 &position)
{
    cpsBindMethod("WorldToViewportPoint");
    void *args[] = { (void*)&position };
    return s_method.invoke(*this, args).getValue<Vector3>();
}


cpsImplTraits(UnityEngine, Light);
Light::Light(cpsObject obj) : super(obj) {}



cpsImplTraits(UnityEngine, Renderer);
Renderer::Renderer(cpsObject obj) : super(obj) {}



cpsImplTraits(UnityEngine, MeshRenderer);
MeshRenderer::MeshRenderer(cpsObject obj) : super(obj) {}



cpsImplTraits(UnityEngine, SpriteRenderer);
SpriteRenderer::SpriteRenderer(cpsObject obj) : super(obj) {}







cpsImplTraits(UnityEngine, Application);

/*static*/ cpsString Application::get_dataPath()
{
    cpsBindMethod("get_dataPath");
    return cpsString(s_method.invoke(nullptr));
}

/*static*/ bool Application::get_isEditor()
{
    cpsBindMethod("get_isEditor");
    cpsObject ret = s_method.invoke(nullptr);
    return *((gboolean*)ret.getDataPtr()) != 0;
}

/*static*/ void Application::CancelQuit()
{
    cpsBindMethod("CancelQuit");
    s_method.invoke(nullptr);
}
/*static*/ bool Application::CanStreamedLevelBeLoaded(int levelIndex)
{
    cpsBindMethod("CancelQuit");
    void *args[] = {&levelIndex};
    return s_method.invoke(nullptr, args).getValue<gboolean>() != 0;
}
/*static*/ void Application::CaptureScreenshot(cpsString filename, int superSize)
{
    cpsBindMethod("CaptureScreenshot");
    void *args[] = { filename, &superSize };
    s_method.invoke(nullptr, args);
}
///*static*/ void Application::ExternalCall(cpsString functionName, cpsArray args); // Web Player only
///*static*/ void Application::ExternalEval(cpsString script); // Web Player only
/*static*/ float Application::GetStreamProgressForLevel(int levelIndex)
{
    cpsBindMethod("GetStreamProgressForLevel");
    void *args[] = { &levelIndex };
    return s_method.invoke(nullptr, args).getValue<float>();
}
/*static*/ bool Application::HasProLicense()
{
    cpsBindMethod("HasProLicense");
    return s_method.invoke(nullptr).getValue<gboolean>() != 0;
}
/*static*/ bool Application::HasUserAuthorization(UserAuthorization mode)
{
    cpsBindMethod("HasUserAuthorization");
    void *args[] = { &mode };
    return s_method.invoke(nullptr, args).getValue<gboolean>() != 0;
}
/*static*/ void Application::LoadLevel(int index)
{
    static const char *names[] = {cpsTypename<int>()};
    cpsBindMethod("LoadLevel", _countof(names), names);
    void *args[] = { &index };
    s_method.invoke(nullptr, args);
}
/*static*/ void Application::LoadLevel(cpsString name)
{
    static const char *names[] = { cpsTypename<cpsString>() };
    cpsBindMethod("LoadLevel", _countof(names), names);
    void *args[] = { name };
    s_method.invoke(nullptr, args);
}
/*static*/ void Application::LoadLevelAdditive(int index)
{
    static const char *names[] = { cpsTypename<int>() };
    cpsBindMethod("LoadLevelAdditive", _countof(names), names);
    void *args[] = { &index };
    s_method.invoke(nullptr, args);
}
/*static*/ void Application::LoadLevelAdditive(cpsString name)
{
    static const char *names[] = { cpsTypename<cpsString>() };
    cpsBindMethod("LoadLevelAdditive", _countof(names), names);
    void *args[] = { name };
    s_method.invoke(nullptr, args);
}
/*static*/ AsyncOperation Application::LoadLevelAdditiveAsync(int index)
{
    static const char *names[] = { cpsTypename<int>() };
    cpsBindMethod("LoadLevelAdditiveAsync", _countof(names), names);
    void *args[] = { &index };
    return s_method.invoke(nullptr, args);
}
/*static*/ AsyncOperation Application::LoadLevelAdditiveAsync(cpsString levelName)
{
    static const char *names[] = { cpsTypename<cpsString>() };
    cpsBindMethod("LoadLevelAdditiveAsync", _countof(names), names);
    void *args[] = { levelName };
    return s_method.invoke(nullptr, args);
}
/*static*/ AsyncOperation Application::LoadLevelAsync(int index)
{
    static const char *names[] = { cpsTypename<int>() };
    cpsBindMethod("LoadLevelAsync", _countof(names), names);
    void *args[] = { &index };
    return s_method.invoke(nullptr, args);
}
/*static*/ AsyncOperation Application::LoadLevelAsync(cpsString levelName)
{
    static const char *names[] = { cpsTypename<cpsString>() };
    cpsBindMethod("LoadLevelAsync", _countof(names), names);
    void *args[] = { levelName };
    return s_method.invoke(nullptr, args);
}
/*static*/ void Application::OpenURL(cpsString url)
{
    cpsBindMethod("OpenURL", 1);
    void *args[] = { url };
    s_method.invoke(nullptr, args);
}
/*static*/ void Application::Quit()
{
    cpsBindMethod("Quit", 0);
    s_method.invoke(nullptr);
}
///*static*/ void Application::RegisterLogCallback(LogCallback handler);
///*static*/ void Application::RegisterLogCallbackThreaded(LogCallback handler);
/*static*/ AsyncOperation Application::RequestUserAuthorization(UserAuthorization mode)
{
    cpsBindMethod("RequestUserAuthorization", 1);
    void *args[] = { &mode };
    return s_method.invoke(nullptr, args);
}




cpsImplTraits(UnityEngine, Debug);


/*static*/ bool Debug::get_developerConsoleVisible()
{
    cpsBindMethod("get_developerConsoleVisible");
    return s_method.invoke(nullptr).getValue<gboolean>() != 0;
}
/*static*/ void Debug::set_developerConsoleVisible(bool v_)
{
    cpsBindMethod("set_developerConsoleVisible");
    gboolean v = v_;
    void *args[] = {&v};
    s_method.invoke(nullptr, args);
}
/*static*/ bool Debug::get_isDebugBuild()
{
    cpsBindMethod("get_isDebugBuild");
    return s_method.invoke(nullptr).getValue<gboolean>() != 0;
}

/*static*/ void Debug::Break()
{
    cpsBindMethod("Break");
    s_method.invoke(nullptr);
}
/*static*/ void Debug::ClearDeveloperConsole()
{
    cpsBindMethod("ClearDeveloperConsole");
    s_method.invoke(nullptr);
}
/*static*/ void Debug::DrawLine(const Vector3 &start, const Vector3 &end, const Color &color, float duration, bool depthTest_)
{
    cpsBindMethod("DrawLine");
    gboolean depthTest = depthTest_;
    void *args[] = { (void*)&start, (void*)&end, (void*)&color, &duration, &depthTest };
    s_method.invoke(nullptr, args);
}
/*static*/ void Debug::DrawRay(const Vector3 &start, const Vector3 &dir, const Color &color, float duration, bool depthTest_)
{
    cpsBindMethod("DrawRay");
    gboolean depthTest = depthTest_;
    void *args[] = { (void*)&start, (void*)&dir, (void*)&color, &duration, &depthTest };
    s_method.invoke(nullptr, args);
}
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
/*static*/ void Debug::LogError(cpsString message)
{
    cpsBindMethod("LogError", 1);
    void *args[] = { message };
    s_method.invoke(nullptr, args);
}
/*static*/ void Debug::LogError(cpsString message, cpsObject context)
{
    cpsBindMethod("LogError", 2);
    void *args[] = { message, context };
    s_method.invoke(nullptr, args);
}
///*static*/ void Debug::LogException(Exception exception);
///*static*/ void Debug::LogException(Exception exception, Object context);
/*static*/ void Debug::LogWarning(cpsString message)
{
    cpsBindMethod("LogWarning", 1);
    void *args[] = { message };
    s_method.invoke(nullptr, args);
}
/*static*/ void Debug::LogWarning(cpsString message, cpsObject context)
{
    cpsBindMethod("LogWarning", 2);
    void *args[] = { message, context };
    s_method.invoke(nullptr, args);
}



cpsImplTraits(UnityEngine, GL);
/*static*/ void GL::Begin(int mode)
{
    cpsBindMethod("Begin");
    void *args[] = {&mode};
    s_method.invoke(nullptr, args);
}
/*static*/ void GL::Clear(bool clearDepth_, bool clearColor_, const Color &backgroundColor, float depth)
{
    cpsBindMethod("Clear");
    gboolean clearDepth = clearDepth_;
    gboolean clearColor = clearColor_;
    void *args[] = { &clearDepth, &clearColor, (void*)&backgroundColor, &depth };
    s_method.invoke(nullptr, args);
}
/*static*/ void GL::ClearWithSkybox(bool clearDepth_, Camera camera)
{
    cpsBindMethod("ClearWithSkybox");
    gboolean clearDepth = clearDepth_;
    void *args[] = { &clearDepth, camera };
    s_method.invoke(nullptr, args);
}
/*static*/ void GL::Color_(const Color &c)
{
    cpsBindMethod("Color");
    void *args[] = { (void*)&c };
    s_method.invoke(nullptr, args);
}
/*static*/ void GL::End()
{
    cpsBindMethod("End");
    s_method.invoke(nullptr);
}
/*static*/ Matrix4x4 GL::GetGPUProjectionMatrix(const Matrix4x4 &proj, bool renderIntoTexture_)
{
    cpsBindMethod("GetGPUProjectionMatrix");
    gboolean renderIntoTexture = renderIntoTexture_;
    void *args[] = { (void*)&proj, &renderIntoTexture };
    return s_method.invoke(nullptr, args).getValue<Matrix4x4>();
}
/*static*/ void GL::InvalidateState()
{
    cpsBindMethod("InvalidateState");
    s_method.invoke(nullptr);
}
/*static*/ void GL::IssuePluginEvent(int eventID)
{
    cpsBindMethod("IssuePluginEvent");
    void *args[] = { &eventID };
    s_method.invoke(nullptr, args);
}
/*static*/ void GL::LoadIdentity()
{
    cpsBindMethod("LoadIdentity");
    s_method.invoke(nullptr);
}
/*static*/ void GL::LoadOrtho()
{
    cpsBindMethod("LoadOrtho");
    s_method.invoke(nullptr);
}
/*static*/ void GL::LoadPixelMatrix()
{
    cpsBindMethod("LoadPixelMatrix");
    s_method.invoke(nullptr);
}
/*static*/ void GL::LoadProjectionMatrix(const Matrix4x4 &mat)
{
    cpsBindMethod("LoadProjectionMatrix");
    void *args[] = { (void*)&mat };
    s_method.invoke(nullptr, args);
}
/*static*/ void GL::MultiTexCoord(int unit, const Vector3 &v)
{
    cpsBindMethod("MultiTexCoord");
    void *args[] = { &unit, (void*)&v };
    s_method.invoke(nullptr, args);
}
/*static*/ void GL::MultiTexCoord2(int unit, float x, float y)
{
    cpsBindMethod("MultiTexCoord2");
    void *args[] = { &unit, &x, &y };
    s_method.invoke(nullptr, args);
}
/*static*/ void GL::MultiTexCoord3(int unit, float x, float y, float z)
{
    cpsBindMethod("MultiTexCoord3");
    void *args[] = { &unit, &x, &y, &z };
    s_method.invoke(nullptr, args);
}
/*static*/ void GL::MultMatrix(const Matrix4x4 &mat)
{
    cpsBindMethod("MultMatrix");
    void *args[] = { (void*)&mat };
    s_method.invoke(nullptr, args);
}
/*static*/ void GL::PopMatrix()
{
    cpsBindMethod("PopMatrix");
    s_method.invoke(nullptr);
}
/*static*/ void GL::PushMatrix()
{
    cpsBindMethod("PushMatrix");
    s_method.invoke(nullptr);
}
/*static*/ void GL::SetRevertBackfacing(bool revertBackFaces_)
{
    cpsBindMethod("SetRevertBackfacing");
    gboolean revertBackFaces = revertBackFaces_;
    void *args[] = { &revertBackFaces };
    s_method.invoke(nullptr, args);
}
/*static*/ void GL::TexCoord(const Vector3 &v)
{
    cpsBindMethod("TexCoord");
    void *args[] = { (void*)&v };
    s_method.invoke(nullptr, args);
}
/*static*/ void GL::TexCoord2(float x, float y)
{
    cpsBindMethod("TexCoord2");
    void *args[] = { &x, &y };
    s_method.invoke(nullptr, args);
}
/*static*/ void GL::TexCoord3(float x, float y, float z)
{
    cpsBindMethod("TexCoord3");
    void *args[] = { &x, &y, &z };
    s_method.invoke(nullptr, args);
}
/*static*/ void GL::Vertex(const Vector3 &v)
{
    cpsBindMethod("Vertex");
    void *args[] = { (void*)&v };
    s_method.invoke(nullptr, args);
}
/*static*/ void GL::Vertex3(float x, float y, float z)
{
    cpsBindMethod("Vertex3");
    void *args[] = { &x, &y, &z };
    s_method.invoke(nullptr, args);
}
/*static*/ void GL::Viewport(const Rect &pixelRect)
{
    cpsBindMethod("Viewport");
    void *args[] = { (void*)&pixelRect };
    s_method.invoke(nullptr, args);
}



cpsImplTraits(UnityEngine, GUI);



cpsImplTraits(UnityEngine, Graphics);

/*static*/ RenderBuffer Graphics::get_activeColorBuffer()
{
    cpsBindMethod("get_activeColorBuffer");
    cpsObject ret = s_method.invoke(nullptr);
    return ret.getValue<RenderBuffer>();
}
/*static*/ RenderBuffer Graphics::get_activeDepthBuffer()
{
    cpsBindMethod("get_activeDepthBuffer");
    cpsObject ret = s_method.invoke(nullptr);
    return ret.getValue<RenderBuffer>();
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
    return ret.getValue<gboolean>()!=0;
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
    return ret.getValue<Vector3>();
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
    return ret.getValue<float>();
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
    return ret.getValue<float>();
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
    return ret.getValue<float>();
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
    return ret.getValue<float>();
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
    return ret.getValue<float>();
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
    return ret.getValue<int>();
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
    return ret.getValue<gboolean>() != 0;
}
/*static*/ bool Physics::CheckSphere(const Vector3 &position, float radius, int layerMask)
{
    static const char *names[] = { cpsTypename<Vector3>(), cpsTypename<float>(), cpsTypename<int>() };
    cpsBindMethod("CheckSphere", _countof(names), names);
    void *args[] = { (void*)&position, &radius, &layerMask };
    cpsObject ret = s_method.invoke(nullptr, args);
    return ret.getValue<gboolean>() != 0;
}
/*static*/ bool Physics::Raycast(const Ray &ray, RaycastHit &hitInfo, float distance, int layerMask)
{
    static const char *names[] = { cpsTypename<Ray>(), cpsTypenameRef<RaycastHit>(), cpsTypename<float>(), cpsTypename<int>() };
    cpsBindMethod("Raycast", _countof(names), names);
    void *args[] = { (void*)&ray, &hitInfo, &distance, &layerMask };
    cpsObject ret = s_method.invoke(nullptr, args);
    return ret.getValue<gboolean>() != 0;
}
/*static*/ bool Physics::CapsuleCast(const Vector3 &point1, const Vector3 &point2, float radius, const Vector3 &direction, RaycastHit &hitInfo, float distance, int layerMask)
{
    static const char *names[] = { cpsTypename<Vector3>(), cpsTypename<Vector3>(), cpsTypename<float>(), cpsTypename<Vector3>(), cpsTypenameRef<RaycastHit>(), cpsTypename<float>(), cpsTypename<int>() };
    cpsBindMethod("CapsuleCast", _countof(names), names);
    void *args[] = { (void*)&point1, (void*)&point2, (void*)&radius, (void*)&direction, (void*)&hitInfo, (void*)&distance, (void*)&layerMask };
    cpsObject ret = s_method.invoke(nullptr, args);
    return ret.getValue<gboolean>() != 0;
}
/*static*/ bool Physics::Linecast(const Vector3 &start, const Vector3 &end, RaycastHit &hitInfo, int layerMask)
{
    static const char *names[] = { cpsTypename<Vector3>(), cpsTypename<Vector3>(), cpsTypenameRef<RaycastHit>(), cpsTypename<int>() };
    cpsBindMethod("Linecast", _countof(names), names);
    void *args[] = { (void*)&start, (void*)&end, (void*)&hitInfo, (void*)&layerMask };
    cpsObject ret = s_method.invoke(nullptr, args);
    return ret.getValue<gboolean>() != 0;
}
/*static*/ bool Physics::SphereCast(const Ray &ray, float radius, RaycastHit &hitInfo, float distance, int layerMask)
{
    static const char *names[] = { cpsTypename<Ray>(), cpsTypename<float>(), cpsTypenameRef<RaycastHit>(), cpsTypename<float>(), cpsTypename<int>() };
    cpsBindMethod("SphereCast", _countof(names), names);
    void *args[] = { (void*)&ray, (void*)&radius, (void*)&hitInfo, (void*)&distance, (void*)&layerMask };
    cpsObject ret = s_method.invoke(nullptr, args);
    return ret.getValue<gboolean>() != 0;
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
    return ret.getValue<gboolean>() != 0;
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



cpsImplTraits(UnityEngine, Resources);

/*static*/ cpsObject Resources::Load(cpsString path)
{
    cpsBindMethod("Load", 1);
    void *args[] = { path };
    return s_method.invoke(nullptr, args);
}
/*static*/ cpsTArray<cpsObject> Resources::LoadAll(cpsString path)
{
    cpsBindMethod("LoadAll", 1);
    void *args[] = { path };
    cpsObject ret = s_method.invoke(nullptr, args);
    return cpsTArray<cpsObject>(ret);
}

//static Object Resources::LoadAssetAtPath(cpsString assetPath, Type type);

/*static*/ ResourceRequest Resources::LoadAsync(cpsString path)
{
    cpsBindMethod("LoadAsync", 1);
    void *args[] = { path };
    return s_method.invoke(nullptr, args);
}
/*static*/ void Resources::UnloadAsset(Object assetToUnload)
{
    cpsBindMethod("UnloadAsset", 1);
    void *args[] = { assetToUnload };
    s_method.invoke(nullptr, args);
}
/*static*/ AsyncOperation Resources::UnloadUnusedAssets()
{
    cpsBindMethod("UnloadAsset", 0);
    return s_method.invoke(nullptr);
}


cpsImplTraits(UnityEngine, Time);
/*static*/ int Time::get_captureFramerate()
{
    cpsBindMethod("get_captureFramerate");
    return s_method.invoke(nullptr).getValue<int>();
}
/*static*/ void Time::set_captureFramerate(int v)
{
    cpsBindMethod("set_captureFramerate");
    void *args[] = { &v };
    s_method.invoke(nullptr, args);
}
/*static*/ float Time::get_deltaTime()
{
    cpsBindMethod("get_deltaTime");
    return s_method.invoke(nullptr).getValue<float>();
}
/*static*/ float Time::get_fixedDeltaTime()
{
    cpsBindMethod("get_fixedDeltaTime");
    return s_method.invoke(nullptr).getValue<float>();
}
/*static*/ void Time::set_fixedDeltaTime(float v)
{
    cpsBindMethod("set_fixedDeltaTime");
    void *args[] = { &v };
    s_method.invoke(nullptr, args);
}
/*static*/ float Time::get_fixedTime()
{
    cpsBindMethod("get_fixedTime");
    return s_method.invoke(nullptr).getValue<float>();
}
/*static*/ int Time::get_frameCount()
{
    cpsBindMethod("get_frameCount");
    return s_method.invoke(nullptr).getValue<int>();
}
/*static*/ float Time::get_maximumDeltaTime()
{
    cpsBindMethod("get_maximumDeltaTime");
    return s_method.invoke(nullptr).getValue<float>();
}
/*static*/ void Time::set_maximumDeltaTime(float v)
{
    cpsBindMethod("set_maximumDeltaTime");
    void *args[] = { &v };
    s_method.invoke(nullptr, args);
}
/*static*/ float Time::get_realtimeSinceStartup()
{
    cpsBindMethod("get_realtimeSinceStartup");
    return s_method.invoke(nullptr).getValue<float>();
}
/*static*/ int Time::get_renderedFrameCount()
{
    cpsBindMethod("get_renderedFrameCount");
    return s_method.invoke(nullptr).getValue<int>();
}
/*static*/ float Time::get_smoothDeltaTime()
{
    cpsBindMethod("get_smoothDeltaTime");
    return s_method.invoke(nullptr).getValue<float>();
}
/*static*/ float Time::get_time()
{
    cpsBindMethod("get_time");
    return s_method.invoke(nullptr).getValue<float>();
}
/*static*/ float Time::get_timeScale()
{
    cpsBindMethod("get_timeScale");
    return s_method.invoke(nullptr).getValue<float>();
}
/*static*/ void Time::set_timeScale(float v)
{
    cpsBindMethod("set_timeScale");
    void *args[] = { &v };
    s_method.invoke(nullptr, args);
}
/*static*/ float Time::get_timeSinceLevelLoad()
{
    cpsBindMethod("get_timeSinceLevelLoad");
    return s_method.invoke(nullptr).getValue<float>();
}
/*static*/ float Time::get_unscaledDeltaTime()
{
    cpsBindMethod("get_unscaledDeltaTime");
    return s_method.invoke(nullptr).getValue<float>();
}
/*static*/ float Time::get_unscaledTime()
{
    cpsBindMethod("get_unscaledTime");
    return s_method.invoke(nullptr).getValue<float>();
}


cpsImplTraits(UnityEngine, Profiler);
/*static*/ bool Profiler::get_enableBinaryLog()
{
    cpsBindMethod("get_enableBinaryLog");
    return s_method.invoke(nullptr).getValue<gboolean>() != 0;
}
/*static*/ void Profiler::set_enableBinaryLog(bool v_)
{
    cpsBindMethod("set_enableBinaryLog");
    gboolean v = v_;
    void *args[] = { &v };
    s_method.invoke(nullptr, args);
}
/*static*/ bool Profiler::get_enabled()
{
    cpsBindMethod("get_enabled");
    return s_method.invoke(nullptr).getValue<gboolean>() != 0;
}
/*static*/ void Profiler::set_enabled(bool v_)
{
    cpsBindMethod("set_enabled");
    gboolean v = v_;
    void *args[] = { &v };
    s_method.invoke(nullptr, args);
}
/*static*/ cpsString Profiler::get_logFile()
{
    cpsBindMethod("get_logFile");
    return cpsString(s_method.invoke(nullptr));
}
/*static*/ void Profiler::set_logFile(cpsString v)
{
    cpsBindMethod("set_logFile");
    void *args[] = { v };
    s_method.invoke(nullptr, args);
}
/*static*/ bool Profiler::get_supported()
{
    cpsBindMethod("get_supported");
    return s_method.invoke(nullptr).getValue<gboolean>() != 0;
}
/*static*/ void Profiler::set_supported(bool v)
{
    cpsBindMethod("set_supported");
    void *args[] = { &v };
    s_method.invoke(nullptr, args);
}
/*static*/ uint32_t Profiler::get_usedHeapSize()
{
    cpsBindMethod("get_usedHeapSize");
    return s_method.invoke(nullptr).getValue<uint32_t>();
}

/*static*/ void Profiler::AddFramesFromFile(cpsString file)
{
    cpsBindMethod("AddFramesFromFile");
    void *args[] = { file };
    s_method.invoke(nullptr, args);
}
/*static*/ void Profiler::BeginSample(cpsString name)
{
    cpsBindMethod("BeginSample", 1);
    void *args[] = { name };
    s_method.invoke(nullptr, args);
}
/*static*/ void Profiler::BeginSample(cpsString name, Object targetObject)
{
    cpsBindMethod("BeginSample", 2);
    void *args[] = { name, targetObject };
    s_method.invoke(nullptr, args);
}
/*static*/ void Profiler::EndSample()
{
    cpsBindMethod("EndSample");
}
/*static*/ uint32_t Profiler::GetMonoHeapSize()
{
    cpsBindMethod("GetMonoHeapSize");
    return s_method.invoke(nullptr).getValue<uint32_t>();
}
/*static*/ uint32_t Profiler::GetMonoUsedSize()
{
    cpsBindMethod("GetMonoUsedSize");
    return s_method.invoke(nullptr).getValue<uint32_t>();
}
/*static*/ int Profiler::GetRuntimeMemorySize(Object o)
{
    cpsBindMethod("GetRuntimeMemorySize");
    void *args[] = { o };
    return s_method.invoke(nullptr).getValue<int>();
}
/*static*/ uint32_t Profiler::GetTotalAllocatedMemory()
{
    cpsBindMethod("GetTotalAllocatedMemory");
    return s_method.invoke(nullptr).getValue<uint32_t>();
}
/*static*/ uint32_t Profiler::GetTotalReservedMemory()
{
    cpsBindMethod("GetTotalReservedMemory");
    return s_method.invoke(nullptr).getValue<uint32_t>();
}
/*static*/ uint32_t Profiler::GetTotalUnusedReservedMemory()
{
    cpsBindMethod("GetTotalUnusedReservedMemory");
    return s_method.invoke(nullptr).getValue<uint32_t>();
}


} // namespace UnityEngine


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

cpsImplTraitsF(UnityEngine, RenderingPath)
cpsImplTraitsF(UnityEngine, CameraClearFlags)
cpsImplTraitsF(UnityEngine, DepthTextureMode)
cpsImplTraitsF(UnityEngine, TransparencySortMode)
