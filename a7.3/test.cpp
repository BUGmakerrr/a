#include<iostream>
using namespace std;

class Base {
public:
	virtual void func() = 0;
};
class Derive1 :public Base {
public:
	void func() {
		cout << "call Derive1::func()" << endl;
	}
};
class Derive2 :public Base {
public:
	void func() {
		cout << "call Derive2::func()" << endl;
	}
	void D2func() {
		cout << "call Derive2::D2func()" << endl;
	}
};
void showFunc(Base* p) {
	//dynamic_cast����p�Ƿ�ָ��һ��Derive2���Ͷ�������ǣ����ظ�Derive2�����ַ��������ǣ�����nullptr
	//static_cast�Ǿ�̬ת�����鿴���Ǳ���ʱ�ڵ����͡�dynamic_cast��ȥRTTI�в鿴����ʱ�ڵ�����
	Derive2* pd2 = dynamic_cast<Derive2*>(p);
	if (pd2 == nullptr) {
		pd2->func();
	}
	else {
		pd2->D2func();
	}
}
int main() {
	Derive1 d1;
	Derive2 d2;
	showFunc(&d1);
	showFunc(&d2);

#if 0
	int* p1 = nullptr;
	double* p2 = reinterpret_cast<double*>(p1);
	//֧��ת�������ܲ���ȫ
#endif
#if 0
	int a = 10;
	char b = static_cast<char>(a); //������������ת���ɵ�����
	cout << typeid(b).name() << endl << b << endl;

	/*int* p1 = nullptr;
	short* p2 = static_cast<short*>(p1);������֧�����������������ת����������ֻת����Ϊ����ϵ������*/
#endif
#if 0
	//const_cast��ȥ���������Ե�����ת��
	const int a = 10;
	int* p1 = (int*)&a;
	int* p2 = const_cast<int*>(&a);//�൱��һ��ģ�壬������������ת���ɵ�����
	//���ַ�ʽ�����Ļ��ָ����ȫ��ͬ
	//���Ǵ�������ͻ�ָ��������ԭ���Ͳ������const_cast�ᱨ����ǿת��û������
	//int b = const_cast<int>a;����const_cast �е����ͱ�����ָ�롢���û�ָ��������ͳ�Ա��ָ��
#endif
	return 0;
}