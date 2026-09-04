#include <stdio.h>
#include <stdint.h>
#include <iostream>
#include <string>
#include <bitset>

int main(void) {
    uint32_t val1 = 255;
    uint32_t val2 = 0xffffffff;
    uint32_t val3 = 0x183061c1;

    std::bitset<32> bit1 = std::bitset<32>(val1);
    std::bitset<32> bit2 = std::bitset<32>(val2);
    std::bitset<32> bit3 = std::bitset<32>(val3);
    
	std::cout << bit1.to_string() << std::endl;
    std::cout << bit2.to_string() << std::endl;
    std::cout << bit3.to_string() << std::endl;

    std::cout << "bit1[7] is " << bit1.test(7) << std::endl;
    std::cout << "bit1[8] is " << bit1.test(8) << std::endl;

	return 0;
}
