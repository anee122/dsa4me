# HỆ THỐNG CÁC DẠNG BÀI QUAY LUI (BACKTRACKING) VÀ NHÁNH CẬN (BRANCH AND BOUND)

---

## PHẦN 1: TỔNG QUAN KIẾN TRÚC CHUNG

### 1.1. Sơ đồ khung của một hàm quay lui

Mọi bài quay lui đều có thể quy về khung sau:

```cpp
void TryStep(int step) {
    if (step > n) {          // Điều kiện dừng: đã xây xong lời giải
        Result();             // Xử lý / ghi nhận lời giải
        return;
    }
    for (candidate = danh_sach_lua_chon(step)) {
        if (ThoaManDieuKien(candidate, step)) {   // Kiểm tra tính hợp lệ
            ChonCandidate(candidate, step);       // "Đi tới"
            TryStep(step + 1);                    // Đệ quy xuống bước sau
            HuyChonCandidate(candidate, step);    // "Quay lui" - undo
        }
    }
}
```

**3 thành phần bắt buộc phải xác định khi giải 1 bài quay lui:**
1. **Không gian trạng thái**: mỗi bước chọn cái gì, tập ứng viên là gì.
2. **Điều kiện chấp nhận (constraint check)**: candidate có hợp lệ với các bước trước không.
3. **Điều kiện dừng (goal test)**: khi nào thì đã có 1 lời giải đầy đủ.

### 1.2. Khung của Nhánh cận (mở rộng từ quay lui)

Nhánh cận = Quay lui + **hàm đánh giá cận (bound function)** để cắt tỉa sớm những nhánh chắc chắn không tốt hơn lời giải tốt nhất đã tìm được.

```cpp
void TryStep(int step, int currentValue) {
    if (step > n) {
        if (currentValue > best) best = currentValue; // cập nhật kỷ lục
        return;
    }
    for (candidate = danh_sach_lua_chon(step)) {
        if (ThoaManDieuKien(candidate, step)) {
            int newValue = currentValue + Gia_tri(candidate);
            int can = Uoc_luong_can(step, newValue); // cận trên phần còn lại
            if (can > best) {          // chỉ đi tiếp nếu còn "hi vọng" vượt best
                ChonCandidate(candidate, step);
                TryStep(step + 1, newValue);
                HuyChonCandidate(candidate, step);
            }
        }
    }
}
```

Khác biệt cốt lõi so với quay lui thuần: **có thêm hàm cận** và **so sánh với best hiện tại** để quyết định có "vào nhánh" hay không.

---

## PHẦN 2: CÁC DẠNG BÀI QUAY LUI KINH ĐIỂN

### Dạng 1: Liệt kê dãy nhị phân độ dài n

**Hướng giải**: mỗi bước chọn 0 hoặc 1, không cần điều kiện ràng buộc.

```cpp
int n, x[100];

void TryStep(int step) {
    if (step > n) {
        for (int i = 1; i <= n; i++) cout << x[i];
        cout << "\n";
        return;
    }
    for (int v = 0; v <= 1; v++) {
        x[step] = v;
        TryStep(step + 1);
    }
}
```

### Dạng 2: Liệt kê hoán vị (Permutation)

**Đặc điểm nhận dạng**: mỗi phần tử 1..n chỉ được dùng đúng 1 lần → cần mảng `used[]` đánh dấu.

```cpp
int n, x[100];
bool used[100];

void TryStep(int step) {
    if (step > n) {
        for (int i = 1; i <= n; i++) cout << x[i] << " ";
        cout << "\n";
        return;
    }
    for (int v = 1; v <= n; v++) {
        if (!used[v]) {
            x[step] = v;
            used[v] = true;
            TryStep(step + 1);
            used[v] = false;   // quay lui
        }
    }
}
```

**Biến thể**: sinh hoán vị bằng `next_permutation` (không phải quay lui, nhưng hay đi kèm chủ đề này để so sánh):
```cpp
vector<int> a = {1,2,3,4};
sort(a.begin(), a.end());
do {
    for (int x : a) cout << x << " ";
    cout << "\n";
} while (next_permutation(a.begin(), a.end()));
```

### Dạng 3: Liệt kê tổ hợp chập k của n (k-combinations)

**Đặc điểm nhận dạng**: chọn k phần tử không kể thứ tự, tránh trùng bằng cách ép **chỉ chọn phần tử lớn hơn phần tử trước đó**.

```cpp
int n, k, x[100];

void TryStep(int step) {
    if (step > k) {
        for (int i = 1; i <= k; i++) cout << x[i] << " ";
        cout << "\n";
        return;
    }
    // v bắt đầu từ x[step-1]+1 để đảm bảo dãy tăng dần -> không trùng tổ hợp
    for (int v = x[step-1] + 1; v <= n; v++) {
        x[step] = v;
        TryStep(step + 1);
    }
}
// gọi TryStep(1), với x[0] = 0
```

