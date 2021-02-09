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
	Test* p = new Test[5];//��ʱ���ڶѵ׶��⿪��һ��4�ֽڵĿռ�������Ԫ�صĸ������ܹ���4+5*4=24���ֽڡ�
	//p��Ȼָ����Ԫ�ص�ַ��������Ԫ�ص�ַΪ0x104����pָ��0x104��0x100��int������������
	cout << p << endl;
	delete[]p;
	//ʣ�µ�20�ֽ�ƽ��5���������������ĵ�ַ��ȥ�������ǵ���������
	//�ͷŵ�ʱ��p-4��0x100�ͷ�
}
//