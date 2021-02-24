#include<iostream>
using namespace std;

template<typename T>
class myGreater {
public:
	bool operator()(T a, T b) {
		return a > b;
	}
};
template<typename T>
class myLess {
public:
	bool operator()(T a, T b) {
		return a < b;
	}
};
template<typename T, typename Compare>
bool compare(T a, T b, Compare com) {
	return com(a, b);
}
int main() {
	//bool compare<int, myLess<int>>(int a, int b, myLess<int> com)
	cout << compare(1, 5, myLess<int>()) << endl;
	cout << compare(1, 5, myGreater<int>()) << endl;

	//myLess<int> myless;
	//cout << compare(1, 5, myless) << endl;

	return 0;
}
#if 0
template<typename T>
bool mygreater(T a, T b) {
	return a > b;
}
template<typename T>
bool myless(T a, T b) {
	return a < b;
}

template<typename T,typename Compare>
bool compare(T a, T b, Compare com) {
	return com(a, b);
}

int main() {
	//bool compare<int, bool (*)(int, int)>(int a, int b, bool (*com)(int, int))
	cout << compare(1, 5, myless<int>) << endl;
	cout << compare(1, 5, mygreater<int>) << endl;
	return 0;
}
#endif
#if 0
int sum1(int a, int b) {
	return a + b;
}
class Sum {
public:
	int operator()(int a, int b) {
		return a + b;
	}
};
int main() {
	Sum sum2;
	int ret1 = sum1(1, 2);
	int ret2 = sum2(1, 2);//sum2称为函数对象或仿函数
	cout << ret1 << endl;
	cout << ret2 << endl;
	
	return 0;
}
#endif