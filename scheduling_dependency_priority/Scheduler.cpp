#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>

using namespace std;

int main() {
    // Graph
    unordered_map<char, vector<char>> graph = {
        {'A', {'B', 'C'}},
        {'B', {'D'}},
        {'C', {'B'}}
    };

    // Priority (lower = higher priority)
    unordered_map<char, int> priority = {
        {'A', 1},
        {'B', 2},
        {'C', 3},
        {'D', 4}
    };

    // Step 1: compute indegree
    unordered_map<char, int> indegree;
    for (auto &p : priority) {
        indegree[p.first] = 0;
    }

    for (auto &p : graph) {
        for (char nei : p.second) {
            indegree[nei]++;
        }
    }

    // Step 2: min-heap by priority
    auto cmp = [&](char a, char b) {
        return priority[a] > priority[b];  // min-heap
    };
    priority_queue<char, vector<char>, decltype(cmp)> pq(cmp);

    // Step 3: push indegree == 0
    for (auto &p : indegree) {
        if (p.second == 0) {
            pq.push(p.first);
        }
    }

    // Step 4: topological sort
    vector<char> result;

    while (!pq.empty()) {
        char cur = pq.top();
        pq.pop();
        result.push_back(cur);

        for (char nei : graph[cur]) {
            if (--indegree[nei] == 0) {
                pq.push(nei);
            }
        }
    }

    // Output
    cout << "Stop order: ";
    for (char c : result) {
        cout << c << " ";
    }
    cout << endl;

    return 0;
}






