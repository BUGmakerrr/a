#include<iostream>
using namespace std;

class Base {
public:
	Base(int data)
		:ma(data)
	{}
	//�麯��
	virtual void show() {
		cout << "Base::show()" << endl;
	}
	virtual void show(int) {
		cout << "Base::show(int)" << endl;
	}
protected:
	int ma;
};
class Derive :public Base {
public:
	Derive(int data)
		:Base(data)
		, mb(data)
	{}
	void show() {
		cout << "Derive::show()" << endl;
	}
protected:
	int mb;
};
int main() {
	Derive d(50);
	Base* pb = &d;
	pb->show();//call        Base::show (0FF1037h)
	pb->show(5);//call        Base::show (0FF12F3h)
	//û���麯�����Ǿ�̬�󶨣�����ʱ�ھ�ȷ���õ��ú���

	cout << sizeof(Base) << endl;
	cout << sizeof(Derive) << endl;
	cout << typeid(pb).name() << endl;
	cout << typeid(*pb).name() << endl;
	
	return 0;
}