# CẤU TRÚC DỮ LIỆU VÀ GIẢI THUẬT (DATA STRUCTURES & ALGORITHMS)
### Tài liệu tổng hợp toàn diện — Minh họa bằng ngôn ngữ C++

---

## MỤC LỤC

1. Nhập môn & Độ phức tạp thuật toán
2. Cấu trúc dữ liệu tuyến tính: Mảng, Danh sách liên kết
3. Ngăn xếp (Stack) & Hàng đợi (Queue)
4. Đệ quy & Chia để trị (Divide and Conquer)
5. Giải thuật sắp xếp (Sorting)
6. Giải thuật tìm kiếm (Searching)
7. Cây (Tree): Cây nhị phân, BST, Cây cân bằng, Heap
8. Bảng băm (Hash Table)
9. Đồ thị (Graph): Biểu diễn, BFS, DFS, đường đi ngắn nhất
10. Quy hoạch động (Dynamic Programming)
11. Giải thuật tham lam (Greedy Algorithms)
12. Quay lui (Backtracking)
13. Tổng kết & Bảng so sánh độ phức tạp

---

## CHƯƠNG 1: NHẬP MÔN & ĐỘ PHỨC TẠP THUẬT TOÁN

### 1.1. Cấu trúc dữ liệu là gì?

Cấu trúc dữ liệu (Data Structure) là cách tổ chức, lưu trữ dữ liệu trong bộ nhớ sao cho việc truy xuất và xử lý hiệu quả nhất. Giải thuật (Algorithm) là một chuỗi các bước hữu hạn để giải quyết một bài toán cụ thể.

```
Chương trình = Cấu trúc dữ liệu + Giải thuật
```

Chọn sai cấu trúc dữ liệu, một thuật toán "hay" vẫn có thể chạy chậm; chọn đúng cấu trúc dữ liệu, một thuật toán "đơn giản" vẫn có thể chạy rất nhanh.

### 1.2. Độ phức tạp thuật toán (Big O Notation)

- **Độ phức tạp thời gian (Time Complexity):** số phép tính cơ bản tăng theo kích thước đầu vào `n`.
- **Độ phức tạp không gian (Space Complexity):** lượng bộ nhớ phụ trội cần dùng.

Ký hiệu: **O(f(n))** — cận trên (xấu nhất, hay dùng nhất), **Ω(f(n))** — cận dưới, **Θ(f(n))** — cận chặt.

| Ký hiệu | Tên gọi | Ví dụ |
|---|---|---|
| O(1) | Hằng số | Truy cập phần tử mảng theo chỉ số |
| O(log n) | Logarit | Tìm kiếm nhị phân |
| O(n) | Tuyến tính | Duyệt qua mảng |
| O(n log n) | Tuyến tính-logarit | Merge Sort, Quick Sort (TB) |
| O(n²) | Bình phương | Bubble Sort, Selection Sort |
| O(2ⁿ) | Mũ | Đệ quy Fibonacci không tối ưu |
| O(n!) | Giai thừa | Bài toán người du lịch (brute-force) |

**Ví dụ phân tích bằng C++:**

```cpp
#include <vector>
using namespace std;

int tong(const vector<int>& arr) {       // n = arr.size()
    int s = 0;                            // O(1)
    for (int x : arr) {                   // lặp n lần -> O(n)
        s += x;                           // O(1) mỗi lần
    }
    return s;                             // O(1)
}
// Tổng độ phức tạp: O(n)

void co_cap_trung(const vector<int>& arr) {
    for (int i : arr)
        for (int j : arr)
            cout << i << " " << j << endl;
}
// Độ phức tạp: O(n^2)
```

**Quy tắc nhanh khi tính Big O:**
1. Bỏ hằng số nhân: O(2n) → O(n)
2. Chỉ giữ số hạng bậc cao nhất: O(n² + n) → O(n²)
3. Vòng lặp lồng nhau độc lập → nhân độ phức tạp
4. Vòng lặp tuần tự (không lồng) → cộng, rồi lấy bậc cao nhất

---

## CHƯƠNG 2: CẤU TRÚC DỮ LIỆU TUYẾN TÍNH

### 2.1. Mảng (Array)

Mảng lưu các phần tử **liên tiếp trong bộ nhớ**, truy cập trực tiếp qua chỉ số.

| Thao tác | Độ phức tạp |
|---|---|
| Truy cập arr[i] | O(1) |
| Tìm kiếm giá trị | O(n) |
| Chèn/xóa ở giữa | O(n) |
| Chèn/xóa ở cuối (vector) | O(1) (amortized) |

