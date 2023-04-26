#include "pch.h"
#include "Game.h"
#include "Engine.h"
#include "SceneManager.h"




void Game::Init(const WindowInfo& info)
{
	GEngine->Init(info);
	SceneManager::GetInstance()->LoadScene(L"TestScene");
}

void Game::Update()
{
	GEngine->Update();
}
