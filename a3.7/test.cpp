#include <iostream>
#include <typeinfo>
using namespace std;

class Test {
public:
	int ma;
	static int mb;
	void Func() {
		cout << "Test::Func" << endl;
	}
	static void static_Func() {
		cout << "Test::static_Func" << endl;
	}
};
int Test::mb;
int main() {
	Test t1;//栈上的对象
	Test* t2 = new Test();//堆上的对象
#if 0
	//int* p = &Test::ma;"int Test::*" 类型的值不能用于初始化 "int *" 类型的实体
	int Test::* p = &Test::ma;
	//*p = 10;必须依赖对象
	t1.*p = 10;
	cout << t1.ma << endl;//10
	t2->*p = 20;
	cout << t2->ma << endl;//20

	int * q = &Test::mb;
	*q = 30;//不依赖于对象
	cout << Test::mb << endl;
	cout << typeid(p).name() << endl;//int Test::*
	cout << typeid(q).name() << endl;//int *
#endif

	//void *pFunc() = &Test::Func; 一般函数指针的定义方式"void (Test::*)()" 类型的值不能用于初始化 "void *" 类型的实体
	void (Test::* p1Func)() = &Test::Func;
	(t1.*p1Func)();//使用对象调用
	(t2->*p1Func)();//使用对象调用
	void(*p2static_Func)() = &Test::static_Func;//都是void*类型
	(*p2static_Func)();
	//static成员使用不依赖于对象，只是落在了类的作用域
	delete t2;
	return 0;
}