```cpp
#include <vector>
#include <iostream>
using namespace std;

int main() {
    vector<int> arr = {10, 20, 30, 40};
    cout << arr[2] << endl;              // O(1) -> 30

    arr.insert(arr.begin() + 1, 99);      // O(n) -> {10, 99, 20, 30, 40}
    arr.pop_back();                       // O(1) -> xóa phần tử cuối

    for (int x : arr) cout << x << " ";
    return 0;
}
```

**Ưu điểm:** truy cập ngẫu nhiên nhanh, cache-friendly.
**Nhược điểm:** mảng tĩnh có kích thước cố định, chèn/xóa giữa mảng tốn kém.

### 2.2. Danh sách liên kết (Linked List)

Mỗi phần tử (Node) chứa dữ liệu và con trỏ trỏ tới node tiếp theo.

```cpp
#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

class LinkedList {
private:
    Node* head;
public:
    LinkedList() : head(nullptr) {}

    void themDau(int data) {              // O(1)
        Node* node = new Node(data);
        node->next = head;
        head = node;
    }

    void themCuoi(int data) {              // O(n)
        Node* node = new Node(data);
        if (!head) { head = node; return; }
        Node* cur = head;
        while (cur->next) cur = cur->next;
        cur->next = node;
    }

    bool xoa(int key) {                    // O(n)
        Node* cur = head;
        Node* prev = nullptr;
        while (cur && cur->data != key) {
            prev = cur;
            cur = cur->next;
        }
        if (!cur) return false;
        if (!prev) head = cur->next;
        else prev->next = cur->next;
        delete cur;
        return true;
    }

    void hienThi() {
        Node* cur = head;
        while (cur) {
            cout << cur->data << " -> ";
            cur = cur->next;
        }
        cout << "NULL" << endl;
    }
};

int main() {
    LinkedList ll;
    ll.themDau(3); ll.themDau(2); ll.themDau(1);
    ll.themCuoi(4);
    ll.hienThi();   // 1 -> 2 -> 3 -> 4 -> NULL
    return 0;
}
```

| Thao tác | Mảng | Linked List |
|---|---|---|
| Truy cập theo chỉ số | O(1) | O(n) |
| Chèn đầu danh sách | O(n) | O(1) |
| Chèn/xóa giữa (đã có con trỏ) | O(n) | O(1) |
| Bộ nhớ | Ít overhead | Tốn thêm cho con trỏ |

---

## CHƯƠNG 3: NGĂN XẾP (STACK) & HÀNG ĐỢI (QUEUE)

### 3.1. Stack — LIFO (Last In, First Out)

```cpp
#include <stack>
#include <string>
#include <unordered_map>
#include <iostream>
using namespace std;

bool kiemTraNgoac(const string& s) {
    stack<char> st;
    unordered_map<char, char> doi = {{')', '('}, {']', '['}, {'}', '{'}};

    for (char ch : s) {
        if (ch == '(' || ch == '[' || ch == '{') {
            st.push(ch);                       // O(1)
        } else if (ch == ')' || ch == ']' || ch == '}') {
            if (st.empty() || st.top() != doi[ch]) return false;
            st.pop();                          // O(1)
        }
    }
    return st.empty();
}

int main() {
    cout << boolalpha;
    cout << kiemTraNgoac("{[()]}") << endl;    // true
    cout << kiemTraNgoac("{[(])}") << endl;    // false
    return 0;
}
```

**Ứng dụng thực tế:** Undo/Redo trong trình soạn thảo, gọi hàm đệ quy (call stack), duyệt biểu thức hậu tố (postfix), thuật toán DFS.

### 3.2. Queue — FIFO (First In, First Out)

```cpp
#include <queue>
#include <iostream>
using namespace std;

int main() {
    queue<int> q;
    q.push(1); q.push(2); q.push(3);   // enqueue - O(1)

    cout << q.front() << endl;          // 1
    q.pop();                             // dequeue - O(1)
    cout << q.front() << endl;          // 2
    return 0;
}
```

**Biến thể quan trọng:**
- **Circular Queue:** hàng đợi vòng, tránh lãng phí bộ nhớ khi dùng mảng cố định.
- **Priority Queue:** phần tử có độ ưu tiên (`std::priority_queue`), cài bằng Heap (xem Chương 7).
- **Deque (`std::deque`):** thêm/xóa được ở cả hai đầu.

**Ứng dụng thực tế:** Xử lý tác vụ theo thứ tự, BFS trong đồ thị, bộ đệm dữ liệu, quản lý hàng chờ in ấn.

---

## CHƯƠNG 4: ĐỆ QUY & CHIA ĐỂ TRỊ

