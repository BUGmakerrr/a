#include<iostream>
using namespace std;

class Base {
public:
	Base(int data = 20)
		:ma(data)
	{
		cout << "Base()" << endl;
	}
	virtual void show() {
		cout << "call Base::show()" << endl;
	}
protected:
	int ma;
};
class Derive :public Base {
public:
	Derive(int data = 20)
		:Base(data)
		, mb(data)
	{
		cout << "Derive()" << endl;
	}
	void show() {
		cout << "call Derive::show()" << endl;
	}
protected:
	int mb;
};
int main() {
	Base b;
	Derive d;

	//�ö���������麯���ǲ��ᷢ����̬�󶨵�
	b.show();//��̬��
	d.show();//��̬��

	//ָ������õ����麯�����Ƕ�̬��
	Base* pb1 = &b;
	pb1->show();//��̬��
	Base* pb2 = &d;
	pb2->show();//��̬��

	Base& rb1 = b;
	rb1.show();//��̬��
	Base& rb2 = d;
	rb2.show();//��̬��

	Derive* pd1 = &d;
	pd1->show();//��̬��
	Derive& rd = d;
	rd.show();//��̬��

	Derive* pd2 = (Derive*)&b;
	pd2->show();//�Ƕ�̬�󶨣�����pd2�����õõ�b������vfptrָ�����Base��vftable�����б�����ǻ�����麯����ַ
	//������һ���Ƕ�̬�󶨣����Ե��õ��ǻ����麯��

	return 0;
}