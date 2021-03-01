#include<iostream>
using namespace std;

#if 0
class Test {
public:
	Test(int data = 0) :ma(data) {
		cout << "Test(int)" << endl;
	}
	~Test() {
		cout << "~Test()" << endl;
	}
	Test(const Test& t) :ma(t.ma) {
		cout << "Test(const Test&)" << endl;
	}
	Test& operator=(const Test& t) {
		cout << "operator=" << endl;
		ma = t.ma;
		return *this;
	}
private:
	int ma;
};
int main() {
	Test t1;
	Test t2 = t1;
	Test t3 = Test(10);//显示生成临时对象，等同于Test t3(20);
	t3 = t2;
	t3 = Test(15);//此处会生成临时对象，因为调用operator=(const Test& t)需要传入对象
	t3 = (Test)30;
	cout << endl;
	//Test* p = &Test(20);出语句临时对象析构
	const Test& ref = Test(20);//出语句临时对象不析构
	return 0;
}
#endif
class Test {
public:
	Test(int a = 0, int b = 0)
		: ma(a)
		, mb(b) {
		cout << "Test(int)" << endl;
	}
	~Test() {
		cout << "~Test()" << endl;
	}
	Test(const Test& t)
		: ma(t.ma)
		, mb(t.mb) {
		cout << "Test(const Test&)" << endl;
	}
	Test& operator=(const Test& t) {
		cout << "operator=" << endl;
		ma = t.ma;
		mb = t.mb;
		return *this;
	}
private:
	int ma;
	int mb;
};
//以下语句编译运行的顺序
Test t1(10, 10);//1 19 析构
int main() {
	Test t2(20, 20);//3 16 析构
	Test t3 = t2;//4 16 析构
	static Test t4 = Test(30, 30);//5 静态变量初始化时间是第一次运行到它的时候 优化后不会有临时对象 17 静态变量在数据端上，程序结束再析构
	t2 = Test(40, 40);//6 会有临时对象
	t2 = (Test)(50, 50);//(50, 50)为逗号表达式，意义同表达式最后一个值50 即50传给a，b为默认值0
	t2 = 60;//8 隐式生成临时对象
	Test* p1 = new Test(70, 70);//9 不是临时对象，delete时析构 
	Test* p2 = new Test[2];//10 对象数组，调用两次构造函数
	//Test* p3 = &Test(80, 80);//11 指针指向临时对象
	const Test& p4 = Test(90, 90);//12 引用临时对象，语句结束不析构 15析构
	delete p1;//13 调用析构
	delete[] p2;//14 调用两次析构

}
Test t5(100, 100);//2 先初始化全局变量 18 析构