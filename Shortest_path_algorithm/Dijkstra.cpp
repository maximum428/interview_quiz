void print(vector<int>& result) {
    cout << "Vertex \t\t Distance from Source\n" << endl;
    for (int i = 0; i < result.size(); i++) 
        cout << i << " \t\t " << result[i] << endl;
}

int minDistance(vector<int>& dp, vector<bool>& visited) {
    int min = INT_MAX, min_index;
    
    for (int i = 0; i < dp.size(); i++) {
        if (visited[i] == false && dp[i] <= min)
            min = dp[i], min_index = i;
    }
    return min_index;
}

vector<int> dijkstra(vector<vector<int>>& graph) {
    if (graph.size() == 0) return {};
    
    int size = graph[0].size();
    
    vector<int> dp(size, INT_MAX);
    vector<bool> visited(size);
    
    dp[0] = 0;
    
    for (int i = 0; i < size - 1; i++) {
        int u = minDistance(dp, visited);
        visited[u] = true;
        
        for (int j = 0; j < size; j++) {
            if (!visited[j] && graph[u][j] && dp[u] != INT_MAX && dp[u] + graph[u][j] < dp[j])
                dp[j] = dp[u] + graph[u][j];
        }
    }
    return dp;
}


int main() {
    vector<vector<int>> graph = {{ 0, 4, 0, 0, 0, 0, 0, 8, 0 },
                                 { 4, 0, 8, 0, 0, 0, 0, 11, 0 }, 
                                 { 0, 8, 0, 7, 0, 4, 0, 0, 2 }, 
                                 { 0, 0, 7, 0, 9, 14, 0, 0, 0 }, 
                                 { 0, 0, 0, 9, 0, 10, 0, 0, 0 }, 
                                 { 0, 0, 4, 14, 10, 0, 2, 0, 0 }, 
                                 { 0, 0, 0, 0, 0, 2, 0, 1, 6 }, 
                                 { 8, 11, 0, 0, 0, 0, 1, 0, 7 }, 
                                 { 0, 0, 2, 0, 0, 0, 6, 7, 0 } };
    vector<int> res = dijkstra(graph);
    print(res);
}
