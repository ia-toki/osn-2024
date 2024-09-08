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
	askAllExcept(1);
	cin >> d;
	if (d != 0) {
		cout << "JAWAB 1" << endl;
		return 0;
	}
	
	askAllExcept(2);
	cin >> d;
	if (d != 0) {
		cout << "JAWAB 2" << endl;
	} else {
		cout << "JAWAB 3" << endl;
	}
}