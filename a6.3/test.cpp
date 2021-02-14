#include<iostream>
using namespace std;

class Base {
public:
	Base(int data) 
	:ma(data)
	{}
	void show() {
		cout << "Base::show()" << endl;
	}
	void show(int) {
		cout << "Base::show(int)" << endl;
	}
protected:
	int ma;
};
class Derive :public Base {
public:
	Derive(int data)
		:Base(data)
		,mb(data)
	{}
	void show() {
		cout << "Derive::show()" << endl;
	}
protected:
	int mb;
};
#if 0
int main() {
	Derive d(10);
	d.show();
	d.show(10);
	return 0;
}
#endif
int main() {
	Base b(20);
	Derive d(20);
	b = d;//派生类对象可以赋给基类对象，类型从下向上的转换
	//d = b;基类对象不可以赋给派生类对象

	Base* pb = &d;//基类指针可以指向派生类对象，只能通过解引用访问派生类中从基类继承的部分

	pb->show();
	pb->show(10);
	//调用的都是基类中的成员

	((Derive*)pb)->show();//强转后可以访问派生类成员
	//((Derive*)pb)->show(10);

	//Derive* pd = &b;派生类指针不可以指向基类对象，存在内存非法访问
	Derive* pd = (Derive*)&b;//危险，存在内存非法访问
	pd->show();//访问派生类成员，实际内存中并没有派生类对象
	//pd->show(10);
	
	return 0;
}