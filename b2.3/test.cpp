#include<iostream>

using namespace std;

template<typename T>
class RefCnt {
public:
	RefCnt<T>(T* ptr = nullptr)
		:mptr(ptr) {
		if (mptr != nullptr) {
			mcount = 1;
		}
	}
	void addRef(){
		++mcount;
	}
	int delRef(){
		return --mcount;
	}
private:
	T* mptr;
	int mcount;
};

template<typename T>
class CSmartPtr {
public:
	CSmartPtr(T* ptr = nullptr)
		:mptr(ptr) {
		mpRefCnt = new RefCnt<T>(mptr);
	}
	~CSmartPtr() {
		if (0 == mpRefCnt->delRef()) {
			delete mptr;
			mptr = nullptr;
		}
	}

	CSmartPtr(const CSmartPtr<T>& src)
		:mptr(src.mptr)
		,mpRefCnt(src.mpRefCnt){
		if (mptr != nullptr) {
			mpRefCnt->addRef();
		}
	}
	CSmartPtr<T>& operator=(const CSmartPtr<T>& src) {
		if (&src == this)
			return *this;
		if (0 == mpRefCnt->delRef()) {
			delete mptr;
		}
		mptr = src.mptr;
		mpRefCnt = src.mpRefCnt;
		mpRefCnt->addRef();
		return *this;
	}
	T& operator*() {
		return *mptr;
	}
	T* operator->() {
		return mptr;
	}
private:
	T* mptr;
	RefCnt<T>* mpRefCnt;
};
int main() {
	CSmartPtr<int>ptr1(new int);
	CSmartPtr<int>ptr2(ptr1);
	CSmartPtr<int>ptr3;
	ptr3 = ptr2;
	*ptr1 = 10;
	cout << *ptr2 << " " << *ptr3 << endl;
	return 0;
}