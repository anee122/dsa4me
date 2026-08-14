# HỆ THỐNG CÁC DẠNG BÀI SINH KẾ TIẾP (SUCCESSOR GENERATION)

Sinh kế tiếp là kỹ thuật sinh lần lượt các cấu hình tổ hợp theo một **thứ tự** cố định (thường là thứ tự từ điển), đi từ cấu hình hiện tại sang cấu hình **kế tiếp** mà không cần liệt kê lại từ đầu bằng đệ quy như quay lui. Ưu điểm: **không tốn ngăn xếp đệ quy**, tốc độ nhanh hơn, phù hợp khi cần sinh cấu hình thứ k hoặc lặp vòng lặp lớn.

---

## PHẦN 1: TƯ TƯỞNG CHUNG

Với một dãy đang xét `x[1..n]` theo thứ tự từ điển, thuật toán sinh kế tiếp luôn theo khuôn mẫu:

1. Tìm từ phải sang trái vị trí `i` đầu tiên "còn có thể tăng được" (điểm neo - pivot).
2. Tăng giá trị tại vị trí `i` lên mức hợp lệ tiếp theo.
3. Gán lại các vị trí phía sau `i` theo cấu hình **nhỏ nhất có thể** (thường là tăng dần).
4. Nếu không tìm được vị trí `i` nào → đã hết cấu hình (kết thúc).

Độ phức tạp trung bình mỗi lần sinh: **O(1) amortized** hoặc O(n) trong trường hợp xấu nhất — vượt trội so với quay lui khi cần duyệt tuần tự toàn bộ không gian.

---

## Dạng 1: Sinh dãy nhị phân kế tiếp (đếm nhị phân)

**Bản chất**: dãy nhị phân độ dài n tương ứng với số nhị phân từ 0 đến 2^n - 1. Sinh kế tiếp = "cộng 1" vào số nhị phân.

```cpp
bool NextBinary(vector<int>& x) {
    int n = x.size();
    int i = n - 1;
    while (i >= 0 && x[i] == 1) {
        x[i] = 0;   // giống phép nhớ khi cộng 1
        i--;
    }
    if (i < 0) return false; // đã tràn, hết dãy
    x[i] = 1;
    return true;
}

int main() {
    int n = 4;
    vector<int> x(n, 0);
    do {
        for (int v : x) cout << v;
        cout << "\n";
    } while (NextBinary(x));
}
```

## Dạng 2: Sinh hoán vị kế tiếp — next_permutation tự cài đặt

**Thuật toán chuẩn (Narayana Pandita)**:
1. Tìm chỉ số lớn nhất `i` sao cho `a[i] < a[i+1]` (đi từ phải sang trái).
2. Nếu không có `i` → đây là hoán vị lớn nhất, hết dãy.
3. Tìm chỉ số lớn nhất `j > i` sao cho `a[j] > a[i]`.
4. Đổi chỗ `a[i]` và `a[j]`.
5. Đảo ngược đoạn từ `i+1` đến hết.

```cpp
bool NextPermutation(vector<int>& a) {
    int n = a.size();
    int i = n - 2;
    while (i >= 0 && a[i] >= a[i+1]) i--;   // bước 1
    if (i < 0) return false;                 // bước 2: đã là hoán vị cuối
    int j = n - 1;
    while (a[j] <= a[i]) j--;                // bước 3
    swap(a[i], a[j]);                        // bước 4
    reverse(a.begin() + i + 1, a.end());     // bước 5
    return true;
}
```

**Sinh hoán vị kế tiếp TRƯỚC (prev_permutation)**: đảo chiều toàn bộ so sánh (`<` thành `>`), tư duy đối xứng.

**Biến thể hay gặp trong CP**: 
- Tìm hoán vị thứ k theo thứ tự từ điển (dùng giai thừa + phép chia, KHÔNG lặp next_permutation k lần vì quá chậm — xem Dạng 5).
- Tìm số thứ tự (rank) của một hoán vị cho trước.

## Dạng 3: Sinh tổ hợp chập k kế tiếp

**Ý tưởng**: dãy tăng ngặt `x[1] < x[2] < ... < x[k]`, mỗi `x[i] ∈ [1, n]`. Tìm từ phải sang trái vị trí có thể tăng mà không vi phạm khoảng trống cần để các vị trí sau đủ chỗ.

```cpp
bool NextCombination(vector<int>& x, int n) {
    int k = x.size();
    int i = k - 1;
    // điều kiện "còn tăng được": x[i] chưa chạm giá trị lớn nhất cho phép ở vị trí i
    while (i >= 0 && x[i] == n - k + i + 1) i--;
    if (i < 0) return false;
    x[i]++;
    for (int j = i + 1; j < k; j++)
        x[j] = x[j-1] + 1;   // gán lại phần đuôi nhỏ nhất có thể
    return true;
}

int main() {
    int n = 5, k = 3;
    vector<int> x(k);
    iota(x.begin(), x.end(), 1);   // khởi tạo 1,2,3
    do {
        for (int v : x) cout << v << " ";
        cout << "\n";
    } while (NextCombination(x, n));
}
```

## Dạng 4: Sinh tập con kế tiếp theo thứ tự tăng dần của "mặt nạ nhị phân" (bitmask)

Không dùng công thức tăng/giảm như trên mà lặp trực tiếp qua toàn bộ số nguyên từ `0` đến `2^n - 1`, mỗi bit biểu diễn có/không chọn phần tử — bản chất đây cũng là một dạng "sinh kế tiếp" đơn giản và cực nhanh:

