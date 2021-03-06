#include<iostream>

using namespace std;

template<typename T>
class CSmartPtr {
public:
	CSmartPtr(T*ptr=nullptr)
		:mptr(ptr){}
	~CSmartPtr() {
		delete mptr;
	}
	T& operator*() {
		return *mptr;
	}
	T* operator->() {
		return mptr;
	}
private:
	T* mptr;
};
class Test {
public:
	void test() {
		cout << "Test::test()" << endl;
	}
};
int main() {
	CSmartPtr<int> ptr1(new int);//出作用域自动调用delete
	//CSmartPtr<int> *ptr2 = new CSmartPtr<int>(new int);//堆上定义智能指针对象无法自动delete，此处ptr2是裸指针
	CSmartPtr<Test> ptr3 = new Test();
	*ptr1 = 10;
	ptr3->test();
	return 0;
}