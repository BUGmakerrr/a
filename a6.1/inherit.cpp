#include<iostream>
using namespace std;

class A {
public:
	int ma;
protected:
	int mb;
private:
	int mc;
};
class B :public A {//A:父类/基类 B:子类/派生类
public:
	int md;
protected:
	int me;
private:
	int mf;
};