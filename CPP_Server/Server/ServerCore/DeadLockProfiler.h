#pragma once



class DeadLockProfiler
{
public:
	void PushLock(const char* name);
	void PopLock(const char* name);
	void CheckCycle();

private:
	void Dfs(int32 index);

private:
	unordered_map<const char*, int32>	_nameToId;
	unordered_map<int32, const char*>	_idToName;
	stack<int32>						_lockStack;
	map<int32, set<int32>>				_lockHistory;

	Mutex _lock;

private:
	vector<int32>	_discoveredOrder;//노드 발견 순서 기록
	int32			_discoveredCount = 0; // 바ㅏㄹ견 순서 카운팅
	vector<bool>	_finished; // dfs(i)종료되었는지
	vector<int32>	_parent;
};

