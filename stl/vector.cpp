#include <bits/stdc++.h>

using namespace std;

int main(){
    //khai bao vector rong
    vector<int> v1;

    //khai bao vector co phan tu
    vector<int> v2 = {1,2,3,4,5};

    //khai bao vector co san n phan tu
    int n = 20;
    vector<int> v3(n);

    //khai bao vector co n phan tu cung gia tri val
    int val = 0;
    vector<int> v4(n,val);

    vector<int> v;
    v.push_back(1); // them phan tu 1 vao cuoi danh sach

    cout << "Kich thuoc" << v.size() << endl;
    //duyet chi so vector

    for(int i = 0;i<v.size();i++){
        cout << v[i] << " ";
    }

    //duyet bang for-each

    for(auto x:v) cout << v <<" ";

    return 0;
}