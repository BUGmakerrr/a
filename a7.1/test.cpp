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
class B :virtual public A {//��̳У���A��Ϊ�����
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
	delete pa;//����û���⣬delete�����
	return 0;
}