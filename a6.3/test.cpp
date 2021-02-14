#include<iostream>
using namespace std;

class Base {
public:
	Base(int data) 
	:ma(data)
	{}
	void show() {
		cout << "Base::show()" << endl;
	}
	void show(int) {
		cout << "Base::show(int)" << endl;
	}
protected:
	int ma;
};
class Derive :public Base {
public:
	Derive(int data)
		:Base(data)
		,mb(data)
	{}
	void show() {
		cout << "Derive::show()" << endl;
	}
protected:
	int mb;
};
#if 0
int main() {
	Derive d(10);
	d.show();
	d.show(10);
	return 0;
}
#endif
int main() {
	Base b(20);
	Derive d(20);
	b = d;//�����������Ը�������������ʹ������ϵ�ת��
	//d = b;������󲻿��Ը������������

	Base* pb = &d;//����ָ�����ָ�����������ֻ��ͨ�������÷����������дӻ���̳еĲ���

	pb->show();
	pb->show(10);
	//���õĶ��ǻ����еĳ�Ա

	((Derive*)pb)->show();//ǿת����Է����������Ա
	//((Derive*)pb)->show(10);

	//Derive* pd = &b;������ָ�벻����ָ�������󣬴����ڴ�Ƿ�����
	Derive* pd = (Derive*)&b;//Σ�գ������ڴ�Ƿ�����
	pd->show();//�����������Ա��ʵ���ڴ��в�û�����������
	//pd->show(10);
	
	return 0;
}