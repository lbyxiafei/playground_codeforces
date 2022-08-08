#include <bits/stdc++.h>

using namespace std;

typedef long long LL;
typedef unsigned long long ULL;
typedef pair<int,int> PII;

int main(){
#ifdef _LBY
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
#endif

    int T;
    cin >> T;
    while(T--){
        string s;
        cin >> s;
        int a=0, b=0, c=0;
        for(char ch:s){
            if(ch=='A') a++;
            if(ch=='B') b++;
            if(ch=='C') c++;
        }
        //cout << s << endl;
        //cout << a << ',' << b << ',' << c << endl;
        if(s.size()%2==0 && b==a+c) puts("YES");
        else puts("NO");

    }


    return 0;
}