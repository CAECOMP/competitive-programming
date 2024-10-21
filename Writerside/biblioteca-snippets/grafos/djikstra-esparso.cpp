//            cost  x     y
typedef tuple<int, int, int> costCoord;
void dijkstra(int size, vector<vector<int>> &grid) {
    const int movx[] = {1, -1, 0, 0};
    const int movy[] = {0, 0, 1, -1};
    priority_queue<costCoord, vector<costCoord>, greater<costCoord>> queue;
    queue.push({0, 0, 0});
    while (!queue.empty()) {
        auto [cost, x, y] = queue.top();
        queue.pop();
        for (int i = 0; i < 4; i++) {
            int cy = y + movy[i];
            int cx = x + movx[i];
            if (cy < 0 || cx < 0 || cy >= size || cx >= size)
                continue;
            queue.push({cost + grid[cx][cy], cx, cy});
        }
    }
}
