# HỆ THỐNG QUY HOẠCH ĐỘNG (DYNAMIC PROGRAMMING)

---

## PHẦN 1: TƯ TƯỞNG CHUNG VÀ QUY TRÌNH GIẢI

Một bài QHĐ luôn cần xác định 4 thành phần:
1. **Trạng thái (state)**: `dp[i]` hoặc `dp[i][j]` biểu diễn điều gì?
2. **Công thức truy hồi (transition)**: `dp[i]` được tính từ những trạng thái nào trước đó?
3. **Trạng thái cơ sở (base case)**: giá trị khởi tạo.
4. **Thứ tự tính** (và đôi khi cần khôi phục lời giải — truy vết/trace).

**Hai cách cài đặt**:
- **Top-down (nhớ hóa - memoization)**: đệ quy + mảng nhớ, dễ tư duy hơn.
- **Bottom-up (bảng - tabulation)**: vòng lặp, nhanh hơn, không tốn ngăn xếp đệ quy.

```cpp
// Top-down mẫu
int memo[MAXN];
bool computed[MAXN];
int Solve(int state) {
    if (/* base case */) return baseValue;
    if (computed[state]) return memo[state];
    computed[state] = true;
    return memo[state] = /* công thức truy hồi, gọi đệ quy Solve(...) */ 0;
}
```

---

## PHẦN 2: DP TRÊN DÃY SỐ (1 CHIỀU)

### Dạng 1: Dãy Fibonacci / Bài toán leo cầu thang (Climbing Stairs)

```cpp
long long ClimbStairs(int n) {
    if (n <= 2) return n;
    vector<long long> dp(n + 1);
    dp[1] = 1; dp[2] = 2;
    for (int i = 3; i <= n; i++) dp[i] = dp[i-1] + dp[i-2];
    return dp[n];
}
```

### Dạng 2: Dãy con tăng dài nhất (LIS) — O(n²) và O(n log n)

```cpp
int LIS_On2(vector<int>& a) {
    int n = a.size();
    vector<int> dp(n, 1); // dp[i] = độ dài LIS kết thúc tại i
    int best = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (a[j] < a[i]) dp[i] = max(dp[i], dp[j] + 1);
        }
        best = max(best, dp[i]);
    }
    return best;
}
// Bản O(n log n) dùng lower_bound đã trình bày ở file Sắp xếp - Tìm kiếm, Dạng 6
```

### Dạng 3: Tổng con lớn nhất (Maximum Subarray Sum - Kadane)

```cpp
long long MaxSubarraySum(vector<int>& a) {
    long long best = a[0], curSum = a[0];
    for (int i = 1; i < (int)a.size(); i++) {
        curSum = max((long long)a[i], curSum + a[i]);
        best = max(best, curSum);
    }
    return best;
}
```

### Dạng 4: Bài toán Cắt thanh gỗ / Chia tối ưu 1 chiều (Rod Cutting)

```cpp
int RodCutting(vector<int>& price, int n) {
    vector<int> dp(n + 1, 0);
    for (int len = 1; len <= n; len++) {
        for (int cut = 1; cut <= len; cut++) {
            dp[len] = max(dp[len], price[cut] + dp[len - cut]);
        }
    }
    return dp[n];
}
```

---

## PHẦN 3: DP TRÊN 2 DÃY (LCS / EDIT DISTANCE)

### Dạng 5: Dãy con chung dài nhất (Longest Common Subsequence - LCS)

```cpp
int LCS(string& a, string& b) {
    int n = a.size(), m = b.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (a[i-1] == b[j-1]) dp[i][j] = dp[i-1][j-1] + 1;
            else dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
        }
    }
    return dp[n][m];
}
```

### Dạng 6: Khoảng cách chỉnh sửa (Edit Distance - Levenshtein)

