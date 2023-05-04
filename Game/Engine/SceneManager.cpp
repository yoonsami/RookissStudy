#include "pch.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Engine.h"
#include "Material.h"
#include "GameObject.h"
#include "MeshRenderer.h"
#include "Camera.h"
#include "Light.h"
#include "Transform.h"
#include "TestCameraScript.h"
#include "Resources.h"

void SceneManager::Update()
{
	if (_activeScene == nullptr)
		return;
	
	_activeScene->Update();
	_activeScene->LateUpdate();
	_activeScene->FinalUpdate();
	

}

void SceneManager::Render()
{
	if (_activeScene)
		_activeScene->Render();

	


}

void SceneManager::LoadScene(const wstring& sceneName)
{

	// 기존 Scene 정리
	// 파일에서 Scene 불러오기

	_activeScene = LoadTestScene();

	_activeScene->Awake();
	_activeScene->Start();
}

void SceneManager::SetLayerName(uint8 index, const wstring& name)
{
	const wstring& preName = _layerNames[index];
	_layerIndex.erase(preName);

	_layerNames[index] = name;
	_layerIndex[name] = index;

}

uint8 SceneManager::LayerNameToIndex(const wstring& name)
{
	auto findit = _layerIndex.find(name);
	if (findit == _layerIndex.end())
		return 0;

	return findit->second;
}

