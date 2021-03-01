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
	//����ֵ���ò����Ŀ�������
	MyString(const MyString& str) {
		cout << "MyString(const MyString& str)" << endl;
		mptr = new char[strlen(str.mptr) + 1];
		strcpy(mptr, str.mptr);
	}
	//����ֵ���ò����Ŀ������죬ʹ����ʱ���󿽱�����ʱ���ô˺���
	MyString(MyString&& str) {
		cout << "MyString(MyString&& str)" << endl;
		mptr = str.mptr;
		str.mptr = nullptr;
	}
	//����ֵ���ò����ĸ�ֵ���غ���
	MyString& operator=(const MyString& str) {
		cout << "operator=(const MyString& str)" << endl;
		if (&str == this)return *this;
		delete[] mptr;
		mptr = new char[strlen(str.mptr) + 1];
		strcpy(mptr, str.mptr);
		return *this;
	}
	//����ֵ���ò����ĸ�ֵ���غ���
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
	T* allocate(size_t size) {//���𿪱��ڴ�
		return (T*)malloc(sizeof(T) * size);
	}
	void deallocate(void* p) {//�����ͷ��ڴ�
		free(p);
	}
	//void construct(T* p, const T& val) {
	//	new(p)T(val);
	//}
	//void construct(T* p, T&& val) {
	//	new(p)T(move(val));//ǿתΪ��ֵȥ��������
	//}
	template<typename Ty>
	void construct(T* p, Ty&& val) {
		new(p)T(forward<Ty>(val));
		}
	void destroy(T* p) {//�����������
		p->~T();//T��������ֱ�ӵ���������������
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
		for (T* p = _first; p != _last; ++p) {//������Ч�ڴ�
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
		for (T* p = _first; p != _last; ++p) {//������Ч�ڴ�
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
	T& operator[](int index) {//ֻ���ڴ������������������ṩ[]����
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
	//����ֵ���ò�����push_back
	void push_back(T&& val) {
		if (full())
			expand();
		//_allocator.construct(_last, val);//val��������ֵ����Ҫǿת����ֵ�����ÿռ��������Ĳ���Ϊ��ֵ���õ�construct
		_allocator.construct(_last, move(val));
		//move���ƶ����壬�õ���ֵ����
		_last++;
	}
	̫����*/
	template<typename Ty>
	void push_back(Ty&& val) {
		//������ֵstr����������ΪMyString& && val
		//������ʱ������ֵ����������ΪMyString&& val
		//�����۵���&+&&=&��&&+&&=&&
		if (full())
			expand();
		_allocator.construct(_last, forward<Ty>(val));
		//forward�����͵�����ת�����ܹ�ʶ����ֵ����ֵ���ͣ����ݲ�������ʱ�����ͷ�����Ӧ������
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