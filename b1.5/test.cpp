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
};

template<typename T>
class Allocator {
public:
	T* allocate(size_t size) {//负责开辟内存
		return (T*)malloc(sizeof(T) * size);
	}
	void deallocate(void* p) {//负责释放内存
		free(p);
	}
	//void construct(T* p, const T& val) {
	//	new(p)T(val);
	//}
	//void construct(T* p, T&& val) {
	//	new(p)T(move(val));//强转为右值去拷贝构造
	//}
	template<typename Ty>
	void construct(T* p, Ty&& val) {
		new(p)T(forward<Ty>(val));
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

	/*
	void push_back(const T& val) {
		if (full())
			expand();
		_allocator.construct(_last, val);
		_last++;
	}
	//带右值引用参数的push_back
	void push_back(T&& val) {
		if (full())
			expand();
		//_allocator.construct(_last, val);//val本身是左值，需要强转成右值来调用空间配置器的参数为右值引用的construct
		_allocator.construct(_last, move(val));
		//move：移动语义，得到右值类型
		_last++;
	}
	太复杂*/
	template<typename Ty>
	void push_back(Ty&& val) {
		//传入左值str的类型推演为MyString& && val
		//传入临时变量右值的类型推演为MyString&& val
		//引用折叠：&+&&=&，&&+&&=&&
		if (full())
			expand();
		_allocator.construct(_last, forward<Ty>(val));
		//forward：类型的完美转发，能够识别左值和右值类型，根据参数定义时的类型返回相应的类型
		_last++;
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

int main() {
	MyString str("aaa");
	Vector<MyString> vec;
	cout << "-------------------------------------------" << endl;
	vec.push_back(str);
	vec.push_back(MyString("bbb"));
	cout << "-------------------------------------------" << endl;
	return 0;
}