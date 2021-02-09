#include<iostream>
#include<vector>
using namespace std;

#if 0

int main() {
	vector<int> vec;
	for (int i = 0; i < 10; ++i) {
		vec.push_back(rand() % 100 + 1);
	}
	for (int v : vec) {
		cout << v << " ";
	}
	cout << endl;
#if 0
	auto it = vec.begin();
	for (; it != vec.end(); ++it) {
		cout << *it << endl;
		if (*it % 2 == 0) {
			vec.insert(it, *it - 1);
			break;//如果去掉break，进程运行出现意外错误
			//第一次调用insert()后，迭代器it就失效了
		}
	}
#endif
#if 1
	auto it1 = vec.begin();
	for (; it1 != vec.end(); ++it1) {
		if (*it1 % 2 == 0) {
			it1 = vec.insert(it1, *it1 - 1);
			++it1;
		}
	}
	for (int v : vec) {
		cout << v << " ";
	}
	cout << endl;
#endif
#if 0
	auto it = vec.begin();
	for (; it != vec.end(); ++it) {
		cout << *it << endl;
		if (*it % 2 == 0) {
			vec.erase(it);//insert(it,val),erase(it)：在指定迭代器位置增删元素
			break;//如果去掉break，进程运行出现意外错误
			//第一次调用erase()后，迭代器it就失效了
		}
	}
#endif
#if 0
	auto it2 = vec.begin();
	while (it2 != vec.end()) {
		if (*it2 % 2 == 0)
			it2 = vec.erase(it2);
		else ++it2;
	}
	for (int v : vec) {
		cout << v << " ";
	}
	cout << endl;
#endif
	return 0;
}
#endif