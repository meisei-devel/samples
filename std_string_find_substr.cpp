#include <iostream>
#include <string>

int main(int argc, char **argv) {

	const char *cs = "あいうえお〔かきくけこ〕";
	std::string ss = std::string(cs);

	std::string::size_type c1, c2;

	if((c1 = ss.find("〔")) != std::string::npos &&
		(c2 = ss.find( "〕", c1 + 3)) != std::string::npos) {

		std::cout << c1 << std::endl;
		std::cout << c2 << std::endl;

		std::string h1 = ss.substr(0, c1);
		std::string h2 = ss.substr(c1 + 3, c2 - (c1 + 3));

		std::cout << h1 << std::endl;
		std::cout << h2 << std::endl;

		ss.erase(c1);

		std::cout << ss << std::endl;
	}

	return 0;
}
