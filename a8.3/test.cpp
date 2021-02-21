#include<iostream>
#include<set>//包含set、multiset
#include<map>//包含map、multimap
#include<unordered_set>//包含unordered_set、unordered_multiset
#include<unordered_map >//包含unordered_map、unordered_multimap
#include<string>

using namespace std;

int main() {
#if 0
	unordered_set<int> set1;
	for (int i = 0; i < 50; ++i) {
		set1.insert(rand() % 100 + 1);//与线性表不同，不需要迭代器指定插入的位置，插入的位置由哈希表的哈希函数决定
	}
	cout << set1.size() << endl;
	cout << set1.count(17) << endl;//返回该数字的个数，单重集合一定是1或0	unordered_set<int> set1;
	unordered_multiset<int> set2;
	for (int i = 0; i < 50; ++i) {
		set2.insert(rand() % 100 + 1);//与线性表不同，不需要迭代器指定插入的位置，插入的位置由哈希表的哈希函数决定
	}
	cout << set2.size() << endl;
	cout << set2.count(11) << endl;//返回该数字的个数，单重集合一定是1或0

	set1.erase(20);//按key值删除元素

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

	it1 = set1.find(50);//找到了返回指向该位置的迭代器，没找到返回end()
	if (it1 != set1.end()) {
		set1.erase(it1);
	}
	for (int v : set1) {
		cout << v << " ";
	}
#endif
	/*
	map中保存的都是pair对象
	struct pair{
	first;保存key
	second;保存value
	}
	*/
#if 0
	unordered_map<int, string> map1;
	map1.insert(make_pair(100, "angry"));//不能直接传入数据，需要先用make_pair函数将数据打包为pair对象
	map1.insert({ 101, "video" });//或使用{}传入初始化数据，此法用来初始化struct定义的类
	map1.insert({ 102, "game" });
	map1.insert({ 100, "nerd" });
	cout << map1.size() << endl;//3，改成multimap是4
	cout << map1[100] << endl;//operator[](key)=>返回value。multimap没有该运算符
	map1[200]; //operator[](key)不仅有查询的功能，如果输入的key值不存在，则插入一个该key值，value值为默认构造的成员
	cout << map1.size() << endl;
	map1[1000] = "AVGN";//[]插入的应用，相当于map1.insert({ 1000, "AVGN" });
	map1[1000] = "AVGN2";//修改

	map1.erase(102);

	auto it1 = map1.find(1000);
	if (it1 != map1.end()) {
		cout << "key:" << it1->first << " value:" << it1->second << endl;//迭代器指向的是pair对象
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
	
	//去重
	unordered_set<int> set2;
	for (int v : arr) {
		set2.insert(v);
	}
	for (int v : set2) {
		cout << v << " ";
	}
	#if 0
	unordered_map<int, int> map2;//first表示数字，second表示该数字重复的个数
	for (int k : arr) {
		/*auto it = map2.find(arr[k]);
		if (it == map2.end()) {
			map2.insert({ k, 1 });
		}
		else {
			it->second++;
		}*/
		map2[k]++;//这一句效果等同于上边
	}

	//查重
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