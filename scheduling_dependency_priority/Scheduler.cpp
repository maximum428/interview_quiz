#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>

using namespace std;

vector<char> findStopOrder(unordered_map<char, vector<char>>& graph, unordered_map<char, int>& priority) {
    unordered_map<char, int> indegree;
    
    // Initialize indegree for all nodes
    for (auto& [u, _] : graph) {
        indegree[u] = 0;
    }
    
    // Compute indegree
    for (auto& [u, neighbors] : graph) {
        for (auto& v : neighbors) {
            indegree[v]++;
        }
    }
    
    // Min-heap based on priority
    auto cmp = [&](const char a, const char b) {
        return priority[a] > priority[b];  // smaller number = higher priority
    };
    priority_queue<char, vector<char>, decltype(cmp)> pq(cmp);
    
    // Push all nodes with indegree 0
    for (auto& [node, deg] : indegree) {
        if (deg == 0) {
            pq.push(node);
        }
    }
    
    vector<char> res;
    
    while (!pq.empty()) {
        char curr = pq.top();
        pq.pop();
        res.push_back(curr);
        
        for (auto& next : graph[curr]) {
            indegree[next]--;
            if (indegree[next] == 0) {
                pq.push(next);
            }
        }
    }
    
    // Cycle detection
    if (res.size() != indegree.size()) {
        throw runtime_error("Cycle detected : no valid ordering exists");
    }
    return res;
}

int main() {
    unordered_map<char, vector<char>> graph = {
        {'a', {'b', 'c'}},
        {'b', {'d'}},
        {'c', {'b'}},
        {'d', {}}
    };
    
    unordered_map<char, int> priority = {
        {'a', 1},
        {'b', 2},
        {'c', 3},
        {'d', 4}
    };
    
    try {
        vector<char> order = findStopOrder(graph, priority);
        for (auto& stop : order) {
            cout << stop << " ";
        }
    } catch (const exception& e) {
        cout << e.what() << endl;
    }
    return 0;
}





