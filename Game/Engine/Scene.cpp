#include "pch.h"
#include "Scene.h"
#include "GameObject.h"
#include "Camera.h"
#include "Engine.h"
#include "ConstantBuffer.h"
#include "Light.h"
#include "Resources.h"

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

shared_ptr<Camera> Scene::GetMainCamera()
{
	if (_cameras.empty())
		return nullptr;

	return _cameras[0];
}

void Scene::Render()
{
	// 조명 세팅
	PushLightData();

	ClearRTV();

	RenderShadow();
	RenderDeferred();
	RenderLights();
	RenderFinal();
	RenderForward();
	
}

void Scene::ClearRTV()
{
	// SwapChain Group 초기화
	int8 backIndex = GEngine->GetSwapChain()->GetBackBufferIndex();
	GEngine->GetRTGroup(RENDER_TARGET_GROUP_TYPE::SWAP_CHAIN)->ClearRenderTargetView(backIndex);

	// Shadow Group 초기화
	GEngine->GetRTGroup(RENDER_TARGET_GROUP_TYPE::SHADOW)->ClearRenderTargetView();

	//Deferred Group 초기화
	GEngine->GetRTGroup(RENDER_TARGET_GROUP_TYPE::G_BUFFER)->ClearRenderTargetView();

	//Lighting Group 초기화
	GEngine->GetRTGroup(RENDER_TARGET_GROUP_TYPE::LIGHTING)->ClearRenderTargetView();
}

void Scene::RenderShadow()
{
	//Shadow OMSet
	GEngine->GetRTGroup(RENDER_TARGET_GROUP_TYPE::SHADOW)->OMSetRenderTargets();

	for (auto& light : _lights)
	{
		if (light->GetLightType() != LIGHT_TYPE::DIRECTIONAL_LIGHT)
			continue;

		light->RenderShadow();
	}

	GEngine->GetRTGroup(RENDER_TARGET_GROUP_TYPE::SHADOW)->WaitTargetToResource();
}

void Scene::RenderDeferred()
{
	//Deferred OMSet
	GEngine->GetRTGroup(RENDER_TARGET_GROUP_TYPE::G_BUFFER)->OMSetRenderTargets();

	shared_ptr<Camera> mainCamera = _cameras[0];
	mainCamera->SortGameObject();
	mainCamera->Render_Deferred();
	GEngine->GetRTGroup(RENDER_TARGET_GROUP_TYPE::G_BUFFER)->WaitTargetToResource();
}

void Scene::RenderLights()
{
	shared_ptr<Camera> mainCamera = _cameras[0];
	Camera::S_MatView = mainCamera->GetViewMatrix();
	Camera::S_MatProjection = mainCamera->GetProjectionMatrix();

	GEngine->GetRTGroup(RENDER_TARGET_GROUP_TYPE::LIGHTING)->OMSetRenderTargets();

	// 광원 그림
	for (auto& light : _lights)
	{
		light->Render();
	}

	GEngine->GetRTGroup(RENDER_TARGET_GROUP_TYPE::LIGHTING)->WaitTargetToResource();
}

void Scene::RenderFinal()
{
	int8 backIndex = GEngine->GetSwapChain()->GetBackBufferIndex();
	GEngine->GetRTGroup(RENDER_TARGET_GROUP_TYPE::SWAP_CHAIN)->OMSetRenderTargets(1, backIndex);

	GET_SINGLE(Resources)->Get<Material>(L"Final")->PushGraphicsData();
	GET_SINGLE(Resources)->Get<Mesh>(L"Rectangle")->Render();
}

void Scene::RenderForward()
{
	_cameras[0]->Render_Forward();

	for (auto& camera : _cameras)
	{
		if (camera == _cameras[0])
			continue;

		camera->SortGameObject();
		camera->Render_Forward();
	}
}

void Scene::PushLightData()
{
	LightParams lightParams = {};

	for (auto& light : _lights)
	{
		const LightInfo& lightInfo = light->GetLightInfo();

		light->SetLightIndex(lightParams.lightCount);
		//todo

		lightParams.light[lightParams.lightCount] = lightInfo;
		lightParams.lightCount++;

	}

	CONST_BUFFER(CONSTANT_BUFFER_TYPE::GLOBAL)->SetGraphicsGlobalData(&lightParams, sizeof(lightParams));
}

void Scene::AddGameObject(shared_ptr<GameObject> gameObject)
{
	if (gameObject->GetCamera())
		_cameras.push_back(gameObject->GetCamera());

	else if (gameObject->GetLight())
		_lights.push_back(gameObject->GetLight());

	_gameObjects.push_back(gameObject);
}

void Scene::RemoveGameObject(shared_ptr<GameObject> gameObject)
{
	if (gameObject->GetCamera())
	{
		auto findit = find(_cameras.begin(), _cameras.end(), gameObject->GetCamera());
		if (findit != _cameras.end())
			_cameras.erase(findit);
	}

	if (gameObject->GetLight())
	{
		auto findit = find(_lights.begin(), _lights.end(), gameObject->GetLight());
		if (findit != _lights.end())
			_lights.erase(findit);
	}

	auto findit = find(_gameObjects.begin(), _gameObjects.end(), gameObject);
	if (findit != _gameObjects.end())
	{
		_gameObjects.erase(findit);
	}

}
