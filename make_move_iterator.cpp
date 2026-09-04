#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <utility>
#include <algorithm>
#include <iterator>

int main(int argc, char **argv) {

	std::vector<std::shared_ptr<std::string>> v = std::vector<std::shared_ptr<std::string>>();

	std::shared_ptr<std::string> s1 = std::make_shared<std::string>("あ");
	std::shared_ptr<std::string> s2 = std::make_shared<std::string>("い");
	std::shared_ptr<std::string> s3 = std::make_shared<std::string>("う");
	std::shared_ptr<std::string> s4 = std::make_shared<std::string>("え");
	std::shared_ptr<std::string> s5 = std::make_shared<std::string>("お");

	v.push_back(s1);
	v.push_back(s2);
	v.push_back(s3);
	v.push_back(s4);
	v.push_back(s5);

	std::for_each(v.begin(), v.end(), [&](auto const& s) {
		std::cout << *s;
	});
	std::cout << std::endl;

	//単純な例 「え」を２番目に移動する
	v.insert(v.begin() + 1, s4);
	v.erase(v.begin() + 4); //要素が1つ増えているので旧ポインタ場所を削除

	std::for_each(v.begin(), v.end(), [&](auto const& s) {
		std::cout << *s;
	});
	std::cout << std::endl;

	//「あいうえお」に戻す
	v.insert(v.begin() + 4, s4);
	v.erase(v.begin() + 1);

	std::for_each(v.begin(), v.end(), [&](auto const& s) {
		std::cout << *s;
	});
	std::cout << std::endl;

	//「いうえ」だけ別配列に移動する
	std::vector<std::shared_ptr<std::string>> v2 = std::vector<std::shared_ptr<std::string>>();
	v2.insert(v2.begin(), std::make_move_iterator(v.begin() + 1), std::make_move_iterator(v.begin() + 4));
	v.erase(v.begin() + 1, v.begin() + 4); //元の配列では不定要素になっているので削除する

	std::for_each(v2.begin(), v2.end(), [&](auto const& s) {
		std::cout << *s;
	});
	std::cout << std::endl;

	std::for_each(v.begin(), v.end(), [&](auto const& s) {
		std::cout << *s;
	});
	std::cout << std::endl;
}
