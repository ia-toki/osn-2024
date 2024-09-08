#include <bits/stdc++.h>
using namespace std;

int n, m, res;
string s[30];

int main() {
	cin >> n >> m;
	for (int i = 0; i < n; i++) cin >> s[i];
	
	assert(n == 3 && m == 5);
	assert(s[0] == "10011");
	assert(s[1] == "00101");
	assert(s[2] == "10101");
	
	cout << "AKSELERASI 1" << endl;
	for (int i = 0; i < n; i++) cin >> s[i];
	assert(s[0] == "11001");
	assert(s[1] == "10011");
	assert(s[2] == "10010");
	
	cout << "AKSELERASI 1" << endl;
	for (int i = 0; i < n; i++) cin >> s[i];
	assert(s[0] == "10100");
	assert(s[1] == "11001");
	assert(s[2] == "11011");
	
	cout << "EKSPERIMEN 2 5" << endl;
	cin >> res;
	assert(res == 1);
	
	cout << "EKSPERIMEN 3 5" << endl;
	cin >> res;
	assert(res == 2);
	
	cout << "EKSPERIMEN 1 1" << endl;
	cin >> res;
	assert(res == 1);
	
	cout << "AKSELERASI 4" << endl;
	for (int i = 0; i < n; i++) cin >> s[i];
	assert(s[0] == "11010");
	assert(s[1] == "10000");
	assert(s[2] == "10000");
	
	cout << "EKSPERIMEN 3 1" << endl;
	cin >> res;
	assert(res == 2);
	
	cout << "AKSELERASI 1000" << endl;
	for (int i = 0; i < n; i++) cin >> s[i];
	assert(s[0] == "01000");
	assert(s[1] == "10010");
	assert(s[2] == "00000");
	
	cout << "EKSPERIMEN 1 2" << endl;
	cin >> res;
	assert(res == 1);
	
	cout << "EKSPERIMEN 2 4" << endl;
	cin >> res;
	assert(res == 1);
	
	cout << "EKSPERIMEN 2 1" << endl;
	cin >> res;
	assert(res == 2);
}