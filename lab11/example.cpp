#include<iostream>
using namespace std;

int main(){
    int a = 2;
    int d = a;
    int *b = &a;
    int *c = new int;
    c = b;
    (*c)++;
    cout << a << " " << *b << " " << *c << d << endl;
}