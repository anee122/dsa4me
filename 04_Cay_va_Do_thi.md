# HỆ THỐNG CÂY & ĐỒ THỊ

---

## PHẦN 1: BIỂU DIỄN ĐỒ THỊ

```cpp
// Cách 1: Danh sách kề (khuyên dùng cho đồ thị thưa)
vector<int> adj[MAXN];
void AddEdge(int u, int v) { adj[u].push_back(v); adj[v].push_back(u); } // vô hướng

// Cách 2: Ma trận kề (khi n nhỏ, cần kiểm tra cạnh O(1))
int adjMatrix[1005][1005];

// Cách 3: Danh sách cạnh (dùng cho Kruskal, Bellman-Ford)
struct Edge { int u, v, w; };
vector<Edge> edges;
```

---

## PHẦN 2: DUYỆT ĐỒ THỊ CƠ BẢN

### Dạng 1: DFS (Depth-First Search)

```cpp
vector<int> adj[MAXN];
bool visited[MAXN];

void DFS(int u) {
    visited[u] = true;
    // Xử lý đỉnh u ở đây (tiền thứ tự)
    for (int v : adj[u]) {
        if (!visited[v]) DFS(v);
    }
}

// Phiên bản không đệ quy dùng ngăn xếp tường minh (tránh tràn stack khi n lớn)
void DFSIterative(int start) {
    stack<int> st;
    st.push(start);
    while (!st.empty()) {
        int u = st.top(); st.pop();
        if (visited[u]) continue;
        visited[u] = true;
        for (int v : adj[u]) if (!visited[v]) st.push(v);
    }
}
```

### Dạng 2: BFS (Breadth-First Search) — đường đi ngắn nhất không trọng số

```cpp
int dist[MAXN];

void BFS(int start) {
    fill(dist, dist + MAXN, -1);
    queue<int> q;
    dist[start] = 0;
    q.push(start);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : adj[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
}
```

### Dạng 3: Đếm/liệt kê thành phần liên thông

```cpp
int CountComponents(int n) {
    fill(visited, visited + n + 1, false);
    int count = 0;
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) { DFS(i); count++; }
    }
    return count;
}
```

### Dạng 4: Kiểm tra chu trình & sắp xếp topo (Topological Sort)

```cpp
// Kahn's algorithm - dùng bậc vào (in-degree)
vector<int> TopoSort(int n) {
    vector<int> inDegree(n + 1, 0);
    for (int u = 1; u <= n; u++)
        for (int v : adj[u]) inDegree[v]++;

    queue<int> q;
    for (int i = 1; i <= n; i++) if (inDegree[i] == 0) q.push(i);

    vector<int> order;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        order.push_back(u);
        for (int v : adj[u]) {
            if (--inDegree[v] == 0) q.push(v);
        }
    }
    // Nếu order.size() < n => đồ thị có chu trình, không tồn tại thứ tự topo
    return order;
}
```

**Ứng dụng thực tế hay dùng để dạy**: lập lịch công việc có phụ thuộc (course schedule), phát hiện deadlock.

---

## PHẦN 3: CÂY (TREE)

### Dạng 5: Duyệt cây nhị phân (Binary Tree Traversal)

```cpp
struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int v) : val(v), left(nullptr), right(nullptr) {}
};

void Preorder(TreeNode* root) {   // Gốc - Trái - Phải
    if (!root) return;
    cout << root->val << " ";
    Preorder(root->left);
    Preorder(root->right);
}

void Inorder(TreeNode* root) {    // Trái - Gốc - Phải (cho BST -> thứ tự tăng dần)
    if (!root) return;
    Inorder(root->left);
    cout << root->val << " ";
    Inorder(root->right);
}

void Postorder(TreeNode* root) {  // Trái - Phải - Gốc
    if (!root) return;
    Postorder(root->left);
    Postorder(root->right);
    cout << root->val << " ";
}

void LevelOrder(TreeNode* root) { // BFS theo từng tầng
    if (!root) return;
    queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        int sz = q.size();
        for (int i = 0; i < sz; i++) {
            TreeNode* node = q.front(); q.pop();
            cout << node->val << " ";
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
        cout << "\n";
    }
}
```

### Dạng 6: Cây tìm kiếm nhị phân (Binary Search Tree - BST)

```cpp
TreeNode* Insert(TreeNode* root, int val) {
    if (!root) return new TreeNode(val);
    if (val < root->val) root->left = Insert(root->left, val);
    else root->right = Insert(root->right, val);
    return root;
}

TreeNode* Search(TreeNode* root, int val) {
    if (!root || root->val == val) return root;
    return val < root->val ? Search(root->left, val) : Search(root->right, val);
}

TreeNode* FindMin(TreeNode* root) {
    while (root->left) root = root->left;
    return root;
}

TreeNode* Delete(TreeNode* root, int val) {
    if (!root) return nullptr;
    if (val < root->val) root->left = Delete(root->left, val);
    else if (val > root->val) root->right = Delete(root->right, val);
    else {
        if (!root->left) return root->right;
        if (!root->right) return root->left;
        TreeNode* successor = FindMin(root->right);
        root->val = successor->val;
        root->right = Delete(root->right, successor->val);
    }
    return root;
}
```

