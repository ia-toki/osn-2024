#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> PII;
typedef pair<PII, int> PIII;

const int ROW = 0;
const int COL = 1;
const int WHITE = 0;
const int BLACK = 1;

int n, m, processed;
string s[200007];
int row[200007][3], col[200007][3];
bool proc_row[200007], proc_col[200007];
vector<PIII> ans;

int main() {
	scanf("%d%d",&n, &m);
	for (int i = 0; i < n; i++) cin >> s[i];
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (s[i][j] == '.') {
				row[i][WHITE]++;
				col[j][WHITE]++;
			} else {
				row[i][BLACK]++;
				col[j][BLACK]++;
			}
		}
	}
	
	for (int i = 0; i < n; i++) {
		if (row[i][WHITE] == 0) {
			proc_row[i] = true;
			ans.push_back(PIII(PII(ROW, i), BLACK));
		} else if (row[i][BLACK] == 0) {
			proc_row[i] = true;
			ans.push_back(PIII(PII(ROW, i), WHITE));
		}
	}
	
	for (int j = 0; j < m; j++) {
		if (col[j][WHITE] == 0) {
			proc_col[j] = true;
			ans.push_back(PIII(PII(COL, j), BLACK));
		} else if (col[j][BLACK] == 0) {
			proc_col[j] = true;
			ans.push_back(PIII(PII(COL, j), WHITE));
		}
	}
	
	processed = 0;
	while (processed < ans.size()) {
		int rowcol = ans[processed].first.first;
		int idx = ans[processed].first.second;
		int color = ans[processed].second;
		processed++;
		
		if (rowcol == ROW) {
			for (int j = 0; j < m; j++) if (!proc_col[j]) {
				col[j][color]--;
				if (col[j][color] == 0) {
					proc_col[j] = true;
					ans.push_back(PIII(PII(COL, j), 1 - color));
				}
			}
		} else {
			for (int i = 0; i < n; i++) if (!proc_row[i]) {
				row[i][color]--;
				if (row[i][color] == 0) {
					proc_row[i] = true;
					ans.push_back(PIII(PII(ROW, i), 1 - color));
				}
			}
		}
	}
	
	printf("%d\n", (int) ans.size());
	for (int i = (int) ans.size() - 1; i >= 0; i--) {
		int rowcol = ans[i].first.first;
		int idx = ans[i].first.second;
		int color = ans[i].second;
		
		if (rowcol == ROW) printf("BARIS "); else printf("KOLOM ");
		printf("%d", idx + 1);
		if (color == BLACK) printf(" #\n"); else printf(" .\n");
	}
}