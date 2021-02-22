#include<iostream>
#include<vector>

using namespace std;

int main() {
	vector<int> vec;
	for (int i = 0; i < 20; ++i) {
		vec.push_back(rand() % 100 + 1);
	}
	vector<int>::const_iterator it1 = vec.begin();//iterator对象传给const_iterator对象
	for (; it1 != vec.end(); ++it1) {
		cout << *it1 << " ";
		//*it1 = 0;不能修改
	}
	cout << endl;
	//rbegin()：返回最后一个元素的迭代器表示 
	//rend()：返回首元素前驱位置的反向迭代器表示
	//vector<int>::reverse_iterator it2 = vec.rbegin();
	auto rit = vec.rbegin();
	for (; rit != vec.rend(); ++rit) {
		cout << *rit << " ";
	}
	vector<int>::const_reverse_iterator it3 = vec.rbegin();//常反向迭代器
	return 0;
}