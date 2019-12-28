int minDistance(int dist[], int size, bool visited[]) {
    int min = INT_MAX, min_index;
    for (int vertex = 0; vertex < size; vertex++) {
        if (!visited[vertex] && dist[vertex] <= min)
            min = dist[vertex], min_index = vertex;
    }
    return min_index;
}

void print(int dist[], int size) {
    cout << "Vertex \t\t Distance from Source\n";
    for (int i = 0; i < size; i++)
        printf("%d \t\t %d\n", i, dist[i]);
}

void dijkstra(vector<vector<int>>& graph, int start) {
    int size = graph.size();
    int dist[size];
    bool visited[size];
    
    for (int i = 0; i < size; i++)
        dist[i] = INT_MAX, visited[i] = false;
    
    dist[start] = 0;
    for (int vertex = 0; vertex < size; vertex++) {
        int u = minDistance(dist, size, visited);
        visited[u] = true;
        
        for (int vertex = 0; vertex < size; vertex++) {
            if (!visited[vertex] && graph[u][vertex] && dist[u] != INT_MAX && dist[u] + graph[u][vertex] < dist[vertex])
                dist[vertex] = dist[u] + graph[u][vertex];
        }
    }
    print(dist, size);
}
int main() {
    vector<vector<int>> graph = {{0,4,0,0,0,0,0,8,0},
                                 {4,0,8,0,0,0,0,11,0},
                                 {0,8,0,7,0,4,0,0,2},
                                 {0,0,7,0,9,14,0,0,0},
                                 {0,0,0,9,0,10,0,0,0},
                                 {0,0,4,14,10,0,2,0,0},
                                 {0,0,0,0,0,2,0,1,6},
                                 {8,11,0,0,0,0,1,0,7},
                                 {0,0,2,0,0,0,6,7,0}};
    dijkstra(graph, 0);
    return 0;
}
