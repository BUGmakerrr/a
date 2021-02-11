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
	void push(const T& val) {//β��
		QueueItem* item = new QueueItem(val);
		_rear->_next = item;
		_rear = item;
	}
	void pop() {//ͷɾ
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
	struct QueueItem {//���нڵ�
		QueueItem(T data=T())//�㹹��
			:_data(data)
			,_next(nullptr)
		{}

		//��QueueItem�ṩ�Զ����ڴ����
		//new��delete�����غ����ᱻ�Զ������static���������ڶ���
		void* operator new(size_t size) {
			if (_itemPool == nullptr) {
				_itemPool = (QueueItem*)new char[POOL_ITEM_SIZE * sizeof(QueueItem)];//ֱ��newQueueItem�ֻ���õ��˺������˴����ֽڿ���
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
		}//��δʵ���ͷ�new���ڴ�
		T _data;
		QueueItem* _next;

		static QueueItem* _itemPool;//�������ʼ��ַ�����нڵ��׽ڵ��ַ
		static const int POOL_ITEM_SIZE;//����ؽڵ�����
	};
	QueueItem* _front;//ָ��ͷ�ڵ�
	QueueItem* _rear;//ָ���β
};

template<typename T>
typename Queue<T>::QueueItem* Queue<T>::QueueItem::_itemPool = nullptr;
/*���е��˴���û�б��뵽�ࣨ��δʵ�������󣩣���������֪��QueueItem��һ���Զ������ͣ��޷�ȷ������ġ�*����ָ�뻹�ǳ˷�
����typename����Ϊ���߱�����QueueItem��һ���Զ�������*/


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