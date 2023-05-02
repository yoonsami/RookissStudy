#include "pch.h"
#include "Camera.h"
#include "Transform.h"
#include "Scene.h"
#include "SceneManager.h"
#include "GameObject.h"
#include "MeshRenderer.h"
#include "Engine.h"

Matrix Camera::S_MatView;

Matrix Camera::S_MatProjection;

Camera::Camera() :Component(COMPONENT_TYPE::CAMERA)
{
}

Camera::~Camera()
{
}

void Camera::FinalUpdate()
{
	_matView = GetTransform()->GetLocalToWorldMatrix().Invert();

	float width = static_cast<float>(GEngine->GetWindow().width);
	float height = static_cast<float>(GEngine->GetWindow().height);

	if (_type == PROJECTION_TYPE::PERSPECTIVE)
		_matProjection = ::XMMatrixPerspectiveFovLH(_fov, width / height, _near, _far);
	else
		_matProjection = ::XMMatrixOrthographicLH(width * _scale, height * _scale, _near, _far);

	S_MatView = _matView;
	S_MatProjection = _matProjection;

	_frustum.FinalUpdate();
}

void Camera::Render()
{
	shared_ptr<Scene> scene = SceneManager::GetInstance()->GetActiveScene();

	const vector<shared_ptr<GameObject>>& gameObjects = scene->GetGameObjects();

	for (auto& gameobject : gameObjects)
	{
		if(gameobject->GetMeshRenderer() == nullptr)
			continue;


		if (gameobject->GetCheckFrustum())
		{
			if (_frustum.ContainSphere(
				gameobject->GetTransform()->GetWorldPosition(),
				gameobject->GetTransform()->GetBoundingSphereRadius()) == false)
			{
				continue;
			}
		}
		gameobject->GetMeshRenderer()->Render();
	}

}