**Lưu ý dạy học**: BST không cân bằng có thể suy biến thành danh sách liên kết (O(n) mỗi thao tác) — đây là lý do dẫn nhập vào cây cân bằng (AVL, Red-Black) hoặc giới thiệu `set`/`map` của STL (cài bằng Red-Black Tree, đảm bảo O(log n)).

### Dạng 7: Cây khung nhỏ nhất (Minimum Spanning Tree)

**Kruskal (dùng DSU)**:
```cpp
int parent[MAXN], rnk[MAXN];
int Find(int x) { return parent[x] == x ? x : parent[x] = Find(parent[x]); }
void Union(int x, int y) {
    x = Find(x); y = Find(y);
    if (x == y) return;
    if (rnk[x] < rnk[y]) swap(x, y);
    parent[y] = x;
    if (rnk[x] == rnk[y]) rnk[x]++;
}

long long Kruskal(int n, vector<Edge>& edges) {
    sort(edges.begin(), edges.end(), [](Edge& a, Edge& b) { return a.w < b.w; });
    for (int i = 1; i <= n; i++) { parent[i] = i; rnk[i] = 0; }
    long long total = 0;
    for (auto& e : edges) {
        if (Find(e.u) != Find(e.v)) {
            Union(e.u, e.v);
            total += e.w;
        }
    }
    return total;
}
```

**Prim (dùng priority_queue)**:
```cpp
long long Prim(int n, vector<vector<pair<int,int>>>& adjW, int start = 1) {
    vector<bool> inMST(n + 1, false);
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;
    pq.push({0, start});
    long long total = 0;
    while (!pq.empty()) {
        auto [w, u] = pq.top(); pq.pop();
        if (inMST[u]) continue;
        inMST[u] = true;
        total += w;
        for (auto [v, weight] : adjW[u])
            if (!inMST[v]) pq.push({weight, v});
    }
    return total;
}
```

### Dạng 8: LCA - Tổ tiên chung gần nhất (Lowest Common Ancestor)

```cpp
const int LOG = 20;
int up[MAXN][LOG], depth[MAXN];

void DFSBuildLCA(int u, int parent, vector<int> tree[]) {
    up[u][0] = parent;
    for (int j = 1; j < LOG; j++)
        up[u][j] = (up[u][j-1] != -1) ? up[up[u][j-1]][j-1] : -1;
    for (int v : tree[u]) {
        if (v != parent) { depth[v] = depth[u] + 1; DFSBuildLCA(v, u, tree); }
    }
}

int LCA(int u, int v) {
    if (depth[u] < depth[v]) swap(u, v);
    int diff = depth[u] - depth[v];
    for (int j = 0; j < LOG; j++)
        if ((diff >> j) & 1) u = up[u][j];
    if (u == v) return u;
    for (int j = LOG - 1; j >= 0; j--) {
        if (up[u][j] != up[v][j]) { u = up[u][j]; v = up[v][j]; }
    }
    return up[u][0];
}
```

**Kỹ thuật**: Binary Lifting — cha thứ `2^j` của một đỉnh, cho phép nhảy nhanh O(log n) thay vì đi từng bước O(n).

---

## PHẦN 4: ĐƯỜNG ĐI NGẮN NHẤT (SHORTEST PATH)

### Dạng 9: Dijkstra — đơn nguồn, trọng số không âm

```cpp
vector<pair<int,int>> adjW[MAXN]; // {đỉnh kề, trọng số}
long long dist[MAXN];

void Dijkstra(int start, int n) {
    fill(dist, dist + n + 1, LLONG_MAX);
    priority_queue<pair<long long,int>, vector<pair<long long,int>>, greater<>> pq;
    dist[start] = 0;
    pq.push({0, start});
    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (d > dist[u]) continue;   // đã có đường đi tốt hơn, bỏ qua
        for (auto [v, w] : adjW[u]) {
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
}
```

### Dạng 10: Bellman-Ford — cho phép trọng số âm, phát hiện chu trình âm

```cpp
bool BellmanFord(int n, vector<Edge>& edges, int start, vector<long long>& dist) {
    dist.assign(n + 1, LLONG_MAX);
    dist[start] = 0;
    for (int i = 1; i <= n - 1; i++) {
        for (auto& e : edges) {
            if (dist[e.u] != LLONG_MAX && dist[e.u] + e.w < dist[e.v])
                dist[e.v] = dist[e.u] + e.w;
        }
    }
    // Vòng lặp thứ n: nếu vẫn còn cập nhật được => có chu trình âm
    for (auto& e : edges) {
        if (dist[e.u] != LLONG_MAX && dist[e.u] + e.w < dist[e.v])
            return false; // tồn tại chu trình âm
    }
    return true;
}
```

### Dạng 11: Floyd-Warshall — toàn cặp đỉnh (All-Pairs Shortest Path)

