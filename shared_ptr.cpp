#include <iostream>
#include <memory>

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
	std::shared_ptr<A> mA;

	B(void) {
		std::cout << "B constructor" << std::endl;
		mA = std::make_shared<A>();
	}

	A& getA(void){
		return *(mA);
	}

	virtual ~B(void) {
		std::cout << "B destructor" << std::endl;
	}

	void hello(void) {
		std::cout << "B said こんにちは" << std::endl;
	}
};

class C {
public:
	std::shared_ptr<B> mB;

	C(void) {
		std::cout << "C constructor" << std::endl;
		mB = std::make_shared<B>();
	}

	B& getB(void){
		return *(mB);
	}

	virtual ~C(void) {
		std::cout << "C destructor" << std::endl;
	}

	void hello(void) {
		std::cout << "C said こんにちは" << std::endl;
	}
};

int main(int argc, char **argv) {

	std::shared_ptr<C> c = std::make_shared<C>();
	c->hello();

	B &b = c->getB();
	b.hello();

	A &a = b.getA();
	a.hello();

	return 0;
}
