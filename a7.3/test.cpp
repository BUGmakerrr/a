#include<iostream>
using namespace std;

class Base {
public:
	virtual void func() = 0;
};
class Derive1 :public Base {
public:
	void func() {
		cout << "call Derive1::func()" << endl;
	}
};
class Derive2 :public Base {
public:
	void func() {
		cout << "call Derive2::func()" << endl;
	}
	void D2func() {
		cout << "call Derive2::D2func()" << endl;
	}
};
void showFunc(Base* p) {
	//dynamic_cast会检查p是否指向一个Derive2类型对象，如果是，返回该Derive2对象地址，如果不是，返回nullptr
	//static_cast是静态转换，查看的是编译时期的类型。dynamic_cast会去RTTI中查看运行时期的类型
	Derive2* pd2 = dynamic_cast<Derive2*>(p);
	if (pd2 == nullptr) {
		pd2->func();
	}
	else {
		pd2->D2func();
	}
}
int main() {
	Derive1 d1;
	Derive2 d2;
	showFunc(&d1);
	showFunc(&d2);

#if 0
	int* p1 = nullptr;
	double* p2 = reinterpret_cast<double*>(p1);
	//支持转换，尽管不安全
#endif
#if 0
	int a = 10;
	char b = static_cast<char>(a); //尖括号中是想转换成的类型
	cout << typeid(b).name() << endl << b << endl;

	/*int* p1 = nullptr;
	short* p2 = static_cast<short*>(p1);报错：不支持这种无意义的类型转换，编译器只转换认为有联系的类型*/
#endif
#if 0
	//const_cast：去掉常量属性的类型转换
	const int a = 10;
	int* p1 = (int*)&a;
	int* p2 = const_cast<int*>(&a);//相当于一个模板，尖括号中是想转换成的类型
	//两种方式产生的汇编指令完全相同
	//但是传入的类型或指针类型与原类型不相符，const_cast会报错。而强转则没有限制
	//int b = const_cast<int>a;报错：const_cast 中的类型必须是指针、引用或指向对象类型成员的指针
#endif
	return 0;
}