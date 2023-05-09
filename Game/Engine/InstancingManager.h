#pragma once
#include "InstancingBuffer.h"

class GameObject;

class InstancingManager : public Singleton<InstancingManager>
{
private:
	InstancingManager() {}
	~InstancingManager() {}
	friend class Singleton<InstancingManager>;

public:
	void Render(vector<shared_ptr<GameObject>>& gameObject);

	void ClearBuffer();
	void Clear() { _buffers.clear(); }

private:
	void AddParam(uint64 instancId, InstancingParams& data);

private:
	map<uint64, shared_ptr<InstancingBuffer>> _buffers;

};

