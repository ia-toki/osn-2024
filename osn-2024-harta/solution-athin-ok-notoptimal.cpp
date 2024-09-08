#include <bits/stdc++.h>
using namespace std;

int d;

void askAllExcept(int x) {
	cout << "TANYA 255" << endl;
	for (int i = 1; i <= 256; i++) {
		if (i != x) cout << i << " ";
	}
	cout << endl;
}

int main() {
	for (int i = 1; i <= 255; i++) {
		askAllExcept(i);
		cin >> d;
		if (d != 0) {
			cout << "JAWAB " << i << endl;
			return 0;
		}
	}
	cout << "JAWAB 256" << endl;
}