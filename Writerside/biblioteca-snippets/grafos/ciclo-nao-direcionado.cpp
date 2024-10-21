bool hasCycle(int V, vector<int> adj[]) {
    UnionFind DSU(V);

    set<pair<int, int>> visited;

    for (int i = 0; i < V; ++i) {
        vector<int> v = adj[i];
        for (int j = 0; j < v.size(); ++j) {
            if (visited.count({i, v[j]}) || visited.count({v[j], i}))
                continue;
            visited.insert({i, v[j]});
            if (DSU.merge(i, v[j]))
                return true;
        }
    }

    return false;
}
