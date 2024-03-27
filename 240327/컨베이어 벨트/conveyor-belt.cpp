#include <iostream>
using namespace std;

int n, t;
int arr[3][201];

int main() {
    cin >> n >> t;
    for(int i = 1; i <=2; i++){
        for(int j = 1; j <= n; j++){
            cin >> arr[i][j];
        }
    }

    for(int i = 0; i < t; i++){
        int tmp = arr[2][n];
        for(int j = n; j >= 1; j--){
            arr[2][j] = arr[2][j - 1];
        }
        arr[2][1] = arr[1][n];
        for(int j = n; j >= 1; j--){
            arr[1][j] = arr[1][j - 1];
        }
        arr[1][1] = tmp;
    }

    for(int i = 1; i <= 2; i++){
        for(int j = 1; j <= n; j++){
            cout << arr[i][j] << " ";
        }
        cout << "\n";
    }
    return 0;
}