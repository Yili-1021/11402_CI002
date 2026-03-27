#include<iostream>
using namespace std;

int main() {
	int s, d;
	while (cin >> s >> d) {
		int sum = 0;
		for (int day = s;; day++) {
			sum += day;
			if (sum >= d) {
				cout << day << endl;
				break;
			}
		}
	}
};
