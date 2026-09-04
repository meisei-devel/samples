#include <iostream>

class Test {
public:
	static int sSequence;
	int mClassNo;
	Test(void);
	~Test(void);
};

Test::Test(void) {
	mClassNo = sSequence++; //自分のクラス番号をスタティックシーケンスから付与し、シーケンスを加算する
}

Test::~Test(void) {

}

int main(void) {
	Test t1 = Test();
	Test t2 = Test();

	std::cout << "t1 no=" << t1.mClassNo << ",t2 no=" << t2.mClassNo << ",sequence=" << Test::sSequence << std::endl;

	return 0;
}
