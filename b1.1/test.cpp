#include<iostream>
using namespace std;

#if 0
class Test {
public:
	Test(int data = 0) :ma(data) {
		cout << "Test(int)" << endl;
	}
	~Test() {
		cout << "~Test()" << endl;
	}
	Test(const Test& t) :ma(t.ma) {
		cout << "Test(const Test&)" << endl;
	}
	Test& operator=(const Test& t) {
		cout << "operator=" << endl;
		ma = t.ma;
		return *this;
	}
private:
	int ma;
};
int main() {
	Test t1;
	Test t2 = t1;
	Test t3 = Test(10);//��ʾ������ʱ���󣬵�ͬ��Test t3(20);
	t3 = t2;
	t3 = Test(15);//�˴���������ʱ������Ϊ����operator=(const Test& t)��Ҫ�������
	t3 = (Test)30;
	cout << endl;
	//Test* p = &Test(20);�������ʱ��������
	const Test& ref = Test(20);//�������ʱ��������
	return 0;
}
#endif
class Test {
public:
	Test(int a = 0, int b = 0)
		: ma(a)
		, mb(b) {
		cout << "Test(int)" << endl;
	}
	~Test() {
		cout << "~Test()" << endl;
	}
	Test(const Test& t)
		: ma(t.ma)
		, mb(t.mb) {
		cout << "Test(const Test&)" << endl;
	}
	Test& operator=(const Test& t) {
		cout << "operator=" << endl;
		ma = t.ma;
		mb = t.mb;
		return *this;
	}
private:
	int ma;
	int mb;
};
//�������������е�˳��
Test t1(10, 10);//1 19 ����
int main() {
	Test t2(20, 20);//3 16 ����
	Test t3 = t2;//4 16 ����
	static Test t4 = Test(30, 30);//5 ��̬������ʼ��ʱ���ǵ�һ�����е�����ʱ�� �Ż��󲻻�����ʱ���� 17 ��̬���������ݶ��ϣ��������������
	t2 = Test(40, 40);//6 ������ʱ����
	t2 = (Test)(50, 50);//(50, 50)Ϊ���ű��ʽ������ͬ���ʽ���һ��ֵ50 ��50����a��bΪĬ��ֵ0
	t2 = 60;//8 ��ʽ������ʱ����
	Test* p1 = new Test(70, 70);//9 ������ʱ����deleteʱ���� 
	Test* p2 = new Test[2];//10 �������飬�������ι��캯��
	//Test* p3 = &Test(80, 80);//11 ָ��ָ����ʱ����
	const Test& p4 = Test(90, 90);//12 ������ʱ���������������� 15����
	delete p1;//13 ��������
	delete[] p2;//14 ������������

}
Test t5(100, 100);//2 �ȳ�ʼ��ȫ�ֱ��� 18 ����