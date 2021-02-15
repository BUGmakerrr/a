#include<iostream>
#include<string>
using namespace std;

class Animal {
public:
	Animal(string name):_name(name){}
	virtual void bark() = 0;
protected:
	string _name;
};

class Cat :public Animal {
public:
	Cat(string name):Animal(name){}
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

//通过引用的动态绑定
//下面的bark API接口无法做到软件设计要求的“开-闭”原则、高内聚低耦合
//“开-闭”原则：对修改关闭，对扩展开发。比如再增加或减少Animal类时也不用删掉bark API接口
/*
void bark(Cat& cat) {
	cat.bark();
}
void bark(Mouse& mouse) {
	mouse.bark();
}
void bark(Dog& dog) {
	dog.bark();
}
*/

//多态
//做到了低耦合，不会随派生类改变而改变
void bark(Animal& p) {
	p.bark();
}

int main() {
	Cat cat("Tom");
	Mouse mouse("Jerry");
	Dog dog("Spike");
	bark(cat);
	bark(mouse);
	bark(dog);
	return 0;
}