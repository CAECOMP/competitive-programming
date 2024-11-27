void bellman_ford(vector<tuple<int, int, int>> &graph, int vertices, int src) {
    const int inf = INT_MAX;
    vector<int> dist(vertices, inf);
    dist[src] = 0;
    for (int i = 0; i < vertices - 1; i++)
        for (auto [cost, from, to] : graph) {
            if (dist[from] != inf && (dist[from] + cost) < dist[to])
                dist[to] = dist[from] + cost;
        }
    // Checkando se tem algum ciclo de peso negativo
    for (auto [cost, from, to] : graph) {
        if (dist[from] != inf && (dist[from] + cost) < dist[to]) {
            cout << "lascou" << endl;
            return;
        }
    }
    for (int i = 0; i < vertices; i++)
        cout << i << "\t\t" << dist[i] << endl;
}
