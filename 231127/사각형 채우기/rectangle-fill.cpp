#include <iostream>
using namespace std;

int dp[1001];

// dp[n] = dp[n - 1] + dp[n - 2]
void recur(int n) {
    for(int i = 3; i <= n; i++){
        if(dp[i] == 0){
            dp[i] = dp[i - 1] + dp[i - 2];
        }
    }
}

int main() {
    int n;
    dp[1] = 1;
    dp[2] = 2;
    cin >> n;
    recur(n);
    cout << dp[n] << endl;
    return 0;
}