```cpp
int EditDistance(string& a, string& b) {
    int n = a.size(), m = b.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1));
    for (int i = 0; i <= n; i++) dp[i][0] = i;
    for (int j = 0; j <= m; j++) dp[0][j] = j;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (a[i-1] == b[j-1]) dp[i][j] = dp[i-1][j-1];
            else dp[i][j] = 1 + min({dp[i-1][j], dp[i][j-1], dp[i-1][j-1]});
            // dp[i-1][j]: xoá, dp[i][j-1]: chèn, dp[i-1][j-1]: thay thế
        }
    }
    return dp[n][m];
}
```

### Dạng 7: Xâu con đối xứng dài nhất (Longest Palindromic Substring)

```cpp
string LongestPalindrome(string s) {
    int n = s.size();
    vector<vector<bool>> dp(n, vector<bool>(n, false));
    int start = 0, maxLen = 1;
    for (int i = 0; i < n; i++) dp[i][i] = true;
    for (int len = 2; len <= n; len++) {
        for (int i = 0; i + len - 1 < n; i++) {
            int j = i + len - 1;
            if (s[i] == s[j] && (len == 2 || dp[i+1][j-1])) {
                dp[i][j] = true;
                if (len > maxLen) { start = i; maxLen = len; }
            }
        }
    }
    return s.substr(start, maxLen);
}
```

---

## PHẦN 4: DP TRÊN CÁI TÚI (KNAPSACK FAMILY)

### Dạng 8: Cái túi 0/1 (0/1 Knapsack)

```cpp
int Knapsack01(vector<int>& w, vector<int>& v, int W) {
    int n = w.size();
    vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));
    for (int i = 1; i <= n; i++) {
        for (int cap = 0; cap <= W; cap++) {
            dp[i][cap] = dp[i-1][cap]; // không lấy vật i
            if (cap >= w[i-1])
                dp[i][cap] = max(dp[i][cap], dp[i-1][cap - w[i-1]] + v[i-1]); // lấy vật i
        }
    }
    return dp[n][W];
}

// Tối ưu bộ nhớ O(W) — DUYỆT NGƯỢC vì mỗi vật chỉ dùng 1 lần
int Knapsack01_Optimized(vector<int>& w, vector<int>& v, int W) {
    vector<int> dp(W + 1, 0);
    for (int i = 0; i < (int)w.size(); i++) {
        for (int cap = W; cap >= w[i]; cap--) {
            dp[cap] = max(dp[cap], dp[cap - w[i]] + v[i]);
        }
    }
    return dp[W];
}
```

### Dạng 9: Cái túi không giới hạn (Unbounded Knapsack)

```cpp
int UnboundedKnapsack(vector<int>& w, vector<int>& v, int W) {
    vector<int> dp(W + 1, 0);
    for (int cap = 1; cap <= W; cap++) {
        // DUYỆT XUÔI vì mỗi vật có thể dùng nhiều lần
        for (int i = 0; i < (int)w.size(); i++) {
            if (cap >= w[i]) dp[cap] = max(dp[cap], dp[cap - w[i]] + v[i]);
        }
    }
    return dp[W];
}
```

**Điểm mấu chốt để giảng**: chiều duyệt của biến `cap` (ngược cho 0/1, xuôi cho Unbounded) là điểm sinh viên hay nhầm nhất — nên minh hoạ bằng ví dụ cụ thể để thấy rõ tại sao duyệt xuôi sẽ dùng lại 1 vật nhiều lần.

### Dạng 10: Đếm số cách đạt tổng cho trước (Subset Sum Counting / Coin Change)

```cpp
long long CoinChangeWays(vector<int>& coins, int target) {
    vector<long long> dp(target + 1, 0);
    dp[0] = 1;
    for (int c : coins) {
        for (int cap = c; cap <= target; cap++) {
            dp[cap] += dp[cap - c];
        }
    }
    return dp[target];
}

int CoinChangeMinCoins(vector<int>& coins, int target) {
    vector<int> dp(target + 1, INT_MAX);
    dp[0] = 0;
    for (int cap = 1; cap <= target; cap++) {
        for (int c : coins) {
            if (cap >= c && dp[cap - c] != INT_MAX)
                dp[cap] = min(dp[cap], dp[cap - c] + 1);
        }
    }
    return dp[target] == INT_MAX ? -1 : dp[target];
}
```