**Lưu ý dạy học**: đây chính là ý tưởng để thầy/cô giải thích tại sao cần "cắt tỉa còn đủ chỗ": có thể thêm điều kiện `v <= n - (k - step)` để bỏ qua các nhánh không đủ phần tử còn lại — đây là bước đệm dẫn vào tư duy nhánh cận.

### Dạng 4: Liệt kê tập con (Subset)

```cpp
int n, x[100]; // x[i] = 1 nếu chọn phần tử i, 0 nếu không

void TryStep(int step) {
    if (step > n) {
        for (int i = 1; i <= n; i++)
            if (x[i]) cout << i << " ";
        cout << "\n";
        return;
    }
    x[step] = 0; TryStep(step + 1);
    x[step] = 1; TryStep(step + 1);
}
```

### Dạng 5: Bài toán N-Quân hậu (N-Queens)

**Đặc điểm nhận dạng**: ràng buộc không cùng cột, không cùng đường chéo chính, không cùng đường chéo phụ.

```cpp
int n, x[100];
bool colUsed[100], diag1[210], diag2[210];

bool ThoaManDieuKien(int col, int row) {
    return !colUsed[col] && !diag1[row + col] && !diag2[row - col + n];
}

void TryStep(int row) {
    if (row > n) {
        for (int i = 1; i <= n; i++) cout << x[i] << " ";
        cout << "\n";
        return;
    }
    for (int col = 1; col <= n; col++) {
        if (ThoaManDieuKien(col, row)) {
            x[row] = col;
            colUsed[col] = diag1[row+col] = diag2[row-col+n] = true;
            TryStep(row + 1);
            colUsed[col] = diag1[row+col] = diag2[row-col+n] = false;
        }
    }
}
```

**Điểm mấu chốt để giảng**: đường chéo `\` có `row - col` là hằng số, đường chéo `/` có `row + col` là hằng số → dùng làm chỉ số mảng đánh dấu (cộng thêm n để tránh chỉ số âm).

### Dạng 6: Sinh xâu/ dãy con thỏa điều kiện đặc biệt

Ví dụ: liệt kê các dãy tăng ngặt độ dài bất kỳ từ tập số, hoặc các xâu ký tự không chứa 2 ký tự giống nhau liên tiếp. **Hướng giải chung**: giữ nguyên khung Dạng 1/4, chỉ thay đổi hàm `ThoaManDieuKien`.

---

## PHẦN 3: CÁC DẠNG BÀI NHÁNH CẬN KINH ĐIỂN

### Dạng 7: Bài toán Cái túi 0/1 (0/1 Knapsack) bằng nhánh cận

**Ý tưởng cận**: sắp xếp vật theo tỉ suất giá trị/khối lượng giảm dần, ước lượng cận trên bằng cách cho phép "lấy phần lẻ" của vật tiếp theo (nới lỏng bài toán rời rạc thành bài toán liên tục — đây chính là cận Dantzig).

```cpp
struct Item { double w, v, ratio; };
int n;
double W;              // trọng lượng túi
Item item[100];         // đã sắp xếp giảm dần theo ratio = v/w
double best = 0;
bool chosenBest[100], chosen[100];

double Bound(int step, double remainW, double curVal) {
    double bound = curVal;
    int i = step;
    while (i <= n && item[i].w <= remainW) {
        remainW -= item[i].w;
        bound += item[i].v;
        i++;
    }
    if (i <= n) bound += remainW * item[i].ratio; // lấy phần lẻ (nới lỏng)
    return bound;
}

void TryStep(int step, double remainW, double curVal) {
    if (step > n) {
        if (curVal > best) {
            best = curVal;
            for (int i = 1; i <= n; i++) chosenBest[i] = chosen[i];
        }
        return;
    }
    // Nhánh 1: thử LẤY vật step trước (thường cho cận tốt hơn, nên duyệt trước)
    if (item[step].w <= remainW) {
        chosen[step] = true;
        double newBound = Bound(step + 1, remainW - item[step].w, curVal + item[step].v);
        if (newBound > best) {
            TryStep(step + 1, remainW - item[step].w, curVal + item[step].v);
        }
        chosen[step] = false;
    }
    // Nhánh 2: thử KHÔNG LẤY vật step
    double newBound2 = Bound(step + 1, remainW, curVal);
    if (newBound2 > best) {
        TryStep(step + 1, remainW, curVal);
    }
}
```

**Điểm mấu chốt để giảng**: khác với quy hoạch động, nhánh cận không cần bảng phụ, hiệu quả khi n lớn nhưng W lớn (QHĐ tốn bộ nhớ). Cận Dantzig là ví dụ chuẩn để học sinh hiểu "nới lỏng bài toán (relaxation)".

### Dạng 8: Bài toán Người du lịch (TSP) bằng nhánh cận

**Ý tưởng cận đơn giản (cận cạnh nhỏ nhất)**: với mỗi đỉnh chưa thăm, cận dưới của phần đường đi còn lại được ước lượng bằng tổng 2 cạnh nhỏ nhất xuất phát từ mỗi đỉnh còn lại, chia đôi.

```cpp
int n;
double a[50][50];         // ma trận trọng số
int x[50];
bool visited[50];
double best = 1e18;
int bestPath[50];

