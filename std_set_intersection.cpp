//２人の旅程を比較し立ち寄る同じ駅を抽出するサンプル

#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <iterator>
#include <algorithm>

int main(void) {
	std::vector<std::string> ryotei_1 = {"新宿", "西武新宿", "中井", "所沢", "本川越", "川越", "大宮", "池袋"};
	std::vector<std::string> ryotei_2 = {"飯能", "所沢", "池袋", "上野", "秋葉原", "新宿", "中野", "阿佐ヶ谷"};

	//インデックスマップを作成 map[駅名] = 配列インデックス
	std::unordered_map<std::string, int> ryotei_1_map = std::unordered_map<std::string, int>();
	std::unordered_map<std::string, int> ryotei_2_map = std::unordered_map<std::string, int>();
	int i = 0;
	std::for_each(ryotei_1.begin(), ryotei_1.end(), [&](auto &c) {
		ryotei_1_map[c] = i++;
	});
	i = 0;
	std::for_each(ryotei_2.begin(), ryotei_2.end(), [&](auto &c) {
		ryotei_2_map[c] = i++;
	});

	//立ち寄る同じ駅を抽出（ryotei_comに入る）
	//対象配列はあらかじめソートしておかないと機能しない※重要
	std::vector<std::string> ryotei_com = std::vector<std::string>();
	std::sort(ryotei_1.begin(), ryotei_1.end());
	std::sort(ryotei_2.begin(), ryotei_2.end());
	std::set_intersection(ryotei_1.begin(), ryotei_1.end(), ryotei_2.begin(), ryotei_2.end(), std::inserter(ryotei_com, ryotei_com.end()));

	//結果サマリーを出力
	std::cout << "＜２人が両方とも立ち寄る駅＞" << std::endl;
	std::for_each(ryotei_com.begin(), ryotei_com.end(), [&](auto &c) {
		std::cout << c << " : Aさんが " << ryotei_1_map[c] + 1 << " 番目、Bさんが " << ryotei_2_map[c] + 1 << " 番目に立ち寄る駅。" << std::endl;
	});
}

