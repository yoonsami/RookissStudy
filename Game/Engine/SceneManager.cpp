#include "pch.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Engine.h"
#include "Material.h"
#include "GameObject.h"
#include "MeshRenderer.h"
#include "Camera.h"
#include "Transform.h"
#include "TestCameraScript.h"

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
	if (!_activeScene)
		return;

	const vector<shared_ptr<GameObject>>& gameObjects = _activeScene->GetGameObjects();
	for (auto& gameobject : gameObjects)
	{
		if(gameobject->GetCamera() == nullptr)
			continue;

		gameobject->GetCamera()->Render();
	}
}

void SceneManager::LoadScene(const wstring& sceneName)
{

	// 기존 Scene 정리
	// 파일에서 Scene 불러오기

	_activeScene = LoadTestScene();

	_activeScene->Awake();
	_activeScene->Start();
}

shared_ptr<Scene> SceneManager::LoadTestScene()
{
	shared_ptr<Scene> scene = make_shared<Scene>();

#pragma  region TestObject
	shared_ptr<GameObject> gameObject = make_shared<GameObject>();

	vector<Vertex> vertex(4);

	vertex[0].pos = Vec3(-0.5f, 0.5f, 0.5f);
	vertex[0].color = Vec4(1.f, 0.f, 0.f, 1.f);
	vertex[0].uv = Vec2(0.f, 0.f);
	vertex[1].pos = Vec3(0.5f, 0.5f, 0.5f);
	vertex[1].color = Vec4(0.f, 1.0f, 0.f, 1.f);
	vertex[1].uv = Vec2(1.f, 0.f);
	vertex[2].pos = Vec3(0.5f, -0.5f, 0.5f);
	vertex[2].color = Vec4(0.f, 0.f, 1.f, 1.f);
	vertex[2].uv = Vec2(1.f, 1.f);
	vertex[3].pos = Vec3(-0.5f, -0.5f, 0.5f);
	vertex[3].color = Vec4(0.f, 1.f, 0.f, 1.f);
	vertex[3].uv = Vec2(0.f, 1.f);

	vector<uint32> index;
	{
		index.push_back(0);
		index.push_back(1);
		index.push_back(2);
		index.push_back(0);
		index.push_back(2);
		index.push_back(3);
	}


	gameObject->AddComponent(make_shared<Transform>());
	shared_ptr<Transform> transform = gameObject->GetTransform();
	transform->SetLocalPosition(Vec3{ 0.f,100.f,200.f });
	transform->SetLocalScale(Vec3{100.f,100.f,1.f });

	shared_ptr<MeshRenderer> meshRenderer = make_shared<MeshRenderer>();
	{
		shared_ptr<Mesh> mesh = make_shared<Mesh>();
		mesh->Init(vertex, index);	
		meshRenderer->SetMesh(mesh);
	}
	{
		shared_ptr<Shader> shader = make_shared<Shader>();
		shared_ptr<Texture> texture = make_shared<Texture>();
		shader->Init(L"..\\Resources\\Shader\\default.hlsli");
		texture->Init(L"..\\Resources\\Texture\\0.png");

		shared_ptr<Material> material = make_shared<Material>();
		material->SetShader(shader);
		material->SetFloat(0, 0.1f);
		material->SetFloat(1, 0.2f);
		material->SetFloat(2, 0.3f);
		material->SetTexture(0, texture);
		meshRenderer->SetMaterial(material);
	}
	gameObject->AddComponent(meshRenderer);
	scene->AddGameObject(gameObject);
#pragma endregion

#pragma  region Camera
	shared_ptr<GameObject> camera = make_shared<GameObject>();
	camera->AddComponent(make_shared<Transform>());
	camera->AddComponent(make_shared<Camera>());
	camera->AddComponent(make_shared<TestCameraScript>());
	//camera->AddComponent(make_shared<Transform>());
	camera->GetTransform()->SetLocalPosition(Vec3{ 0.f,100.f,0.f });

	scene->AddGameObject(camera);
#pragma  endregion
	return scene;
}
