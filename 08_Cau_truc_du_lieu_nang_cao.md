# HỆ THỐNG CẤU TRÚC DỮ LIỆU NÂNG CAO

---

## PHẦN 1: CÂY PHÂN ĐOẠN (SEGMENT TREE)

### Dạng 1: Segment Tree cơ bản — truy vấn tổng/min/max trên đoạn

```cpp
class SegmentTree {
    vector<long long> tree;
    int n;
public:
    SegmentTree(int size) : n(size) { tree.assign(4 * n, 0); }

    void Build(vector<long long>& a, int node, int l, int r) {
        if (l == r) { tree[node] = a[l]; return; }
        int mid = (l + r) / 2;
        Build(a, node*2, l, mid);
        Build(a, node*2+1, mid+1, r);
        tree[node] = tree[node*2] + tree[node*2+1]; // tổng đoạn, đổi thành min/max tùy bài
    }

    void Update(int node, int l, int r, int pos, long long val) {
        if (l == r) { tree[node] = val; return; }
        int mid = (l + r) / 2;
        if (pos <= mid) Update(node*2, l, mid, pos, val);
        else Update(node*2+1, mid+1, r, pos, val);
        tree[node] = tree[node*2] + tree[node*2+1];
    }

    long long Query(int node, int l, int r, int ql, int qr) {
        if (qr < l || r < ql) return 0;         // ngoài phạm vi -> phần tử trung tính
        if (ql <= l && r <= qr) return tree[node];
        int mid = (l + r) / 2;
        return Query(node*2, l, mid, ql, qr) + Query(node*2+1, mid+1, r, ql, qr);
    }
};
```

**Độ phức tạp**: xây dựng O(n), truy vấn/cập nhật O(log n) mỗi lần — vượt trội hoàn toàn so với Prefix Sum khi có cả cập nhật lẫn truy vấn xen kẽ.

### Dạng 2: Segment Tree với Lazy Propagation — cập nhật khoảng, truy vấn khoảng

```cpp
class SegmentTreeLazy {
    vector<long long> tree, lazy;
    int n;
public:
    SegmentTreeLazy(int size) : n(size) {
        tree.assign(4 * n, 0);
        lazy.assign(4 * n, 0);
    }

    void Push(int node, int l, int r) {
        if (lazy[node] != 0) {
            tree[node] += (r - l + 1) * lazy[node];
            if (l != r) {
                lazy[node*2] += lazy[node];
                lazy[node*2+1] += lazy[node];
            }
            lazy[node] = 0;
        }
    }

    void UpdateRange(int node, int l, int r, int ql, int qr, long long val) {
        Push(node, l, r);
        if (qr < l || r < ql) return;
        if (ql <= l && r <= qr) {
            lazy[node] += val;
            Push(node, l, r);
            return;
        }
        int mid = (l + r) / 2;
        UpdateRange(node*2, l, mid, ql, qr, val);
        UpdateRange(node*2+1, mid+1, r, ql, qr, val);
        tree[node] = tree[node*2] + tree[node*2+1];
    }

    long long QueryRange(int node, int l, int r, int ql, int qr) {
        Push(node, l, r);
        if (qr < l || r < ql) return 0;
        if (ql <= l && r <= qr) return tree[node];
        int mid = (l + r) / 2;
        return QueryRange(node*2, l, mid, ql, qr) + QueryRange(node*2+1, mid+1, r, ql, qr);
    }
};
```

**Lưu ý dạy học**: Lazy Propagation là kỹ thuật khó nhất trong nhóm cấu trúc dữ liệu nâng cao — nên minh hoạ bằng hình vẽ cây và nhấn mạnh nguyên lý "trì hoãn cập nhật xuống con cho đến khi thực sự cần".

### Dạng 3: Persistent Segment Tree (Cây phân đoạn bền vững) — giới thiệu khái niệm

Dùng khi cần lưu lại **lịch sử các phiên bản** của cây sau mỗi lần cập nhật (ví dụ truy vấn "giá trị tại thời điểm t"). Ý tưởng: mỗi lần cập nhật chỉ tạo mới O(log n) node dọc theo đường đi thay vì copy toàn bộ cây.

