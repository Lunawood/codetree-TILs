#include <iostream>
#include <vector>
#include <queue>
#include <limits.h>
#include <cmath>
#include <algorithm>
using namespace std;

// 루돌프 -1
// 산타 1~30
int N, M, P, C, D;

struct santa {
	int row;
	int col;
	int faint = 0;
	bool out = false;
	int score = 0;
};

pair<int, int> deer;
vector<santa> santas(31);
vector<vector<int>> map(51, vector<int>(51, 0));
int life = 0;
int d[8][2] = { {0, -1}, {1, -1}, {1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1} };
// 찾는 우선 순위 : 좌, 하좌, 하, 하우, 우, 상우, 상, 상좌

void printMap() {
	for (int i = 1; i < N + 1; i++) {
		for (int j = 1; j < N + 1; j++) {
			cout << map[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
	for (int i = 1; i <= P; i++) {
		cout << santas[i].score << " ";
	}
	cout << endl;
	cout << "================" << endl;
}

bool compare(int apid, int bpid) {
	if (santas[apid].row == santas[bpid].row)
		return santas[apid].col > santas[bpid].col;
	return santas[apid].row > santas[bpid].row;
}

int deerDirection(int row, int col) {
	vector<int> elements;

	int minSanta = INT_MAX;
	for (int i = 1; i <= P; i++) {
		if (santas[i].out)
			continue;
		int santadis = pow(row - santas[i].row, 2) + pow(col - santas[i].col, 2);
		if (minSanta > santadis) {
			minSanta = santadis;
			elements.clear();
			elements.emplace_back(i);
		}
		else if (minSanta == santadis) {
			elements.emplace_back(i);
		}
	}

	sort(elements.begin(), elements.end(), compare);

	int newR = santas[elements[0]].row;
	int newC = santas[elements[0]].col;

	int minDes = INT_MAX;
	int dir = -1;
	for (int i = 0; i < 8; i++) {
		int Des = pow((row + d[i][0]) - newR, 2) + pow((col + d[i][1]) - newC, 2);
		if (minDes > Des) {
			minDes = Des;
			dir = i;
		}
	}

	return dir;
}

int santaDirection(int row, int col) {
	int minDes = pow(row - deer.first, 2) + pow(col - deer.second, 2);
	int dir = -1;
	for (int i = 0; i < 8; i+=2) {
		int Des = pow((row + d[i][0]) - deer.first, 2) + pow((col + d[i][1]) - deer.second, 2);
		if (minDes >= Des && map[row + d[i][0]][col + d[i][1]] <= 0) {
			minDes = Des;
			dir = i;
		}
	}

	return dir;
}

void setting() {
	// map init
	for (int i = 1; i < N + 1; i++) {
		for (int j = 1; j < N + 1; j++) {
			map[i][j] = 0;
		}
	}

	map[deer.first][deer.second] = -1;
	for (int i = 1; i <= P; i++) {
		santa& san = santas[i];
		if(!san.out)
			map[san.row][san.col] = i;
	}
}

bool checkOut(int row, int col) {
	return !(0 < row && row < N + 1 && 0 < col && col < N + 1);
}

bool smashAnother(int pid) {
	if (map[santas[pid].row][santas[pid].col] == 0)
		return false;
	return map[santas[pid].row][santas[pid].col] != pid;
}

void continueSmash(int pid, int dir) {
	if (checkOut(santas[pid].row, santas[pid].col)) {
		santas[pid].out = true;
		return;
	}
	if (smashAnother(pid)) {
		santas[map[santas[pid].row][santas[pid].col]].row += d[dir][0];
		santas[map[santas[pid].row][santas[pid].col]].col += d[dir][1];
		continueSmash(map[santas[pid].row][santas[pid].col], dir);
	}
	return;
}

void smash(int me, int dir) {
	if (me == -1) { // 루들프
		me = map[deer.first][deer.second];
		santas[me].score += C;
		santas[me].faint = 2;
		santas[me].row += d[dir][0] * C;
		santas[me].col += d[dir][1] * C;
		continueSmash(me, dir);
	}
	else { // 산타
		santas[me].score += D;
		santas[me].faint = 2;
		santas[me].row += d[(dir + 4) % 8][0] * D;
		santas[me].col += d[(dir + 4) % 8][1] * D;
		continueSmash(me, (dir + 4) % 8);
	}
	
}

bool deerSmash(int row, int col) {
	return map[row][col];
}

void moveDeer() {
	int dir = deerDirection(deer.first, deer.second);
	deer.first += d[dir][0];
	deer.second += d[dir][1];
	if(deerSmash(deer.first, deer.second))
		smash(-1, dir);
}

bool santaSmash(int row, int col) {
	return map[row][col] == -1;
}

void moveSanta(int i) {
	int dir = santaDirection(santas[i].row, santas[i].col);
	if (dir == -1)
		return;
	santas[i].row += d[dir][0];
	santas[i].col += d[dir][1];
	if (santaSmash(santas[i].row, santas[i].col))
		smash(i, dir);
}

void calculateFaint() {
	life = 0;
	for (int i = 1; i <= P; i++) {
		if (santas[i].faint)
			santas[i].faint--;
		if (santas[i].out > 0)
			life++;
	}
}

void game() {
	setting();

	// printMap();

	moveDeer();

	for (int i = 1; i <= P; i++) {
		if (!santas[i].faint && !santas[i].out) {
			setting();

			 // printMap();

			moveSanta(i);
		}
	}

	calculateFaint();
}

bool gameOver() {
	return life == P;
}

void bonusPoint() {
	for (int i = 1; i <= P; i++) {
		if (!santas[i].out)
			santas[i].score++;
	}
}

int main() {
	cin >> N >> M >> P >> C >> D;
	cin >> deer.first;
	cin >> deer.second;
	for (int i = 0; i < P; i++) {
		santa san;
		int pid;
		cin >> pid >> san.row >> san.col;
		santas[pid] = san;
	}

	// game simulation
	for (int i = 0; i < M; i++) {
		if (!gameOver()) {
			game();
			bonusPoint();
		}
		// setting();
		// printMap();
	}

	// output
	for (int i = 1; i <= P; i++) {
		cout << santas[i].score << " ";
	}
}