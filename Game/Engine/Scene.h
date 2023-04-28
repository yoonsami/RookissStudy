#pragma once

class GameObject;
class Scene
{

public:
	void Awake();
	void Start();
	void Update();
	void LateUpdate();
	void FinalUpdate();

	void Render();

private:
	void PushLightData();


public:
	const vector<shared_ptr<GameObject>>& GetGameObjects() { return _gameObjects; }

	void AddGameObject(shared_ptr<GameObject> gameObject);
	void RemoveGameObject(shared_ptr<GameObject> gameObject);

private:
	vector<shared_ptr<GameObject>> _gameObjects;
};

