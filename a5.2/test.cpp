#include<iostream>
using namespace std;

class String {
public:
	String(const char* p = nullptr) {
		if (p != nullptr) {
			_pstr = new char[strlen(p) + 1];//+1是为了/0
			strcpy(_pstr, p);
		}
		else {
			_pstr = new char[1];
			*_pstr = '/0';
		}
	}
	~String() {
		delete _pstr;
		_pstr = nullptr;
	}
	String(const String& str) {
		_pstr = new char[strlen(str._pstr) + 1];
		strcpy(_pstr, str._pstr);
	}
	String& operator=(const String& str) {
		if (this == &str)
			return *this;
		delete _pstr;
		_pstr = new char[strlen(str._pstr) + 1];
		strcpy(_pstr, str._pstr);
		return *this;
	}
	bool operator>(const String& str)const {
		return strcmp(_pstr, str._pstr) > 0;
	}
	bool operator<(const String& str)const {
		return strcmp(_pstr, str._pstr) < 0;
	}
	bool operator==(const String& str)const {
		return strcmp(_pstr, str._pstr) == 0;
	}
	int length()const {
		return strlen(_pstr);//有效字符个数，没有'/0'
	}
	char& operator[](int index) {
		return _pstr[index];
	}
	const char* c_str()const {//将String类型转换为const char*得以和普通字符串进行操作
		return _pstr;
	}
	
private:
	char* _pstr;
	friend ostream& operator<<(ostream& out, const String& str);
	friend String operator+(const String& lstr, const String& rstr);
};
String operator+(const String& lstr, const String& rstr) {
	/*my fall：
	String str;
	str._pstr = new char[strlen(lstr._pstr) + strlen(rstr._pstr) + 1];
	str._pstr = strcat(lstr._pstr, rstr._pstr);
	return str;*/
	/*
	char* ptmp = new char[strlen(lstr._pstr) + strlen(rstr._pstr) + 1];
	strcpy(ptmp, lstr._pstr);
	strcat(ptmp, rstr._pstr);//strcat：连接
	//return String(ptmp);没有delete会内存泄漏
	String tmp(ptmp);
	delete ptmp;
	return tmp;
	//问题解决但效率底下
	*/
	String tmp;
	tmp._pstr = new char[strlen(lstr._pstr) + strlen(rstr._pstr) + 1];
	strcpy(tmp._pstr, lstr._pstr);
	strcat(tmp._pstr, rstr._pstr);
	return tmp;
	//优化了但还是不能返回引用
}
ostream& operator<<(ostream& out, const String& str) {
	out << str._pstr;
	return out;
}
int main() {
	String str1("aaa");
	cout << str1 << endl;
	String str2(str1);
	cout << str2 << endl;
	String str3;
	str3 = str1;
	cout << str3 << endl;
	cout << str1.length() << endl;
	cout << str1[0] << endl;
	char cstr[1024] = { 0 };
	strcpy(cstr, str1.c_str());
	cout << cstr << endl;
	String str4("bbb");
	cout << str4 << endl;
	cout << (str1 < str4) << endl;
	cout << (str1 > str4) << endl;
	cout << (str1 == str4) << endl;
	return 0;
}