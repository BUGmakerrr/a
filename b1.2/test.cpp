#include<iostream>
using namespace std;

class Test {
public:
	Test(int a = 10) :ma(a) {
		cout << "Test(int)" << endl;
	}
	~Test() {
		cout << "~Test(int)" << endl;
	}
	Test(const Test& t) :ma(t.ma) {
		cout << "Test(const Test&)" << endl;
	}
	Test& operator=(const Test& t) {
		cout << "operator=(const Test&)" << endl;
		ma = t.ma;
		return *this;
	}
	int getData() {
		return ma;
	}
private:
	int ma;
};
Test GetObject(Test t) {
	int val = t.getData();
	Test tmp(val);
	return tmp;
}
int main() {
	Test t1;
	Test t2;
	t2 = GetObject(t1);//函数返回值拷贝构造一个临时对象，语句结束析构
	return 0;
}