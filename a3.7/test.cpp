#include <iostream>
#include <typeinfo>
using namespace std;

class Test {
public:
	int ma;
	static int mb;
	void Func() {
		cout << "Test::Func" << endl;
	}
	static void static_Func() {
		cout << "Test::static_Func" << endl;
	}
};
int Test::mb;
int main() {
	Test t1;//ջ�ϵĶ���
	Test* t2 = new Test();//���ϵĶ���
#if 0
	//int* p = &Test::ma;"int Test::*" ���͵�ֵ�������ڳ�ʼ�� "int *" ���͵�ʵ��
	int Test::* p = &Test::ma;
	//*p = 10;������������
	t1.*p = 10;
	cout << t1.ma << endl;//10
	t2->*p = 20;
	cout << t2->ma << endl;//20

	int * q = &Test::mb;
	*q = 30;//�������ڶ���
	cout << Test::mb << endl;
	cout << typeid(p).name() << endl;//int Test::*
	cout << typeid(q).name() << endl;//int *
#endif

	//void *pFunc() = &Test::Func; һ�㺯��ָ��Ķ��巽ʽ"void (Test::*)()" ���͵�ֵ�������ڳ�ʼ�� "void *" ���͵�ʵ��
	void (Test::* p1Func)() = &Test::Func;
	(t1.*p1Func)();//ʹ�ö������
	(t2->*p1Func)();//ʹ�ö������
	void(*p2static_Func)() = &Test::static_Func;//����void*����
	(*p2static_Func)();
	//static��Աʹ�ò������ڶ���ֻ�����������������
	delete t2;
	return 0;
}