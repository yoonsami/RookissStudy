#include "pch.h"
#include "TestCameraScript.h"
#include "Transform.h"
#include "Camera.h"
#include "GameObject.h"
#include "Input.h"
#include "Timer.h"

TestCameraScript::TestCameraScript()
{
}

TestCameraScript::~TestCameraScript()
{
}

void TestCameraScript::LateUpdate()
{
	Vec3 pos = GetTransform()->GetLocalPosition();

	if (Input::GetInstance()->GetButton(KEY_TYPE::W))
		pos += GetTransform()->GetLook() * _speed * fDT;

	if (Input::GetInstance()->GetButton(KEY_TYPE::S))
		pos -= GetTransform()->GetLook() * _speed * fDT;

	if (Input::GetInstance()->GetButton(KEY_TYPE::A))
		pos -= GetTransform()->GetRight() * _speed * fDT;

	if (Input::GetInstance()->GetButton(KEY_TYPE::D))
		pos += GetTransform()->GetRight() * _speed * fDT;

	if (Input::GetInstance()->GetButton(KEY_TYPE::Q))
	{
		Vec3 Rotation = GetTransform()->GetLocalRotation();
		Rotation.x += fDT * 0.5f;
		GetTransform()->SetLocalRotation(Rotation);
	}

	if (Input::GetInstance()->GetButton(KEY_TYPE::E))
	{
		Vec3 Rotation = GetTransform()->GetLocalRotation();
		Rotation.x -= fDT * 0.5f;
		GetTransform()->SetLocalRotation(Rotation);
	}

	if (Input::GetInstance()->GetButton(KEY_TYPE::Z))
	{
		Vec3 Rotation = GetTransform()->GetLocalRotation();
		Rotation.y += fDT * 0.5f;
		GetTransform()->SetLocalRotation(Rotation);
	}

	if (Input::GetInstance()->GetButton(KEY_TYPE::C))
	{
		Vec3 Rotation = GetTransform()->GetLocalRotation();
		Rotation.y -= fDT * 0.5f;
		GetTransform()->SetLocalRotation(Rotation);
	}


	GetTransform()->SetLocalPosition(pos);
}
