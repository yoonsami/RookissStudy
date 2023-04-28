#include "pch.h"
#include "Scene.h"
#include "GameObject.h"
#include "Camera.h"
#include "Engine.h"
#include "ConstantBuffer.h"
#include "Light.h"

void Scene::Awake()
{
	for (const auto& gameObject : _gameObjects)
		gameObject->Awake();
}

void Scene::Start()
{
	for (const auto& gameObject : _gameObjects)
		gameObject->Start();
}

void Scene::Update()
{
	for (const auto& gameObject : _gameObjects)
		gameObject->Update();
}

void Scene::LateUpdate()
{
	for (const auto& gameObject : _gameObjects)
		gameObject->LateUpdate();
}

void Scene::FinalUpdate()
{
	for (const auto& gameObject : _gameObjects)
		gameObject->FinalUpdate();
}

void Scene::Render()
{
	// 조명 세팅
	PushLightData();

	for (auto& gameobject : _gameObjects)
	{
		if (gameobject->GetCamera() == nullptr)
			continue;

		gameobject->GetCamera()->Render();
	}
}

void Scene::PushLightData()
{
	LightParams lightParams = {};

	for (auto& gameobject : _gameObjects)
	{
		if(!gameobject->GetLight())
			continue;

		const LightInfo& lightInfo = gameobject->GetLight()->GetLightInfo();

		lightParams.light[lightParams.lightCount] = lightInfo;
		lightParams.lightCount++;

	}

	CONST_BUFFER(CONSTANT_BUFFER_TYPE::GLOBAL)->SetGlobalData(&lightParams, sizeof(lightParams));
}

void Scene::AddGameObject(shared_ptr<GameObject> gameObject)
{
	_gameObjects.push_back(gameObject);
}

void Scene::RemoveGameObject(shared_ptr<GameObject> gameObject)
{
	auto findit = find(_gameObjects.begin(), _gameObjects.end(), gameObject);

	if (findit != _gameObjects.end())
	{
		_gameObjects.erase(findit);
	}

}
