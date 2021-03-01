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
//Test GetObject(Test t) {
//	int val = t.getData();
//	Test tmp(val);
//	return tmp;
//}
Test GetObject(Test& t) {
	int val = t.getData();
	return Test(val);
	//用临时对象拷贝构造一个main栈帧上的新对象
	//临时对象拷贝构造一个同类型的新对象，会被编译器优化为直接构造新对象，不生成临时对象
}
int main() {
	Test t1;
	//Test t2;
	//t2 = GetObject(t1);
	Test t2 = GetObject(t1);
	//函数返回值临时对象拷贝构造main栈帧上的新临时对象，
	//main栈帧上的新临时对象再拷贝构造t2，
	//被优化为val直接构造t2
	return 0;
}