#include<iostream>
using namespace std;

class Base {
public:
	Base() {
		/*
		���ú���ʱ����Ϊ��������ջ֡
		Ϊ���캯��������ջ֡�Ժ�����������麯�������vftable��ַ������ǰvfptr
		*/
		cout << "call Base()" << endl;
		clear();
	}
	void clear() {
		memset(this, 0, sizeof(*this));//�������ڴ����
	}
	virtual void show() {
		cout << "call Base::show()" << endl;
	}
};
class Derive :public Base {
public:
	Derive() {
		//Ϊ���캯��������ջ֡�Ժ󣬰�vftable��ַ������ǰvfptr
		cout << "call Derive()" << endl;
	}
protected:
	virtual void show() {
		cout << "call Derive::show()" << endl;
	}
};
int main() {
	Base* pb1 = new Base();
	//pb1->show();//����
	//���û��๹�죬vftable��ַ������ǰvfptr��vfptr����Ϊ0���޷��ҵ��麯��

	Base* pb2 = new Derive();
	pb2->show();
	//�ȵ���Base���죬vftable��ַ������ǰvfptr��vfptr����Ϊ0
	//�ٵ���Derive���죬vftable��ַ�ٸ�����ǰvfptr

	delete pb1;
	delete pb2;

	return 0;
}
#if 0
class Base {
public:
	virtual void show() {
		cout << "call Base::show()" << endl;
	}
};
class Derive :public Base {
private:
	void show() {
		cout << "call Derive::show()" << endl;
	}
};
int main() {
	Base* p = new Derive();
	p->show();//call Derive::show()
	//��Ȼ���Ե�����������˽�е��麯��
	//��Ϊ���տ��Ե��õ�Derive::show()��������ʱ�ڲ�ȷ����
	//��Ա�ķ���Ȩ���ǲ���public���ڱ���ʱ�ھ�ȷ����
	delete p;
	return 0;
}
#endif
#if 0
class Base {
public:
	virtual void show(int i = 10) {
		cout << "call Base::show(i) : " << i << endl;
	}
};
class Derive :public Base {
public:
	void show(int i = 20) {
		cout << "call Derive::show(i) : " << i << endl;
	}
};
int main() {
	Derive d;
	Base* pb = &d;
	pb->show();//call Derive::show(i) : 10
	//�������麯�������˻����麯��������ʹ���˻����麯����Ĭ��ֵ
	/*
	�ڱ���ʱ��
	��ʱ��δ������̬�󶨣�������ֻ�ܵõ������麯��
	push 0Ah �Ƚ������麯��Ĭ��ֵѹջ
	����ʱ��
	move eax,dword ptr[p] ��ǰ�ĸ��ֽڼ�vfptr����Ĵ���
	move ecx,dword ptr[eax] ��vfptr���麯����ַ����Ĵ���
	call ecx
	*/
	return 0;
}
#endif