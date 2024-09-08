/*
 * Subtask 1
 * Time complexity: O(1)
 */

#include <iostream>
#include <vector>
using namespace std;

using ii = pair<int, int>;

int main()
{
	ios :: sync_with_stdio(0);
	cin.tie(0);

	int N, L, R, M, A;
	cin >> N >> L >> R >> M >> A;
	cout << (L <= A && A <= R ? 0 : -1) << '\n';
	return 0;
}