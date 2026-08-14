# HỆ THỐNG THUẬT TOÁN CHIA ĐỂ TRỊ (DIVIDE AND CONQUER)

---

## PHẦN 1: TƯ TƯỞNG CHUNG VÀ PHÂN TÍCH ĐỘ PHỨC TẠP

Chia để trị gồm 3 bước:
1. **Chia (Divide)**: chia bài toán thành các bài toán con nhỏ hơn, cùng dạng.
2. **Trị (Conquer)**: giải đệ quy từng bài toán con (đến khi đủ nhỏ thì giải trực tiếp).
3. **Kết hợp (Combine)**: gộp lời giải các bài toán con thành lời giải bài toán gốc.

### Công thức truy hồi tổng quát (Master Theorem)

Với `T(n) = a·T(n/b) + f(n)`, so sánh `f(n)` với `n^(log_b a)`:

| Trường hợp | Điều kiện | Kết quả |
|---|---|---|
| 1 | f(n) = O(n^(log_b a - ε)) | T(n) = Θ(n^(log_b a)) |
| 2 | f(n) = Θ(n^(log_b a)) | T(n) = Θ(n^(log_b a) · log n) |
| 3 | f(n) = Ω(n^(log_b a + ε)) và điều kiện regularity | T(n) = Θ(f(n)) |

**Ví dụ áp dụng**: Merge Sort có `T(n) = 2T(n/2) + O(n)` → a=2, b=2, log_b a=1, f(n)=Θ(n) → rơi vào trường hợp 2 → T(n) = Θ(n log n).

---

## PHẦN 2: CÁC DẠNG BÀI KINH ĐIỂN

### Dạng 1: Merge Sort / Quick Sort

Đã trình bày chi tiết ở file "Sắp xếp - Tìm kiếm" (Dạng 1-2) — đây là 2 ví dụ nền tảng nhất của Chia để trị, nên dạy lại ngắn gọn ở đây với trọng tâm là **phân tích độ phức tạp bằng cây đệ quy** thay vì trọng tâm cài đặt.

### Dạng 2: Tìm kiếm nhị phân (Binary Search) như một dạng Chia để trị đặc biệt

Đặc biệt vì chỉ có **1 bài toán con** cần giải (a=1), không cần bước Combine. Đã trình bày ở file Sắp xếp - Tìm kiếm.

### Dạng 3: Nhân 2 số lớn — Thuật toán Karatsuba

**Ý tưởng**: thay vì nhân trực tiếp O(n²), chia mỗi số thành 2 nửa và chỉ cần 3 phép nhân con thay vì 4.

```cpp
// x = x1*10^(n/2) + x0,  y = y1*10^(n/2) + y0
// x*y = z2*10^n + z1*10^(n/2) + z0
// z2 = x1*y1,  z0 = x0*y0,  z1 = (x1+x0)*(y1+y0) - z2 - z0   <- chỉ cần 3 phép nhân
// Độ phức tạp: T(n) = 3T(n/2) + O(n) => O(n^log2(3)) ~ O(n^1.585)

typedef vector<int> BigInt; // biểu diễn số lớn, mỗi phần tử 1 chữ số

BigInt Karatsuba(BigInt x, BigInt y) {
    int n = max(x.size(), y.size());
    if (n <= 32) { /* nhân trực tiếp O(n^2) khi n nhỏ, tránh overhead đệ quy */ }
    int half = n / 2;
    // Chia x, y thành x1,x0,y1,y0 rồi tính z2, z0, z1 như trên (chi tiết cài đặt tùy biểu diễn số lớn)
    BigInt result; // gộp z2, z1, z0 lại theo trọng số 10^n, 10^(n/2)
    return result;
}
```

**Lưu ý dạy học**: đây là ví dụ tốt nhất để minh hoạ tại sao "giảm số phép toán con" (3 thay vì 4) lại thay đổi hẳn lớp độ phức tạp — điểm mấu chốt của tư duy Chia để trị nâng cao.

### Dạng 4: Nhân ma trận — Thuật toán Strassen

Tương tự Karatsuba nhưng cho nhân ma trận: giảm từ 8 phép nhân ma trận con xuống còn 7, đạt độ phức tạp O(n^log2(7)) ≈ O(n^2.807) thay vì O(n³).

```cpp
// Với 2 ma trận vuông cấp n chia thành 4 khối cấp n/2:
// M1 = (A11+A22)(B11+B22)
// M2 = (A21+A22)B11
// M3 = A11(B12-B22)
// M4 = A22(B21-B11)
// M5 = (A11+A12)B22
// M6 = (A21-A11)(B11+B12)
// M7 = (A12-A22)(B21+B22)
// C11 = M1+M4-M5+M7,  C12 = M3+M5,  C21 = M2+M4,  C22 = M1-M2+M3+M6
```

**Ghi chú giảng dạy**: Strassen chủ yếu mang tính lý thuyết, ít dùng thực tế vì hằng số ẩn lớn và kém ổn định số học — nên trình bày như minh hoạ tư duy, không yêu cầu cài đặt đầy đủ.

### Dạng 5: Cặp điểm gần nhau nhất (Closest Pair of Points)

**Ý tưởng**: chia mặt phẳng theo trục x thành 2 nửa, giải đệ quy từng nửa, sau đó chỉ cần xét dải hẹp quanh đường chia để kết hợp — đạt O(n log n) thay vì O(n²) duyệt toàn bộ cặp.

