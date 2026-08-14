# HỆ THỐNG CÁC DẠNG BÀI SẮP XẾP - TÌM KIẾM (CHUYÊN SÂU CP/HSG)

---

## PHẦN 1: CÁC THUẬT TOÁN SẮP XẾP NỀN TẢNG

### 1.1. Bảng tổng quan độ phức tạp

| Thuật toán | Trung bình | Xấu nhất | Bộ nhớ phụ | Ổn định (stable) | Ghi chú |
|---|---|---|---|---|---|
| Selection Sort | O(n²) | O(n²) | O(1) | Không | Ít phép hoán đổi nhất |
| Insertion Sort | O(n²) | O(n²) | O(1) | Có | Nhanh với mảng gần đã sắp |
| Bubble Sort | O(n²) | O(n²) | O(1) | Có | Chủ yếu để dạy khái niệm |
| Merge Sort | O(n log n) | O(n log n) | O(n) | Có | Ổn định, tốt cho linked list |
| Quick Sort | O(n log n) | O(n²) | O(log n) | Không | Nhanh thực tế nhất |
| Heap Sort | O(n log n) | O(n log n) | O(1) | Không | Tại chỗ, không cần bộ nhớ phụ |
| Counting Sort | O(n + k) | O(n + k) | O(k) | Có | Chỉ áp dụng khi giá trị bị chặn |
| Radix Sort | O(d·(n+k)) | O(d·(n+k)) | O(n+k) | Có | Sắp xếp theo từng chữ số |

### Dạng 1: Merge Sort — nền tảng của Chia để trị

```cpp
void Merge(vector<int>& a, int l, int mid, int r) {
    vector<int> tmp;
    int i = l, j = mid + 1;
    while (i <= mid && j <= r) {
        if (a[i] <= a[j]) tmp.push_back(a[i++]);
        else tmp.push_back(a[j++]);
    }
    while (i <= mid) tmp.push_back(a[i++]);
    while (j <= r) tmp.push_back(a[j++]);
    for (int k = l; k <= r; k++) a[k] = tmp[k - l];
}

void MergeSort(vector<int>& a, int l, int r) {
    if (l >= r) return;
    int mid = (l + r) / 2;
    MergeSort(a, l, mid);
    MergeSort(a, mid + 1, r);
    Merge(a, l, mid, r);
}
```

**Ứng dụng CP kinh điển đi kèm Merge Sort**: đếm số cặp nghịch thế (inversion count) trong O(n log n), tận dụng ngay bước `Merge`:

```cpp
long long MergeCount(vector<int>& a, int l, int mid, int r) {
    vector<int> tmp;
    int i = l, j = mid + 1;
    long long inv = 0;
    while (i <= mid && j <= r) {
        if (a[i] <= a[j]) tmp.push_back(a[i++]);
        else {
            tmp.push_back(a[j++]);
            inv += (mid - i + 1);   // mọi phần tử còn lại bên trái đều tạo nghịch thế với a[j]
        }
    }
    while (i <= mid) tmp.push_back(a[i++]);
    while (j <= r) tmp.push_back(a[j++]);
    for (int k = l; k <= r; k++) a[k] = tmp[k - l];
    return inv;
}
```

### Dạng 2: Quick Sort — chọn chốt (pivot) và phân hoạch

```cpp
int Partition(vector<int>& a, int l, int r) {
    int pivot = a[l + rand() % (r - l + 1)]; // chọn ngẫu nhiên tránh worst-case O(n^2)
    int i = l, j = r;
    while (i <= j) {
        while (a[i] < pivot) i++;
        while (a[j] > pivot) j--;
        if (i <= j) swap(a[i++], a[j--]);
    }
    return i;
}

void QuickSort(vector<int>& a, int l, int r) {
    if (l >= r) return;
    int idx = Partition(a, l, r);
    QuickSort(a, l, idx - 1);
    QuickSort(a, idx, r);
}
```

**Biến thể CP quan trọng — Quickselect**: tìm phần tử thứ K nhỏ nhất trong O(n) trung bình mà không cần sắp xếp toàn bộ:

```cpp
int Quickselect(vector<int>& a, int l, int r, int k) {
    if (l == r) return a[l];
    int idx = Partition(a, l, r);
    if (k < idx) return Quickselect(a, l, idx - 1, k);
    else return Quickselect(a, idx, r, k);
}
```

### Dạng 3: Counting Sort / Radix Sort — khi giá trị bị chặn nhỏ

```cpp
void CountingSort(vector<int>& a, int maxVal) {
    vector<int> cnt(maxVal + 1, 0);
    for (int x : a) cnt[x]++;
    int idx = 0;
    for (int v = 0; v <= maxVal; v++)
        while (cnt[v]--) a[idx++] = v;
}
```

**Khi nào dùng**: giá trị phần tử bị chặn bởi một số k không quá lớn (k ≈ O(n)) → đạt O(n) thay vì O(n log n). Hay dùng làm bước con trong Radix Sort hoặc bài toán đếm tần suất.

---

