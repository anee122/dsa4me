#include <bits/stdc++.h>
using namespace std;

//STRING
//Bang ASCII : A-Z (60-90) ; a-z(97-122) ; 0-9(48-57)
char c; // kieu du lieu (1 ky tu, 1 byte || -128-127)

bool islower(char c);//kiem tra in thuong
bool isupper(char c);//kiem tra in hoa
bool isalpha(char c);//kiem tra chu cai
bool isdigit(char c);//kiem tra chu so

int tolower(char c);//tra ve ma ascii cua ky tu o dang in thuong
int toupper(char c);//tar ve mai ascii cua ky tu o dang in hoa

int main(){
    string s; //khai bao
    cin >> s;// khi dung cin,s se dung nhap khi gap dau cach
    //khi nhap xau co dau cach
    getline(cin,s); //getline se dung nhap khi gap enter
    //vi vay getline se co mot so tinh huong bi troi lenh
    //nen ta co ham:
    cin.ignore() //loai bo 1 ky tu tren bo dem ban phim (thuong su dung khi truoc getline la cin)
    //trong TH truoc getline la mot getline khac ta k can cin.ignore();
}

//Cac lop ham co san cho string s;
s.size()//do dai xau
s.lenght()//do dai xau (dac thu cho string)
s[i]; //truy cap vao ky tu thu i cua s
//== != : so sanh 2 xau(giong hay khac)
//< > <= >= : so sanh 2 xau (theo thu tu tu dien voi nhau)

//vong lap for each : giup duyet tung ky tu cua xau hoac mang ...
for (char x:s) // duyet tung ky tu cua s 
for (auto x:s) // tuong tu nhung thuat toan auto co the chuyen doi nhanh dua cac kieu du lieu ma k can khai bao cu the

//stringstream (lien quan den cac bai tap tach tu va sd tu trong xau)
//stringstream : bien xau s thanh 1 luong
//CODE:
stringstream(ss);
string word; //dung de luu cac tu
while(ss>>word) cout << word << endl;

//trong TH co cach ky tu khac ngan cach
//VD : ptit-code
//Ta dung:
while(getline(ss,word,'-')) cout << word << endl;