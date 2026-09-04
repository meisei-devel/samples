#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main(void) {

	vector<string> vec = vector<string>();

	vec.push_back(string("はろーわーるど"));

	cout << vec.front() << endl;

	return 0;
}
