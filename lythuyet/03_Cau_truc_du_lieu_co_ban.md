# HỆ THỐNG CẤU TRÚC DỮ LIỆU CƠ BẢN

---

## PHẦN 1: MẢNG (ARRAY)

### Dạng 1: Mảng tĩnh và các thao tác nền tảng

```cpp
const int MAXN = 100005;
int a[MAXN];
int n;

void Insert(int pos, int val, int& n) {          // chèn vào vị trí pos (0-indexed)
    for (int i = n; i > pos; i--) a[i] = a[i-1];
    a[pos] = val;
    n++;
}

void Erase(int pos, int& n) {                     // xoá phần tử tại pos
    for (int i = pos; i < n - 1; i++) a[i] = a[i+1];
    n--;
}
```

**Ghi chú giảng dạy**: chèn/xoá trên mảng tĩnh tốn O(n) — đây là lý do dẫn nhập vào danh sách liên kết.

### Dạng 2: Mảng cộng dồn (Prefix Sum) — kỹ thuật nền tảng bậc nhất

```cpp
long long prefix[MAXN];
void BuildPrefix(int a[], int n) {
    prefix[0] = 0;
    for (int i = 1; i <= n; i++) prefix[i] = prefix[i-1] + a[i];
}
long long RangeSum(int l, int r) { return prefix[r] - prefix[l-1]; } // O(1) mỗi truy vấn
```

**Mở rộng 2D (bảng cộng dồn 2 chiều)**:
```cpp
long long prefix2D[1005][1005];
void Build2D(int a[][1005], int n, int m) {
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            prefix2D[i][j] = a[i][j] + prefix2D[i-1][j] + prefix2D[i][j-1] - prefix2D[i-1][j-1];
}
long long QuerySum(int x1,int y1,int x2,int y2) {
    return prefix2D[x2][y2] - prefix2D[x1-1][y2] - prefix2D[x2][y1-1] + prefix2D[x1-1][y1-1];
}
```

### Dạng 3: Mảng sai phân (Difference Array) — cập nhật khoảng, truy vấn điểm

```cpp
long long diff[MAXN];
void UpdateRange(int l, int r, long long val) {
    diff[l] += val;
    diff[r+1] -= val;
}
void ApplyDiff(int n) {
    for (int i = 1; i <= n; i++) diff[i] += diff[i-1]; // sau khi cộng dồn -> giá trị thực tại i
}
```

**Ứng dụng kinh điển**: bài toán "cộng x vào đoạn [l,r] nhiều lần, in ra mảng cuối cùng" — O(n + q) thay vì O(n·q).

---

## PHẦN 2: NGĂN XẾP (STACK)

### Dạng 4: Ngăn xếp tự cài đặt bằng mảng

```cpp
class MyStack {
    int a[MAXN], top_idx = -1;
public:
    void Push(int x) { a[++top_idx] = x; }
    void Pop() { top_idx--; }
    int Top() { return a[top_idx]; }
    bool Empty() { return top_idx == -1; }
};
```

### Dạng 5: Kiểm tra tính hợp lệ của dãy ngoặc

```cpp
bool ValidParentheses(string s) {
    stack<char> st;
    for (char c : s) {
        if (c == '(' || c == '[' || c == '{') st.push(c);
        else {
            if (st.empty()) return false;
            char top = st.top();
            if ((c == ')' && top != '(') ||
                (c == ']' && top != '[') ||
                (c == '}' && top != '{')) return false;
            st.pop();
        }
    }
    return st.empty();
}
```

### Dạng 6: Ngăn xếp đơn điệu (Monotonic Stack) — kỹ thuật CP quan trọng

**Ứng dụng kinh điển: tìm phần tử lớn hơn gần nhất bên phải (Next Greater Element)**

```cpp
vector<int> NextGreaterElement(vector<int>& a) {
    int n = a.size();
    vector<int> result(n, -1);
    stack<int> st;  // lưu chỉ số, đảm bảo giá trị giảm dần từ đáy lên đỉnh
    for (int i = 0; i < n; i++) {
        while (!st.empty() && a[st.top()] < a[i]) {
            result[st.top()] = a[i];
            st.pop();
        }
        st.push(i);
    }
    return result;
}
```

**Ứng dụng kinh điển khác: diện tích hình chữ nhật lớn nhất trong biểu đồ cột (Largest Rectangle in Histogram)** — độ phức tạp O(n) nhờ ngăn xếp đơn điệu, thường được xem là bài toán "phải biết" khi dạy về stack nâng cao.

### Dạng 7: Định giá biểu thức bằng ngăn xếp (Infix ↔ Postfix, Evaluate)

```cpp
int Precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

string InfixToPostfix(string s) {
    stack<char> ops;
    string result;
    for (char c : s) {
        if (isdigit(c)) result += c;
        else if (c == '(') ops.push(c);
        else if (c == ')') {
            while (ops.top() != '(') { result += ops.top(); ops.pop(); }
            ops.pop();
        } else {
            while (!ops.empty() && Precedence(ops.top()) >= Precedence(c)) {
                result += ops.top(); ops.pop();
            }
            ops.push(c);
        }
    }
    while (!ops.empty()) { result += ops.top(); ops.pop(); }
    return result;
}
```

---

## PHẦN 3: HÀNG ĐỢI (QUEUE)

### Dạng 8: Hàng đợi tự cài đặt bằng mảng vòng (Circular Queue)

```cpp
class MyQueue {
    int a[MAXN], head = 0, tail = 0, cnt = 0;
    static const int CAP = MAXN;
public:
    void Push(int x) { a[tail] = x; tail = (tail + 1) % CAP; cnt++; }
    void Pop() { head = (head + 1) % CAP; cnt--; }
    int Front() { return a[head]; }
    bool Empty() { return cnt == 0; }
};
```