shared_ptr<Scene> SceneManager::LoadTestScene()
{
#pragma region LayerMask
	SetLayerName(0, L"Default");
	SetLayerName(1, L"UI");
#pragma endregion LayerMask
	shared_ptr<Scene> scene = make_shared<Scene>();

#pragma  region Camera
	{
		shared_ptr<GameObject> camera = make_shared<GameObject>();
		camera->SetName(L"Main_Camera");
		camera->AddComponent(make_shared<Transform>());
		camera->GetTransform()->SetLocalPosition(Vec3{ 0.f,0.f,0.f });
		camera->AddComponent(make_shared<Camera>());
		uint8 layerIndex = SceneManager::GetInstance()->LayerNameToIndex(L"UI");
		camera->GetCamera()->SetCullingMaskLayerOnOff(layerIndex, true);
		camera->AddComponent(make_shared<TestCameraScript>());
		scene->AddGameObject(camera);
	}
	{
		shared_ptr<GameObject> camera = make_shared<GameObject>();
		camera->SetName(L"Orthographic_Camera");
		camera->AddComponent(make_shared<Transform>());
		camera->GetTransform()->SetLocalPosition(Vec3{ 0.f,0.f,0.f });
		camera->AddComponent(make_shared<Camera>());
		camera->GetCamera()->SetProjectionType(PROJECTION_TYPE::ORTHOGRAPHIC);
		uint8 layerIndex = SceneManager::GetInstance()->LayerNameToIndex(L"UI");
		camera->GetCamera()->SetCullingMaskAll();
		camera->GetCamera()->SetCullingMaskLayerOnOff(layerIndex, false);
		scene->AddGameObject(camera);
	}
#pragma  endregion

#pragma region SkyBox
	{
		shared_ptr<GameObject> skybox = make_shared<GameObject>();
		skybox->AddComponent(make_shared<Transform>());
		skybox->SetCheckFrustum(false);
		shared_ptr<MeshRenderer> meshRenderer = make_shared<MeshRenderer>();
		{
			shared_ptr<Mesh> sphereMesh = Resources::GetInstance()->LoadSphereMesh();
			meshRenderer->SetMesh(sphereMesh);
		}
		{
			shared_ptr<Shader> shader = Resources::GetInstance()->Get<Shader>(L"Skybox");
			shared_ptr<Texture> texture = Resources::GetInstance()->Load<Texture>(L"Sky01", L"..\\Resources\\Texture\\Sky01.jpg");
			shared_ptr<Material> material = make_shared<Material>();
			material->SetShader(shader);
			material->SetTexture(0, texture);
			meshRenderer->SetMaterial(material);
		}
		skybox->AddComponent(meshRenderer);
		scene->AddGameObject(skybox);
	}
#pragma endregion

#pragma region Sphere
	/*{
		shared_ptr<GameObject> sphere = make_shared<GameObject>();
		sphere->AddComponent(make_shared<Transform>());
		sphere->GetTransform()->SetLocalScale(Vec3(100.f, 100.f, 100.f));
		sphere->GetTransform()->SetLocalPosition(Vec3(0.f, 0.f, 150.f));
		shared_ptr<MeshRenderer> meshRenderer = make_shared<MeshRenderer>();
		{
			shared_ptr<Mesh> sphereMesh = Resources::GetInstance()->LoadSphereMesh();
			meshRenderer->SetMesh(sphereMesh);
		}
		{
			shared_ptr<Shader> shader = make_shared<Shader>();
			shared_ptr<Texture> texture = make_shared<Texture>();
			shader->Init(L"..\\Resources\\Shader\\default.fx");
			texture->Init(L"..\\Resources\\Texture\\veigar.jpg");
			shared_ptr<Material> material = make_shared<Material>();
			material->SetShader(shader);
			material->SetTexture(0, texture);
			meshRenderer->SetMaterial(material);
		}
		sphere->AddComponent(meshRenderer);
		scene->AddGameObject(sphere);
	}*/
#pragma endregion

#pragma region Cube
	{
		shared_ptr<GameObject> sphere = make_shared<GameObject>();
		sphere->AddComponent(make_shared<Transform>());
		sphere->GetTransform()->SetLocalScale(Vec3(100.f, 100.f, 100.f));
		sphere->GetTransform()->SetLocalPosition(Vec3(0.f, 0.f, 150.f));
		shared_ptr<MeshRenderer> meshRenderer = make_shared<MeshRenderer>();
		{
			shared_ptr<Mesh> sphereMesh = Resources::GetInstance()->LoadCubeMesh();
			meshRenderer->SetMesh(sphereMesh);
		}
		{
			shared_ptr<Shader> shader = Resources::GetInstance()->Get<Shader>(L"Forward");
			shared_ptr<Texture> texture = Resources::GetInstance()->Load<Texture>(L"Wood", L"..\\Resources\\Texture\\Wood.jpg");
			shared_ptr<Texture> texture2 = Resources::GetInstance()->Load<Texture>(L"Wood_Normal", L"..\\Resources\\Texture\\Wood_Normal.jpg");
			shared_ptr<Material> material = make_shared<Material>();
			material->SetShader(shader);
			material->SetTexture(0, texture);
			material->SetTexture(1, texture2);
			meshRenderer->SetMaterial(material);
		}
		sphere->AddComponent(meshRenderer);
		scene->AddGameObject(sphere);
	}
#pragma endregion

#pragma region UI_Test
	{
		shared_ptr<GameObject> sphere = make_shared<GameObject>();
		sphere->SetLayerIndex(SceneManager::GetInstance()->LayerNameToIndex(L"UI"));
		sphere->AddComponent(make_shared<Transform>());
		sphere->GetTransform()->SetLocalScale(Vec3(100.f, 100.f, 100.f));
		sphere->GetTransform()->SetLocalPosition(Vec3(0.f,0.f, 500.f));
		shared_ptr<MeshRenderer> renderer = make_shared<MeshRenderer>();
		{
			shared_ptr<Mesh> mesh = Resources::GetInstance()->LoadRectangleMesh();
			renderer->SetMesh(mesh);
		}
		{
			shared_ptr<Shader> shader = Resources::GetInstance()->Get<Shader>(L"Forward");
			shared_ptr<Texture> texture = Resources::GetInstance()->Load<Texture>(L"Wood", L"..\\Resources\\Texture\\Wood.jpg");
			shared_ptr<Material> material = make_shared<Material>();
			material->SetShader(shader);
			material->SetTexture(0,texture);
			renderer->SetMaterial(material);
		}

		sphere->AddComponent(renderer);
		scene->AddGameObject(sphere);
	}
#pragma endregion UI_Test

#pragma region Green Directional Light
	{
		shared_ptr<GameObject> light = make_shared<GameObject>();
		light->AddComponent(make_shared<Transform>());
		//light->GetTransform()->SetLocalPosition(Vec3(0.f, 150.f, 150.f));
		light->AddComponent(make_shared<Light>());
		light->GetLight()->SetLightDirection(Vec3(1.f, 0.f, 1.f));
		light->GetLight()->SetLightType(LIGHT_TYPE::DIRECTIONAL_LIGHT);
		light->GetLight()->SetDiffuse(Vec3(0.5f, 0.5f, 0.5f));
		light->GetLight()->SetAmbient(Vec3(0.1f, 0.1f, 0.1f));
		light->GetLight()->SetSpecular(Vec3(0.1f, 0.1f, 0.1f));

		scene->AddGameObject(light);
	}

#pragma endregion


	return scene;
}