### 4.1. Đệ quy (Recursion)

```cpp
#include <iostream>
using namespace std;

long long giaiThua(int n) {
    if (n <= 1) return 1;                  // base case
    return n * giaiThua(n - 1);             // recursive case
}

int main() {
    cout << giaiThua(5) << endl;   // 120
    return 0;
}
```

**Fibonacci — minh họa vì sao đệ quy "ngây thơ" chậm:**

```cpp
#include <unordered_map>
using namespace std;

int fib(int n) {                    // O(2^n) - rất chậm với n lớn
    if (n <= 1) return n;
    return fib(n - 1) + fib(n - 2);
}

unordered_map<int, long long> cache;
long long fibMemo(int n) {           // O(n) nhờ ghi nhớ (memoization)
    if (n <= 1) return n;
    if (cache.count(n)) return cache[n];
    return cache[n] = fibMemo(n - 1) + fibMemo(n - 2);
}
```

### 4.2. Chia để trị (Divide and Conquer)

Ba bước: **Chia** bài toán lớn thành các bài toán con nhỏ hơn → **Trị** (giải đệ quy) → **Kết hợp** kết quả.

```cpp
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

int timMax(const vector<int>& arr, int l, int r) {
    if (l == r) return arr[l];
    int mid = (l + r) / 2;
    int maxTrai = timMax(arr, l, mid);
    int maxPhai = timMax(arr, mid + 1, r);
    return max(maxTrai, maxPhai);
}

int main() {
    vector<int> arr = {3, 9, 2, 7, 5};
    cout << timMax(arr, 0, arr.size() - 1) << endl;   // 9
    return 0;
}
```

Merge Sort và Quick Sort (Chương 5) là ví dụ điển hình nhất của chia để trị.

---

## CHƯƠNG 5: GIẢI THUẬT SẮP XẾP (SORTING)

### 5.1. Bubble Sort — O(n²)

```cpp
#include <vector>
using namespace std;

void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - 1 - i; j++)
            if (arr[j] > arr[j + 1])
                swap(arr[j], arr[j + 1]);
}
```

### 5.2. Selection Sort — O(n²)

```cpp
void selectionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++)
            if (arr[j] < arr[minIdx]) minIdx = j;
        swap(arr[i], arr[minIdx]);
    }
}
```

### 5.3. Insertion Sort — O(n²), nhanh với mảng gần như đã sắp

```cpp
void insertionSort(vector<int>& arr) {
    for (size_t i = 1; i < arr.size(); i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}
```

### 5.4. Merge Sort — O(n log n), ổn định (stable)

```cpp
#include <vector>
using namespace std;

void tron(vector<int>& arr, int l, int mid, int r) {
    vector<int> trai(arr.begin() + l, arr.begin() + mid + 1);
    vector<int> phai(arr.begin() + mid + 1, arr.begin() + r + 1);

    int i = 0, j = 0, k = l;
    while (i < (int)trai.size() && j < (int)phai.size())
        arr[k++] = (trai[i] <= phai[j]) ? trai[i++] : phai[j++];
    while (i < (int)trai.size()) arr[k++] = trai[i++];
    while (j < (int)phai.size()) arr[k++] = phai[j++];
}

void mergeSort(vector<int>& arr, int l, int r) {
    if (l >= r) return;
    int mid = (l + r) / 2;
    mergeSort(arr, l, mid);
    mergeSort(arr, mid + 1, r);
    tron(arr, l, mid, r);
}
// Gọi: mergeSort(arr, 0, arr.size() - 1);
```

### 5.5. Quick Sort — O(n log n) trung bình, O(n²) xấu nhất

```cpp
#include <vector>
using namespace std;

int phanHoach(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int p = phanHoach(arr, low, high);
        quickSort(arr, low, p - 1);
        quickSort(arr, p + 1, high);
    }
}
// Gọi: quickSort(arr, 0, arr.size() - 1);
```

### 5.6. Heap Sort — O(n log n)

```cpp
#include <vector>
using namespace std;

void heapify(vector<int>& arr, int n, int i) {
    int lon = i, trai = 2 * i + 1, phai = 2 * i + 2;
    if (trai < n && arr[trai] > arr[lon]) lon = trai;
    if (phai < n && arr[phai] > arr[lon]) lon = phai;
    if (lon != i) {
        swap(arr[i], arr[lon]);
        heapify(arr, n, lon);
    }
}

void heapSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = n / 2 - 1; i >= 0; i--)       // xây Max-Heap - O(n)
        heapify(arr, n, i);

    for (int i = n - 1; i > 0; i--) {           // O(n log n)
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}
```

### 5.7. Bảng so sánh các giải thuật sắp xếp

