#pragma once
#include "Allocator.h"

template<typename Type,typename... Args>
Type* xnew(Args&&... args)
{
	Type* memory = static_cast<Type*>(Xalloc(sizeof(Type)));

	// placement new �Ҵ�� �޸� ���� ������ ȣ��
	new(memory)Type(forward<Args>(args)...);
	return memory;
}

template<typename Type>
void xdelete(Type* obj)
{
	// �Ҹ��� ȣ��
	obj->~Type();

	Xrelease(obj);
}
