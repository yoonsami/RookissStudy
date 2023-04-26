#pragma once

class Timer : public Singleton<Timer>
{
private:
	Timer();
	virtual ~Timer();

	friend class Singleton<Timer>;
public:
	void Init();
	void Update();

	uint32 GetFPS() { return _fps; }
	double GetdoubleDeltaTime() { return _deltaTime; }
	float GetfloatDeltaTime() { return float(_deltaTime); }

private:
	LARGE_INTEGER _frequency{};
	LARGE_INTEGER _prevCount{};
	LARGE_INTEGER _currCount{};
	double  _deltaTime = 0.;
	double  _timeScale = 0.;

private:
	uint32 _frameCount = 0;
	double  _frameTime = 0.f;
	uint32 _fps = 0;
};

