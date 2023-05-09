#pragma once
#include "GameObject.h"
#include "Material.h"
#include "Mesh.h"
#include "Texture.h"
#include "Shader.h"
class Resources : public Singleton<Resources>
{
private:
	friend class Singleton<Resources>;
	Resources();
	~Resources();

public:
	void Init();

	template <typename T>
	shared_ptr<T> Load(const wstring& key, const wstring& path);

	template <typename T>
	bool Add(const wstring& key, shared_ptr<T> object);

	template <typename T>
	shared_ptr<T> Get(const wstring& key);	

	template<typename T>
	OBJECT_TYPE GetObjectType();

	shared_ptr<Mesh> LoadCubeMesh();
	shared_ptr<Mesh> LoadSphereMesh();
	shared_ptr<Mesh> LoadRectangleMesh();
	shared_ptr<Mesh> LoadPointMesh();

	shared_ptr<Texture> CreateTexture(const wstring& name, DXGI_FORMAT format, uint32 width, uint32 height,
		const D3D12_HEAP_PROPERTIES& heapProperty, D3D12_HEAP_FLAGS heapFlags,
		D3D12_RESOURCE_FLAGS resFlags = D3D12_RESOURCE_FLAG_NONE, Vec4 clearColor = Vec4());

	shared_ptr<Texture> CreateTextureFromResource(const wstring& name, ComPtr<ID3D12Resource> tex2D);

private:
	void CreateDefaultShader();
	void CreateDefaultMaterial();

private:
	using KeyObjMap = map<wstring, shared_ptr<Object>>;
	array<KeyObjMap, OBJECT_TYPE_COUNT> _resources;

};

template <typename T>
inline shared_ptr<T> Resources::Load(const wstring& key, const wstring& path)
{
	OBJECT_TYPE objectType = GetObjectType<T>();
	KeyObjMap& keyObjMap = _resources[static_cast<uint8>(objectType)];

	auto findit = keyObjMap.find(key);
	if (findit != keyObjMap.end())
	{
		return static_pointer_cast<T>(findit->second);
	}
	shared_ptr<T> object = make_shared<T>();
	object->Load(path);
	keyObjMap[key] = object;

	return object;
}

template <typename T>
inline bool Resources::Add(const wstring& key, shared_ptr<T> object)
{
	OBJECT_TYPE objectType = GetObjectType<T>();
	KeyObjMap& keyObjMap = _resources[static_cast<uint8>(objectType)];

	auto findit = keyObjMap.find(key);
	if (findit != keyObjMap.end())
		return false;

	keyObjMap[key] = object;
	return true;
}

template <typename T>
inline shared_ptr<T> Resources::Get(const wstring& key)
{
	OBJECT_TYPE objectType = GetObjectType<T>();
	KeyObjMap& keyObjMap = _resources[static_cast<uint8>(objectType)];

	auto findit = keyObjMap.find(key);
	if (findit != keyObjMap.end())
		return static_pointer_cast<T>(findit->second);

	return nullptr;
}

template<typename T>
inline OBJECT_TYPE Resources::GetObjectType()
{
	if (is_same_v<T, GameObject>)
		return OBJECT_TYPE::GAMEOBJECT;
	else if (is_same_v<T, Material>)
		return OBJECT_TYPE::MATERIAL;
	else if (is_same_v<T, Mesh>)
		return OBJECT_TYPE::MESH;
	else if (is_same_v<T, Shader>)
		return OBJECT_TYPE::SHADER;
	else if (is_same_v<T, Texture>)
		return OBJECT_TYPE::TEXTURE;
	else if (is_convertible_v<T, Component>)
		return OBJECT_TYPE::COMPONENT;
	else
		return OBJECT_TYPE::NONE;

}