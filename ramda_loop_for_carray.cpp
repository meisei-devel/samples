#include <iostream>
#include <cstring>
#include <algorithm>

int main(void) {
	struct {
		char key[32];
		char value[64];
	}arrays[8] = {
		{"きー１", "ばりゅー１"},
		{"きー２", "ばりゅー２"},
		{"きー３", "ばりゅー３"},
		{"きー４", "ばりゅー４"},
		{"きー５", "ばりゅー５"},
		{"きー６", "ばりゅー６"},
		{"きー７", "ばりゅー７"},
		{"きー８", "ばりゅー８"},
	};

	//ループ出力
	std::for_each(arrays, arrays + 8, [&](auto &c) {
		std::cout << c.key << "+" << c.value << std::endl;
	});

	//値に５を含む要素の検索
	auto itr = std::find_if(arrays, arrays + 8, [&](auto &c) {
		return strstr(c.value, "５") ? true:false;
	});
	if(itr != arrays + 8) {
		//発見した場合itrは要素のアドレス: itr->key, itr->valueでアクセス可能
		int i = std::distance(arrays, itr);
		std::cout << "arrays[" << i << "].valueに５発見" << std::endl;
	}

	return 0;
}
