# HỆ THỐNG THUẬT TOÁN THAM LAM (GREEDY)

---

## PHẦN 1: TƯ TƯỞNG CHUNG

Thuật toán tham lam đưa ra lựa chọn **tốt nhất tại thời điểm hiện tại** mà không xem xét lại (không truy hồi/quay lui), với hi vọng tổng hợp các lựa chọn cục bộ tối ưu sẽ cho ra lời giải tối ưu toàn cục. **Tham lam KHÔNG phải lúc nào cũng đúng** — điều kiện tiên quyết để áp dụng được là bài toán phải có:

1. **Tính chất lựa chọn tham lam (Greedy Choice Property)**: luôn tồn tại một lựa chọn tối ưu cục bộ mà không cần xem xét lại về sau.
2. **Cấu trúc con tối ưu (Optimal Substructure)**: lời giải tối ưu của bài toán chứa lời giải tối ưu của các bài toán con.

**Kỹ năng dạy quan trọng nhất**: luôn yêu cầu sinh viên **chứng minh** (bằng exchange argument hoặc quy nạp) trước khi tin vào một chiến lược tham lam, vì trực giác sai rất dễ xảy ra ở dạng bài này.

---

## PHẦN 2: CÁC DẠNG BÀI KINH ĐIỂN

### Dạng 1: Bài toán chọn hoạt động (Activity Selection)

**Đề bài**: chọn số lượng hoạt động tối đa không giao nhau về thời gian.
**Chiến lược đúng**: sắp xếp theo **thời gian kết thúc tăng dần**, luôn chọn hoạt động kết thúc sớm nhất trong các hoạt động còn khả thi.

```cpp
struct Activity { int start, finish; };

int ActivitySelection(vector<Activity>& acts) {
    sort(acts.begin(), acts.end(), [](Activity& a, Activity& b) {
        return a.finish < b.finish;
    });
    int count = 1;
    int lastFinish = acts[0].finish;
    for (int i = 1; i < (int)acts.size(); i++) {
        if (acts[i].start >= lastFinish) {
            count++;
            lastFinish = acts[i].finish;
        }
    }
    return count;
}
```

**Lưu ý dạy học**: đây là bài toán "phải dạy đầu tiên" vì có chứng minh tham lam ngắn gọn, trực quan bằng exchange argument — làm nền cho các bài toán sau.

### Dạng 2: Bài toán Cái túi phần trăm (Fractional Knapsack)

**Khác biệt cốt lõi với 0/1 Knapsack**: được lấy phần lẻ của vật → tham lam đúng, không cần QHĐ.

```cpp
struct Item { double w, v, ratio; };

double FractionalKnapsack(vector<Item>& items, double W) {
    sort(items.begin(), items.end(), [](Item& a, Item& b) {
        return a.ratio > b.ratio;  // ưu tiên tỉ suất giá trị/khối lượng cao nhất
    });
    double totalValue = 0;
    for (auto& item : items) {
        if (W <= 0) break;
        if (item.w <= W) {
            totalValue += item.v;
            W -= item.w;
        } else {
            totalValue += item.ratio * W; // lấy phần lẻ
            W = 0;
        }
    }
    return totalValue;
}
```

**Điểm mấu chốt để giảng**: đối chiếu trực tiếp với 0/1 Knapsack (file Quy hoạch động) để sinh viên hiểu rõ tại sao cùng một bài toán "gần giống nhau" nhưng một dạng dùng được tham lam, dạng kia bắt buộc phải QHĐ.

### Dạng 3: Mã hóa Huffman (Huffman Coding)

**Chiến lược**: luôn ghép 2 node có tần suất nhỏ nhất lại với nhau, dùng hàng đợi ưu tiên.

