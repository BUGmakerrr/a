#include<iostream>
#include<set>//����set��multiset
#include<map>//����map��multimap
#include<unordered_set>//����unordered_set��unordered_multiset
#include<unordered_map >//����unordered_map��unordered_multimap
#include<string>

using namespace std;

int main() {
#if 0
	unordered_set<int> set1;
	for (int i = 0; i < 50; ++i) {
		set1.insert(rand() % 100 + 1);//�����Ա�ͬ������Ҫ������ָ�������λ�ã������λ���ɹ�ϣ��Ĺ�ϣ��������
	}
	cout << set1.size() << endl;
	cout << set1.count(17) << endl;//���ظ����ֵĸ��������ؼ���һ����1��0	unordered_set<int> set1;
	unordered_multiset<int> set2;
	for (int i = 0; i < 50; ++i) {
		set2.insert(rand() % 100 + 1);//�����Ա�ͬ������Ҫ������ָ�������λ�ã������λ���ɹ�ϣ��Ĺ�ϣ��������
	}
	cout << set2.size() << endl;
	cout << set2.count(11) << endl;//���ظ����ֵĸ��������ؼ���һ����1��0

	set1.erase(20);//��keyֵɾ��Ԫ��

	auto it1 = set1.begin();
	for (; it1 != set1.end(); ++it1) {
		cout << *it1 << " ";
	}
	for (it1 = set1.begin(); it1 != set1.end();) {
		if (*it1 == 10) {
			set1.erase(it1);
		}
		else {
			++it1;
		}
	}

	it1 = set1.find(50);//�ҵ��˷���ָ���λ�õĵ�������û�ҵ�����end()
	if (it1 != set1.end()) {
		set1.erase(it1);
	}
	for (int v : set1) {
		cout << v << " ";
	}
#endif
	/*
	map�б���Ķ���pair����
	struct pair{
	first;����key
	second;����value
	}
	*/
#if 0
	unordered_map<int, string> map1;
	map1.insert(make_pair(100, "angry"));//����ֱ�Ӵ������ݣ���Ҫ����make_pair���������ݴ��Ϊpair����
	map1.insert({ 101, "video" });//��ʹ��{}�����ʼ�����ݣ��˷�������ʼ��struct�������
	map1.insert({ 102, "game" });
	map1.insert({ 100, "nerd" });
	cout << map1.size() << endl;//3���ĳ�multimap��4
	cout << map1[100] << endl;//operator[](key)=>����value��multimapû�и������
	map1[200]; //operator[](key)�����в�ѯ�Ĺ��ܣ���������keyֵ�����ڣ������һ����keyֵ��valueֵΪĬ�Ϲ���ĳ�Ա
	cout << map1.size() << endl;
	map1[1000] = "AVGN";//[]�����Ӧ�ã��൱��map1.insert({ 1000, "AVGN" });
	map1[1000] = "AVGN2";//�޸�

	map1.erase(102);

	auto it1 = map1.find(1000);
	if (it1 != map1.end()) {
		cout << "key:" << it1->first << " value:" << it1->second << endl;//������ָ�����pair����
	}
#endif
	int arr[100] = { 0 };
	for (int i = 0; i < 100; ++i) {
		arr[i] = rand() % 20 + 1;
	}
	for (int v : arr) {
		cout << arr[v] << " ";
	}
	cout << endl;
	
	//ȥ��
	unordered_set<int> set2;
	for (int v : arr) {
		set2.insert(v);
	}
	for (int v : set2) {
		cout << v << " ";
	}
	#if 0
	unordered_map<int, int> map2;//first��ʾ���֣�second��ʾ�������ظ��ĸ���
	for (int k : arr) {
		/*auto it = map2.find(arr[k]);
		if (it == map2.end()) {
			map2.insert({ k, 1 });
		}
		else {
			it->second++;
		}*/
		map2[k]++;//��һ��Ч����ͬ���ϱ�
	}

	//����
	for (const pair<int, int> &p : map2) {
		if (p.second > 1) {
			cout << "key:" << p.first << " count:" << p.second << " ";
		}
	}
	cout << endl;
	auto it = map2.begin();
	for (; it != map2.end(); ++it) {
		if (it->second > 1) {
			cout << "key:" << it->first << " count:" << it->second << " ";
		}
	}
#endif
	return 0;
}