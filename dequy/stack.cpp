#include <bits/stdc++.h>
using namespace std;
#define ll long long

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    stack <int> s;      //head = empty
    s.push(1);          //1(head)        
    s.push(2);          //1 2(head) 
    s.push(3);          //1 2 3(head)

    while(!s.empty()){
        cout << s.top() << endl;  //--> 1 2(head) //--> 1(head)
        s.pop();
    }
    //output : 3 2 1
    return 0;
}