```cpp
struct HuffNode {
    int freq;
    HuffNode *left, *right;
    HuffNode(int f) : freq(f), left(nullptr), right(nullptr) {}
};

struct Compare {
    bool operator()(HuffNode* a, HuffNode* b) { return a->freq > b->freq; }
};

HuffNode* BuildHuffmanTree(vector<int>& freqs) {
    priority_queue<HuffNode*, vector<HuffNode*>, Compare> pq;
    for (int f : freqs) pq.push(new HuffNode(f));

    while (pq.size() > 1) {
        HuffNode* left = pq.top(); pq.pop();
        HuffNode* right = pq.top(); pq.pop();
        HuffNode* merged = new HuffNode(left->freq + right->freq);
        merged->left = left; merged->right = right;
        pq.push(merged);
    }
    return pq.top();
}
```

### Dạng 4: Bài toán trả tiền thối (Coin Change - Greedy, KHÔNG PHẢI LUÔN ĐÚNG)

```cpp
int CoinChangeGreedy(vector<int>& coins, int amount) {
    sort(coins.rbegin(), coins.rend()); // giảm dần
    int count = 0;
    for (int c : coins) {
        count += amount / c;
        amount %= c;
    }
    return amount == 0 ? count : -1;
}
```

**CẢNH BÁO SƯ PHẠM QUAN TRỌNG**: chiến lược này **chỉ đúng với hệ tiền "chuẩn"** (canonical coin system, ví dụ tiền Việt Nam, USD). Với hệ mệnh giá tuỳ ý (ví dụ {1, 3, 4} và amount = 6), tham lam cho kết quả sai (4+1+1=3 đồng trong khi 3+3=2 đồng là tối ưu). **Đây là ví dụ kinh điển nên đưa ra để dạy sinh viên về giới hạn của tham lam** — nên đối chiếu trực tiếp với lời giải QHĐ đúng đắn ở file Quy hoạch động (Dạng 10).

### Dạng 5: Bài toán xếp lịch giảm thiểu trễ hạn (Job Sequencing with Deadlines)

```cpp
struct Job { int deadline, profit; };

int JobSequencing(vector<Job>& jobs, int maxDeadline) {
    sort(jobs.begin(), jobs.end(), [](Job& a, Job& b) {
        return a.profit > b.profit;  // ưu tiên lợi nhuận cao nhất trước
    });
    vector<bool> slot(maxDeadline + 1, false);
    int totalProfit = 0;
    for (auto& job : jobs) {
        // Tìm chỗ trống muộn nhất có thể trước deadline của job này
        for (int t = min(maxDeadline, job.deadline); t >= 1; t--) {
            if (!slot[t]) {
                slot[t] = true;
                totalProfit += job.profit;
                break;
            }
        }
    }
    return totalProfit;
}
```

### Dạng 6: Bài toán hòn đảo/con ếch nhảy xa nhất (Jump Game)

```cpp
bool CanJump(vector<int>& nums) {
    int maxReach = 0;
    for (int i = 0; i < (int)nums.size(); i++) {
        if (i > maxReach) return false;
        maxReach = max(maxReach, i + nums[i]);
    }
    return true;
}

int MinJumps(vector<int>& nums) {
    int n = nums.size();
    int jumps = 0, curEnd = 0, farthest = 0;
    for (int i = 0; i < n - 1; i++) {
        farthest = max(farthest, i + nums[i]);
        if (i == curEnd) {
            jumps++;
            curEnd = farthest;
        }
    }
    return jumps;
}
```

### Dạng 7: Ghép cặp / Phân công tối ưu bằng sắp xếp 2 mảng ngược chiều

**Ví dụ**: cho 2 mảng, ghép mỗi phần tử mảng A với 1 phần tử mảng B để tối ưu tổng — chiến lược: sắp xếp A tăng dần, B giảm dần (hoặc ngược lại tuỳ hàm mục tiêu), ghép theo cặp.

```cpp
long long OptimalPairSum(vector<int> a, vector<int> b) {
    sort(a.begin(), a.end());
    sort(b.rbegin(), b.rend());
    long long total = 0;
    for (int i = 0; i < (int)a.size(); i++) total += (long long)a[i] * b[i];
    return total;
}
```

### Dạng 8: Bài toán "hai chỉ số" tối thiểu hoá số thao tác — Two Pointers kết hợp Greedy

