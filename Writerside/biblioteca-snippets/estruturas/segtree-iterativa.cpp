struct IterativeSegtree {
    vector<int> tree;
    int size;

    IterativeSegtree(const vector<int> &orig) : size(orig.size()) {
        for (int i = 0; i < size; ++i)
            tree[i + size] = orig[i];
        for (int i = size - 1; i > 0; --i)
            tree[i] = tree[i << 1] + tree[i << 1 | 1];
    }

    void update(int index, int val) {
        for (tree[index += size] = val; index > 1; index >>= 1)
            tree[index >> 1] = tree[index] + tree[index ^ 1];
    }

    int query(int start, int end) {
        int val = 0;
        for (start += size, end += size; start <= end; start >>= 1, end >>= 1) {
            if (start & 1)
                val += tree[start++];
            if (!(end & 1))
                val += tree[end--];
        }
        return val;
    }
};
