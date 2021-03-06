#include<iostream>
#include<memory>

using namespace std;

template<typename T>
class CSmartPtr {
public:
	CSmartPtr(T* ptr = nullptr)
		:mptr(ptr) {}
	~CSmartPtr() {
		delete mptr;
	}
	CSmartPtr(const CSmartPtr<T>& src) {
		mptr = new T(*src.mptr);

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

int main() {
	//CSmartPtr<int> ptr1(new int);
	//CSmartPtr<int> ptr2(ptr1);//编译器视为ptr1、ptr2管理同一块资源，
	//智能指针特殊情况：拷贝构造中为ptr2.mptr开辟内存后仍视为管理ptr1的同一块资源
	auto_ptr<int> ptr1(new int);
	auto_ptr<int> ptr2(ptr1);
	//cout << *ptr1 << endl;

	unique_ptr<int>ptr1(new int);
	unique_ptr<int>ptr2(move(ptr1));
	return 0;
}