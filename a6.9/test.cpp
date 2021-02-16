#include<iostream>
using namespace std;

class Base {
public:
	Base() {
		/*
		调用函数时，先为函数开辟栈帧
		为构造函数开辟完栈帧以后，如果该类有虚函数，会把vftable地址给到当前vfptr
		*/
		cout << "call Base()" << endl;
		clear();
	}
	void clear() {
		memset(this, 0, sizeof(*this));//将对象内存清空
	}
	virtual void show() {
		cout << "call Base::show()" << endl;
	}
};
class Derive :public Base {
public:
	Derive() {
		//为构造函数开辟完栈帧以后，把vftable地址给到当前vfptr
		cout << "call Derive()" << endl;
	}
protected:
	virtual void show() {
		cout << "call Derive::show()" << endl;
	}
};
int main() {
	Base* pb1 = new Base();
	//pb1->show();//出错
	//调用基类构造，vftable地址给到当前vfptr，vfptr被清为0，无法找到虚函数

	Base* pb2 = new Derive();
	pb2->show();
	//先调用Base构造，vftable地址给到当前vfptr，vfptr被清为0
	//再调用Derive构造，vftable地址再给到当前vfptr

	delete pb1;
	delete pb2;

	return 0;
}
#if 0
class Base {
public:
	virtual void show() {
		cout << "call Base::show()" << endl;
	}
};
class Derive :public Base {
private:
	void show() {
		cout << "call Derive::show()" << endl;
	}
};
int main() {
	Base* p = new Derive();
	p->show();//call Derive::show()
	//仍然可以调用派生类中私有的虚函数
	//因为最终可以调用到Derive::show()是在运行时期才确定的
	//成员的访问权限是不是public是在编译时期就确定的
	delete p;
	return 0;
}
#endif
#if 0
class Base {
public:
	virtual void show(int i = 10) {
		cout << "call Base::show(i) : " << i << endl;
	}
};
class Derive :public Base {
public:
	void show(int i = 20) {
		cout << "call Derive::show(i) : " << i << endl;
	}
};
int main() {
	Derive d;
	Base* pb = &d;
	pb->show();//call Derive::show(i) : 10
	//派生类虚函数覆盖了基类虚函数，但是使用了基类虚函数的默认值
	/*
	在编译时期
	此时还未发生动态绑定，编译器只能得到基类虚函数
	push 0Ah 先将基类虚函数默认值压栈
	运行时期
	move eax,dword ptr[p] 将前四个字节即vfptr放入寄存器
	move ecx,dword ptr[eax] 将vfptr中虚函数地址放入寄存器
	call ecx
	*/
	return 0;
}
#endif