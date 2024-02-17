#include <iostream>
#include <vector>
using namespace std;

int k, n;
vector<int> vec;

void func(int n) {
	if (n == 0) {
		for (auto p : vec) {
			cout << p << " ";
		}
		cout << "\n";
		return;
	}
	
	for (int i = 1; i <= k; i++) {
		vec.push_back(i);
		func(n - 1);
		vec.pop_back();
	}
}

int main() {
	cin >> k >> n;

	func(n);
}