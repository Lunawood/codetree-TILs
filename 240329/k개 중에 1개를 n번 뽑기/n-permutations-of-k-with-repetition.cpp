#include <iostream>
using namespace std;

int K, N;

void func(int k, int n) {
    cout << k << " " << n << "\n";

    if(k == K and n == N){
        return;
    }

    if(n == N){
        k++;
        n=0;
    }


    func(k, ++n);
}

int main() {
    cin >> K >> N;

    func(1, 1);

    return 0;
}