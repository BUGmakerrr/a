#include<iostream>
using namespace std;

void* operator new(size_t size) {
	void* p = malloc(size);
	if (p == nullptr)
		throw bad_alloc();
	return p;
}
void operator delete(void* ptr) {
	free(ptr);
}
void* operator new[](size_t size) {
	void* p = malloc(size);
	if (p == nullptr)
		throw bad_alloc();
	cout << p << endl;
	return p;
}
void operator delete[](void* ptr) {
	free(ptr);
}

class Test {
public:
	Test(int data=10)
		:ma(data)
	{
		cout << "Test" << endl;
	}
	~Test() { cout << "~Test" << endl; }
private:
	int ma;
};
int main() {
	Test* p = new Test[5];//此时会在堆底额外开辟一个4字节的空间来储存元素的个数，总共有4+5*4=24个字节。
	//p仍然指向首元素地址，假设首元素地址为0x104，那p指向0x104，0x100的int储存对象个数。
	cout << p << endl;
	delete[]p;
	//剩下的20字节平分5份来推算出各对象的地址，去调用它们的析构函数
	//释放的时候p-4从0x100释放
}
//