**Ví dụ kinh điển**: cho mảng thuyền có sức chở tối đa, mỗi thuyền chở tối đa 2 người, tìm số thuyền ít nhất.

```cpp
int MinBoats(vector<int>& people, int limit) {
    sort(people.begin(), people.end());
    int i = 0, j = people.size() - 1, boats = 0;
    while (i <= j) {
        if (people[i] + people[j] <= limit) i++;
        j--;
        boats++;
    }
    return boats;
}
```

---

## PHẦN 3: KỸ THUẬT CHỨNG MINH THAM LAM (DẠY TƯ DUY, KHÔNG CHỈ DẠY CODE)

### 3.1. Chứng minh bằng lập luận trao đổi (Exchange Argument)

Các bước chuẩn để trình bày cho sinh viên:
1. Giả sử tồn tại lời giải tối ưu O khác với lời giải tham lam G.
2. Chỉ ra rằng có thể "trao đổi" một phần tử trong O để nó giống G hơn mà không làm giảm chất lượng lời giải.
3. Lặp lại quá trình trao đổi → O có thể biến đổi thành G mà chất lượng không đổi hoặc tốt hơn.
4. Kết luận: G cũng là lời giải tối ưu.

### 3.2. Chứng minh bằng quy nạp trên cấu trúc con tối ưu

Chỉ ra rằng nếu loại bỏ lựa chọn tham lam đầu tiên, bài toán còn lại là một bài toán con **cùng dạng** với bài toán gốc, và theo giả thiết quy nạp, tham lam giải đúng bài toán con đó.

### 3.3. Phản ví dụ (Counter-example) — công cụ dạy quan trọng không kém

Luôn khuyến khích sinh viên **thử tìm phản ví dụ trước khi tin vào 1 chiến lược tham lam** — xem Dạng 4 (Coin Change) làm ví dụ mẫu.

---

## PHẦN 4: BẢNG NHẬN DẠNG DẠNG BÀI

| Dấu hiệu đề bài | Dạng bài | Chiến lược sắp xếp |
|---|---|---|
| Chọn số hoạt động/khoảng thời gian tối đa không giao nhau | Activity Selection | Theo thời gian kết thúc tăng dần |
| Cho phép lấy "phần lẻ" của vật | Fractional Knapsack | Theo tỉ suất giá trị/khối lượng giảm dần |
| Xây mã nhị phân tối ưu theo tần suất | Huffman Coding | Ghép 2 tần suất nhỏ nhất |
| Deadline + lợi nhuận, chọn tối đa lợi nhuận | Job Sequencing | Theo lợi nhuận giảm dần |
| Mảng bước nhảy, tối thiểu số bước | Jump Game | Theo tầm xa nhất đạt được |
| Ghép cặp 2 mảng tối ưu tổng/tích | Pair Matching | Sắp xếp ngược chiều nhau |
| **Đổi tiền với mệnh giá bất kỳ** | ❌ KHÔNG dùng Greedy | Chuyển sang QHĐ |

---

## PHẦN 5: LỖI THƯỜNG GẶP KHI DẠY

1. **Áp dụng tham lam mà không chứng minh** — sinh viên dễ nhầm "trực giác đúng" với "chứng minh đúng". Luôn yêu cầu ít nhất lập luận sơ bộ.
2. **Chọn sai tiêu chí sắp xếp**: ví dụ Activity Selection nếu sắp theo thời gian bắt đầu thay vì kết thúc sẽ cho kết quả sai — nên minh hoạ bằng phản ví dụ cụ thể.
3. **Nhầm giữa bài toán có cấu trúc tương tự nhưng chiến lược khác nhau**: 0/1 Knapsack (không tham lam được) vs Fractional Knapsack (tham lam đúng) là cặp ví dụ đối chiếu quan trọng nhất.
4. **Không kiểm tra điều kiện biên**: Job Sequencing cần kiểm tra deadline hợp lệ, Coin Change Greedy cần biết trước hệ tiền có "chuẩn" hay không.

---

*Phong cách trình bày tham khảo: Cẩm nang thuật toán – Lê Minh Hoàng.*
