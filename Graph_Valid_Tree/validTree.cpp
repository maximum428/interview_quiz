class Solution {
public:
    bool validTree(int n, vector<pair<int, int>>& edges) {
#if 1
#if 0
        vector<int> roots(n, -1);
        for (auto a : edges) {
            int x = find(roots, a.first), y = find(roots, a.second);
            if (x == y) return false;
            roots[x] = y;
        }
        return edges.size() == n - 1;
#else
        vector<unordered_set<int>> graph(n, unordered_set<int>());
        unordered_set<int> s{{0}};
        queue<int> q{{0}};
        for (auto edge : edges) {
            graph[edge.first].insert(edge.second);
            graph[edge.second].insert(edge.first);
        }
        while (!q.empty()) {
            auto t = q.front();
            q.pop();
            for (auto a : graph[t]) {
                if (s.count(a)) return false;
                s.insert(a);
                q.push(a);
                graph[a].erase(t);
            }
        }
        return s.size() == n;
#endif
#else
        vector<vector<int>> graph(n, vector<int>());
        vector<bool> visited(n);
        for (auto edge : edges) {
            graph[edge.first].push_back(edge.second);
            graph[edge.second].push_back(edge.first);
        }
        if (!helper(graph, visited, 0, -1)) return false;
        for (auto node : visited) 
            if (!node) return false;
        return true;
#endif
    }
    
    int find(vector<int>& roots, int i) {
        while (roots[i] != -1)
            i = roots[i];
        return i;
    }
    
    bool helper(vector<vector<int>>& graph, vector<bool>& visited, int cur, int pre) {
        if (visited[cur]) return false;
        visited[cur] = true;
        for (auto a : graph[cur]) {
            if (a != pre) 
                if (!helper(graph, visited, a, cur)) return false;
        }
        return true;
    }
};

int main() {
    int n = 5;
    vector<pair<int, int>> edges = {{0, 1}, {0, 2}, {0, 3}, {1, 4}};
    
    Solution solution;
    cout << solution.validTree(n, edges) << endl;
}