---

## PHẦN 5: DP TRÊN KHOẢNG (INTERVAL DP)

### Dạng 11: Nhân ma trận dây chuyền (Matrix Chain Multiplication)

```cpp
int MatrixChainOrder(vector<int>& p) { // p có n+1 phần tử cho n ma trận
    int n = p.size() - 1;
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
    for (int len = 2; len <= n; len++) {
        for (int i = 1; i <= n - len + 1; i++) {
            int j = i + len - 1;
            dp[i][j] = INT_MAX;
            for (int k = i; k < j; k++) {
                int cost = dp[i][k] + dp[k+1][j] + p[i-1] * p[k] * p[j];
                dp[i][j] = min(dp[i][j], cost);
            }
        }
    }
    return dp[1][n];
}
```

### Dạng 12: Trò chơi lấy sỏi/tối ưu khoảng chung (Interval DP tổng quát)

**Khuôn mẫu chung cho DP khoảng**:
```cpp
// dp[i][j] = giá trị tối ưu trên đoạn [i, j]
for (int len = 2; len <= n; len++) {
    for (int i = 1; i + len - 1 <= n; i++) {
        int j = i + len - 1;
        for (int k = i; k < j; k++) {
            // dp[i][j] = tối ưu(dp[i][k] + dp[k+1][j] + chi_phi_gop(i, k, j));
        }
    }
}
```

**Ứng dụng kinh điển khác**: bài toán tam giác phân đa giác lồi tối ưu (Optimal Polygon Triangulation), bài toán đốt pháo bóng bay (Burst Balloons).

---

## PHẦN 6: DP TRÊN BITMASK (TRẠNG THÁI TẬP HỢP)

### Dạng 13: Bài toán người du lịch bằng DP Bitmask (TSP chính xác)

```cpp
const int INF = 1e9;
int dp_[1 << 20][20]; // dp[mask][i] = chi phí nhỏ nhất thăm hết các đỉnh trong mask, đang ở i
int dist_[20][20];

int TSP_Bitmask(int n) {
    for (int mask = 0; mask < (1 << n); mask++)
        fill(dp_[mask], dp_[mask] + n, INF);
    dp_[1][0] = 0; // bắt đầu tại đỉnh 0, mask chỉ chứa đỉnh 0

    for (int mask = 1; mask < (1 << n); mask++) {
        for (int u = 0; u < n; u++) {
            if (!(mask & (1 << u)) || dp_[mask][u] == INF) continue;
            for (int v = 0; v < n; v++) {
                if (mask & (1 << v)) continue;
                int newMask = mask | (1 << v);
                dp_[newMask][v] = min(dp_[newMask][v], dp_[mask][u] + dist_[u][v]);
            }
        }
    }
    int result = INF;
    for (int u = 1; u < n; u++)
        if (dp_[(1<<n) - 1][u] != INF)
            result = min(result, dp_[(1<<n) - 1][u] + dist_[u][0]);
    return result;
}
```

**Độ phức tạp**: O(n² · 2ⁿ) — khả thi khi n ≤ 20, vượt trội hoàn toàn so với duyệt vét cạn O(n!) hay nhánh cận trong trường hợp xấu nhất.

### Dạng 14: Bài toán phân công công việc (Assignment Problem) bằng Bitmask

```cpp
int dpAssign[1 << 20];
int cost[20][20]; // cost[i][j] = chi phí gán người i cho việc j

int AssignmentDP(int n) {
    fill(dpAssign, dpAssign + (1 << n), INF);
    dpAssign[0] = 0;
    for (int mask = 0; mask < (1 << n); mask++) {
        if (dpAssign[mask] == INF) continue;
        int person = __builtin_popcount(mask); // đã gán 'person' người, xét người tiếp theo
        if (person >= n) continue;
        for (int job = 0; job < n; job++) {
            if (mask & (1 << job)) continue;
            int newMask = mask | (1 << job);
            dpAssign[newMask] = min(dpAssign[newMask], dpAssign[mask] + cost[person][job]);
        }
    }
    return dpAssign[(1 << n) - 1];
}
```

