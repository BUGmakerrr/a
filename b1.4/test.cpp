#include<iostream>

using namespace std;

class MyString {
public:
	MyString(const char* str = nullptr) {
		cout << "MyString(const char*)" << endl;
		if (str != nullptr) {
			mptr = new char[strlen(str) + 1];
			strcpy(mptr, str);
		}
		else {
			mptr = new char[1];
			*mptr = '0';
		}
	}
	~MyString() {
		cout << "~MyString(const char*)" << endl;
		delete mptr;
		mptr = nullptr;
	}
	//带左值引用参数的拷贝构造
	MyString(const MyString& str) {
		cout << "MyString(const MyString& str)" << endl;
		mptr = new char[strlen(str.mptr) + 1];
		strcpy(mptr, str.mptr);
	}
	//带右值引用参数的拷贝构造，使用临时对象拷贝构造时调用此函数
	MyString(MyString&& str) {
		cout << "MyString(MyString&& str)" << endl;
		mptr = str.mptr;
		str.mptr = nullptr;
	}
	//带左值引用参数的赋值重载函数
	MyString& operator=(const MyString& str) {
		cout << "operator=(const MyString& str)" << endl;
		if (&str == this)return *this;
		delete[] mptr;
		mptr = new char[strlen(str.mptr) + 1];
		strcpy(mptr, str.mptr);
		return *this;
	}
	//带右值引用参数的赋值重载函数
	MyString& operator=(MyString&& str) {
		cout << "operator=(MyString&& str)" << endl;
		if (&str == this)return *this;
		delete[] mptr;
		mptr = str.mptr;
		str.mptr = nullptr;
		return *this;
	}
	const char* c_str()const { return mptr; }
private:
	char* mptr;
	friend MyString operator+(const MyString& lhs, const MyString& rhs);
};
MyString operator+(const MyString& lhs, const MyString& rhs) {
	//char* ptmp = new char[strlen(lhs.mptr) + strlen(rhs.mptr) + 1];
	MyString tmpStr;
	tmpStr.mptr = new char[strlen(lhs.mptr) + strlen(rhs.mptr) + 1];
	strcpy(tmpStr.mptr, lhs.mptr);
	strcat(tmpStr.mptr, rhs.mptr);

	//MyString tmpStr(ptmp);
	//delete[]ptmp;
	return tmpStr;//调用了右值引用拷贝构造
	/*return MyString(ptmp);*/
}
MyString getString(const MyString& str) {
	const char* pstr = str.c_str();
	MyString tmpstr(pstr);
	return tmpstr;
}
int main() {
	MyString str1("aaaa");
	MyString str2;

	MyString str3 = str1 + str2;
	//cout << str3 << endl;
	//str2 = getString(str1);
	//cout << str2.c_str() << endl;
	return 0;
}