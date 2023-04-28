#include "pch.h"
#include "Engine.h"
#include "Material.h"
#include "Transform.h"
#include "Input.h"
#include "Timer.h"
#include "SceneManager.h"
#include "Light.h"


void Engine::Init(const WindowInfo& info)
{
	_window = info;
	

	// 그려질 화면 크기 설정
	_viewport = { 0, 0, static_cast<FLOAT>(info.width), static_cast<FLOAT>(info.height), 0.0f, 1.0f };
	_scissorRect = CD3DX12_RECT(0, 0, info.width, info.height);

	_device->Init();
	_cmdQueue->Init(_device->GetDevice(), _swapChain);
	_swapChain->Init(info, _device->GetDevice(), _device->GetDXGI(), _cmdQueue->GetCmdQueue());
	_rootSignature->Init();
	_tableDescHeap->Init(256);
	_depthStencilBuffer->Init(_window);

	CreateConstantBuffer(CBV_REGISTER::b0, sizeof(LightParams), 1);

	CreateConstantBuffer(CBV_REGISTER::b1, sizeof(TransformParams), 256);
	CreateConstantBuffer(CBV_REGISTER::b2, sizeof(MaterialParams), 256);

	ResizeWindow(info.width, info.height);

	Input::GetInstance()->Init(info.hwnd);
	Timer::GetInstance()->Init();
}

void Engine::Update()
{
	Input::GetInstance()->Update();
	Timer::GetInstance()->Update();
	SceneManager::GetInstance()->Update();

	Render();


	ShowFPS();
}

void Engine::LateUpdate()
{

}

void Engine::Render()
{
	RenderBegin();

	SceneManager::GetInstance()->Render();

	RenderEnd();
}

void Engine::RenderBegin()
{
	_cmdQueue->RenderBegin(&_viewport, &_scissorRect);
}

void Engine::RenderEnd()
{
	_cmdQueue->RenderEnd();
}

void Engine::ResizeWindow(int32 width, int32 height)
{
	_window.width = width;
	_window.height = height;


	RECT rect = { 0, 0, width, height };
	// :: ->global namespace
	//윈도우 크기 조절
	::AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);
	//윈도우 pos 조절
	::SetWindowPos(_window.hwnd, 0, 100, 100, _window.width, _window.height, 0);
	
	_depthStencilBuffer->Init(_window);
}

void Engine::ShowFPS()
{
	uint32 fps = Timer::GetInstance()->GetFPS();
	WCHAR szBuffer[255] = {};
	swprintf_s(szBuffer, L"FPS : %d, DT : %f", fps, fDT);
	SetWindowText(_window.hwnd, szBuffer);
}

void Engine::CreateConstantBuffer(CBV_REGISTER reg, uint32 bufferSize, uint32 count)
{
	uint8 typeInt = static_cast<uint8>(reg);
	assert(_constantBuffers.size() == typeInt);

	shared_ptr<ConstantBuffer> buffer = make_shared<ConstantBuffer>();
	buffer->Init(reg, bufferSize, count);
	_constantBuffers.push_back(buffer);
}
