#include<iostream>
using namespace std;

template<typename T>
class Allocator {
public:
	T* allocate(size_t size) {//负责开辟内存
		return (T*)malloc(sizeof(T) * size);
	}
	void deallocate(void* p) {//负责释放内存
		free(p);
	}
	void construct(T* p, const T& val) {//负责对象构造
		new(p)T(val);//定位new，在*p拷贝构造val
	}
	void destroy(T* p) {//负责对象析构
		p->~T();//T是类名，直接调用它的析构函数
	}
};

template<typename T, typename Alloc = Allocator<T>>
class Vector {
public:
	Vector<T, Alloc>(size_t size = 10) {
		//_first = new T[size];
		_first = _allocator.allocate(size);

		_last = _first;
		_end = _first + size;
	}
	~Vector<T, Alloc>() {
		//delete[]_first;
		for (T* p = _first; p != _last; ++p) {//析构有效内存
			_allocator.destroy(p);
		}
		_allocator.deallocate(_first);

		_first = _last = _end = nullptr;
	}
	Vector<T, Alloc>(const Vector<T>& rhs) {
		int size = rhs._end - rhs._first;
		//_first = new T[size];
		_first = _allocator.allocate(size);

		int len = rhs._last - rhs._first;

		for (int i = 0; i < len; ++i) {
			//_first[i] = rhs._first[i];
			_allocator.construct(_first + i, rhs._first[i]);
		}

		_last = _first + len;
		_end = _first + size;
	}
	Vector<T, Alloc>& operator=(const Vector<T>& rhs) {
		if (this == &rhs)
			return *this;
		//delete[]_first;
		for (T* p = _first; p != _last; ++p) {//析构有效内存
			_allocator.destroy(p);
		}
		_allocator.deallocate(_first);

		int size = rhs._end - rhs._first;
		//_first = new T[size];
		_first = _allocator.allocate(size);

		int len = rhs._last - rhs._first;
		for (int i = 0; i < len; ++i) {
			//_first[i] = rhs._first[i];
			_allocator.construct(_first + i, rhs._first[i]);
		}
		_last = _first + len;
		_end = _first + size;

		return *this;
	}
	void push_back(const T& val) {
		if (full())
			expand();
		//*_last++ = val;
		_allocator.construct(_last, val);
		_last++;
	}
	void pop_back() {
		if (empty())
			return;
		//--_last;
		--_last;
		_allocator.destroy(_last);
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
	T& operator[](int index) {//只有内存是连续的容器才能提供[]重载
		if (index < 0 || index >= size())
			throw"OutOfRangeException";
		return _first[index];
	}

	class iterator {
	public:
		iterator(T* p = nullptr)
			:_p(p)
		{}
		bool operator!=(const iterator& it)const {
			return _p != it._p;
		}
		void operator++() {
			++_p;
		}
		T& operator*() {
			return *_p;
		}
	private:
		T* _p;
	};
	iterator begin() {
		return iterator(_first);
	}
	iterator end() {
		return iterator(_last);
	}
private:
	T* _first;
	T* _last;
	T* _end;

	Alloc _allocator;
	void expand() {
		int size = _end - _first;
		//T* ptmp = new T[size * 2];
		T* ptmp = _allocator.allocate(size * 2);
		for (int i = 0; i < size; ++i) {
			//ptmp[i]=_first[i];
			_allocator.construct(ptmp + i, _first[i]);
		}
		//delete[]_first;
		for (T* p = _first; p != _last; ++p) {
			_allocator.destroy(p);
		}
		_allocator.deallocate(_first);

		_first = ptmp;
		_last = _first + size;
		_end = _first + size * 2;
	}
};
class Test {
public:
	Test() {
		cout << "Test()" << endl;
	}
	~Test() {
		cout << "~Test()" << endl;
	}
	Test(const Test& test) {
		cout << "Test(const Test& test)" << endl;
	}
private:
	friend ostream& operator<<(ostream& out, Test& t);
};
ostream& operator<<(ostream& out, Test& t) {
	out << "coutTest";
	cout << endl;
	return out;
}
int main() {
	Test t1, t2, t3;
	Vector<Test> vec1;
	vec1.push_back(t1);
	vec1.push_back(t2);
	vec1.push_back(t3);

	Vector<Test>::iterator it1;
	for (it1 = vec1.begin(); it1 != vec1.end(); ++it1) {
		cout << *it1 << endl;
	}
	cout << "------------------------" << endl;
	Vector<int> vec2;
	for (int i = 0; i < 10; ++i) {
		vec2.push_back(rand() % 100);
	}
	Vector<int>::iterator it2;
	for (it2 = vec2.begin(); it2 != vec2.end(); ++it2) {
		cout << *it2 << endl;
	}
	cout << "---------------" << endl;
	for (int val : vec2) {
		cout << val << endl;
	}
	cout << "---------------" << endl;
	//效果相同，只有内存联系的容器可以使用
	int size = vec2.size();
	for (int i = 0; i < 10; ++i) {
		cout << vec2[i] << endl;
	}

	return 0;
}