```cpp
long long d[505][505];

void FloydWarshall(int n) {
    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                if (d[i][k] < LLONG_MAX && d[k][j] < LLONG_MAX)
                    d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
}
```

**Bảng lựa chọn thuật toán đường đi ngắn nhất**:

| Tình huống | Thuật toán | Độ phức tạp |
|---|---|---|
| Đơn nguồn, không trọng số | BFS | O(V + E) |
| Đơn nguồn, trọng số không âm | Dijkstra (heap) | O((V+E) log V) |
| Đơn nguồn, có trọng số âm | Bellman-Ford | O(V·E) |
| Toàn cặp đỉnh, n nhỏ (≤ 500) | Floyd-Warshall | O(V³) |
| Toàn cặp đỉnh, đồ thị thưa | Chạy Dijkstra từ mỗi đỉnh | O(V·(V+E) log V) |

---

## PHẦN 5: CÁC BÀI TOÁN ĐỒ THỊ NÂNG CAO KHÁC

### Dạng 12: Luồng cực đại (Max Flow) — Ford-Fulkerson / Edmonds-Karp

```cpp
int capacity_[105][105];
bool visitedFlow[105];

bool BFSFindPath(int s, int t, int n, vector<int>& parent) {
    fill(visitedFlow, visitedFlow + n + 1, false);
    queue<int> q; q.push(s); visitedFlow[s] = true; parent[s] = -1;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v = 1; v <= n; v++) {
            if (!visitedFlow[v] && capacity_[u][v] > 0) {
                parent[v] = u; visitedFlow[v] = true;
                if (v == t) return true;
                q.push(v);
            }
        }
    }
    return false;
}

int EdmondsKarp(int s, int t, int n) {
    int maxFlow = 0;
    vector<int> parent(n + 1);
    while (BFSFindPath(s, t, n, parent)) {
        int pathFlow = INT_MAX;
        for (int v = t; v != s; v = parent[v])
            pathFlow = min(pathFlow, capacity_[parent[v]][v]);
        for (int v = t; v != s; v = parent[v]) {
            capacity_[parent[v]][v] -= pathFlow;
            capacity_[v][parent[v]] += pathFlow;
        }
        maxFlow += pathFlow;
    }
    return maxFlow;
}
```

### Dạng 13: Kiểm tra đồ thị hai phía (Bipartite Check) bằng tô màu 2 màu

```cpp
int color[MAXN]; // -1: chưa tô, 0/1: hai màu

bool IsBipartite(int n) {
    fill(color, color + n + 1, -1);
    for (int start = 1; start <= n; start++) {
        if (color[start] != -1) continue;
        queue<int> q; q.push(start); color[start] = 0;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : adj[u]) {
                if (color[v] == -1) { color[v] = 1 - color[u]; q.push(v); }
                else if (color[v] == color[u]) return false;
            }
        }
    }
    return true;
}
```

### Dạng 14: Thành phần liên thông mạnh (Strongly Connected Components - Tarjan)

```cpp
int disc[MAXN], low[MAXN], sccId[MAXN], idx_ = 0, sccCount = 0;
bool onStack[MAXN];
stack<int> stck;

void TarjanSCC(int u) {
    disc[u] = low[u] = idx_++;
    stck.push(u); onStack[u] = true;
    for (int v : adj[u]) {
        if (disc[v] == -1) {
            TarjanSCC(v);
            low[u] = min(low[u], low[v]);
        } else if (onStack[v]) {
            low[u] = min(low[u], disc[v]);
        }
    }
    if (low[u] == disc[u]) {
        while (true) {
            int v = stck.top(); stck.pop(); onStack[v] = false;
            sccId[v] = sccCount;
            if (v == u) break;
        }
        sccCount++;
    }
}
```

---

## PHẦN 6: BẢNG NHẬN DẠNG DẠNG BÀI

| Dấu hiệu đề bài | Kỹ thuật |
|---|---|
| "Đường đi ngắn nhất giữa 2 đỉnh, không trọng số" | BFS |
| "Đường đi ngắn nhất, trọng số dương" | Dijkstra |
| "Có cạnh trọng số âm" | Bellman-Ford |
| "Nhiều truy vấn khoảng cách giữa các cặp đỉnh" | Floyd-Warshall / tiền xử lý LCA |
| "Kết nối tất cả với tổng chi phí nhỏ nhất" | Kruskal / Prim (MST) |
| "Xếp lịch có phụ thuộc" | Topological Sort |
| "Chia thành 2 nhóm không xung đột" | Kiểm tra Bipartite |
| "Luồng tối đa / ghép cặp tối đa" | Max Flow |
| "Tổ tiên chung / truy vấn trên cây nhiều lần" | LCA + Binary Lifting |
| "Nhóm các đỉnh có thể đi qua lại lẫn nhau" | SCC (Tarjan/Kosaraju) |

---

*Phong cách trình bày tham khảo: Cẩm nang thuật toán – Lê Minh Hoàng.*
