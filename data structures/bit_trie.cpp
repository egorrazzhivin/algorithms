const int LOG = 30;

struct bit_trie {
    struct node {
        int cnt, right, left;
        node() {
            cnt = 0;
            right = left = -1;
        }
    };
    int n, new_vertex;
    vector<node> trie;
    bit_trie (int n) {
        trie.resize(n);
        new_vertex = 1;
    }
    void insert(int x) {
        int v = 0; // current vertex
        for (int bit = LOG - 1; bit >= 0; bit--) {
            if (x & (1 << bit)) {
                // right child
                if (trie[v].right == -1) {
                    trie[v].right = new_vertex;
                    new_vertex++;
                }
                trie[trie[v].right].cnt++;
                v = trie[v].right;
            }
            else {
                // left child
                if (trie[v].left == -1) {
                    trie[v].left = new_vertex;
                    new_vertex++;
                }
                trie[trie[v].left].cnt++;
                v = trie[v].left;
            }
        }
    }
};

//bit_trie trie(n * LOG + 5);
