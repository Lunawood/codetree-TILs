#include <iostream>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, m, ans = 0;
    int arr[101][101];

    // 입력값
    cin >> n >> m;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cin >> arr[i][j];
        }
    }

    for(int i = 0; i < n; i++){
        int row_cnt = 1;
        int col_cnt = 1;
        int row_num = -1;
        int col_num = -1;

        for(int j = 0; j < n; j++){
            if(row_num == arr[i][j])
                row_cnt++;
            if(col_num == arr[j][i])
                col_cnt++;
            row_num = arr[i][j];
            col_num = arr[j][i];
        }

        if(row_cnt >= m)
            ans++;
        if(col_cnt >= m)
            ans++;
    }

    cout << ans << "\n";
    return 0;
}