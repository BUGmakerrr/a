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
	Vector<T>(size_t size = 10) {
		//_first = new T[size];
		_first = _allocator.allocate(size);

		_last = _first;
		_end = _first + size;
	}
	~Vector<T>() {
		//delete[]_first;
		for (T* p = _first; p != _last; ++p) {//析构有效内存
			_allocator.destroy(p);
		}
		_allocator.deallocate(_first);

		_first = _last = _end = nullptr;
	}
	Vector<T>(const Vector<T>& rhs) {
		int size = rhs._end - rhs._first;
		//_first = new T[size];
		_first = _allocator.allocate(size);

		int len = rhs._last - rhs._first;

		for (int i = 0; i < len; ++i) {
			//_first[i] = rhs._first[i];
			_allocator.construct(_first + i,rhs._first[i]);
		}

		_last = _first + len;
		_end = _first + size;
	}
	Vector<T>& operator=(const Vector<T>& rhs) {
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

private:
	T* _first;
	T* _last;
	T* _end;

	Alloc _allocater;
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
};
int main() {
	//Vector<Test> vec1;//会生成10个构造函数和析构函数，new开辟空间的同时调用构造
	Test t1, t2, t3;
	Vector<Test> vec1;
	vec1.push_back(t1);
	vec1.push_back(t2);
	vec1.push_back(t3);
	vec1.pop_back();

	return 0;
}