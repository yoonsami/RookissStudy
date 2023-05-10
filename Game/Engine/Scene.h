#pragma once

class GameObject;
class Camera;
class Scene
{

public:
	void Awake();
	void Start();
	void Update();
	void LateUpdate();
	void FinalUpdate();

	shared_ptr<Camera> GetMainCamera();

	void Render();

	void ClearRTV();

	void RenderShadow();
	void RenderDeferred();
	void RenderLights();
	void RenderFinal();

	void RenderForward();

private:
	void PushLightData();


public:
	const vector<shared_ptr<GameObject>>& GetGameObjects() { return _gameObjects; }

	void AddGameObject(shared_ptr<GameObject> gameObject);
	void RemoveGameObject(shared_ptr<GameObject> gameObject);

private:
	vector<shared_ptr<GameObject>>		_gameObjects;
	vector<shared_ptr<Camera>>	_cameras;
	vector<shared_ptr<class Light>>		_lights;

};

