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
	CSmartPtr<int> ptr1(new int);//���������Զ�����delete
	//CSmartPtr<int> *ptr2 = new CSmartPtr<int>(new int);//���϶�������ָ������޷��Զ�delete���˴�ptr2����ָ��
	CSmartPtr<Test> ptr3 = new Test();
	*ptr1 = 10;
	ptr3->test();
	return 0;
}