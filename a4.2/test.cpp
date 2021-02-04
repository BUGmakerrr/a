#include<iostream>
using namespace std;

/*�����Ͳ���ģ��
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

//ģ��ʵ��˳��ջ
template<typename T>//���Դ�Ĭ�����Ͳ���template<typename T = int> ����������ʱ����ʡ��int��SeqStack<> s1;
class SeqStack {//ģ�����Ӳ����б����������SeqStackֻ��ģ����
public://���캯�������������ĺ���������ʡ�Բ����б�<T>
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
		//������memcopy��������ΪT������������
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
	T top()const {//ֻ�������ӿڽ���д�ɳ���������ͨ���󳣶����ܵ���
		if (empty())
			throw"empty!";//���쳣�����ڲ�֪������ֵ���ͣ�����ǿյ��޷����ֵ�����쳣��ɴ������߼�����
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
	//˳��ջ�ײ����鰴������ʽ����
	void expand() {
		T* ptmp = new T[_size *= 2];
		for (int i = 0; i < _top; ++i) {
			ptmp[i] = _pstack[i];
		}
		delete[]_pstack;
		_pstack = ptmp;
	}
};
/*�����������ʵ��
template<typename T>����һ��ģ�������ֻ�ܴ���һ��{��������һ��}��������Ҫ���¶���һ��
void SeqStack<T>::push(const T& val) {��Ҫע��SeqStack<T>��������������
	if (full())
		expand();
	_pstack[_top++] = val;
}*/
int main() {
	SeqStack<int> s1;//��ʵ������һ���������͵�ģ����class SeqStck<int>{};�����Ҹ�����ֻ��Ŀǰ�õ��Ĺ��캯������������
	s1.push(11);
	s1.pop();//�ù���ʵ������push()��pop()
	//��Ϊ��ģ���ѡ����ʵ����
	return 0;
}