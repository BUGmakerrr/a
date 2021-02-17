#include<iostream>
using namespace std;
class A {
public:
	A(int data) :ma(data) {
		cout << "call A()" << endl;
	}
	~A() {
		cout << "call ~A()" << endl;
	}
protected:
	int ma;
 };

class B :virtual public A {
public:
	B(int data) :A(data), mb(data) {
		cout << "call B()" << endl;
	}
	~B() {
		cout << "call ~B()" << endl;
	}
protected:
	int mb;
};
class C :virtual public A {
public:
	C(int data) :A(data), mc(data) {
		cout << "call C()" << endl;
	}
	~C() {
		cout << "call ~C()" << endl;
	}
protected:
	int mc;
};
class D :public B, public C {
public:
	D(int data) :A(data), B(data), C(data), md(data) {
		cout << "call D()" << endl;
	}
	~D() {
		cout << "call ~D()" << endl;
	}
protected:
	int md;
};
int main() {
	D d(11);
	return 0;
}