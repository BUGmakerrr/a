#include<iostream>
#include<vector>

using namespace std;

int main() {
	vector<int> vec;
	for (int i = 0; i < 20; ++i) {
		vec.push_back(rand() % 100 + 1);
	}
	vector<int>::const_iterator it1 = vec.begin();//iterator���󴫸�const_iterator����
	for (; it1 != vec.end(); ++it1) {
		cout << *it1 << " ";
		//*it1 = 0;�����޸�
	}
	cout << endl;
	//rbegin()���������һ��Ԫ�صĵ�������ʾ 
	//rend()��������Ԫ��ǰ��λ�õķ����������ʾ
	//vector<int>::reverse_iterator it2 = vec.rbegin();
	auto rit = vec.rbegin();
	for (; rit != vec.rend(); ++rit) {
		cout << *rit << " ";
	}
	vector<int>::const_reverse_iterator it3 = vec.rbegin();//�����������
	return 0;
}