---

## PHẦN 7: DP TRÊN CÂY (TREE DP)

### Dạng 15: Tập độc lập lớn nhất trên cây (Maximum Independent Set on Tree)

**Ứng dụng thực tế**: bài toán "chọn tập nhân viên tổ chức tiệc sao cho không ai chọn cùng sếp trực tiếp" (kinh điển).

```cpp
int dpIn[MAXN], dpOut[MAXN]; // dpIn[u]: giá trị tốt nhất khi CHỌN u, dpOut[u]: khi KHÔNG chọn u
int value_[MAXN];
vector<int> tree[MAXN];

void DFS_TreeDP(int u, int parent) {
    dpIn[u] = value_[u];
    dpOut[u] = 0;
    for (int v : tree[u]) {
        if (v == parent) continue;
        DFS_TreeDP(v, u);
        dpIn[u] += dpOut[v];                     // đã chọn u -> con không được chọn
        dpOut[u] += max(dpIn[v], dpOut[v]);        // không chọn u -> con tuỳ ý
    }
}
// Kết quả: max(dpIn[root], dpOut[root])
```

### Dạng 16: Đường kính của cây (Tree Diameter) bằng DP

```cpp
int diameter = 0;

int DFS_Diameter(int u, int parent) {
    int best1 = 0, best2 = 0; // 2 nhánh sâu nhất từ u
    for (int v : tree[u]) {
        if (v == parent) continue;
        int depth = DFS_Diameter(v, u) + 1;
        if (depth > best1) { best2 = best1; best1 = depth; }
        else if (depth > best2) best2 = depth;
    }
    diameter = max(diameter, best1 + best2);
    return best1;
}
```

---

## PHẦN 8: BẢNG NHẬN DẠNG DẠNG BÀI DP

| Dấu hiệu đề bài | Dạng DP | Trạng thái điển hình |
|---|---|---|
| "Dãy con dài nhất thoả tính chất tăng/giảm" | LIS | dp[i] = độ dài LIS kết thúc tại i |
| "So sánh/biến đổi giữa 2 chuỗi" | LCS / Edit Distance | dp[i][j] trên 2 chỉ số |
| "Chọn vật với trọng lượng giới hạn, tối ưu giá trị" | Knapsack | dp[i][cap] |
| "Đếm số cách đạt tổng/đổi tiền" | Coin Change | dp[cap] += dp[cap-c] |
| "Chia đoạn/khoảng, tối ưu chi phí ghép" | Interval DP | dp[i][j] trên đoạn |
| n ≤ 20, cần thăm hết tập đỉnh với chi phí tối ưu | Bitmask DP | dp[mask][i] |
| Bài toán trên cấu trúc cây, cha-con | Tree DP | dp[u] tính từ dp[con] |
| "Tối ưu tuyến tính, chỉ phụ thuộc 1-2 trạng thái liền trước" | DP 1 chiều | dp[i] từ dp[i-1], dp[i-2]... |

---

## PHẦN 9: LỖI THƯỜNG GẶP KHI DẠY

1. **Không xác định rõ trạng thái trước khi viết công thức** → dẫn đến công thức sai hoặc thiếu trường hợp.
2. **Nhầm chiều duyệt vòng lặp** trong Knapsack 0/1 vs Unbounded (đã nêu ở Dạng 8-9).
3. **Quên khởi tạo base case đúng** (ví dụ `dp[0][j] = j` trong Edit Distance).
4. **Tràn số** khi cộng dồn số cách (Coin Change Ways) — cần dùng `long long` hoặc lấy MOD tuỳ đề bài.
5. **Nhầm giữa "đếm số cách" và "tối ưu giá trị"** dẫn đến áp dụng sai công thức truy hồi (phép cộng `+=` vs phép `min/max`).

---

*Phong cách trình bày tham khảo: Cẩm nang thuật toán – Lê Minh Hoàng.*
