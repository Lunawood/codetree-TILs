#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int R, C, K;
// 숲 : 0
// 골렘 : 1~1000
// 출구 : -1~-1000
// 정령 : P

void mapInit(vector<vector<int>> &vec) {
    for (int i = 0; i < R + 3; i++) {
        for (int j = 0; j < C; j++) {
            vec[i][j] = 0;
        }
    }
}

int fairy(int row, int col, vector<vector<int>> &vec) {
    queue<pair<int, int>> q;
    vector<vector<bool>> visited(R, vector<bool>(C, false));
    q.emplace(row, col);
    visited[row][col] = true;

    int result = row;

    while (!q.empty()) {
        int newR = q.front().first;
        int newC = q.front().second;
        int pid = vec[newR + 3][newC];
        result = max(result, newR);
        q.pop();

        // 아래
        if (
            newR + 1 < R &&
            (pid == vec[newR + 3 + 1][newC] || (pid < 0 && vec[newR + 3 + 1][newC] > 0) || (pid > 0 && vec[newR + 3 + 1][newC] == -pid)) &&
            !visited[newR + 1][newC]
            ) {
            q.emplace(newR + 1, newC);
            visited[newR + 1][newC] = true;
        }
        // 왼쪽
        if (
            newC - 1 > -1 &&
            (pid == vec[newR + 3][newC - 1] || (pid < 0 && vec[newR + 3][newC - 1] > 0) || (pid > 0 && vec[newR + 3][newC - 1] == -pid)) &&
            !visited[newR][newC - 1]
            ) {
            q.emplace(newR, newC - 1);
            visited[newR][newC - 1] = true;
        }
        // 위
        if (
            newR - 1 > -1 &&
            (pid == vec[newR + 3 - 1][newC] || (pid < 0 && vec[newR + 3 - 1][newC] > 0) || (pid > 0 && vec[newR + 3 - 1][newC] == -pid)) &&
            !visited[newR - 1][newC]
            ) {
            q.emplace(newR - 1, newC);
            visited[newR - 1][newC] = true;
        }
        // 왼쪽
        if (
            newC + 1 < C &&
            (pid == vec[newR + 3][newC + 1] || (pid < 0 && vec[newR + 3][newC + 1] > 0) || (pid > 0 && vec[newR + 3][newC + 1] == -pid)) &&
            !visited[newR][newC + 1]
            ) {
            q.emplace(newR, newC + 1);
            visited[newR][newC + 1] = true;
        }
    }

    return result + 1;
}

pair<int, int> machine(int pid, int c, int d, vector<vector<int>> &vec) {
    int newR = 0;
    int newC = c - 1;

    while (true) {
        // 아래로
        if (
            newR + 2 < R + 3 &&
            vec[newR + 1][newC - 1] == 0 &&
            vec[newR + 2][newC] == 0 &&
            vec[newR + 1][newC + 1] == 0) {
            newR = newR + 1;
        }
        // 왼쪽으로
        else if (
            newR + 2 < R + 3 &&
            newC - 2 > -1 &&
            vec[newR - 1][newC - 1] == 0 &&
            vec[newR][newC - 2] == 0 &&
            vec[newR + 1][newC - 1] == 0 &&
            vec[newR + 1][newC - 2] == 0 &&
            vec[newR + 2][newC - 1] == 0) {
            d = ((d - 1) + 4) % 4;
            newR = newR + 1;
            newC = newC -1;
        }
        // 오른쪽으로
        else if (
            newR + 2 < R + 3 &&
            newC + 2 < C &&
            vec[newR - 1][newC + 1] == 0 &&
            vec[newR][newC + 2] == 0 &&
            vec[newR + 1][newC + 1] == 0 &&
            vec[newR + 1][newC + 2] == 0 &&
            vec[newR + 2][newC + 1] == 0) {
            d = (d + 1) % 4;
            newR = newR + 1;
            newC = newC + 1;
        }
        else {
            break;
        }
    }

    vec[newR][newC] = pid;
    vec[newR - 1][newC] = pid;
    vec[newR][newC - 1] = pid;
    vec[newR + 1][newC] = pid;
    vec[newR][newC + 1] = pid;

    if (d == 0) {
        vec[newR - 1][newC] = -pid;
    }
    else if (d == 1) {
        vec[newR][newC + 1] = -pid;
    }
    else if (d == 2) {
        vec[newR + 1][newC] = -pid;
    }
    else if (d == 3) {
        vec[newR][newC - 1] = -pid;
    }

    return make_pair(newR, newC);
}

int process(int pid, int c, int d, vector<vector<int>> &vec) {
    pair<int, int> machinePos;
    machinePos = machine(pid, c, d, vec);
    if (machinePos.first > 3)
        return fairy(machinePos.first - 3, machinePos.second, vec);
    mapInit(vec);
    return 0;
}

int main() {
    int c, d, answer = 0;

    // input
    cin >> R >> C >> K;
    
    // 맵을 3만큼 늘림. 시작은 3행부터 숲!
    vector<vector<int>> vec(R + 3, vector<int>(C, 0));

    for (int i = 0; i < K; i++) {
        cin >> c >> d;
        answer += process(i + 1, c, d, vec);
    }

    // output
    cout << answer << endl;

    vec.clear();

    return 0;
}