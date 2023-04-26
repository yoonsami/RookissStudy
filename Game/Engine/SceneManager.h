#pragma once

class Scene;
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
public:
	shared_ptr<Scene> GetActiveScene() { return _activeScene; }

private:
	shared_ptr<Scene> LoadTestScene();

private:
	shared_ptr<Scene> _activeScene;
};

