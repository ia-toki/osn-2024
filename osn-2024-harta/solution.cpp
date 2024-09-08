#include <bits/stdc++.h>
using namespace std;

int d1, d2, d3;

void askAllExcept(int x) {
	cout << "TANYA 255" << endl;
	for (int i = 1; i <= 256; i++) {
		if (i != x) cout << i << " ";
	}
	cout << endl;
}

int main() {
	cout << "TANYA 128" << endl;
	for (int i = 1; i <= 128; i++) {
		cout << i << " ";
	}
	cout << endl;
	
	cin >> d1;
	if (d1 == 0) {
		// same as solution-3.cpp
		cout << "TANYA 128" << endl;
		for (int i = 129; i <= 256; i++) {
			cout << i << " ";
		}
		cout << endl;
		
		cin >> d2;
		askAllExcept(d2);
		
		cin >> d3;
		if (d3 != 0) {
			cout << "JAWAB " << d2 << endl;
		} else {
			cout << "JAWAB " << 129 - d2 << endl;
		}
		
	} else {
		askAllExcept(128 + d1);
		cin >> d2;
		if (d2 != 0) {
			cout << "JAWAB " << 128 + d1 << endl;
		} else {
			cout << "JAWAB " << 257 - d1 << endl;
		}
	}
}