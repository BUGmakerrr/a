#include<iostream>
using namespace std;

class A {
public:
	virtual void func() {
		cout << "call A::func()" << endl;
	}
protected:
	int ma;
};
class B :virtual public A {//虚继承，类A称为虚基类
public:
	void func() {
		cout << "call B::func()" << endl;
	}
private:
	int mb;
};
int main() {
	A* pa = new B();
	pa->func();
	delete pa;//调用没问题，delete会出错
	return 0;
}