#include <iostream>
using namespace std;

int N, num, ans = 0;
int arr[21][21];

int func(int y, int x) {
    int MAX = 0;
    for (int i = y + 0; i < y + 3; i++) {
        for (int j = x + 0; j < x + 3; j++) {
            if (arr[i][j] == 1) {
                MAX++;
            }
        }
    }
    return MAX;
}

int main() {
    cin >> N;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            cin >> arr[i][j];
        }
    }

    for (int i = 1; i <= N - 2; i++) {
        for (int j = 1; j <= N - 2; j++) {
            ans = max(func(i, j), ans);
        }
    }

    cout << ans << "\n";
}