#include <bits/stdc++.h>

using namespace std;

int main(){
    //freopen("input.txt","r",stdin);
    cout << _DEBUG;

    string s,res;
    cin >> s;
    unordered_set<char> V{'a','e','i','o','u','A','E','I','O','U','y','Y'};

    for(char ch:s){
        if(V.count(ch)) continue;
        res+='.';
        res+=tolower(ch);
    }
    cout << res << endl;

    return 0;
}