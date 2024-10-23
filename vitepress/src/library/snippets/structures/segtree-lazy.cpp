struct LazySegTree {
    vector<int> tree;
    vector<int> lazy;
    int last;

    LazySegTree(const vector<int> &arr) : last(arr.size() - 1) {
        tree.resize(arr.size() * 4);
        lazy.resize(arr.size() * 4);
        build(arr, 1, 0, last);
    }
    void build(const vector<int> &arr, int v, int tl, int tr) {
        if (tl == tr) {
            tree[v] = arr[tl];
            return;
        }

        int mid = tl + (tr - tl) / 2;
        build(arr, v << 1, tl, mid);
        build(arr, v << 1 | 1, mid + 1, tr);
        tree[v] = tree[v << 1] + tree[v << 1 | 1];
    }

    void addRange(int start, int end, int val) {
        addRange(start, end, val, 1, 0, last);
    }

    void unlazy(int v, int tl, int tr) {
        tree[v] += (tr - tl + 1) * lazy[v];
        if (tl != tr) {
            lazy[v << 1] += lazy[v];
            lazy[v << 1 | 1] += lazy[v];
        }
        lazy[v] = 0;
    }
    void addRange(int start, int end, int val, int v, int tl, int tr) {
        unlazy(v, tl, tr);
        if (tl > end || tr < start)
            return;
        if (start <= tl && tr <= end) {
            lazy[v] = val;
            unlazy(v, tl, tr);
            return;
        }

        int mid = tl + (tr - tl) / 2;
        addRange(start, end, val, v << 1, tl, mid);
        addRange(start, end, val, v << 1 | 1, mid + 1, tr);
        tree[v] = tree[v << 1] + tree[v << 1 | 1];
    }

    int query(int start, int end) { return query(start, end, 1, 0, last); }
    int query(int start, int end, int v, int tl, int tr) {
        unlazy(v, tl, tr);
        if (tr < start || tl > end)
            return 0;
        if (start <= tl && tr <= end)
            return tree[v];

        int mid = tl + (tr - tl) / 2;

        return query(start, end, v << 1, tl, mid) +
               query(start, end, v << 1 | 1, mid + 1, end);
    }
};
