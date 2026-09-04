#include <iostream>
#include <vector>
#include <string>
#include <numeric>

class Test {
public:
	int number;
	std::string string;
	Test(int n, std::string s) {
		number = n;
		string = s;
	}
};

int main(void) {

	std::vector<Test> tests = std::vector<Test>();

	tests.push_back(Test(1, std::string("あ")));
	tests.push_back(Test(2, std::string("い")));
	tests.push_back(Test(3, std::string("う")));
	tests.push_back(Test(4, std::string("え")));
	tests.push_back(Test(5, std::string("お")));

	int number_all = std::accumulate( tests.begin(), tests.end(), 0,
		[]( int n, auto &c ){ return n + c.number; } );

	std::string string_all = std::accumulate( tests.begin(), tests.end(), std::string(""),
		[]( std::string s, auto &c ){ return s + c.string; } );

	std::cout << "number_all=" << number_all << ", string_all=" << string_all << std::endl;

	return 0;
}