### Dạng 9: Hàng đợi 2 đầu (Deque) và ứng dụng Sliding Window Maximum

**Bài toán**: tìm giá trị lớn nhất của mỗi cửa sổ trượt kích thước k trên mảng — độ phức tạp O(n) nhờ deque đơn điệu.

```cpp
vector<int> SlidingWindowMax(vector<int>& a, int k) {
    deque<int> dq; // lưu chỉ số, giá trị giảm dần từ đầu đến cuối deque
    vector<int> result;
    for (int i = 0; i < (int)a.size(); i++) {
        while (!dq.empty() && dq.front() <= i - k) dq.pop_front(); // loại phần tử ra khỏi cửa sổ
        while (!dq.empty() && a[dq.back()] < a[i]) dq.pop_back();  // loại phần tử nhỏ hơn phía sau
        dq.push_back(i);
        if (i >= k - 1) result.push_back(a[dq.front()]);
    }
    return result;
}
```

### Dạng 10: Hàng đợi ưu tiên (Priority Queue / Heap)

```cpp
priority_queue<int> maxHeap;                              // mặc định max-heap
priority_queue<int, vector<int>, greater<int>> minHeap;    // min-heap

// Ứng dụng kinh điển: Merge k dãy đã sắp xếp (K-way merge)
vector<int> MergeKSortedArrays(vector<vector<int>>& arrays) {
    priority_queue<pair<int,pair<int,int>>, vector<pair<int,pair<int,int>>>, greater<>> pq;
    for (int i = 0; i < (int)arrays.size(); i++)
        if (!arrays[i].empty()) pq.push({arrays[i][0], {i, 0}});

    vector<int> result;
    while (!pq.empty()) {
        auto [val, idx] = pq.top(); pq.pop();
        auto [arrIdx, elemIdx] = idx;
        result.push_back(val);
        if (elemIdx + 1 < (int)arrays[arrIdx].size())
            pq.push({arrays[arrIdx][elemIdx+1], {arrIdx, elemIdx+1}});
    }
    return result;
}
```

---

## PHẦN 4: DANH SÁCH LIÊN KẾT (LINKED LIST)

### Dạng 11: Danh sách liên kết đơn — thao tác cơ bản

```cpp
struct Node {
    int val;
    Node* next;
    Node(int v) : val(v), next(nullptr) {}
};

void InsertFront(Node*& head, int val) {
    Node* newNode = new Node(val);
    newNode->next = head;
    head = newNode;
}

void InsertAfter(Node* prev, int val) {
    if (!prev) return;
    Node* newNode = new Node(val);
    newNode->next = prev->next;
    prev->next = newNode;
}

void DeleteNode(Node*& head, int val) {
    if (!head) return;
    if (head->val == val) { Node* tmp = head; head = head->next; delete tmp; return; }
    Node* cur = head;
    while (cur->next && cur->next->val != val) cur = cur->next;
    if (cur->next) { Node* tmp = cur->next; cur->next = tmp->next; delete tmp; }
}
```

### Dạng 12: Đảo ngược danh sách liên kết (Reverse Linked List)

```cpp
Node* Reverse(Node* head) {
    Node* prev = nullptr;
    Node* cur = head;
    while (cur) {
        Node* nxt = cur->next;
        cur->next = prev;
        prev = cur;
        cur = nxt;
    }
    return prev;
}
```

### Dạng 13: Phát hiện chu trình — Thuật toán Rùa và Thỏ (Floyd's Cycle Detection)

```cpp
bool HasCycle(Node* head) {
    Node* slow = head;
    Node* fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) return true;
    }
    return false;
}

// Tìm điểm bắt đầu chu trình
Node* FindCycleStart(Node* head) {
    Node* slow = head; Node* fast = head;
    while (fast && fast->next) {
        slow = slow->next; fast = fast->next->next;
        if (slow == fast) {
            Node* ptr = head;
            while (ptr != slow) { ptr = ptr->next; slow = slow->next; }
            return ptr;
        }
    }
    return nullptr;
}
```

### Dạng 14: Danh sách liên kết đôi (Doubly Linked List)

```cpp
struct DNode {
    int val;
    DNode *prev, *next;
    DNode(int v) : val(v), prev(nullptr), next(nullptr) {}
};
```

**Ứng dụng thực tế hay được hỏi**: cài đặt cấu trúc **LRU Cache** bằng Doubly Linked List + Hash Map, đạt O(1) cho cả get và put.

---

## PHẦN 5: BẢNG SO SÁNH LỰA CHỌN CẤU TRÚC DỮ LIỆU

| Nhu cầu | Cấu trúc phù hợp | Độ phức tạp thao tác chính |
|---|---|---|
| Truy cập ngẫu nhiên theo chỉ số | Mảng | O(1) |
| Chèn/xoá đầu-cuối thường xuyên | Deque | O(1) |
| Chèn/xoá giữa dãy thường xuyên | Danh sách liên kết | O(1) sau khi có con trỏ |
| Duyệt LIFO (vào sau ra trước) | Stack | O(1) |
| Duyệt FIFO (vào trước ra trước) | Queue | O(1) |
| Luôn cần lấy min/max hiện có | Priority Queue (Heap) | O(log n) |
| Cộng dồn đoạn tĩnh, truy vấn nhiều lần | Prefix Sum | O(1) truy vấn sau O(n) tiền xử lý |
| Cập nhật nhiều đoạn, truy vấn 1 lần cuối | Difference Array | O(1) cập nhật, O(n) tổng hợp |

---

*Phong cách trình bày tham khảo: Cẩm nang thuật toán – Lê Minh Hoàng.*
