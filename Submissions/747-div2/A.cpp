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
        LL n;
        cin >> n;
        if(n==1){
            cout << "0 1" << endl;
            continue;
        }
        cout << -(n-1) << ' ' << n << endl;
    }

    return 0;
}