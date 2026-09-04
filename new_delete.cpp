#include <iostream>

class A {
public:
	A(void) {
		std::cout << "A constructor" << std::endl;
	}

	virtual ~A(void) {
		std::cout << "A destructor" << std::endl;
	}

	void hello(void) {
		std::cout << "A said こんにちは" << std::endl;
	}
};

class B {
public:
	A *mA;

	B(void) {
		std::cout << "B constructor" << std::endl;
		mA = new A();
	}

	A* getA(void){
		return mA;
	}

	virtual ~B(void) {
		std::cout << "B destructor" << std::endl;
		delete mA;
	}

	void hello(void) {
		std::cout << "B said こんにちは" << std::endl;
	}
};

class C {
public:
	B *mB;

	C(void) {
		std::cout << "C constructor" << std::endl;
		mB = new B;
	}

	B* getB(void){
		return mB;
	}

	virtual ~C(void) {
		std::cout << "C destructor" << std::endl;
		delete mB;
	}

	void hello(void) {
		std::cout << "C said こんにちは" << std::endl;
	}
};

int main(int argc, char **argv) {

	C *c = new C();
	c->hello();

	B *b = c->getB();
	b->hello();

	A *a = b->getA();
	a->hello();

	delete c;

	return 0;
}
