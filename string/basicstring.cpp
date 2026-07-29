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