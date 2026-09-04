#include <algorithm>
#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <time.h>
#include <sys/time.h>

class Test {
public:
	std::string s_val;
	int n_val;
	Test(std::string s, int n) {
		s_val = s;
		n_val = n;
	}

	static double getmicrotime(void) {
		struct timeval tv;
		gettimeofday(&tv, NULL);
		return (((double)tv.tv_sec)*((double)1000000)+((double)tv.tv_usec));
	}
};

int main(int argc, char **argv) {

	std::vector<std::shared_ptr<Test>> tests = std::vector<std::shared_ptr<Test>>();

	int i; char buf[256]; double mt_fr, mt_to;

	for(i = 0; i < 100000; i++) {
		sprintf(buf, "要素%d", i);
		tests.push_back(std::make_shared<Test>(std::string(buf), i));
	}

	std::cout << "tests counts=" << tests.size() << std::endl;


	mt_fr = Test::getmicrotime();

	std::for_each(tests.begin(), tests.end(), [&](auto &c) {
		if(c->n_val % 10000 == 0) {
			std::cout << c->s_val << std::endl;
		}
	});

	mt_to = Test::getmicrotime();

	std::cout << "std::for_each loop time = " << (mt_to - mt_fr) / 1000 << "ms" << std::endl;

	mt_fr = Test::getmicrotime();

	std::all_of(tests.begin(), tests.end(), [&](auto &c) {
		if(c->n_val % 10000 == 0) {
			std::cout << c->s_val << std::endl;
		}
		return true;
	});

	mt_to = Test::getmicrotime();

	std::cout << "std::all_of loop time = " << (mt_to - mt_fr) / 1000 << "ms" << std::endl;

	mt_fr = Test::getmicrotime();

	std::all_of(tests.begin(), tests.end(), [&](auto &c) {
		if(c->n_val >= 50000) {
			return false;
		}
		if(c->n_val % 10000 == 0) {
			std::cout << c->s_val << std::endl;
		}
		return true;
	});

	mt_to = Test::getmicrotime();

	std::cout << "std::all_of break loop time = " << (mt_to - mt_fr) / 1000 << "ms" << std::endl;

	return 0;
}
