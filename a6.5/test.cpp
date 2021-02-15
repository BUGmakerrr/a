#include<iostream>
using namespace std;

class Base {
public:
	Base(int data)
		:ma(data)
	{
		cout << "Base()" << endl;
	}
	virtual ~Base() {
		cout << "~Base()" << endl;
	}
	void show1() {
		cout << "call Base::show()" << endl;
	}
	virtual void show2() {
		cout << "call Base::show()" << endl;
	}
protected:
	int ma;
};
class Derive :public Base {
public:
	Derive(int data)
		:Base(data)
		, mb(data)
	{
		cout << "Derive()" << endl;
	}
	~Derive() {
		cout << "Derive()" << endl;
	}
protected:
	int mb;
};
int main() {
	Base* pb = new Derive(20);
	pb->show1();//��̬��
	pb->show2();//��̬��
	delete pb;//��ӡ�������������������û�б����ã�
	/*pb->~Base();����������������ͨ���������Խ����˾�̬��
	call Base::~Base()
	*/

	/*��������������дΪ�麯�������������������Զ���Ϊ�麯��
	������ͻ��������������Ϊͬ�����������������������Ḳ�ǻ������������������ͷ����������ڴ���ǻ���ȥ�ͷŻ����ڴ�
	*/

	/*Derive d(20);
	Base* pb = &d;
	pb->show();*/

	return 0;
}