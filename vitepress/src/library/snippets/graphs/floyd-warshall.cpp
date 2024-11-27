void floyd_warshall() {
    const int inf = INT_MAX;
    int size = 20;
    int dist[size][size];
    for (int mid = 0; mid < size; ++mid)
        for (int from = 0; from < size; ++from)
            if (dist[from][mid] < inf)
                for (int to = 0; to < size; ++to)
                    if (dist[mid][to] < inf)
                        dist[from][to] = min(dist[from][to],
                                             dist[from][mid] + dist[mid][to]);
}