## PHẦN 2: CÁC DẠNG BÀI TÌM KIẾM

### Dạng 4: Tìm kiếm nhị phân cổ điển (Binary Search)

```cpp
int BinarySearch(vector<int>& a, int target) {
    int l = 0, r = (int)a.size() - 1;
    while (l <= r) {
        int mid = l + (r - l) / 2;
        if (a[mid] == target) return mid;
        else if (a[mid] < target) l = mid + 1;
        else r = mid - 1;
    }
    return -1; // không tìm thấy
}
```

### Dạng 5: Tìm kiếm nhị phân trên "hàm đơn điệu" (Binary Search on Answer)

**Đặc điểm nhận dạng đề bài**: "tìm giá trị nhỏ nhất/lớn nhất sao cho điều kiện X thoả mãn", trong đó điều kiện X có tính đơn điệu (nếu x thoả thì mọi giá trị x' > x — hoặc < x — cũng thoả).

```cpp
bool KiemTra(long long x) {
    // Hàm kiểm tra điều kiện đơn điệu, tùy bài toán cụ thể
    // Ví dụ: có thể chia thành k phần sao cho mỗi phần <= x hay không
    return true; // placeholder
}

long long BinarySearchOnAnswer(long long lo, long long hi) {
    long long ans = hi;
    while (lo <= hi) {
        long long mid = lo + (hi - lo) / 2;
        if (KiemTra(mid)) {
            ans = mid;
            hi = mid - 1;    // tìm giá trị NHỎ NHẤT thoả điều kiện
        } else {
            lo = mid + 1;
        }
    }
    return ans;
}
```

**Ví dụ kinh điển để dạy dạng này**: "Chia mảng thành k đoạn sao cho tổng lớn nhất của một đoạn là nhỏ nhất có thể" (Split Array Largest Sum), "Bắn pháo hoa/chia kẹo Nguyễn Kera", "Aggressive Cows" (đặt bò sao cho khoảng cách gần nhất là lớn nhất).

### Dạng 6: `lower_bound` / `upper_bound` và ứng dụng

```cpp
vector<int> a = {1, 3, 3, 5, 7};
int x = 3;
auto it_lower = lower_bound(a.begin(), a.end(), x); // vị trí đầu tiên >= x
auto it_upper = upper_bound(a.begin(), a.end(), x); // vị trí đầu tiên > x
int count_x = it_upper - it_lower;                    // đếm số lần xuất hiện của x
```

**Ứng dụng CP kinh điển — LIS O(n log n) (Dãy con tăng dài nhất)**:

```cpp
int LIS(vector<int>& a) {
    vector<int> tail; // tail[i] = giá trị nhỏ nhất có thể kết thúc LIS độ dài i+1
    for (int x : a) {
        auto it = lower_bound(tail.begin(), tail.end(), x);
        if (it == tail.end()) tail.push_back(x);
        else *it = x;
    }
    return tail.size();
}
```

**Lưu ý dạy học**: đây là ví dụ tiêu biểu nhất cho việc kết hợp tìm kiếm nhị phân với quy hoạch động — nên nhấn mạnh `tail[]` không phải là LIS thực sự, chỉ là mảng phụ trợ để tính độ dài.

### Dạng 7: Two Pointers (Hai con trỏ) — thường đi kèm sau khi sắp xếp

```cpp
// Ví dụ: đếm số cặp (i, j) sao cho a[i] + a[j] <= x, mảng đã sắp xếp tăng dần
long long CountPairs(vector<int>& a, int x) {
    sort(a.begin(), a.end());
    int i = 0, j = (int)a.size() - 1;
    long long count = 0;
    while (i < j) {
        if (a[i] + a[j] <= x) {
            count += (j - i);   // mọi cặp (i, i+1..j) đều thoả
            i++;
        } else {
            j--;
        }
    }
    return count;
}
```

**Biến thể "Sliding Window" (cửa sổ trượt)** — hai con trỏ cùng chiều, dùng cho bài toán tổng/độ dài đoạn con thoả điều kiện:

```cpp
// Tìm độ dài đoạn con liên tiếp ngắn nhất có tổng >= target
int MinSubArrayLen(vector<int>& a, int target) {
    int n = a.size(), l = 0;
    long long sum = 0;
    int best = INT_MAX;
    for (int r = 0; r < n; r++) {
        sum += a[r];
        while (sum >= target) {
            best = min(best, r - l + 1);
            sum -= a[l++];
        }
    }
    return best == INT_MAX ? 0 : best;
}
```

### Dạng 8: Tìm kiếm nhị phân trên mảng xoay / mảng đặc biệt

```cpp
// Mảng tăng dần bị xoay tại 1 điểm, ví dụ [4,5,6,7,0,1,2]
int SearchRotated(vector<int>& a, int target) {
    int l = 0, r = a.size() - 1;
    while (l <= r) {
        int mid = (l + r) / 2;
        if (a[mid] == target) return mid;
        if (a[l] <= a[mid]) {           // nửa trái đang sắp xếp
            if (a[l] <= target && target < a[mid]) r = mid - 1;
            else l = mid + 1;
        } else {                          // nửa phải đang sắp xếp
            if (a[mid] < target && target <= a[r]) l = mid + 1;
            else r = mid - 1;
        }
    }
    return -1;
}
```

### Dạng 9: Ternary Search — tìm cực trị của hàm đơn mode (unimodal)

```cpp
double TernarySearch(function<double(double)> f, double lo, double hi) {
    for (int iter = 0; iter < 100; iter++) {
        double m1 = lo + (hi - lo) / 3;
        double m2 = hi - (hi - lo) / 3;
        if (f(m1) < f(m2)) lo = m1;  // tìm cực đại thì đổi chiều so sánh
        else hi = m2;
    }
    return (lo + hi) / 2;
}
```

---

## PHẦN 3: KỸ THUẬT SẮP XẾP ĐI KÈM CẤU TRÚC DỮ LIỆU (nâng cao)

### Dạng 10: Merge Sort Tree / Sắp xếp từng phần cho truy vấn offline

Dùng khi cần trả lời nhiều truy vấn dạng "đếm số phần tử nhỏ hơn x trong đoạn [l, r]" — mỗi node của cây phân đoạn lưu một mảng đã sắp xếp:

```cpp
vector<int> tree[400005];

void Build(int node, int l, int r, vector<int>& a) {
    if (l == r) { tree[node] = {a[l]}; return; }
    int mid = (l + r) / 2;
    Build(node*2, l, mid, a);
    Build(node*2+1, mid+1, r, a);
    merge(tree[node*2].begin(), tree[node*2].end(),
          tree[node*2+1].begin(), tree[node*2+1].end(),
          back_inserter(tree[node]));
}

// Truy vấn đếm số phần tử < x trong đoạn [l, r]
int Query(int node, int nodeL, int nodeR, int l, int r, int x) {
    if (r < nodeL || nodeR < l) return 0;
    if (l <= nodeL && nodeR <= r)
        return lower_bound(tree[node].begin(), tree[node].end(), x) - tree[node].begin();
    int mid = (nodeL + nodeR) / 2;
    return Query(node*2, nodeL, mid, l, r, x) + Query(node*2+1, mid+1, nodeR, l, r, x);
}
```

### Dạng 11: Sắp xếp theo nhiều tiêu chí (Comparator tùy chỉnh)

```cpp
struct Job { int deadline, profit; };

sort(jobs.begin(), jobs.end(), [](const Job& a, const Job& b) {
    if (a.deadline != b.deadline) return a.deadline < b.deadline;
    return a.profit > b.profit;   // tiêu chí phụ khi tiêu chí chính bằng nhau
});
```

---

## PHẦN 4: BẢNG NHẬN DẠNG DẠNG BÀI THEO ĐẶC ĐIỂM ĐỀ

| Dấu hiệu đề bài | Dạng bài | Kỹ thuật |
|---|---|---|
| "Sắp xếp lại mảng theo..." | Chọn thuật toán phù hợp độ lớn n | Phần 1 |
| "Tìm giá trị nhỏ nhất/lớn nhất sao cho..." + tính đơn điệu | Binary Search on Answer | Dạng 5 |
| "Đếm số cặp (i,j) thoả điều kiện" trên mảng đã/có thể sắp xếp | Two Pointers | Dạng 7 |
| "Đoạn con liên tiếp thoả điều kiện tổng/độ dài" | Sliding Window | Dạng 7 (biến thể) |
| "Dãy con tăng dài nhất" | LIS O(n log n) | Dạng 6 |
| Mảng đã sắp nhưng bị xoay/biến dạng | Binary Search biến thể | Dạng 8 |
| Tìm cực trị hàm lồi/lõm liên tục | Ternary Search | Dạng 9 |
| Nhiều truy vấn đếm phần tử trong đoạn | Merge Sort Tree | Dạng 10 |

---

## PHẦN 5: LỖI THƯỜNG GẶP KHI DẠY / SINH VIÊN HAY MẮC

1. **Tràn số khi tính `mid`**: luôn dùng `l + (r - l) / 2` thay vì `(l + r) / 2` để tránh tràn khi `l + r` vượt giới hạn kiểu dữ liệu.
2. **Vòng lặp vô hạn trong binary search on answer**: cần xác định rõ đang tìm giá trị nhỏ nhất hay lớn nhất thoả điều kiện để cập nhật đúng chiều `lo`/`hi`, tránh trường hợp `mid` không thay đổi khi `hi = lo + 1`.
3. **Nhầm lẫn `lower_bound` và `upper_bound`**: nên minh họa trực quan bằng dòng số có phần tử trùng lặp.
4. **Two pointers áp dụng sai khi mảng chưa sắp xếp**: cần nhấn mạnh điều kiện tiên quyết là mảng phải đơn điệu (đã sắp xếp) trừ một số biến thể sliding window đặc biệt.

---

*Phong cách trình bày tham khảo: Cẩm nang thuật toán – Lê Minh Hoàng.*
