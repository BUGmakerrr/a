#include<iostream>
#include<vector>
#include<string>
#include<deque>
#include<list>

#include<stack>//ջstack
#include<queue>//����queue�����ȼ�����priority queue

using namespace std;

//template<typename T,typename Container=deque<T>>
//class Stack {
//public:
//	void push(const T& val) {
//		con.push_back(val);
//	}
//	void pop() {
//		con.pop_back;
//	}
//	T& top()const {
//		return con.back();//�鿴ջ������dequeĩβԪ��
//	}
//private:
//	Container con;
//};
int main() {
	priority_queue<int> pque;
	//�����ȼ����ӣ�Խ�����ȼ�Խ��
	for (int i = 0; i < 20; ++i) {
		pque.push(rand() % 100 + 1);
	}
	cout << pque.size() << endl;

	while (!pque.empty()) {
		cout << pque.top() << " ";//���ȼ������ڶ���
		pque.pop();
	}
	cout << endl;
	cout << "-------------------------------------------------------------" << endl;

	queue<int> que;
	//�Ƚ��ȳ���������
	for (int i = 0; i < 20; ++i) {
		que.push(rand() % 100 + 1);
	}
	cout << que.size() << endl;
	
	while (!que.empty()) {
		cout << que.front() << " ";//��ͷ
		que.pop();
	}
	cout << endl;
	cout << "-------------------------------------------------------------" << endl;
	stack<int> s1;
	//�Ƚ����������ȳ�
	for (int i = 0; i < 20; ++i) {
		s1.push(rand() % 100 + 1);
	}
	cout << s1.size() << endl;
	
	while (!s1.empty()) {
		cout << s1.top() << " ";//ջ��
		s1.pop();
	}
	cout << endl;
	return 0;
}