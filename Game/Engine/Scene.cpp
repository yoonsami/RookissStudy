#include "pch.h"
#include "Scene.h"
#include "GameObject.h"

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
