#pragma once

// 할당 정책 관리

// BaseAllocator

class BaseAllocator
{
public:
	static void*	Alloc(int32 size);
	static void		Release(void* ptr);
};

// StompAllocator
// 속도 뭐 이런거보다 메모리 오염 같은 버그 잡기에 좋음
// ex) 메모리 해제 후에 사용하려는 문제(Use After Free)
//// 유저레벨(메모장 등)
//	//------------
//	// 커널 레벨 (OS )
//	// 유저레벨 간 간섭 불가
//
//	// 가상 주소(다른 프로젝트에서 이 주소로 접근해서 데이터를 바꿔도 안바뀜)
//
//	// 메모리 접근 권한 등을 설정하는 메모리가 또 필요함
//	// 보통 4KB 단위로 페이지별로 관리
//
//SYSTEM_INFO info;
//GetSystemInfo(&info);
//info.dwPageSize; // 기본 4kb
//info.dwAllocationGranularity; // 기본 64kb 메모리 할당 시 배수 단위
//
//// new 등은 c++ 표준일 뿐, os에 직접 요청하는건 아님
//
//
//// 어떻게 사용할 것인지 등 세세하게 조절해서 할당 가능
//int* test = (int*)::VirtualAlloc(NULL, 4, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
//*test = 100;
//VirtualFree(test, 0, MEM_RELEASE);
//
//// 왜 new delete 안쓰고 이걸 하냐
//// -> 이 이후에 test에 접근하면 크래시가 남
//// new delete는 아님

class StompAllocator
{
	enum {PAGE_SIZE = 0x1000};
public:
	static void*	Alloc(int32 size);
	static void		Release(void* ptr);


};