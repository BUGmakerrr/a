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
	//erase()���Խ��յ�����Ҳ���Խ���key
	cout << stuMap[102] << endl;
	//map���򿴵���keyֵ���˴�Ϊint��������Ҫ�ṩ'<'�����غ���
	auto it = stuMap.begin();
	for (; it != stuMap.end(); ++it) {
		cout << it->first << " " << it->second << endl;
	}
	return 0;
}

#if 0
int main() {
	set<Student> set2;//���Զ������ʹ���������������������֪���������,��Ҫ�ṩ'<'�����غ���
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
	//}//�ײ��Ǻ������������Ľ��
	return 0;
}
#endif