#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
#include <memory>

class Test {
public:
	int my_number;
	std::string my_name;
	Test(int number, std::string name) {
		my_number = number;
		my_name = name;
	}
};

int main(void) {

	std::vector<std::shared_ptr<Test>> tests = std::vector<std::shared_ptr<Test>>();

	tests.push_back(std::make_shared<Test>(10, std::string("たなか")));
	tests.push_back(std::make_shared<Test>(11, std::string("なかむら")));
	tests.push_back(std::make_shared<Test>(12, std::string("きむら")));
	tests.push_back(std::make_shared<Test>(13, std::string("さわだ")));
	tests.push_back(std::make_shared<Test>(14, std::string("いのうえ")));

	auto itr = std::find_if(tests.begin(), tests.end(), [&](auto &c) {
		return (c->my_number == 12);
	});
	if(itr != tests.end()) {
		int itr_index = std::distance(tests.begin(), itr);
		std::cout << "my_numberが12の人がtests配列 INDEX:" << itr_index << " に見つかりました。名前は " << (*itr)->my_name << "さんです。" << std::endl;
	}
	else {
		std::cout << "my_numberが12の人はtests配列に存在しませんでした。" << std::endl;
	}

	itr = std::find_if(tests.begin(), tests.end(), [&](auto &c) {
		return (c->my_name == "さわだ");
	});
	if(itr != tests.end()) {
		int itr_index = std::distance(tests.begin(), itr);
		std::cout << "my_nameがさわだの人がtests配列 INDEX:" << itr_index << " に見つかりました。" << std::endl;
	}
	else {
		std::cout << "my_nameがさわだの人はtests配列に存在しませんでした。" << std::endl;
	}

	return 0;
}