```cpp
struct Point { double x, y; };

double Dist(Point a, Point b) {
    return sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
}

double ClosestPairRec(vector<Point>& pts, int l, int r) {
    // pts đã sắp xếp theo x
    if (r - l <= 3) {
        double best = 1e18;
        for (int i = l; i <= r; i++)
            for (int j = i+1; j <= r; j++)
                best = min(best, Dist(pts[i], pts[j]));
        return best;
    }
    int mid = (l + r) / 2;
    double midX = pts[mid].x;
    double d1 = ClosestPairRec(pts, l, mid);
    double d2 = ClosestPairRec(pts, mid + 1, r);
    double d = min(d1, d2);

    // Xét dải hẹp quanh midX, chỉ cần so sánh với vài điểm lân cận theo y
    vector<Point> strip;
    for (int i = l; i <= r; i++)
        if (fabs(pts[i].x - midX) < d) strip.push_back(pts[i]);
    sort(strip.begin(), strip.end(), [](Point a, Point b){ return a.y < b.y; });

    for (int i = 0; i < (int)strip.size(); i++)
        for (int j = i+1; j < (int)strip.size() && strip[j].y - strip[i].y < d; j++)
            d = min(d, Dist(strip[i], strip[j]));

    return d;
}
```

### Dạng 6: Đếm nghịch thế (Inversion Count)

Đã trình bày chi tiết ở file Sắp xếp - Tìm kiếm (kết hợp trong Merge Sort) — nên nhắc lại ở đây như ví dụ về việc "tận dụng bước Combine sẵn có để giải quyết thêm 1 bài toán phụ" mà không tăng độ phức tạp tổng thể.

### Dạng 7: Lũy thừa nhanh (Fast Exponentiation) — Chia để trị trên số mũ

```cpp
long long PowerFast(long long base, long long exp, long long mod) {
    long long result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) result = (result * base) % mod;
        base = (base * base) % mod;
        exp >>= 1;
    }
    return result;
}
```

**Bản đệ quy tường minh (đúng tinh thần chia để trị)**:
```cpp
long long PowerRecursive(long long base, long long exp, long long mod) {
    if (exp == 0) return 1;
    long long half = PowerRecursive(base, exp / 2, mod);
    long long result = (half * half) % mod;
    if (exp % 2 == 1) result = (result * base) % mod;
    return result;
}
```

**Ứng dụng mở rộng cùng tư tưởng**: nhân ma trận nhanh để tính số Fibonacci thứ n trong O(log n), giải công thức truy hồi tuyến tính bậc k bất kỳ.

### Dạng 8: Tìm phần tử xuất hiện nhiều hơn n/2 lần (Majority Element) bằng Chia để trị

```cpp
int CountInRange(vector<int>& a, int l, int r, int val) {
    int count = 0;
    for (int i = l; i <= r; i++) if (a[i] == val) count++;
    return count;
}

int MajorityRec(vector<int>& a, int l, int r) {
    if (l == r) return a[l];
    int mid = (l + r) / 2;
    int leftMajority = MajorityRec(a, l, mid);
    int rightMajority = MajorityRec(a, mid + 1, r);
    if (leftMajority == rightMajority) return leftMajority;

    int leftCount = CountInRange(a, l, r, leftMajority);
    int rightCount = CountInRange(a, l, r, rightMajority);
    return leftCount > rightCount ? leftMajority : rightMajority;
}
```

**Ghi chú giảng dạy**: bài này thường được dùng để đối chiếu với thuật toán Boyer-Moore Voting (O(n), không cần chia để trị) — giúp sinh viên thấy Chia để trị không phải lúc nào cũng là lựa chọn tối ưu nhất.

---

## PHẦN 3: BẢNG NHẬN DẠNG DẠNG BÀI

| Dấu hiệu đề bài | Dạng bài | Độ phức tạp đạt được |
|---|---|---|
| Sắp xếp mảng | Merge/Quick Sort | O(n log n) |
| Tìm kiếm trên dãy đã sắp xếp | Binary Search | O(log n) |
| Nhân 2 số/đa thức bậc cao | Karatsuba | O(n^1.585) |
| Nhân ma trận lớn | Strassen | O(n^2.807) |
| Tìm cặp điểm gần nhất trong mặt phẳng | Closest Pair | O(n log n) |
| Đếm cặp "nghịch đảo" trong mảng | Inversion Count | O(n log n) |
| Tính a^n mod m nhanh | Fast Exponentiation | O(log n) |
| Tìm phần tử đa số | Majority Element (D&C) | O(n log n) — nhưng Boyer-Moore O(n) tốt hơn |

---

## PHẦN 4: LỖI THƯỜNG GẶP KHI DẠY

1. **Không phân tích độ phức tạp bằng công thức truy hồi** — sinh viên code đúng nhưng không hiểu tại sao thuật toán lại nhanh. Nên luôn đi kèm cây đệ quy minh hoạ.
2. **Bỏ sót bước Combine** khi bài toán con không độc lập hoàn toàn (ví dụ Closest Pair cần xét dải giữa).
3. **Đệ quy quá sâu** gây tràn ngăn xếp — với Merge Sort/Quick Sort trên mảng rất lớn nên cân nhắc chuyển sang phiên bản lặp hoặc tăng giới hạn stack.
4. **Nhầm chia để trị với quy hoạch động**: điểm khác biệt cốt lõi là D&C có các bài toán con **độc lập, không chồng lặp** — nếu bài toán con lặp lại nhiều lần, nên chuyển sang QHĐ (nhớ hoá) để tránh làm lại công việc.

---

*Phong cách trình bày tham khảo: Cẩm nang thuật toán – Lê Minh Hoàng.*