```cpp
struct Node { int val; Node *left, *right; };
Node* roots[MAXN]; // roots[t] = gốc cây tại phiên bản thời điểm t

Node* Update(Node* prev, int l, int r, int pos, int val) {
    if (l == r) return new Node{val, nullptr, nullptr};
    int mid = (l + r) / 2;
    Node* newNode = new Node{0, prev->left, prev->right};
    if (pos <= mid) newNode->left = Update(prev->left, l, mid, pos, val);
    else newNode->right = Update(prev->right, mid+1, r, pos, val);
    return newNode;
}
```

---

## PHẦN 2: CÂY CHỈ SỐ NHỊ PHÂN (BINARY INDEXED TREE / FENWICK TREE)

### Dạng 4: BIT cơ bản — tổng tiền tố, cập nhật điểm

```cpp
class Fenwick {
    vector<long long> bit;
    int n;
public:
    Fenwick(int size) : n(size) { bit.assign(n + 1, 0); }

    void Update(int pos, long long val) {
        for (; pos <= n; pos += pos & (-pos))
            bit[pos] += val;
    }

    long long Query(int pos) { // tổng từ 1 đến pos
        long long sum = 0;
        for (; pos > 0; pos -= pos & (-pos))
            sum += bit[pos];
        return sum;
    }

    long long RangeQuery(int l, int r) { return Query(r) - Query(l - 1); }
};
```

**Ưu điểm so với Segment Tree**: code ngắn hơn nhiều, hằng số nhỏ hơn, dễ cài đặt hơn — nên dạy BIT trước Segment Tree ở mức nhập môn, chỉ chuyển sang Segment Tree khi cần truy vấn phức tạp hơn (min/max, lazy propagation).

### Dạng 5: BIT cho cập nhật khoảng, truy vấn điểm (dùng mảng sai phân + BIT)

```cpp
Fenwick fen(MAXN);
void UpdateRange(int l, int r, long long val) {
    fen.Update(l, val);
    fen.Update(r + 1, -val);
}
long long QueryPoint(int pos) { return fen.Query(pos); }
```

### Dạng 6: BIT 2 chiều (2D Fenwick) — truy vấn tổng trên hình chữ nhật

```cpp
class Fenwick2D {
    vector<vector<long long>> bit;
    int n, m;
public:
    Fenwick2D(int rows, int cols) : n(rows), m(cols) {
        bit.assign(n + 1, vector<long long>(m + 1, 0));
    }
    void Update(int x, int y, long long val) {
        for (int i = x; i <= n; i += i & (-i))
            for (int j = y; j <= m; j += j & (-j))
                bit[i][j] += val;
    }
    long long Query(int x, int y) {
        long long sum = 0;
        for (int i = x; i > 0; i -= i & (-i))
            for (int j = y; j > 0; j -= j & (-j))
                sum += bit[i][j];
        return sum;
    }
};
```

### Dạng 7: BIT để đếm nghịch thế / tìm phần tử thứ k (kết hợp nén tọa độ)

```cpp
// Đếm nghịch thế bằng BIT thay vì Merge Sort - O(n log n)
long long CountInversionsBIT(vector<int>& a) {
    vector<int> sorted_a = a;
    sort(sorted_a.begin(), sorted_a.end());
    sorted_a.erase(unique(sorted_a.begin(), sorted_a.end()), sorted_a.end());

    Fenwick fen(sorted_a.size());
    long long inversions = 0;
    for (int i = a.size() - 1; i >= 0; i--) {
        int rank = lower_bound(sorted_a.begin(), sorted_a.end(), a[i]) - sorted_a.begin() + 1;
        inversions += fen.Query(rank - 1); // đếm số phần tử nhỏ hơn đã xuất hiện bên phải
        fen.Update(rank, 1);
    }
    return inversions;
}
```

---

## PHẦN 3: HỢP - TÌM (DISJOINT SET UNION / UNION-FIND)

### Dạng 8: DSU với nén đường dẫn + hợp theo hạng (Union by Rank/Size)

```cpp
class DSU {
    vector<int> parent, rnk;
public:
    DSU(int n) {
        parent.resize(n + 1);
        rnk.assign(n + 1, 0);
        iota(parent.begin(), parent.end(), 0);
    }

    int Find(int x) {
        if (parent[x] != x) parent[x] = Find(parent[x]); // nén đường dẫn
        return parent[x];
    }

    bool Union(int x, int y) {
        int rx = Find(x), ry = Find(y);
        if (rx == ry) return false; // đã cùng tập hợp
        if (rnk[rx] < rnk[ry]) swap(rx, ry);
        parent[ry] = rx;
        if (rnk[rx] == rnk[ry]) rnk[rx]++;
        return true;
    }
};
```

