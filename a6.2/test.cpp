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
		:Base(data)//直接调用基类的构造函数而不是自己去初始化基类成员变量
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