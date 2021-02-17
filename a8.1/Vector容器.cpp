#include<iostream>
#include<vector>

using namespace std;

int main() {
#if 0
	vector<int> vec;
	for (int i = 0; i < 20; ++i) {
		vec.push_back(rand() % 100 + 1);
	}

	//两种遍历方式
	int size = vec.size();
	for (int i = 0; i < size; ++i) {
		cout << vec[i] << " ";
	}
	cout << endl;

	auto it1 = vec.begin();
	for (; it1 != vec.end(); ++it1) {
		cout << *it1 << " ";
	}
	cout << endl;

	//删除所有偶数
	auto it2 = vec.begin();
	while (it2 != vec.end()) {
		if (*it2 % 2 == 0) {
			it2 = vec.erase(it2);
		}
		else {
			++it2;
		}
	}
	auto it3 = vec.begin();
	for (; it3 != vec.end(); ++it3) {
		cout << *it3 << " ";
	}
	cout << endl;

	//给当前所有奇数前添加一个小于1的数
	for (auto it1 = vec.begin(); it1 != vec.end(); ++it1) {
		if (*it1 % 2 != 0) {
			it1 = vec.insert(it1, *it1 - 1);
			++it1;
		}
	}
	auto it4 = vec.begin();
	for (; it4 != vec.end(); ++it4) {
		cout << *it4 << " ";
	}
	cout << endl;
#endif
	vector<int> vec;//初始没有开辟空间，随着push_back开始扩容：0，1，2，4，8...效率低代价高
	//所以需要预留空间
#if 0
	vec.reserve(20);
	cout << vec.empty() << endl;//预留空间后仍是空的
	cout << vec.size() << endl;
	for (int i = 0; i < 20; ++i) {//不用再扩容
		vec.push_back(rand() % 100 + 1);
	}
	cout << vec.empty() << endl;
	cout << vec.size() << endl;
#endif
	vec.resize(20);//开辟20个空间并放了20个0
	cout << vec.empty() << endl;
	cout << vec.size() << endl;
	for (int i = 0; i < 20; ++i) {
		vec.push_back(rand() % 100 + 1);
	}
	cout << vec.empty() << endl;
	cout << vec.size() << endl;
	return 0;
}