#include<iostream>
using namespace std;

/*非类型参数模板
template<typename T,int SIZE>
void sort(T* arr) {
	for (int i = 0; i < SIZE - 1; ++i) {
		for (int j = 0; j < SIZE - 1 - i; ++j) {
			if (arr[j] > arr[j + 1]) {
				int tmp = arr[j];
				arr[j + 1] = tmp;
			}
		}
	}
}
int main() {
	int arr[] = { 1,4,235,64,23,7,5 };
	const int size = sizeof(arr) / sizeof(arr[0]);
	sort<int, size>(arr);
	for (int val : arr) {
		cout << val << " ";
	}
	cout << endl;
	return 0;
}
*/

//模板实现顺序栈
template<typename T>//可以带默认类型参数template<typename T = int> 主函数调用时可以省略int，SeqStack<> s1;
class SeqStack {//模板名加参数列表才是类名，SeqStack只是模板名
public://构造函数和析构函数的函数名可以省略参数列表<T>
	SeqStack<T>(int size = 20)
		: _pstack(new T[size])
		,_top(0)
		,_size(size)
	{}
	~SeqStack<T>() {
		delete[]_pstack;
		_pstack = nullptr;
	}
	SeqStack<T>(const SeqStack<T>& stack) 
		:_top(stack._top)
		,_size(stack._size)
	{
		_pstack = new T[_size];
		//不能用memcopy拷贝，因为T可能是类类型
		for (int i = 0; i < _top; ++i) {
			_pstack[i] = stack._pstack[i];
		}
	}
	SeqStack<T>& operator=(const SeqStack<T>& stack) {
		if (this = &stack)
			return *this;		
		delete[]_pstack;
		_pstack = new T[stack._size];
		_top = stack._top;
		_size = stack._size;
		for (int i = 0; i < _top; ++i) {
			_pstack[i] = stack._pstack[i];
		}
		return *this;
	}
	void push(const T& val) {
		if (full())
			expand();
		_pstack[_top++] = val;
	}
	void pop() {
		if (empty())
			return;
		--_top;
	}
	T top()const {//只读操作接口建议写成常方法，普通对象常对象都能调用
		if (empty())
			throw"empty!";//抛异常，由于不知道返回值类型，如果是空的无法填返回值。抛异常便可代表函数逻辑结束
		return _pstack[_top - 1];
	}
	bool full()const {
		return _top == _size;
	}
	bool empty()const {
		return _top == 0;
	}
private:
	T* _pstack;
	int _top;
	int _size;
	//顺序栈底层数组按二倍方式扩容
	void expand() {
		T* ptmp = new T[_size *= 2];
		for (int i = 0; i < _top; ++i) {
			ptmp[i] = _pstack[i];
		}
		delete[]_pstack;
		_pstack = ptmp;
	}
};
/*如果想在类外实现
template<typename T>定义一次模板参数，只能从下一个{持续到下一个}，所以需要重新定义一次
void SeqStack<T>::push(const T& val) {需要注意SeqStack<T>才是完整函数名
	if (full())
		expand();
	_pstack[_top++] = val;
}*/
int main() {
	SeqStack<int> s1;//会实例化出一个处理整型的模板类class SeqStck<int>{};，并且该类中只有目前用到的构造函数和析构函数
	s1.push(11);
	s1.pop();//用过才实例化出push()和pop()
	//称为类模板的选择性实例化
	return 0;
}