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
	//CSmartPtr<int> ptr2(ptr1);//��������Ϊptr1��ptr2����ͬһ����Դ��
	//����ָ���������������������Ϊptr2.mptr�����ڴ������Ϊ����ptr1��ͬһ����Դ
	auto_ptr<int> ptr1(new int);
	auto_ptr<int> ptr2(ptr1);
	//cout << *ptr1 << endl;

	unique_ptr<int>ptr1(new int);
	unique_ptr<int>ptr2(move(ptr1));
	return 0;
}