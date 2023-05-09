#include "pch.h"
#include "GameObject.h"
#include "Transform.h"
#include "MeshRenderer.h"
#include "MonoBehaviour.h"
#include "Camera.h"
#include "Light.h"
#include "ParticleSystem.h"

GameObject::GameObject() :Object(OBJECT_TYPE::GAMEOBJECT)
{
}

GameObject::~GameObject()
{
}



void GameObject::Awake()
{
	for (shared_ptr<Component>& component : _components)
	{
		if(component)
			component->Awake();
	}

	for (shared_ptr<MonoBehaviour>& script : _scripts)
	{
		script->Awake();
	}
}

void GameObject::Start()
{
	for (shared_ptr<Component>& component : _components)
	{
		if (component)
			component->Start();
	}

	for (shared_ptr<MonoBehaviour>& script : _scripts)
	{
		script->Start();
	}
}

void GameObject::Update()
{
	for (shared_ptr<Component>& component : _components)
	{
		if (component)
			component->Update();
	}

	for (shared_ptr<MonoBehaviour>& script : _scripts)
	{
		script->Update();
	}
}

void GameObject::LateUpdate()
{
	for (shared_ptr<Component>& component : _components)
	{
		if (component)
			component->LateUpdate();
	}

	for (shared_ptr<MonoBehaviour>& script : _scripts)
	{
		script->LateUpdate();
	}
}

void GameObject::FinalUpdate()
{
	for (shared_ptr<Component>& component : _components)
	{
		if (component)
			component->FinalUpdate();
	}
}

shared_ptr<Component> GameObject::GetFixedComponent(COMPONENT_TYPE type)
{
	uint8 index = static_cast<uint8>(type);
	assert(index < FIXED_COMPONENT_COUNT);
	return _components[index];
}

shared_ptr<Transform> GameObject::GetTransform()
{
	return static_pointer_cast<Transform>(GetFixedComponent(COMPONENT_TYPE::TRANSFORM));
}

shared_ptr<MeshRenderer> GameObject::GetMeshRenderer()
{
	return static_pointer_cast<MeshRenderer>(GetFixedComponent(COMPONENT_TYPE::MESH_RENDERER));
}

shared_ptr<Camera> GameObject::GetCamera()
{
	return static_pointer_cast<Camera>(GetFixedComponent(COMPONENT_TYPE::CAMERA));
}

shared_ptr<Light> GameObject::GetLight()
{
	return static_pointer_cast<Light>(GetFixedComponent(COMPONENT_TYPE::LIGHT));
}

shared_ptr<ParticleSystem> GameObject::GetParticleSystem()
{
	return static_pointer_cast<ParticleSystem>(GetFixedComponent(COMPONENT_TYPE::PARTICLE_SYSTEM));
}

void GameObject::AddComponent(shared_ptr<Component> component)
{
	component->SetGameObject(shared_from_this());

	uint8 index = static_cast<uint8>(component->GetType());
	if (index < FIXED_COMPONENT_COUNT)
	{
		_components[index] = component;

	}
	else
	{
		_scripts.push_back(dynamic_pointer_cast<MonoBehaviour>(component));
	}

}
