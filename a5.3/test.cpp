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

	//给String类型提供迭代器实现
	class iterator {
	public:
		iterator(char* p = nullptr)
			:_p(p)
		{}
		bool operator!=(const iterator& it) {
			return _p != it._p;
		}
		void operator++() {
			++_p;
		}
		char& operator*() {
			return *_p;
		}
	private:
		char* _p;
	};
	iterator begin() {
		return iterator(_pstr);
	}
	iterator end() {
		return iterator(_pstr + length());
	}
private:
	char* _pstr;
	friend ostream& operator<<(ostream& out, const String& str);
	friend String operator+(const String& lstr, const String& rstr);
};
String operator+(const String& lstr, const String& rstr) {
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
	String str1("COYS!");
	for (String::iterator it = str1.begin(); it != str1.end(); ++it) {//it的类型在C++11下也可写为auto
		cout << *it << " ";
	}
	cout << endl;
	for (char ch : str1) {//C++11
		cout << ch << " ";
	}
	cout << endl;
	return 0;
}