**Độ phức tạp**: gần như O(1) mỗi thao tác (chính xác là O(α(n)) với α là hàm Ackermann ngược, tăng cực chậm).

### Dạng 9: Ứng dụng DSU — Kiểm tra chu trình, kết nối động (Kruskal đã trình bày ở file Cây & Đồ thị)

**Ứng dụng bổ sung — DSU có trọng số (Weighted Union-Find)**: lưu thêm khoảng cách/quan hệ giữa node và cha, dùng cho bài toán kiểm tra quan hệ tương đối (ví dụ bài toán "kiểm tra hệ phương trình chênh lệch có mâu thuẫn không").

```cpp
vector<int> parent, weight; // weight[x] = quan hệ giữa x và parent[x]

int FindWeighted(int x) {
    if (parent[x] == x) return x;
    int root = FindWeighted(parent[x]);
    weight[x] += weight[parent[x]];  // cộng dồn quan hệ dọc đường nén
    parent[x] = root;
    return root;
}
```

---

## PHẦN 4: CẤU TRÚC XÂU NÂNG CAO

### Dạng 10: Trie (Cây tiền tố)

```cpp
struct TrieNode {
    TrieNode* children[26];
    bool isEnd;
    TrieNode() { isEnd = false; fill(children, children + 26, nullptr); }
};

class Trie {
    TrieNode* root;
public:
    Trie() { root = new TrieNode(); }

    void Insert(string word) {
        TrieNode* node = root;
        for (char c : word) {
            int idx = c - 'a';
            if (!node->children[idx]) node->children[idx] = new TrieNode();
            node = node->children[idx];
        }
        node->isEnd = true;
    }

    bool Search(string word) {
        TrieNode* node = root;
        for (char c : word) {
            int idx = c - 'a';
            if (!node->children[idx]) return false;
            node = node->children[idx];
        }
        return node->isEnd;
    }

    bool StartsWith(string prefix) {
        TrieNode* node = root;
        for (char c : prefix) {
            int idx = c - 'a';
            if (!node->children[idx]) return false;
            node = node->children[idx];
        }
        return true;
    }
};
```

**Ứng dụng mở rộng**: Trie nhị phân (Binary Trie) cho bài toán XOR lớn nhất giữa 2 phần tử trong mảng — kỹ thuật CP hay gặp.

### Dạng 11: KMP (Knuth-Morris-Pratt) — tìm kiếm chuỗi con O(n + m)

```cpp
vector<int> BuildLPS(string& pattern) {
    int m = pattern.size();
    vector<int> lps(m, 0);
    int len = 0, i = 1;
    while (i < m) {
        if (pattern[i] == pattern[len]) lps[i++] = ++len;
        else if (len > 0) len = lps[len - 1];
        else lps[i++] = 0;
    }
    return lps;
}

vector<int> KMPSearch(string& text, string& pattern) {
    vector<int> lps = BuildLPS(pattern);
    vector<int> occurrences;
    int i = 0, j = 0;
    while (i < (int)text.size()) {
        if (text[i] == pattern[j]) { i++; j++; }
        if (j == (int)pattern.size()) {
            occurrences.push_back(i - j);
            j = lps[j - 1];
        } else if (i < (int)text.size() && text[i] != pattern[j]) {
            if (j > 0) j = lps[j - 1];
            else i++;
        }
    }
    return occurrences;
}
```

### Dạng 12: Băm chuỗi (String Hashing) — so sánh xâu con O(1) sau tiền xử lý

```cpp
const long long MOD = 1e9 + 7, BASE = 131;
vector<long long> hashArr, powArr;

void BuildHash(string& s) {
    int n = s.size();
    hashArr.assign(n + 1, 0);
    powArr.assign(n + 1, 1);
    for (int i = 0; i < n; i++) {
        hashArr[i+1] = (hashArr[i] * BASE + s[i]) % MOD;
        powArr[i+1] = (powArr[i] * BASE) % MOD;
    }
}

long long GetHash(int l, int r) { // hash đoạn [l, r], 0-indexed
    long long result = (hashArr[r+1] - hashArr[l] * powArr[r-l+1]) % MOD;
    return (result + MOD) % MOD;
}
```

