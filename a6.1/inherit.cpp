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
class B :public A {//A:����/���� B:����/������
public:
	int md;
protected:
	int me;
private:
	int mf;
};