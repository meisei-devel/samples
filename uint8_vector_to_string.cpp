#include <iostream>
#include <vector>
#include <string>
#include <cstdint>

int main(void) {
	std::vector<uint8_t> v = std::vector<uint8_t>();

	v.push_back(0x30); //0
	v.push_back(0x31); //1
	v.push_back(0x32); //2
	v.push_back(0x33); //3
	v.push_back(0x34); //4

	std::string s = std::string(v.begin(), v.end());

	std::cout << s << std::endl;

	return 0;
}
