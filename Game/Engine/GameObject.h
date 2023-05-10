#pragma once
#include "Component.h"
#include "Object.h"

class Transform;
class MeshRenderer;
class MonoBehaviour;
class Camera;
class Light;
class ParticleSystem;
class Terrain;
class BaseCollider;

class GameObject :public Object, public enable_shared_from_this<GameObject>
{
public:
	GameObject();
	virtual ~GameObject();



	void Awake();
	void Start();
	void Update();
	void LateUpdate();
	void FinalUpdate();

	shared_ptr<Component>		GetFixedComponent(COMPONENT_TYPE type);

	shared_ptr<Transform>		GetTransform();
	shared_ptr<MeshRenderer>	GetMeshRenderer();
	shared_ptr<Camera>			GetCamera();
	shared_ptr<Light>			GetLight();
	shared_ptr<ParticleSystem>	GetParticleSystem();
	shared_ptr<Terrain>			GetTerrain();
	shared_ptr<BaseCollider>	GetCollider();

	void AddComponent(shared_ptr<Component> component); 

	void SetCheckFrustum(bool checkFrustum) { _checkFrustum = checkFrustum; }
	bool GetCheckFrustum() { return _checkFrustum; }

	void SetLayerIndex(uint8 index) { _layerIndex = index; }
	uint8 GetLayerIndex() { return _layerIndex; }

	void SetStatic(bool flag) { _static = flag; }
	bool IsStatic() { return _static; }

private:
	array<shared_ptr<Component>, FIXED_COMPONENT_COUNT> _components;
	vector<shared_ptr<MonoBehaviour>> _scripts;

	bool _checkFrustum = true;
	UINT _layerIndex = 0;
	bool _static = true;
};

