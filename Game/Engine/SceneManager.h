#pragma once

class Scene;
class GameObject;

enum
{
	MAX_LAYER = 32,
};

class SceneManager : public Singleton<SceneManager>
{
private:
	SceneManager() {}
	~SceneManager() {}
	friend class Singleton<SceneManager>;

public:
	void Update();
	void Render();
	void LoadScene(const wstring& sceneName);

	void SetLayerName(uint8 index, const wstring& name);
	const wstring& IndexToLayerName(uint8 index) { return _layerNames[index]; }
	uint8 LayerNameToIndex(const wstring& name);

	shared_ptr<GameObject> Pick(int32 screenX, int32 screenY);

public:
	shared_ptr<Scene> GetActiveScene() { return _activeScene; }

private:
	shared_ptr<Scene> LoadTestScene();

private:
	shared_ptr<Scene> _activeScene;

	array<wstring, MAX_LAYER> _layerNames;
	map<wstring, uint8> _layerIndex;
};

