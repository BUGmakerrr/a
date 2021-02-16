#include<iostream>
#include<string>
using namespace std;

//拥有纯虚函数的类叫做抽象类
//抽象类不能实例化对象，只能定义指针/引用变量
class Animal {
public:
	Animal(string name) :_name(name) {}
	//纯虚函数
	//纯虚函数是一种特殊的虚函数，在许多情况下，在基类中不能对虚函数给出有意义的实现，而把它声明为纯虚函数，它的实现留给该基类的派生类去做
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