| Giải thuật | Tốt nhất | Trung bình | Xấu nhất | Bộ nhớ | Ổn định |
|---|---|---|---|---|---|
| Bubble Sort | O(n) | O(n²) | O(n²) | O(1) | Có |
| Selection Sort | O(n²) | O(n²) | O(n²) | O(1) | Không |
| Insertion Sort | O(n) | O(n²) | O(n²) | O(1) | Có |
| Merge Sort | O(n log n) | O(n log n) | O(n log n) | O(n) | Có |
| Quick Sort | O(n log n) | O(n log n) | O(n²) | O(log n) | Không |
| Heap Sort | O(n log n) | O(n log n) | O(n log n) | O(1) | Không |

> **Lưu ý thực tế:** trong C++, `std::sort` đã cài đặt sẵn Introsort (kết hợp Quick Sort + Heap Sort + Insertion Sort) — nên dùng trực tiếp trong dự án thực tế, tự cài đặt các giải thuật trên chỉ để học nguyên lý.

---

## CHƯƠNG 6: GIẢI THUẬT TÌM KIẾM (SEARCHING)

### 6.1. Tìm kiếm tuyến tính (Linear Search) — O(n)

```cpp
#include <vector>
using namespace std;

int linearSearch(const vector<int>& arr, int x) {
    for (size_t i = 0; i < arr.size(); i++)
        if (arr[i] == x) return i;
    return -1;
}
```

### 6.2. Tìm kiếm nhị phân (Binary Search) — O(log n)

**Điều kiện bắt buộc: mảng phải đã được sắp xếp.**

```cpp
#include <vector>
#include <iostream>
using namespace std;

int binarySearch(const vector<int>& arr, int x) {
    int l = 0, r = arr.size() - 1;
    while (l <= r) {
        int mid = l + (r - l) / 2;
        if (arr[mid] == x) return mid;
        else if (arr[mid] < x) l = mid + 1;
        else r = mid - 1;
    }
    return -1;
}

int main() {
    vector<int> arr = {1, 3, 5, 7, 9, 11};
    cout << binarySearch(arr, 7) << endl;   // 3
    return 0;
}
```

> C++ STL cũng có sẵn `std::binary_search`, `std::lower_bound`, `std::upper_bound` cho mảng đã sắp xếp.

---

## CHƯƠNG 7: CÂY (TREE)

### 7.1. Khái niệm cơ bản

Cây là cấu trúc phân cấp gồm các **node**, node gốc gọi là **root**, node không có con gọi là **lá (leaf)**.

### 7.2. Cây nhị phân tìm kiếm (Binary Search Tree - BST)

```cpp
#include <iostream>
#include <vector>
using namespace std;

struct NodeBST {
    int data;
    NodeBST* left;
    NodeBST* right;
    NodeBST(int val) : data(val), left(nullptr), right(nullptr) {}
};

class BST {
private:
    NodeBST* root;

    NodeBST* themDeQuy(NodeBST* node, int data) {
        if (!node) return new NodeBST(data);
        if (data < node->data) node->left = themDeQuy(node->left, data);
        else node->right = themDeQuy(node->right, data);
        return node;
    }

    NodeBST* timDeQuy(NodeBST* node, int data) {
        if (!node || node->data == data) return node;
        if (data < node->data) return timDeQuy(node->left, data);
        return timDeQuy(node->right, data);
    }

    void inorderDeQuy(NodeBST* node, vector<int>& ketQua) {
        if (!node) return;
        inorderDeQuy(node->left, ketQua);
        ketQua.push_back(node->data);
        inorderDeQuy(node->right, ketQua);
    }

public:
    BST() : root(nullptr) {}

    void them(int data) { root = themDeQuy(root, data); }        // TB O(log n)
    NodeBST* tim(int data) { return timDeQuy(root, data); }       // TB O(log n)

    vector<int> duyetInorder() {
        vector<int> ketQua;
        inorderDeQuy(root, ketQua);
        return ketQua;
    }
};

int main() {
    BST bst;
    for (int x : {8, 3, 10, 1, 6, 14, 4, 7}) bst.them(x);

    for (int x : bst.duyetInorder()) cout << x << " ";
    // 1 3 4 6 7 8 10 14 - đã sắp xếp!
    return 0;
}
```

**Ba cách duyệt cây (Tree Traversal):**
- **Inorder** (Trái - Gốc - Phải): cho ra dãy đã sắp xếp với BST.
- **Preorder** (Gốc - Trái - Phải): dùng để sao chép cây.
- **Postorder** (Trái - Phải - Gốc): dùng để xóa cây, tính biểu thức hậu tố.

