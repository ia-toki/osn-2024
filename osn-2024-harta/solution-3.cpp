#include <bits/stdc++.h>
using namespace std;

int d1, d2;

void askAllExcept(int x) {
	cout << "TANYA 255" << endl;
	for (int i = 1; i <= 256; i++) {
		if (i != x) cout << i << " ";
	}
	cout << endl;
}

int main() {
	cout << "TANYA 128" << endl;
	for (int i = 129; i <= 256; i++) {
		cout << i << " ";
	}
	cout << endl;
	
	cin >> d1;
	askAllExcept(d1);
	
	cin >> d2;
	if (d2 != 0) {
		cout << "JAWAB " << d1 << endl;
	} else {
		cout << "JAWAB " << 129 - d1 << endl;
	}
}