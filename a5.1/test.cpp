#include<iostream>
using namespace std;

//������
class CComplex {
public:
	CComplex(int r = 0, int i = 0)
		:mreal(r)
		, mimage(i)
	{}
	void show() {
		cout << "mreal=" << mreal << " mimage=" << mimage << endl;
	}
	CComplex operator+(const CComplex& src) {//����ֵ����������/ָ������Ϊcomp�������������ʱ����
		//CComplex comp;
		//comp.mreal = mreal + src.mreal;
		//comp.mimage = mimage + src.mimage;
		//return comp;
		//�����Ż���
		return CComplex(mreal + src.mreal, mimage + src.mimage);
	}
	/*
	CComplex operator++() {
		return CComplex(++mreal, ++mimage);
	}
	*/
	CComplex& operator++() {
		++mreal;
		++mimage;
		return *this;
	}
	CComplex operator++(int) {
		return CComplex(mreal++, mimage++);
	}
	void operator+=(const CComplex& src) {
		mreal += src.mreal;
		mimage += src.mimage;
	}
private:
	int mreal;//ʵ��
	int mimage;//����
	friend CComplex operator+(const CComplex& lhs, const CComplex& rhs);
	friend ostream& operator<<(ostream& out, const CComplex& src);
	friend istream& operator>>(istream& in, CComplex& src);
};
CComplex operator+(const CComplex& lhs, const CComplex& rhs) {
	return(CComplex(lhs.mreal + rhs.mreal, lhs.mimage + rhs.mimage));//���⺯���޷�����˽�г�Ա��������Ҫ����Ϊ��Ԫ����
}
ostream& operator<<(ostream& out, const CComplex& src) {
	out << "mreal=" << src.mreal << " mimage=" << src.mimage << endl;
	return out;
}
istream& operator>>(istream& in, CComplex& src) {
	in >> src.mreal >> src.mimage;
	return in;
}
int main() {
	CComplex comp1(10, 10);
	CComplex comp2(20, 20);
	CComplex comp3 = comp1 + comp2;
	comp3.show();

	CComplex comp4 = comp1 + 20;//��20�����β�src����intǿתΪCComplex���ͣ����������Ҵ�int������CComplex���캯�����൱����20������һ����ʱ����
	comp4.show();
	CComplex comp5 = 20 + comp1;//�޷����ó�Ա����������дһ��ȫ�ַ���Ӧ�Դ����
	//����������������ʱ������ö������������غ��������ȵ������Ա����������Ҳ����ͻ�ȥȫ����������
	comp5.show();

	comp4 = comp1++;//++ --��Ŀ�������Ϊ������ǰ�úͺ��ã�ǰ��Ϊoperator++()������operator++(int),int�����壬ֻ��Ϊ������
	comp5 = ++comp2;
	comp4.show();
	comp1.show();
	comp5.show();

	cout << comp5 << endl;//����������ߣ��޷�д����Ա����

	cin >> comp5;
	cout << comp5 << endl;
	return 0;
}