**Nhược điểm BST thường:** nếu chèn dữ liệu đã sắp xếp sẵn, cây bị "lệch" thành danh sách liên kết → độ phức tạp giảm còn O(n).

### 7.3. Cây cân bằng (AVL Tree, Red-Black Tree)

Tự động cân bằng lại (rotation) sau mỗi lần chèn/xóa để đảm bảo chiều cao luôn O(log n). Đây chính là cấu trúc bên trong của `std::map` và `std::set` trong C++ STL (cài đặt bằng Red-Black Tree).

### 7.4. Heap (Đống)

Cây nhị phân gần hoàn chỉnh: **Max-Heap** (cha ≥ con) hoặc **Min-Heap** (cha ≤ con). Thường cài đặt bằng mảng: node `i` có con trái `2i+1`, con phải `2i+2`, cha `(i-1)/2`.

```cpp
#include <queue>
#include <vector>
#include <iostream>
using namespace std;

int main() {
    // Min-Heap trong C++ STL
    priority_queue<int, vector<int>, greater<int>> minHeap;
    for (int x : {5, 2, 8, 1, 9}) minHeap.push(x);   // O(log n)

    cout << minHeap.top() << endl;   // 1 (nhỏ nhất luôn ở đỉnh)
    minHeap.pop();

    // Max-Heap (mặc định của priority_queue)
    priority_queue<int> maxHeap;
    for (int x : {5, 2, 8, 1, 9}) maxHeap.push(x);
    cout << maxHeap.top() << endl;   // 9
    return 0;
}
```

**Ứng dụng:** Priority Queue, thuật toán Dijkstra, Heap Sort, tìm k phần tử lớn/nhỏ nhất.

### 7.5. Cây Trie (Cây tiền tố)

Chuyên dùng để lưu trữ và tìm kiếm chuỗi/từ hiệu quả (gợi ý gõ từ, kiểm tra chính tả).

```cpp
#include <unordered_map>
#include <string>
using namespace std;

struct TrieNode {
    unordered_map<char, TrieNode*> con;
    bool ketThucTu = false;
};

class Trie {
private:
    TrieNode* root;
public:
    Trie() { root = new TrieNode(); }

    void chen(const string& tu) {              // O(độ dài từ)
        TrieNode* node = root;
        for (char ch : tu) {
            if (!node->con.count(ch)) node->con[ch] = new TrieNode();
            node = node->con[ch];
        }
        node->ketThucTu = true;
    }

    bool timKiem(const string& tu) {            // O(độ dài từ)
        TrieNode* node = root;
        for (char ch : tu) {
            if (!node->con.count(ch)) return false;
            node = node->con[ch];
        }
        return node->ketThucTu;
    }
};
```

---

## CHƯƠNG 8: BẢNG BĂM (HASH TABLE)

### 8.1. Nguyên lý

Dùng **hàm băm (hash function)** để ánh xạ khóa sang một chỉ số trong mảng, cho phép truy cập trung bình **O(1)**. Trong C++, `unordered_map`/`unordered_set` chính là hash table dựng sẵn.

```cpp
#include <unordered_map>
#include <string>
#include <iostream>
using namespace std;

int main() {
    unordered_map<string, string> sinhVien;
    sinhVien["SV001"] = "Nguyễn Văn A";    // O(1) trung bình
    sinhVien["SV002"] = "Trần Thị B";

    cout << sinhVien["SV001"] << endl;      // O(1) trung bình -> Nguyễn Văn A
    return 0;
}
```

### 8.2. Đụng độ (Collision) & cách xử lý

- **Separate Chaining:** mỗi ô của mảng chứa một danh sách liên kết các phần tử đụng độ.
- **Open Addressing (Linear/Quadratic Probing, Double Hashing):** tìm ô trống tiếp theo trong mảng.

**Cài đặt minh họa Hash Table bằng Chaining:**

```cpp
#include <vector>
#include <list>
#include <string>
#include <iostream>
using namespace std;

class HashTable {
private:
    int size;
    vector<list<pair<string, int>>> buckets;

    int hashFunc(const string& key) {
        int h = 0;
        for (char c : key) h = (h * 31 + c) % size;
        return h;
    }

public:
    HashTable(int n = 10) : size(n), buckets(n) {}

    void them(const string& key, int value) {
        int idx = hashFunc(key);
        for (auto& cap : buckets[idx]) {
            if (cap.first == key) { cap.second = value; return; }
        }
        buckets[idx].push_back({key, value});
    }

    int lay(const string& key) {
        int idx = hashFunc(key);
        for (auto& cap : buckets[idx])
            if (cap.first == key) return cap.second;
        return -1;
    }
};

int main() {
    HashTable ht;
    ht.them("Bao", 20);
    ht.them("Lan", 22);
    cout << ht.lay("Bao") << endl;   // 20
    return 0;
}
```

