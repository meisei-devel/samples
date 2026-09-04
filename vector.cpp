#include <iostream>
#include <string>
#include <memory>
#include <vector>

class A {
	std::string mName;
public:
	A(void) {
		std::cout << "A constructor" << std::endl;
		mName = std::string("えーでふぉると");
	}
	A(std::string name) {
		std::cout << "A constructor" << std::endl;
		mName = name;
	}
	virtual ~A(void) {
		std::cout << "A destructor" << std::endl;
	}
	void hello(void) {
		std::cout << "A said こんにちは my name is" <<  mName << std::endl;
	}
};

void sample_1(void) {
	std::cout << "enter sample_1" << std::endl;

	std::vector<std::shared_ptr<A>> vec = std::vector<std::shared_ptr<A>>();

	std::shared_ptr<A> a1 = std::make_shared<A>(std::string("えーいち"));
	std::shared_ptr<A> a2 = std::make_shared<A>(std::string("えーに"));
	std::shared_ptr<A> a3 = std::make_shared<A>(std::string("えーさん"));
	std::shared_ptr<A> a4 = std::make_shared<A>(std::string("えーよん"));

	vec.push_back(a1);
	vec.push_back(a2);
	vec.push_back(a3);
	vec.push_back(a4);

	std::cout << "vector count=" << vec.size() << std::endl;

	vec.at(0)->hello();
	vec.back()->hello();

	std::cout << "before vector clear" << std::endl;
	vec.clear();
	std::cout << "after vector clear" << std::endl;

	std::cout << "leave sample_1" << std::endl;
}

void sample_2(void) {

	std::cout << "enter sample_2" << std::endl;

	std::vector<std::shared_ptr<A>> vec = std::vector<std::shared_ptr<A>>();

	vec.push_back(std::make_shared<A>(std::string("えーいち")));
	vec.push_back(std::make_shared<A>(std::string("えーに")));
	vec.push_back(std::make_shared<A>(std::string("えーさん")));
	vec.push_back(std::make_shared<A>(std::string("えーよん")));

	std::cout << "vector count=" << vec.size() << std::endl;

	vec.at(0)->hello();
	vec.back()->hello();

	std::cout << "before vector clear" << std::endl;
	vec.clear();
	std::cout << "after vector clear" << std::endl;

	std::cout << "leave sample_2" << std::endl;
}

int main(int argc, char **argv) {
	std::cout << "enter main" << std::endl;

	sample_1();

	sample_2();

	std::cout << "leave main" << std::endl;

	return 0;
}
