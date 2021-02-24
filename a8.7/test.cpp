#include<iostream>
#include<vector>
#include<algorithm>//������C++ STL�����з����㷨
#include<functional>//�����˺�������Ͱ���
using namespace std;

int main() {
	int arr[10] = { 23,5,2,64,24,12,77,32,1,8 };
	vector<int> vec(arr, arr + sizeof(arr) / sizeof(arr[0]));//�����������˵ĵ�����
	for (int v : vec) {
		cout << v << " ";
	}
	cout << endl;
	sort(vec.begin(), vec.end());//Ĭ��С���������
	for (int v : vec) {
		cout << v << " ";
	}
	cout << endl;
	if (binary_search(vec.begin(), vec.end(), 12)) {//ֻ�������������н��еĶ��ֲ��ң�O(1)
		cout << "12����" << endl;
	}
	sort(vec.begin(), vec.end(), greater<int>());//���뺯������ʹ�ô�С������
	for (int v : vec) {
		cout << v << " ";
	}
	cout << endl;
	auto it1 = find(vec.begin(), vec.end(), 23);//O(n)
	if (it1 != vec.end())cout << "23����" << endl;

	//77 64 32 24 23 12 8 5 2 1
	//���󣺽�11������룬�൱���ҵ�һ��С��11������
	auto it2 = find_if(vec.begin(), vec.end(), bind1st(greater<int>(), 11));//ͬbind2nd(less<int>(), 11)
	vec.insert(it2, 11);
	for (int v : vec) {
		cout << v << " ";
	}
	cout << endl;



	return 0;
}