#include <iostream>
using namespace std;

int n, N;
int arr[200];
int idx1, idx2;

int main() {
    cin >> n;
    N = n;
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }
    for (int i = 0; i < 2; i++) {
        cin >> idx1 >> idx2;
        N -= (idx2 - idx1 + 1);
        for (int i = 0; i < n - idx2 + 1; i++) {
            arr[i + idx1] = arr[i + idx2 + 1];
        }
    }
    cout << N << "\n";
    for (int i = 1; i <= N; i++) {
        cout << arr[i] << "\n";
    }
    return 0;
}