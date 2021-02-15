#include<iostream>
using namespace std;

class Base {
public:
	Base(int data = 20)
		:ma(data)
	{
		cout << "Base()" << endl;
	}
	virtual void show() {
		cout << "call Base::show()" << endl;
	}
protected:
	int ma;
};
class Derive :public Base {
public:
	Derive(int data = 20)
		:Base(data)
		, mb(data)
	{
		cout << "Derive()" << endl;
	}
	void show() {
		cout << "call Derive::show()" << endl;
	}
protected:
	int mb;
};
int main() {
	Base b;
	Derive d;

	//用对象本身调用虚函数是不会发生动态绑定的
	b.show();//静态绑定
	d.show();//静态绑定

	//指针和引用调用虚函数才是动态绑定
	Base* pb1 = &b;
	pb1->show();//动态绑定
	Base* pb2 = &d;
	pb2->show();//动态绑定

	Base& rb1 = b;
	rb1.show();//动态绑定
	Base& rb2 = d;
	rb2.show();//动态绑定

	Derive* pd1 = &d;
	pd1->show();//动态绑定
	Derive& rd = d;
	rd.show();//动态绑定

	Derive* pd2 = (Derive*)&b;
	pd2->show();//是动态绑定，但是pd2解引用得到b，其中vfptr指向的是Base的vftable，其中保存的是基类的虚函数地址
	//所以这一句是动态绑定，但仍调用的是基类虚函数

	return 0;
}