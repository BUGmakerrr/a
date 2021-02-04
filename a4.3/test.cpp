#include<iostream>
using namespace std;

template <typename T>
class vector {
public:
	vector<T>(int size = 10) {
		_first = new T[size];
		_last = _first;
		_end = _first + size;
	}
	~vector<T>() {
		delete[]_first;
		_last = _end = nullptr;
	}
	vector<T>(const vector<T>& rhs) {
		int size = rhs._end - rhs._first;
		_first = new T[size];
		int len = rhs._last - rhs._first;
		for (int i = 0; i < len; ++i) {
			_first[i] = rhs._first[i];
		}
		_last = _first + len;
		_end = _first + size;
	}
	vector<T>& operator=(const vector<T>& rhs) {
		if (this == &rhs)
			return *this;
		delete[]_first;

		int size = rhs._end - rhs._first;
		_first = new T[size];
		int len = rhs._last - rhs._first;
		for (int i = 0; i < len; ++i) {
			_first[i] = rhs._first[i];
		}
		_last = _first + len;
		_end = _first + size;

		return *this;
	}
	void push_back(const T& val) {
		if (full())
			expand();
		*_last++ = val;
	}
	void pop_back() {
		if (empty())
			return;
		--_last;
	}
	T back()const {
		return *(_last - 1);
	}
	bool full()const {
		return _last == _end;
	}
	bool empty()const {
		return _first == _last;
	}
	int size()const {
		return _last - _first;
	}

private:
	/*
	T* _pvec;
	int _cur;//当前有效元素个数
	int _size;
	*/

	T* _first;//指向数组起始位置
	T* _last;//指向最后一个有效元素的后继位置
	T* _end;//指向数组总空间的后继位置

	void expand() {
		int size = _end - _first;
		T* ptmp = new T[size * 2];
		for (int i = 0; i < size; ++i) {
			ptmp[i] = _first[i];
		}
		delete[]_first;
		_first = ptmp;
		_last = _first + size;
		_end = _first + size * 2;
	}
};
int main() {
	vector<int> vec1;
	for (int i = 0; i < 20; ++i) {
		vec1.push_back(rand() % 100);
	}
	while (!vec1.empty()) {
		cout << vec1.back()<<" ";
		vec1.pop_back();
	}
	cout << endl;
	return 0;
}