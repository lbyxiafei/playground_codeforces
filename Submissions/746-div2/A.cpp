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
        int n, h;
        cin >> n >> h;
        int a=0, b=0;
        for(int i=0; i<n; i++){
            int x;
            cin >> x;
            if(x>a){
                b=a;
                a=x;
            }
            else if(x>b){
                b=x;
            }
        }
        int k=h/(a+b);
        int r=h%(a+b);
        int t=0;
        if(r){
            if(r>a) t=2;
            else t=1;
        }
        cout << k*2+t << endl;
    }

    return 0;
}