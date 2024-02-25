#include "pch.h"
#include "ThreadManager.h"
#include "Memory.h"
// 메모리 풀링

// new operator overloading(Global)
//void* operator new(size_t size)
//{
//	void* ptr = ::malloc(size);
//	return ptr;
//}
//
//void operator delete(void* ptr)
//{
//	::free(ptr);
//}

class Test
{
public:
	Test() { cout << "Test()" << endl; }
	Test(int32 a) { cout << "Test(int32)" << endl; }
	~Test() { cout << "~Test()" << endl; }
};

int main()
{
	Test* a = xnew<Test>();
	Test* b = xnew<Test>(5);


	xdelete(a);
	xdelete(b);

}
