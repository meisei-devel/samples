#include <iostream>
#include <string>
#include <memory>
#include <thread>
#include <mutex>

std::mutex gMutex;

class Test {
public:
	Test(void) {}
	~Test(void) {}
	void Thread_Make(void);
	void Thread_Func(int &i, std::string &s);
};

void Test::Thread_Make(void) {

	std::shared_ptr<std::thread> t1 = std::shared_ptr<std::thread>();
	std::shared_ptr<std::thread> t2 = std::shared_ptr<std::thread>();

	int i1 = 5, i2 = 10;
	std::string s1 = std::string("もじ１");
	std::string s2 = std::string("もじ２");

	if(i1 > 0){
		t1 = std::make_shared<std::thread>(&Test::Thread_Func, this, std::ref(i1), std::ref(s1));
	}

	if(i2 > 0){
		t2 = std::make_shared<std::thread>(&Test::Thread_Func, this, std::ref(i2), std::ref(s2));
	}

	if(t1.get() != nullptr){
		t1->join();
	}

	if(t2.get() != nullptr){
		t2->join();
	}
}

void Test::Thread_Func(int &i, std::string &s) {

	gMutex.lock();

	std::cout << "thread id = " << std::this_thread::get_id() << ", i = " << i << ", s = " << s << std::endl;

	gMutex.unlock();
}

int main(void) {

	Test test = Test();
	test.Thread_Make();

	return 0;
}
