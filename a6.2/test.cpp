#include<iostream>
using namespace std;

class Base {
public:
	Base(int data)
		:ma(data)
	{
		cout << "Base()" << endl;
	}
	~Base() {
		cout << "~Base()" << endl;
	}
protected:
	int ma;
};
class Derive :public Base{
public:
	Derive(int data)
		:Base(data)//ֱ�ӵ��û���Ĺ��캯���������Լ�ȥ��ʼ�������Ա����
		, mb(data)
	{
		cout << "Derive()" << endl;
	}
	~Derive() {
		cout << "Derive()" << endl;
	}
protected:
	int mb;
};
int main() {
	Derive d(20);
	return 0;
}