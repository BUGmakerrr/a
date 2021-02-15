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

//ͨ�����õĶ�̬��
//�����bark API�ӿ��޷�����������Ҫ��ġ���-�ա�ԭ�򡢸��ھ۵����
//����-�ա�ԭ�򣺶��޸Ĺرգ�����չ���������������ӻ����Animal��ʱҲ����ɾ��bark API�ӿ�
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

//��̬
//�����˵���ϣ�������������ı���ı�
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