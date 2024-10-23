#define mid(tl, tr) tl + (tr - tl) / 2
struct Segtree {
    vector<int> tree;
    int size;

    Segtree(const vector<int> &arr) : size(arr.size()) {
        tree.resize(size * 4);
        build(arr, 1, 0, size - 1);
    }

    void build(const vector<int> &arr, int v, int tl, int tr) {
        if (tl == tr) {
            tree[v] = arr[tl];
            return;
        }
        int mid = mid(tl, tr);
        build(arr, v << 1, tl, mid);
        build(arr, v << 1 | 1, mid + 1, tr);
        tree[v] = tree[v << 1] + tree[v << 1 | 1];
    }

    void update(int index, int val) { update(index, val, 1, 0, size - 1); }
    void update(int index, int val, int v, int tl, int tr) {
        if (tl == tr) {
            tree[v] = val;
            return;
        }

        int mid = mid(tl, tr);
        if (index <= mid)
            update(index, val, v << 1, tl, mid);
        else
            update(index, val, v << 1 | 1, mid + 1, tr);
        tree[v] = tree[v << 1] + tree[v << 1 | 1];
    }

    int query(int start, int end) { return query(start, end, 1, 0, size - 1); }

    int query(int start, int end, int v, int tl, int tr) {
        if (tr < start || tl > end)
            return 0;
        if (start <= tl && tr <= end)
            return tree[v];

        int mid = mid(tl, tr);

        return query(start, end, v << 1, tl, mid) +
               query(start, end, v << 1 | 1, mid + 1, tr);
    }
};