**Ứng dụng:** đếm tần suất, cache, kiểm tra trùng lặp, `unordered_map`/`unordered_set`.

---

## CHƯƠNG 9: ĐỒ THỊ (GRAPH)

### 9.1. Khái niệm & biểu diễn

Đồ thị G = (V, E) gồm tập đỉnh và tập cạnh. Có thể **có hướng/vô hướng**, **có trọng số/không trọng số**.

```cpp
#include <unordered_map>
#include <vector>
#include <string>
using namespace std;

// 1. Danh sách kề (Adjacency List) - tiết kiệm bộ nhớ, phổ biến nhất
unordered_map<string, vector<string>> graph = {
    {"A", {"B", "C"}},
    {"B", {"A", "D"}},
    {"C", {"A", "D"}},
    {"D", {"B", "C"}}
};

// 2. Ma trận kề (Adjacency Matrix) - tra cứu cạnh O(1), tốn bộ nhớ O(V^2)
// vector<vector<int>> adjMatrix(n, vector<int>(n, 0));
```

### 9.2. Duyệt theo chiều rộng — BFS (Breadth-First Search)

```cpp
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <queue>
#include <string>
#include <iostream>
using namespace std;

vector<string> bfs(unordered_map<string, vector<string>>& graph, const string& start) {
    unordered_set<string> visited = {start};
    queue<string> q;
    q.push(start);
    vector<string> thuTu;

    while (!q.empty()) {
        string node = q.front(); q.pop();
        thuTu.push_back(node);
        for (const string& hangXom : graph[node]) {
            if (!visited.count(hangXom)) {
                visited.insert(hangXom);
                q.push(hangXom);
            }
        }
    }
    return thuTu;
}
// bfs(graph, "A") -> A, B, C, D
```

### 9.3. Duyệt theo chiều sâu — DFS (Depth-First Search)

```cpp
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>
using namespace std;

void dfs(unordered_map<string, vector<string>>& graph, const string& node,
         unordered_set<string>& visited, vector<string>& thuTu) {
    visited.insert(node);
    thuTu.push_back(node);
    for (const string& hangXom : graph[node]) {
        if (!visited.count(hangXom))
            dfs(graph, hangXom, visited, thuTu);
    }
}
// unordered_set<string> visited; vector<string> thuTu;
// dfs(graph, "A", visited, thuTu); -> A, B, D, C
```

| Tiêu chí | BFS | DFS |
|---|---|---|
| Cấu trúc dùng | Queue | Stack / đệ quy |
| Tìm đường ngắn nhất (không trọng số) | Có | Không |
| Ứng dụng | Đường đi ngắn nhất, mạng xã hội | Phát hiện chu trình, tô-pô sort |

### 9.4. Thuật toán Dijkstra — đường đi ngắn nhất có trọng số

```cpp
#include <unordered_map>
#include <vector>
#include <queue>
#include <string>
#include <climits>
#include <iostream>
using namespace std;

unordered_map<string, int> dijkstra(
    unordered_map<string, vector<pair<string, int>>>& graph, const string& start) {

    unordered_map<string, int> khoangCach;
    for (auto& [dinh, _] : graph) khoangCach[dinh] = INT_MAX;
    khoangCach[start] = 0;

    priority_queue<pair<int, string>, vector<pair<int, string>>, greater<>> pq;
    pq.push({0, start});

    while (!pq.empty()) {
        auto [d, node] = pq.top(); pq.pop();
        if (d > khoangCach[node]) continue;

        for (auto& [hangXom, trongSo] : graph[node]) {
            int moi = d + trongSo;
            if (moi < khoangCach[hangXom]) {
                khoangCach[hangXom] = moi;
                pq.push({moi, hangXom});
            }
        }
    }
    return khoangCach;
}

int main() {
    unordered_map<string, vector<pair<string, int>>> graphW = {
        {"A", {{"B", 4}, {"C", 1}}},
        {"B", {{"D", 1}}},
        {"C", {{"B", 2}, {"D", 5}}},
        {"D", {}}
    };
    auto kq = dijkstra(graphW, "A");
    for (auto& [dinh, kc] : kq) cout << dinh << ": " << kc << endl;
    // A:0  B:3  C:1  D:4
    return 0;
}
```

**Các thuật toán đồ thị quan trọng khác:** Bellman-Ford (cạnh âm), Floyd-Warshall (mọi cặp đỉnh), Kruskal/Prim (cây khung nhỏ nhất - MST), Topological Sort.

