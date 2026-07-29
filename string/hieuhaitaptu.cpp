// Cho hai xâu ký tự S1 và S2. Hãy viết chương trình tìm các từ chỉ xuất hiện trong S1 mà không xuất hiện trong S2. Chú ý: mỗi từ chỉ liệt kê 1 lần.
// Dữ liệu vào: Dòng 1 ghi số bộ test. Mỗi bộ test gồm 2 dòng, mỗi dòng ghi một xâu ký tự độ dài không quá 200, chỉ bao gồm các ký tự viết thường và các khoảng trống. 
// Kết quả: Với mỗi bộ test ghi ra các từ có trong S1 mà không có trong S2. Các từ được ghi theo thứ tự từ điển.

//input: 
// 2
// abc ab ab ab abcd
// ab abc
// aaa xyz ab zzz abc dd dd abc
// xyz dd ttt sas cdc

// output:
// abcd
// aaa ab abc zzz


#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;
    cin.ignore();

    while (t--) {
        string s1, s2;
        getline(cin, s1);
        getline(cin, s2);

        set<string> st1, st2;

        stringstream ss1(s1), ss2(s2);
        string word;

        while (ss1 >> word)
            st1.insert(word);

        while (ss2 >> word)
            st2.insert(word);

        for (string x : st1) {
            if (st2.find(x) == st2.end())
                cout << x << " ";
        }
        cout << endl;
    }

    return 0;
}