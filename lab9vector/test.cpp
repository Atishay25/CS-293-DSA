#include<bits/stdc++.h>
using namespace std;

int main(){
    int a = 2;
    int b = 3;
    queue<int> q;
    q.push(a);
    q.push(b);
    cout << "A" << a << endl;
    q.pop();
    q.pop();
    cout << "AB" << a  << b  << q.front() << endl;
}