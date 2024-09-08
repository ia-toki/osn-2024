#include <bits/stdc++.h>
using namespace std;

int d;

int main() {
	for (int i = 1; i <= 255; i++) {
		cout << "TANYA 1" << endl;
		cout << i << endl;
		cin >> d;
		if (d == 0) {
			cout << "JAWAB " << i << endl;
			return 0;
		}
	}
	cout << "JAWAB 256" << endl;
}