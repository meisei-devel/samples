#include <algorithm>
#include <iostream>
#include <vector>
#include <memory>
#include <string>

class Test {
public:
	std::string s_val;
	int n_val;
	Test(std::string s, int n) {
		s_val = s;
		n_val = n;
	}
};

int main(int argc, char **argv) {

	std::vector<std::shared_ptr<Test>> tests = std::vector<std::shared_ptr<Test>>();

	tests.push_back(std::make_shared<Test>(std::string("あ"), 1));
	tests.push_back(std::make_shared<Test>(std::string("い"), 2));
	tests.push_back(std::make_shared<Test>(std::string("う"), 3));
	tests.push_back(std::make_shared<Test>(std::string("え"), 4));
	tests.push_back(std::make_shared<Test>(std::string("お"), 5));

	std::for_each(tests.begin(), tests.end(), [&](auto &c) {
		std::cout << c->s_val << std::endl;
	});

	std::all_of(tests.begin(), tests.end(), [&](auto &c) {
		if(c->n_val >= 4) {
			return false; // break
		}
		std::cout << c->s_val << std::endl;
		return true;
	});

	return 0;
}
