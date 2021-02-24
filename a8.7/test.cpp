#include<iostream>
#include<vector>
#include<algorithm>//包含了C++ STL中所有泛型算法
#include<functional>//包含了函数对象和绑定器
using namespace std;

int main() {
	int arr[10] = { 23,5,2,64,24,12,77,32,1,8 };
	vector<int> vec(arr, arr + sizeof(arr) / sizeof(arr[0]));//传入数组两端的迭代器
	for (int v : vec) {
		cout << v << " ";
	}
	cout << endl;
	sort(vec.begin(), vec.end());//默认小到大的排序
	for (int v : vec) {
		cout << v << " ";
	}
	cout << endl;
	if (binary_search(vec.begin(), vec.end(), 12)) {//只能在有序容器中进行的二分查找，O(1)
		cout << "12存在" << endl;
	}
	sort(vec.begin(), vec.end(), greater<int>());//传入函数对象使用大到小的排序
	for (int v : vec) {
		cout << v << " ";
	}
	cout << endl;
	auto it1 = find(vec.begin(), vec.end(), 23);//O(n)
	if (it1 != vec.end())cout << "23存在" << endl;

	//77 64 32 24 23 12 8 5 2 1
	//需求：将11按序插入，相当于找第一个小于11的数字
	auto it2 = find_if(vec.begin(), vec.end(), bind1st(greater<int>(), 11));//同bind2nd(less<int>(), 11)
	vec.insert(it2, 11);
	for (int v : vec) {
		cout << v << " ";
	}
	cout << endl;



	return 0;
}