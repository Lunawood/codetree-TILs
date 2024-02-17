#include <iostream>
using namespace std;

int N;
int arr[21][21];
int maxNumber = 0;

int main() {
	cin >> N;

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> arr[i][j];
		}
	}

	for (int i = 2; i <= N - 1; i++) {
		for (int j = 2; j <= N - 1; j++) {
			int row = i;
			int col = j;
			int cnt = 0;

			for (int r = -1; r <= 1; r++) {
				for (int c = -1; c <= 1; c++) {
					if (arr[row + r][col + c]) {
						cnt++;
					}
				}
			}

			maxNumber = max(maxNumber, cnt);
		}
	}

	cout << maxNumber << "\n";

	return 0;
}