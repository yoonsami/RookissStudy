#include "pch.h"
#include "Frustum.h"
#include "Camera.h"

void Frustum::FinalUpdate()
{
	Matrix matViewInv = Camera::S_MatView.Invert();
	Matrix matProjectionInv = Camera::S_MatProjection.Invert();
	Matrix matInv = matProjectionInv * matViewInv;

	vector<Vec3> worldPos =
	{
		::XMVector3TransformCoord(Vec3(-1.f,1.f,0.f),matInv),
		::XMVector3TransformCoord(Vec3(1.f,1.f,0.f),matInv),
		::XMVector3TransformCoord(Vec3(1.f,-1.f,0.f),matInv),
		::XMVector3TransformCoord(Vec3(-1.f,-1.f,0.f),matInv),

		::XMVector3TransformCoord(Vec3(-1.f,1.f,1.f),matInv),
		::XMVector3TransformCoord(Vec3(1.f,1.f,1.f),matInv),
		::XMVector3TransformCoord(Vec3(1.f,-1.f,1.f),matInv),
		::XMVector3TransformCoord(Vec3(-1.f,-1.f,1.f),matInv)
	};

	_planes[PLANE_FRONT] = XMPlaneFromPoints(worldPos[0], worldPos[1], worldPos[2]);
	_planes[PLANE_BACK] = XMPlaneFromPoints(worldPos[4], worldPos[7], worldPos[5]);
	_planes[PLANE_UP] = XMPlaneFromPoints(worldPos[4], worldPos[5], worldPos[1]);
	_planes[PLANE_DOWN] = XMPlaneFromPoints(worldPos[3], worldPos[2], worldPos[7]);
	_planes[PLANE_LEFT] = XMPlaneFromPoints(worldPos[4], worldPos[0], worldPos[7]);
	_planes[PLANE_RIGHT] = XMPlaneFromPoints(worldPos[5], worldPos[6], worldPos[1]);


}

bool Frustum::ContainSphere(const Vec3& pos, float radius)
{
	for (const Vec4& plane : _planes)
	{
		Vec3 normal = Vec3(plane.x, plane.y, plane.z);

		if (normal.Dot(pos) + plane.w > radius)
			return false;
	}


	return true;
}
