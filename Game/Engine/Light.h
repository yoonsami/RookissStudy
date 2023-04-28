#pragma once
#include "Component.h"

enum class LIGHT_TYPE :uint8
{
	DIRECTIONAL_LIGHT,
	POINT_LIGHT,
	SPOT_LIGHT,

};

struct LightColor
{
	Vec4 diffuse;
	Vec4 ambient;
	Vec4 specular;

};

struct LightInfo
{
	LightColor color;
	Vec4 position;
	Vec4 direction;
	int32 lightType;
	float range;
	float angle;
	int32 padding;
};

struct LightParams
{
	uint32 lightCount;
	Vec3	padding;
	LightInfo light[50];
};

class Light :public Component
{
public:
	Light();
	virtual ~Light();

	virtual void FinalUpdate() override;

public:
	const LightInfo& GetLightInfo() { return _light; }

	void SetLightDirection(const Vec3& dir) { _light.direction =  dir ; }

	void SetDiffuse(const Vec3& diffuse) { _light.color.diffuse = diffuse ; }
	void SetAmbient(const Vec3& ambient) { _light.color.ambient =  ambient ; }
	void SetSpecular(const Vec3& specular) { _light.color.specular = specular ; }

	void SetLightType(LIGHT_TYPE type) { _light.lightType = static_cast<int32>(type); }
	void SetLightRange(float range) { _light.range = range; }
	void SetLightAngle(float angle) { _light.angle = angle; }

private:
	LightInfo _light{};

};