---

## CHƯƠNG 10: QUY HOẠCH ĐỘNG (DYNAMIC PROGRAMMING)

### 10.1. Nguyên lý

DP giải bài toán bằng cách chia thành các bài toán con **chồng lặp** và **lưu lại kết quả**. Hai cách tiếp cận: **Top-down (Memoization)** và **Bottom-up (Tabulation)**.

### 10.2. Ví dụ kinh điển: Bài toán cái túi (Knapsack 0/1)

```cpp
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

int knapsack(vector<int>& trongLuong, vector<int>& giaTri, int W) {
    int n = trongLuong.size();
    vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            if (trongLuong[i - 1] <= w) {
                dp[i][w] = max(
                    giaTri[i - 1] + dp[i - 1][w - trongLuong[i - 1]],  // lấy món i
                    dp[i - 1][w]                                       // không lấy
                );
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }
    return dp[n][W];
}

int main() {
    vector<int> trongLuong = {1, 3, 4, 5};
    vector<int> giaTri = {1, 4, 5, 7};
    cout << knapsack(trongLuong, giaTri, 7) << endl;   // 9
    return 0;
}
```

### 10.3. Ví dụ: Dãy con chung dài nhất (Longest Common Subsequence)

```cpp
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

int lcs(const string& s1, const string& s2) {
    int m = s1.size(), n = s2.size();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (s1[i - 1] == s2[j - 1]) dp[i][j] = dp[i - 1][j - 1] + 1;
            else dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        }
    }
    return dp[m][n];
}

int main() {
    cout << lcs("ABCBDAB", "BDCABA") << endl;   // 4 ("BCBA")
    return 0;
}
```

**Các bài toán DP kinh điển khác:** Fibonacci, Coin Change, Edit Distance, Longest Increasing Subsequence, Matrix Chain Multiplication.

---

## CHƯƠNG 11: GIẢI THUẬT THAM LAM (GREEDY ALGORITHMS)

### 11.1. Nguyên lý

Tại mỗi bước, chọn lựa chọn **tốt nhất tại thời điểm hiện tại**. **Không phải lúc nào cũng đúng** — chỉ áp dụng khi bài toán có "greedy choice property".

### 11.2. Ví dụ: Bài toán chọn hoạt động (Activity Selection)

```cpp
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

vector<pair<int,int>> chonHoatDong(vector<pair<int,int>> hoatDong) {
    sort(hoatDong.begin(), hoatDong.end(),
         [](auto& a, auto& b) { return a.second < b.second; });  // sắp theo giờ kết thúc

    vector<pair<int,int>> ketQua = {hoatDong[0]};
    int ketThucCuoi = hoatDong[0].second;

    for (size_t i = 1; i < hoatDong.size(); i++) {
        if (hoatDong[i].first >= ketThucCuoi) {
            ketQua.push_back(hoatDong[i]);
            ketThucCuoi = hoatDong[i].second;
        }
    }
    return ketQua;
}

int main() {
    vector<pair<int,int>> hd = {{1,4}, {3,5}, {0,6}, {5,7}, {8,9}, {5,9}};
    for (auto& [bd, kt] : chonHoatDong(hd))
        cout << "(" << bd << "," << kt << ") ";
    // (1,4) (5,7) (8,9)
    return 0;
}
```

### 11.3. Ví dụ: Mã hóa Huffman (Huffman Coding)

Xây cây nhị phân từ dưới lên, luôn ghép hai node có tần suất nhỏ nhất (dùng `priority_queue` làm Min-Heap) — dùng để nén dữ liệu (ZIP, JPEG).

**Các bài toán Greedy kinh điển khác:** Kruskal/Prim (MST), bài toán đổi tiền với hệ số tiền tệ chuẩn, Dijkstra (là Greedy + Heap).

---

## CHƯƠNG 12: QUAY LUI (BACKTRACKING)

### 12.1. Nguyên lý

Thử từng lựa chọn, nếu dẫn đến ngõ cụt thì **quay lui (undo)** và thử lựa chọn khác.

### 12.2. Ví dụ kinh điển: Bài toán 8 quân hậu (N-Queens)

