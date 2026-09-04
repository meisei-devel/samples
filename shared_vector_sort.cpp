#include <iostream>
#include <algorithm>
#include <vector>
#include <memory>
#include <tuple>

class A {
public:
	int mJikan;
	int mDistance;

	A(int jikan, int distance) {
		mJikan = jikan;
		mDistance = distance;
	}

	~A(void) {

	}

	void dump(void) {
		std::cout << "mJikan=" << mJikan << ", mDistance=" << mDistance << std::endl;
	}
};

int main(void) {

	std::shared_ptr<A> a1 = std::make_shared<A>(10, 2);
	std::shared_ptr<A> a2 = std::make_shared<A>(4, 0);
	std::shared_ptr<A> a3 = std::make_shared<A>(7, 6);
	std::shared_ptr<A> a4 = std::make_shared<A>(7, 3);
	std::shared_ptr<A> a5 = std::make_shared<A>(6, 1);

	std::vector<std::shared_ptr<A>> va = std::vector<std::shared_ptr<A>>();
	va.push_back(a1);
	va.push_back(a2);
	va.push_back(a3);
	va.push_back(a4);
	va.push_back(a5);

	//mJikanの昇順でソートする場合

	std::sort(va.begin(), va.end(), [](auto const& c1, auto const& c2) {
		return c1->mJikan < c2->mJikan;
	});

	std::cout << "Sorted by A->mJikan" << std::endl;

	std::for_each(va.begin(), va.end(), [](auto const& c) {
		c->dump();
	});

	//mDistanceの昇順でソートする場合

	std::sort(va.begin(), va.end(), [](auto const& c1, auto const& c2) {
		return c1->mDistance < c2->mDistance;
	});

	std::cout << "Sorted by A->mDistance" << std::endl;

	std::for_each(va.begin(), va.end(), [](auto const& c) {
		c->dump();
	});

	//mJikanの昇順でソートし、mJikanが同一ならmDistanceの昇順でソートする場合

	std::sort(va.begin(), va.end(), [](auto const& c1, auto const& c2) {
		return std::tie(c1->mJikan, c1->mDistance) < std::tie(c2->mJikan, c2->mDistance);
	});

	std::cout << "Sorted by A->mJikan AND A->mDistance" << std::endl;

	std::for_each(va.begin(), va.end(), [](auto const& c) {
		c->dump();
	});

	return 0;
}
