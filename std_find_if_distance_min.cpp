#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <algorithm>

class Test {
public:
	Test(std::string s, int n){
		string = s;
		number = n;
	}
	std::string string;
	int number;
};

int main(int argc, char **argv) {

	//Testクラスポインタ配列定義
	std::vector<std::shared_ptr<Test>> tests = std::vector<std::shared_ptr<Test>>();

	//Testクラス３つ作成＆代入
	tests.push_back(std::make_shared<Test>(std::string("てすと１"), 50));
	tests.push_back(std::make_shared<Test>(std::string("てすと２"), 20));
	tests.push_back(std::make_shared<Test>(std::string("てすと３"), 70));

	//numberが70の最初の要素を検索する(イテレータを返却)
	auto itr = std::find_if(tests.begin(), tests.end(), [&](auto &c) {
		return c->number == 70; //てすと３クラスが返るはず
	});

	int i;

	//見つかった場合
	if(itr != tests.end()) {
		//その配列インデックスを取得
		i = std::distance(tests.begin(), itr);

		std::cout << "number==70 class is " << (*itr)->string << ", and index=" << i << std::endl;
	}

	//numberが最も小さい要素を検索する(イテレータを返却)
	itr = std::min_element(tests.begin(), tests.end(), [&](auto &c1, auto &c2) {
		return c1->number <= c2->number;
	});

	//見つかった場合
	if(itr != tests.end()) {
		//その配列インデックスを取得
		i = std::distance(tests.begin(), itr);

		std::cout << "min number class is " << (*itr)->string << ", number=" << (*itr)->number << ", and index=" << i << std::endl;
	}

	return 0;
}
