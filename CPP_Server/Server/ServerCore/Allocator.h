#pragma once

// �Ҵ� ��å ����

// BaseAllocator

class BaseAllocator
{
public:
	static void*	Alloc(int32 size);
	static void		Release(void* ptr);
};

// StompAllocator
// �ӵ� �� �̷��ź��� �޸� ���� ���� ���� ��⿡ ����
// ex) �޸� ���� �Ŀ� ����Ϸ��� ����(Use After Free)
//// ��������(�޸��� ��)
//	//------------
//	// Ŀ�� ���� (OS )
//	// �������� �� ���� �Ұ�
//
//	// ���� �ּ�(�ٸ� ������Ʈ���� �� �ּҷ� �����ؼ� �����͸� �ٲ㵵 �ȹٲ�)
//
//	// �޸� ���� ���� ���� �����ϴ� �޸𸮰� �� �ʿ���
//	// ���� 4KB ������ ���������� ����
//
//SYSTEM_INFO info;
//GetSystemInfo(&info);
//info.dwPageSize; // �⺻ 4kb
//info.dwAllocationGranularity; // �⺻ 64kb �޸� �Ҵ� �� ��� ����
//
//// new ���� c++ ǥ���� ��, os�� ���� ��û�ϴ°� �ƴ�
//
//
//// ��� ����� ������ �� �����ϰ� �����ؼ� �Ҵ� ����
//int* test = (int*)::VirtualAlloc(NULL, 4, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
//*test = 100;
//VirtualFree(test, 0, MEM_RELEASE);
//
//// �� new delete �Ⱦ��� �̰� �ϳ�
//// -> �� ���Ŀ� test�� �����ϸ� ũ���ð� ��
//// new delete�� �ƴ�

class StompAllocator
{
	enum {PAGE_SIZE = 0x1000};
public:
	static void*	Alloc(int32 size);
	static void		Release(void* ptr);


};