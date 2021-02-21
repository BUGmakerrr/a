#include<iostream>
#include<string>
#include<set>
#include<map>

using namespace std;

class Student {
public:
	Student(string name = "", int ID = 0)
		:_name(name),_ID(ID){}
	//bool operator<(const Student& stu)const {
	//	return _ID < stu._ID;
	//}
private:
	string _name;
	int _ID;
	friend ostream& operator<<(ostream& out, const Student& stu);
};
ostream& operator<<(ostream& out, const Student& stu) {
	out << "name:" << stu._name << " ID:" << stu._ID << endl;
	return out;
}
int main() {
	map<int, Student> stuMap;
	stuMap.insert({ 100,Student("angry", 100) });
	stuMap.insert({ 101,Student("birds", 101) });
	stuMap.insert({ 102,Student("flappy", 102) });
	//erase()可以接收迭代器也可以接受key
	cout << stuMap[102] << endl;
	//map排序看的是key值，此处为int，不在需要提供'<'的重载函数
	auto it = stuMap.begin();
	for (; it != stuMap.end(); ++it) {
		cout << it->first << " " << it->second << endl;
	}
	return 0;
}

#if 0
int main() {
	set<Student> set2;//将自定义类型存入有序容器，编译器不知道如何排序,需要提供'<'的重载函数
	set2.insert(Student("angry", 100));
	set2.insert(Student("birds", 101));
	auto it2 = set2.begin();
	for (; it2 != set2.end(); ++it2) {
		cout << *it2 << " ";
	}
	//set<int> set1;
	//for (int i = 0; i < 20; ++i) {
	//	set1.insert(rand() % 100 + 1);
	//}
	//auto it1 = set1.begin();
	//for (; it1 != set1.end(); ++it1) {
	//	cout << *it1 << " ";
	//}//底层是红黑树中序遍历的结果
	return 0;
}
#endif