double LowerBound(int step, double curLen, bool vis[]) {
    // Cận đơn giản: tổng cạnh đã đi + (n - step + 1) * min cạnh còn lại (tuỳ cách chọn)
    double bound = curLen;
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            double minEdge = 1e18;
            for (int j = 1; j <= n; j++)
                if (i != j) minEdge = min(minEdge, a[i][j]);
            bound += minEdge;
        }
    }
    return bound;
}

void TryStep(int step, double curLen) {
    if (step > n) {
        double total = curLen + a[x[n]][x[1]]; // quay về điểm xuất phát
        if (total < best) {
            best = total;
            for (int i = 1; i <= n; i++) bestPath[i] = x[i];
        }
        return;
    }
    for (int v = 1; v <= n; v++) {
        if (!visited[v]) {
            double newLen = curLen + a[x[step-1]][v];
            visited[v] = true;
            x[step] = v;
            double lb = LowerBound(step + 1, newLen, visited);
            if (lb < best) {              // cận DƯỚI: chỉ đi tiếp nếu còn cơ hội < best
                TryStep(step + 1, newLen);
            }
            visited[v] = false;
        }
    }
}
// x[1] gán cố định = 1 (đỉnh xuất phát) để giảm không gian tìm kiếm (loại hoán vị vòng)
```

**Lưu ý dạy học quan trọng**: TSP là bài toán **tìm min** nên cận là **cận dưới** và điều kiện đi tiếp là `lb < best` — ngược chiều so với Cái túi (bài toán **tìm max** dùng **cận trên**, điều kiện đi tiếp là `bound > best`). Đây là chỗ sinh viên hay nhầm nhất, nên nhấn mạnh riêng.

### Dạng 9: Tô màu đồ thị / Phân công công việc bằng nhánh cận

Khung tương tự N-Queens (Dạng 5) nhưng thêm cận: ví dụ cận dưới số màu cần dùng = bậc lớn nhất + 1, dùng để cắt khi số màu đang thử vượt quá cận.

---

## PHẦN 4: BẢNG SO SÁNH — GIÚP SINH VIÊN CHỌN ĐÚNG DẠNG

| Dấu hiệu đề bài | Dạng bài | Kỹ thuật |
|---|---|---|
| "Liệt kê tất cả..." không có tối ưu | Quay lui thuần | Dạng 1–6 |
| Mỗi phần tử dùng đúng 1 lần, có thứ tự | Hoán vị | Dạng 2 |
| Chọn k phần tử, không thứ tự | Tổ hợp | Dạng 3 |
| Chọn tuỳ ý số phần tử | Tập con | Dạng 4 |
| Ràng buộc theo hàng/cột/đường chéo | Kiểu N-Queens | Dạng 5 |
| "Tìm giá trị lớn nhất/nhỏ nhất thoả ràng buộc", n nhỏ (n ≤ 20–25) nhưng QHĐ không khả thi (trọng số lớn, không nguyên) | Nhánh cận | Dạng 7–9 |
| Bài toán chu trình, khoảng cách, có ma trận trọng số | TSP dạng nhánh cận | Dạng 8 |

---

## PHẦN 5: KỸ THUẬT TỐI ƯU HÓA CHUNG KHI DẠY

1. **Sắp xếp trước dữ liệu** (theo tỉ suất, theo trọng số...) thường giúp cận chặt hơn và tìm ra lời giải tốt gần đầu sớm hơn → cắt tỉa hiệu quả hơn.
2. **Thứ tự duyệt nhánh**: nên thử nhánh "có khả năng tốt" trước (ví dụ LẤY vật trước trong Knapsack) để best được cập nhật sớm, giúp các nhánh sau bị cắt nhiều hơn.
3. **Độ phức tạp**: luôn nhấn mạnh quay lui/nhánh cận có độ phức tạp mũ trong trường hợp xấu nhất — nhánh cận chỉ giảm hằng số thực tế, không đổi lớp độ phức tạp lý thuyết.
4. **Global vs tham số truyền tay**: với sinh viên mới, dùng biến toàn cục (`x[]`, `used[]`, `best`) cho dễ hình dung; với sinh viên khá, có thể chuyển sang truyền tham chiếu để code sạch hơn.

---

*Tài liệu tham khảo phong cách trình bày: Cẩm nang thuật toán – Lê Minh Hoàng.*
