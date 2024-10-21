struct UnionFind {
    vector<int> arr;
    vector<int> dist;

    UnionFind(int size) {
        dist.resize(size + 1);
        arr.resize(size + 1);
        for (int i = 0; i <= size; ++i)
            arr[i] = i;
    }

    int find(int num) {
        if (arr[num] == num)
            return num;

        return arr[num] = find(arr[num]);
    }

    bool merge(int a, int b) {
        a = find(a);
        b = find(b);

        if (a == b)
            return false;

        if (dist[a] < dist[b])
            swap(dist[a], dist[b]);
        else if (dist[a] == dist[b])
            ++dist[a];
        arr[b] = a;
        return true;
    }
};
