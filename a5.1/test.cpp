#include<iostream>
using namespace std;

//复数类
class CComplex {
public:
	CComplex(int r = 0, int i = 0)
		:mreal(r)
		, mimage(i)
	{}
	void show() {
		cout << "mreal=" << mreal << " mimage=" << mimage << endl;
	}
	CComplex operator+(const CComplex& src) {//返回值不能用引用/指针是因为comp是这个函数的临时变量
		//CComplex comp;
		//comp.mreal = mreal + src.mreal;
		//comp.mimage = mimage + src.mimage;
		//return comp;
		//代码优化：
		return CComplex(mreal + src.mreal, mimage + src.mimage);
	}
	/*
	CComplex operator++() {
		return CComplex(++mreal, ++mimage);
	}
	*/
	CComplex& operator++() {
		++mreal;
		++mimage;
		return *this;
	}
	CComplex operator++(int) {
		return CComplex(mreal++, mimage++);
	}
	void operator+=(const CComplex& src) {
		mreal += src.mreal;
		mimage += src.mimage;
	}
private:
	int mreal;//实数
	int mimage;//虚数
	friend CComplex operator+(const CComplex& lhs, const CComplex& rhs);
	friend ostream& operator<<(ostream& out, const CComplex& src);
	friend istream& operator>>(istream& in, CComplex& src);
};
CComplex operator+(const CComplex& lhs, const CComplex& rhs) {
	return(CComplex(lhs.mreal + rhs.mreal, lhs.mimage + rhs.mimage));//类外函数无法访问私有成员，所以需要定义为友元函数
}
ostream& operator<<(ostream& out, const CComplex& src) {
	out << "mreal=" << src.mreal << " mimage=" << src.mimage << endl;
	return out;
}
istream& operator>>(istream& in, CComplex& src) {
	in >> src.mreal >> src.mimage;
	return in;
}
int main() {
	CComplex comp1(10, 10);
	CComplex comp2(20, 20);
	CComplex comp3 = comp1 + comp2;
	comp3.show();

	CComplex comp4 = comp1 + 20;//将20传给形参src，将int强转为CComplex类型，编译器会找带int参数的CComplex构造函数，相当于用20构造了一个临时变量
	comp4.show();
	CComplex comp5 = 20 + comp1;//无法调用成员方法，可以写一个全局方法应对此情况
	//编译器做对象运算时，会调用对象的运算符重载函数。优先调用其成员方法，如果找不到就会去全局作用域找
	comp5.show();

	comp4 = comp1++;//++ --单目运算符，为了区分前置和后置，前置为operator++()，后置operator++(int),int无意义，只是为了区分
	comp5 = ++comp2;
	comp4.show();
	comp1.show();
	comp5.show();

	cout << comp5 << endl;//对象不在最左边，无法写到成员方法

	cin >> comp5;
	cout << comp5 << endl;
	return 0;
}