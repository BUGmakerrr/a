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
		//erase(it);	verify(it._ptr,_last);
		//insert(it,val);	verify(it._ptr,_last);
		verify(_last - 1, _last);

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
		iterator(T* p = nullptr, Vector<T, Alloc>* pVec = nullptr)
			:_ptr(p)
			,_pVec(pVec)
		{
			Iterator_Base* it = new Iterator_Base(this, _pVec->_head.next);
			_pVec->head.next = it;
		}
		bool operator!=(const iterator& it)const {
			//检查迭代器有效性
			if (_pVec == nullptr || _pVec != it._pVec) {
				throw"iterator incompatable!";//迭代器不相符
				//return false;
			}
			return _ptr != it._ptr;
		}
		void operator++() {
			if (_pVec == nullptr) {
				throw"iterator invalid!";//迭代器无效
			}
			++_ptr;
		}
		T& operator*() {
			if (_pVec == nullptr) {
				throw"iterator invalid!";//迭代器无效
			}
			return *_ptr;
		}


	private:
		T* _ptr;
		Vector<T, Alloc>* _pVec;//容器的地址
	};
	iterator begin() {
		return iterator(this,_first);
	}
	iterator end() {
		return iterator(this,_last);
	}
	
	//使无效迭代器失效
	void verify(T* first, T* last) {
		Iterator_Base* pre = &this->_head;
		Iterator_Base* it = this->_head.next;
		while (it != nullptr) {
			if (it->cur->_ptr >= first && it->cur->_ptr <= last) {
				it->cur->_pVec = nullptr;

				pre->next = it->next;
				delete it;
				it = pre->_next;
			}
			else {
				pre = it;
				it = it->next;
			}
		}
	}

	iterator insert(iterator it, T& val) {
		//与库中相比不考虑扩容，不考虑it._ptr合法性
		verify(it._ptr - 1, _last);
		T* p = _last;
		while (p > it._ptr) {
			_allocator.construct(p, *(p - 1));
			_allocator.destroy(p - 1);
			--p;
		}
		_allocator.construct(p, val);
		++_last;
		return(this, p);
	}

	iterator erase(iterator it) {
		verify(it._ptr - 1, _last);
		T* p = it._ptr;
		while(p<_last-1){
			_allocator.destroy(p);
			_allocator.construct(p, *(p + 1));
		}
		_allocator.destroy(p);
		--_last;
		return iterator(this, it._ptr);
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
	struct Iterator_Base {
		Iterator_Base(iterator* c, Iterator_Base* n)
			:cur(c)
			, next(n)
		{}
		iterator* cur;
		Iterator_Base* next;
	};
	Iterator_Base _head;
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
	Vector<int>vec(200);
	for (int i = 0; i < 20; ++i) {
		vec.push_back(rand() % 100);
	}
	auto it = vec.begin();
	for (; it != vec.end(); ++it) {
		cout << *it << endl;
		if (*it % 2 == 0) {
			auto why = *it + 1;
			it = vec.insert(it, why);
			++it;
		}
	}

#if 0
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
#endif
	return 0;
}