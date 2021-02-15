#include<iostream>
using namespace std;

class Base {
public:
	Base(int data)
		:ma(data)
	{
		cout << "Base()" << endl;
	}
	virtual ~Base() {
		cout << "~Base()" << endl;
	}
	void show1() {
		cout << "call Base::show()" << endl;
	}
	virtual void show2() {
		cout << "call Base::show()" << endl;
	}
protected:
	int ma;
};
class Derive :public Base {
public:
	Derive(int data)
		:Base(data)
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
	Base* pb = new Derive(20);
	pb->show1();//静态绑定
	pb->show2();//动态绑定
	delete pb;//打印发现派生类的析构函数没有被调用！
	/*pb->~Base();基类析构函数是普通函数，所以进行了静态绑定
	call Base::~Base()
	*/

	/*将基类析构函数写为虚函数后，派生类析构函数自动成为虚函数
	派生类和基类的析构函数视为同名函数，派生类析构函数会覆盖基类析构函数，但是释放完派生类内存后还是会再去释放基类内存
	*/

	/*Derive d(20);
	Base* pb = &d;
	pb->show();*/

	return 0;
}