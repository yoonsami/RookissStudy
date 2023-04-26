#include "pch.h"
#include "Timer.h"

Timer::Timer()
{
}

Timer::~Timer()
{
}

void Timer::Init()
{
	::QueryPerformanceFrequency(&_frequency);
	::QueryPerformanceCounter(&_prevCount);
	_timeScale = 1. / _frequency.QuadPart;
}

void Timer::Update()
{

	::QueryPerformanceCounter(&_currCount);

	_deltaTime = static_cast<double>(_currCount.QuadPart - _prevCount.QuadPart) * _timeScale;
	_prevCount = _currCount;
	_frameCount++;
	_frameTime += _deltaTime;

	if (_frameTime > 1.f)
	{
		_fps = static_cast<uint32>(_frameCount / _frameTime);
		_frameTime = 0.f;
		_frameCount = 0;
	}
}