**Lưu ý dạy học**: nên dùng double hashing (2 bộ MOD/BASE khác nhau) trong các bài thi để giảm nguy cơ bị đánh sập bằng test đối kháng (anti-hash test).

---

## PHẦN 5: CẤU TRÚC DỮ LIỆU CHO BÀI TOÁN TRUY VẤN TĨNH

### Dạng 13: Sparse Table — truy vấn min/max/gcd trên đoạn, KHÔNG cập nhật, O(1) mỗi truy vấn

```cpp
int sparse[MAXN][20];
int logTable[MAXN];

void BuildSparseTable(vector<int>& a) {
    int n = a.size();
    logTable[1] = 0;
    for (int i = 2; i <= n; i++) logTable[i] = logTable[i/2] + 1;

    for (int i = 0; i < n; i++) sparse[i][0] = a[i];
    for (int j = 1; (1 << j) <= n; j++)
        for (int i = 0; i + (1 << j) - 1 < n; i++)
            sparse[i][j] = min(sparse[i][j-1], sparse[i + (1 << (j-1))][j-1]);
}

int QueryMin(int l, int r) { // truy vấn O(1), 0-indexed
    int j = logTable[r - l + 1];
    return min(sparse[l][j], sparse[r - (1 << j) + 1][j]);
}
```

**Điểm mấu chốt để giảng**: Sparse Table chỉ áp dụng được cho các phép toán "idempotent" (min, max, gcd, and, or — lặp lại không đổi kết quả), **không dùng được cho tổng** (vì các đoạn chồng lấn sẽ tính trùng phần tử).

---

## PHẦN 6: BẢNG NHẬN DẠNG DẠNG BÀI

| Dấu hiệu đề bài | Cấu trúc dữ liệu | Độ phức tạp |
|---|---|---|
| Cập nhật điểm + truy vấn tổng đoạn, nhiều lần | Fenwick Tree (BIT) | O(log n) |
| Cập nhật điểm + truy vấn min/max/phức tạp hơn | Segment Tree | O(log n) |
| Cập nhật CẢ ĐOẠN + truy vấn đoạn | Segment Tree + Lazy | O(log n) |
| Truy vấn đoạn KHÔNG cập nhật | Sparse Table | O(1) mỗi truy vấn |
| Truy vấn "phiên bản cũ" của mảng theo thời gian | Persistent Segment Tree | O(log n) |
| Kiểm tra/hợp nhất các nhóm phần tử động | DSU (Union-Find) | ~O(1) |
| Tìm kiếm/đếm tiền tố chuỗi | Trie | O(độ dài xâu) |
| Tìm kiếm mẫu trong văn bản | KMP | O(n + m) |
| So sánh nhanh nhiều xâu con | String Hashing | O(1) sau O(n) tiền xử lý |
| Đếm nghịch thế / phần tử theo thứ hạng | BIT + nén tọa độ | O(n log n) |

---

## PHẦN 7: LỖI THƯỜNG GẶP KHI DẠY

1. **Nhầm giữa BIT và Segment Tree** khi nào nên dùng cái nào — nên nhấn mạnh BIT chỉ tự nhiên cho phép toán có "phép nghịch đảo" (như tổng, trừ được), còn Segment Tree tổng quát hơn cho min/max.
2. **Quên `Push` lazy trước khi đọc/ghi node** trong Segment Tree Lazy — lỗi runtime khó phát hiện nhất khi dạy.
3. **Chỉ số 0-based vs 1-based lẫn lộn** giữa BIT (thường 1-based bắt buộc vì dùng `x & (-x)`) và Segment Tree (linh hoạt cả hai).
4. **Dùng Sparse Table cho phép toán tổng** — lỗi khái niệm phổ biến, cần nhấn mạnh tính chất idempotent.
5. **Không nén tọa độ trước khi dùng BIT/Segment Tree** khi giá trị phần tử quá lớn so với bộ nhớ cho phép.

---

*Phong cách trình bày tham khảo: Cẩm nang thuật toán – Lê Minh Hoàng.*
