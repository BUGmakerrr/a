#include<iostream>
#include<string>
using namespace std;

//ӵ�д��麯���������������
//�����಻��ʵ��������ֻ�ܶ���ָ��/���ñ���
class Animal {
public:
	Animal(string name) :_name(name) {}
	//���麯��
	//���麯����һ��������麯�������������£��ڻ����в��ܶ��麯�������������ʵ�֣�����������Ϊ���麯��������ʵ�������û����������ȥ��
	virtual void bark() = 0;
protected:
	string _name;
};

class Cat :public Animal {
public:
	Cat(string name) :Animal(name) {}
	void bark() {
		cout << _name << ":meow" << endl;
	}
};
class Mouse :public Animal {
public:
	Mouse(string name) :Animal(name) {}
	void bark() {
		cout << _name << ":squeek" << endl;
	}
};
class Dog :public Animal {
public:
	Dog(string name) :Animal(name) {}
	void bark() {
		cout << _name << ":woof" << endl;
	}
};

void bark(Animal& p) {
	p.bark();
}

class Car {
public:
	Car(string name, double oil) :_name(name), _leftOil(oil) {}
	double getLeftMiles() {
		return getMilesPerGallon() * _leftOil;
	}
	string getName() {
		return _name;
	}
protected:
	string _name;
	double _leftOil;
	virtual double getMilesPerGallon() = 0;
};
class Pontiac :public Car {
public:
	Pontiac(string name, double oil)
		:Car(name, oil)
	{}
	double getMilesPerGallon() {
		return 20.0;
	}
}; 
class Porsche :public Car {
public:
	Porsche(string name, double oil)
		:Car(name, oil)
	{}
	double getMilesPerGallon() {
		return 22.0;
	}
};
class BMW :public Car {
public:
	BMW(string name, double oil)
		:Car(name, oil)
	{}
	double getMilesPerGallon() {
		return 18.0;
	}
};
void showLeftMiles(Car& car) {
	cout << car.getName() << ":" << car.getLeftMiles() << "KM" << endl;
}
int main() {
	Pontiac pontiac("JAZZ", 20.0);
	Porsche porsche("CLIFF", 20.0);
	BMW bmw("MA", 20.0);
	showLeftMiles(pontiac);
	showLeftMiles(porsche);
	showLeftMiles(bmw);
	return 0;
}