#include <iostream>
#include <unordered_map>
#include <vector>
#include <set>
using namespace std;

struct Node{
    int pid;
    int color;
    int depth;
    int priority;
    vector<int> children;
};

vector<int> roots;
unordered_map<int, Node> map;

bool addComfirm(int pid) {
    int cur_pid = pid;
    int depth = 2;
    while (cur_pid != -1) {
        Node &node = map[cur_pid];
        if (depth > node.depth)
            return false;
        depth++;
        cur_pid = node.pid;
    }
    return true;
}

void add(int mid, Node node) {
    if (addComfirm(node.pid)) {
        map[mid] = node;
        if (node.pid != -1) {
            map[node.pid].children.emplace_back(mid);
        }
        else {
            roots.emplace_back(mid);
        }
    }
}



pair<int, int[6]> collect(int mid, int lastColor, int lastPriority) {
    int cur_priority = map[mid].priority;

    if (cur_priority >= lastPriority) {
        lastPriority = cur_priority;
        lastColor = map[mid].color;
    }

    pair<int, int[6]> result;
    result.first = 0;
    for (int i = 1; i < 6; i++) {
        result.second[i] = 0;
    }
    result.second[lastColor] = 1;
    for (auto p : map[mid].children) {
        pair<int, int[6]> subResult = collect(p, lastColor, lastPriority);
        for (int i = 1; i < 6; i++) {
            result.second[i] += subResult.second[i];
        }
        result.first += subResult.first;
    }
    int value = 0;
    for (int i = 1; i < 6; i++) {
        if (result.second[i] > 0)
            value++;
    }
    result.first += value * value;
    
    return result;
}

int printScore() {
    int result = 0;

    for (auto root : roots) {
        int eachValue = collect(root, map[root].color, map[root].priority).first;
        result += eachValue;
    }
    
    return result;
}

int searchColor(int mid) {
    int max = 0;
    int color = map[mid].color;
    int cur_mid = mid;

    while (cur_mid != -1) {
        if (max < map[cur_mid].priority) {
            max = map[cur_mid].priority;
            color = map[cur_mid].color;
        }

        cur_mid = map[cur_mid].pid;
    }

    return color;
}

void updateColor(int mid, int color, int priority) {
    map[mid].color = color;
    map[mid].priority = priority;
}

int main() {
    int Q, c, mid, pid, color, depth;
    int priority = 1;
    cin >> Q;
    for (int i = 0; i < Q; i++) {
        cin >> c;
        if (c == 100) { // ADD
            cin >> mid >> pid >> color >> depth;
            Node node({ pid, color, depth, priority});
            add(mid, node);
            priority++;
        }
        else if (c == 200) { // Change Color
            cin >> mid >> color;
            updateColor(mid, color, priority);
            priority++;
        }
        else if (c == 300) { // Search Color
            cin >> mid;
            cout << searchColor(mid) << "\n";
        }
        else {
            cout << printScore() << "\n";
        }
    }

    return 0;
}