enum { UNVISITED, VISITING, VISITED };

bool dfs(int node, vector<char> &status, vector<vector<int>> &graph) {
    status[node] = VISITING;
    for (int adj : graph[node]) {
        if (status[adj] == UNVISITED) {
            if (dfs(adj, status, graph))
                return true;
        } else if (status[adj] == VISITING)
            return true;
    }
    status[node] = VISITED;
    return false;
}
bool hasCycle(int V, vector<vector<int>> &adj) {
    vector<char> status(V);
    for (int i = 0; i < V; ++i)
        if (status[i] == UNVISITED && dfs(i, status, adj))
            return true;
    return false;
}