```cpp
#include <vector>
#include <cmath>
#include <iostream>
using namespace std;

int demLoiGiai = 0;
vector<int> banCo;

bool anToan(int hang, int cot) {
    for (int h = 0; h < hang; h++) {
        int c = banCo[h];
        if (c == cot || abs(c - cot) == abs(h - hang)) return false;
    }
    return true;
}

void backtrack(int hang, int n) {
    if (hang == n) { demLoiGiai++; return; }
    for (int cot = 0; cot < n; cot++) {
        if (anToan(hang, cot)) {
            banCo[hang] = cot;         // thử đặt hậu
            backtrack(hang + 1, n);     // đệ quy hàng tiếp theo
            banCo[hang] = -1;           // quay lui
        }
    }
}

int giaiNQueens(int n) {
    demLoiGiai = 0;
    banCo.assign(n, -1);
    backtrack(0, n);
    return demLoiGiai;
}

int main() {
    cout << "So loi giai voi N=8: " << giaiNQueens(8) << endl;   // 92
    return 0;
}
```

**Ứng dụng khác:** giải Sudoku, sinh hoán vị/tổ hợp, bài toán tô màu đồ thị (Graph Coloring), giải mê cung.

---

## CHƯƠNG 13: TỔNG KẾT

### 13.1. Bảng tổng hợp độ phức tạp các cấu trúc dữ liệu

| Cấu trúc | Truy cập | Tìm kiếm | Chèn | Xóa | C++ STL tương ứng |
|---|---|---|---|---|---|
| Array | O(1) | O(n) | O(n) | O(n) | `vector`, `array` |
| Linked List | O(n) | O(n) | O(1)* | O(1)* | `list`, `forward_list` |
| Stack/Queue | O(n) | O(n) | O(1) | O(1) | `stack`, `queue` |
| BST (cân bằng) | O(log n) | O(log n) | O(log n) | O(log n) | `map`, `set` |
| Hash Table | — | O(1) TB | O(1) TB | O(1) TB | `unordered_map`, `unordered_set` |
| Heap | — | O(n) | O(log n) | O(log n) | `priority_queue` |

*(*) Với điều kiện đã có con trỏ tới vị trí cần thao tác.*

### 13.2. Kim chỉ nam khi chọn cấu trúc dữ liệu

- Cần **truy cập ngẫu nhiên nhanh** → `vector`
- Cần **chèn/xóa liên tục ở đầu/giữa** → `list`
- Cần **xử lý theo thứ tự Vào-sau-Ra-trước** → `stack`
- Cần **xử lý theo thứ tự Vào-trước-Ra-trước** → `queue`
- Cần **tra cứu nhanh theo khóa** → `unordered_map`
- Cần **dữ liệu luôn có thứ tự + tìm kiếm nhanh** → `map`/`set`
- Cần **luôn lấy ra phần tử nhỏ/lớn nhất** → `priority_queue`
- Cần **mô hình hóa quan hệ, mạng lưới** → Graph (tự cài bằng `vector`/`unordered_map`)

### 13.3. Kim chỉ nam khi chọn chiến lược giải thuật

| Dấu hiệu bài toán | Chiến lược nên dùng |
|---|---|
| Có thể chia nhỏ độc lập rồi gộp kết quả | Chia để trị |
| Có bài toán con **chồng lặp** + cấu trúc con tối ưu | Quy hoạch động |
| Lựa chọn cục bộ tốt luôn dẫn tới lời giải tổng thể tối ưu | Tham lam |
| Cần duyệt hết không gian lời giải, có thể "cắt tỉa" sớm | Quay lui |
| Cần tối ưu đường đi/kết nối trên mạng lưới | Giải thuật đồ thị |

---

## LỜI KHUYÊN HỌC TẬP

1. **Tự cài đặt từng cấu trúc dữ liệu bằng con trỏ thô (raw pointer)** ít nhất một lần để hiểu bản chất quản lý bộ nhớ trong C++, trước khi chuyển sang dùng STL cho dự án thực tế.
2. Với mỗi thuật toán, luôn tự hỏi: *độ phức tạp thời gian/không gian là bao nhiêu? trường hợp xấu nhất xảy ra khi nào?*
3. Nắm vững STL (`vector`, `map`, `unordered_map`, `priority_queue`, `algorithm`) — phần lớn công việc thực tế là dùng đúng cấu trúc có sẵn, không phải tự viết lại.
4. Luyện tập trên LeetCode, Codeforces — biên dịch bằng C++17 trở lên để dùng được `structured bindings` (`auto [a, b] = ...`) như trong tài liệu này.
5. Luôn kiểm tra rò rỉ bộ nhớ (memory leak) khi dùng `new`/`delete` thủ công; cân nhắc dùng `unique_ptr`/`shared_ptr` trong code sản xuất.

---

*Tài liệu này bao quát khung chương trình chuẩn của môn Cấu trúc dữ liệu và Giải thuật ở bậc đại học CNTT, toàn bộ code minh họa bằng C++ (chuẩn C++17).*
