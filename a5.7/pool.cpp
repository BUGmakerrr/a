#include<iostream>
using namespace std;

template<typename T>
class Queue {
public:
	Queue() {
		_front = _rear = new QueueItem();
	}
	~Queue() {
		QueueItem* cur = _front;
		while (cur != nullptr) {
			_front = _front->_next;
			delete cur;
			cur = _front;
		}
	}
	void push(const T& val) {//尾插
		QueueItem* item = new QueueItem(val);
		_rear->_next = item;
		_rear = item;
	}
	void pop() {//头删
		QueueItem* first = _front->_next;
		_front->_next = first->_next;
		if (_front->_next == nullptr) {
			_rear = _front;//?_rear
		}
		delete first;
	}
	T front()const {
		cout << _front->_next->_data << endl;
	}
	bool empty()const { return _front == _rear; }
private:
	struct QueueItem {//队列节点
		QueueItem(T data=T())//零构造
			:_data(data)
			,_next(nullptr)
		{}

		//给QueueItem提供自定义内存管理
		//new和delete的重载函数会被自动处理成static（不依赖于对象）
		void* operator new(size_t size) {
			if (_itemPool == nullptr) {
				_itemPool = (QueueItem*)new char[POOL_ITEM_SIZE * sizeof(QueueItem)];//直接newQueueItem又会调用到此函数，此处用字节开辟
				QueueItem* p = _itemPool;
				for (; p < _itemPool + POOL_ITEM_SIZE - 1; ++p) {
					p->_next = p + 1;
				}
				p->_next = nullptr;
			}
			QueueItem* p = _itemPool;
			_itemPool = _itemPool->_next;
			return p;
		}
		void operator delete(void* ptr) {
			QueueItem* p = (QueueItem*)ptr;
			p->_next = _itemPool;
			_itemPool = p;
		}//还未实现释放new的内存
		T _data;
		QueueItem* _next;

		static QueueItem* _itemPool;//对象池起始地址，空闲节点首节点地址
		static const int POOL_ITEM_SIZE;//对象池节点数量
	};
	QueueItem* _front;//指向头节点
	QueueItem* _rear;//指向队尾
};

template<typename T>
typename Queue<T>::QueueItem* Queue<T>::QueueItem::_itemPool = nullptr;
/*运行到此处还没有编译到类（还未实例化对象），编译器不知道QueueItem是一个自定义类型，无法确定后面的“*”是指针还是乘法
加上typename意义为告诉编译器QueueItem是一个自定义类型*/


template<typename T>
const int Queue<T>::QueueItem::POOL_ITEM_SIZE = 10000;

int main() {
	Queue<int> que;
	for (int i = 0; i < 100000; ++i) {
		que.push(i);
		que.pop();
	}
	cout << que.empty() << endl;
	return 0;
}