```cpp
int n = 4;
for (int mask = 0; mask < (1 << n); mask++) {
    for (int i = 0; i < n; i++)
        if (mask & (1 << i)) cout << i + 1 << " ";
    cout << "\n";
}
```

**Kỹ thuật CP nâng cao đi kèm — Duyệt tập con của một tập con (submask enumeration)**:
```cpp
// Duyệt tất cả submask của mask, độ phức tạp tổng O(3^n)
for (int sub = mask; ; sub = (sub - 1) & mask) {
    // xử lý sub
    if (sub == 0) break;
}
```

## Dạng 5: Sinh cấu hình thứ K trực tiếp (không lặp tuần tự) — Kỹ thuật "đếm để xác định vị trí"

Đây là kỹ thuật chuyên sâu thường gặp trong đề CP/HSG: thay vì gọi kế tiếp K lần (tốn O(K·n)), ta xác định trực tiếp từng vị trí bằng cách **đếm số cấu hình bắt đầu bởi từng lựa chọn**.

**Ví dụ: Tìm hoán vị thứ K (1-indexed) của {1,...,n} theo thứ tự từ điển**

```cpp
// Cho biết có bao nhiêu hoán vị bắt đầu bởi 1 giá trị cố định: đó là (n - vi_tri)!
long long fact[21];
void PrecomputeFactorial() {
    fact[0] = 1;
    for (int i = 1; i <= 20; i++) fact[i] = fact[i-1] * i;
}

vector<int> KthPermutation(int n, long long k) {
    vector<int> candidates(n);
    iota(candidates.begin(), candidates.end(), 1);
    vector<int> result;
    k--; // chuyển về 0-indexed
    for (int i = n; i >= 1; i--) {
        long long block = fact[i - 1];       // số hoán vị ứng với mỗi lựa chọn đầu
        int idx = k / block;                  // chọn ứng viên thứ idx
        result.push_back(candidates[idx]);
        candidates.erase(candidates.begin() + idx);
        k %= block;
    }
    return result;
}
```

**Ứng dụng tương tự cho tổ hợp thứ K**: dùng công thức `C(n, k)` để đếm số tổ hợp bắt đầu bởi việc "chọn" hay "không chọn" phần tử đang xét, từ đó xác định trực tiếp — tránh sinh tuần tự khi K rất lớn (đến 10^18).

## Dạng 6: Sinh dãy con có tổng/tích cố định theo thứ tự tăng dần (kỹ thuật multiset / heap)

Thường gặp trong bài "in ra m số nhỏ nhất dạng 2^a * 3^b * 5^c..." (Ugly numbers / Hamming numbers) — bản chất là sinh kế tiếp trên tập vô hạn bằng hàng đợi ưu tiên.

```cpp
vector<long long> GenerateHammingNumbers(int m) {
    priority_queue<long long, vector<long long>, greater<long long>> pq;
    set<long long> seen;
    pq.push(1); seen.insert(1);
    vector<long long> result;
    int primes[3] = {2, 3, 5};

    while ((int)result.size() < m) {
        long long cur = pq.top(); pq.pop();
        result.push_back(cur);
        for (int p : primes) {
            long long nxt = cur * p;
            if (!seen.count(nxt)) {
                seen.insert(nxt);
                pq.push(nxt);
            }
        }
    }
    return result;
}
```

---

## PHẦN 2: BẢNG SO SÁNH SINH KẾ TIẾP vs QUAY LUI

| Tiêu chí | Sinh kế tiếp | Quay lui (đệ quy) |
|---|---|---|
| Bộ nhớ | O(n), không cần ngăn xếp đệ quy | O(n) ngăn xếp đệ quy, có thể tràn stack nếu n lớn |
| Tốc độ | Nhanh hơn (không có overhead gọi hàm) | Chậm hơn |
| Truy cập cấu hình thứ K | Có thể làm trực tiếp O(n) hoặc O(n log n) | Phải sinh từ đầu, O(K) |
| Độ trực quan khi dạy | Khó hình dung hơn, cần chứng minh đúng đắn | Trực quan, dễ dạy trước |
| Mở rộng thêm điều kiện lọc phức tạp | Khó chỉnh sửa | Dễ chèn thêm điều kiện |

**Gợi ý giảng dạy**: nên dạy quay lui trước để sinh viên hiểu bản chất không gian tổ hợp, sau đó giới thiệu sinh kế tiếp như một "tối ưu hóa" cho các trường hợp cần hiệu năng cao hoặc cần truy cập cấu hình thứ K.

---

## PHẦN 3: BÀI TẬP GỢI Ý THEO MỨC ĐỘ

1. **Cơ bản**: cài đặt lại `next_permutation`, `NextCombination`, `NextBinary` từ đầu (không dùng thư viện).
2. **Trung bình**: tìm số thứ tự (rank) của một hoán vị/tổ hợp cho trước trong thứ tự từ điển.
3. **Nâng cao**: tìm hoán vị/tổ hợp thứ K với K lên đến 10^18 (đòi hỏi số học lớn hoặc kiểm tra tràn số).
4. **CP/HSG**: kết hợp sinh kế tiếp với kỹ thuật hai con trỏ hoặc BFS trên không gian trạng thái để sinh cấu hình theo tổng/tích tăng dần (Ugly Numbers, Super Ugly Numbers).

---

*Phong cách trình bày tham khảo: Cẩm nang thuật toán – Lê Minh Hoàng.*
