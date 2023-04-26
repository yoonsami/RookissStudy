#include "pch.h"
#include "Transform.h"
#include "Engine.h"
#include "Camera.h"

Transform::Transform() :Component(COMPONENT_TYPE::TRANSFORM)
{
}

Transform::~Transform()
{
}

void Transform::FinalUpdate()
{
	Matrix matScale = Matrix::CreateScale(_localScale);

	Matrix matRotation = Matrix::CreateRotationX(_localRotation.x);
	matRotation *= Matrix::CreateRotationY(_localRotation.y);
	matRotation *= Matrix::CreateRotationZ(_localRotation.z);

	Matrix matTrans = Matrix::CreateTranslation(_localPosition);

	_matLocal = matScale * matRotation * matTrans;
	_matWorld = _matLocal;

	shared_ptr<Transform> parent = GetParent().lock();
	{
		if (parent)
			_matWorld *= parent->GetLocalToWorldMatrix();
	}

}

void Transform::PushData()
{
	// W V P
	// 
	// TODO
	Matrix matWVP = _matWorld * Camera::S_MatView * Camera::S_MatProjection;
	CONST_BUFFER(CONSTANT_BUFFER_TYPE::TRANSFORM)->PushData(&matWVP,sizeof(matWVP));

}

