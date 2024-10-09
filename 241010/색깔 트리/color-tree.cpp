#include <iostream>
#include <unordered_map>
#include <vector>
#include <set>
using namespace std;

struct Node{
    int pid;
    int color;
    int depth;
    vector<int> children;
};

vector<int> all;
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
        all.emplace_back(mid);
    }
}

void collectColor(int mid, set<int> &distinctColor) {
    distinctColor.emplace(map[mid].color);

    for (int i = 0; i < map[mid].children.size(); i++) {
        collectColor(map[mid].children[i], distinctColor);
    }
}

int printScore() {
    int result = 0;

    for (auto p : all) {
        set<int> distinctColor;
        collectColor(p, distinctColor);
        int eachValue = distinctColor.size();
        result += (eachValue * eachValue);
    }
    
    return result;
}

int searchColor(int mid) {
    return map[mid].color;
}

void updateColor(int mid, int color) {
    map[mid].color = color;
    for (auto child : map[mid].children) {
        updateColor(child, color);
    }
}

int main() {
    int Q, c, mid, pid, color, depth;
    cin >> Q;
    for (int i = 0; i < Q; i++) {
        cin >> c;
        if (c == 100) { // ADD
            cin >> mid >> pid >> color >> depth;
            Node node({ pid, color, depth });
            add(mid, node);
        }
        else if (c == 200) { // Change Color
            cin >> mid >> color;
            updateColor(mid, color);
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