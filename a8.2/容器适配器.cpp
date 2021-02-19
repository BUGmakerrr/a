#include<iostream>
#include<vector>
#include<string>
#include<deque>
#include<list>

#include<stack>//栈stack
#include<queue>//队列queue和优先级队列priority queue

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
//		return con.back();//查看栈顶返回deque末尾元素
//	}
//private:
//	Container con;
//};
int main() {
	priority_queue<int> pque;
	//按优先级出队，越大优先级越高
	for (int i = 0; i < 20; ++i) {
		pque.push(rand() % 100 + 1);
	}
	cout << pque.size() << endl;

	while (!pque.empty()) {
		cout << pque.top() << " ";//优先级最大的在顶部
		pque.pop();
	}
	cout << endl;
	cout << "-------------------------------------------------------------" << endl;

	queue<int> que;
	//先进先出，后进后出
	for (int i = 0; i < 20; ++i) {
		que.push(rand() % 100 + 1);
	}
	cout << que.size() << endl;
	
	while (!que.empty()) {
		cout << que.front() << " ";//队头
		que.pop();
	}
	cout << endl;
	cout << "-------------------------------------------------------------" << endl;
	stack<int> s1;
	//先进后出，后进先出
	for (int i = 0; i < 20; ++i) {
		s1.push(rand() % 100 + 1);
	}
	cout << s1.size() << endl;
	
	while (!s1.empty()) {
		cout << s1.top() << " ";//栈顶
		s1.pop();
	}
	cout << endl;
	return 0;
}