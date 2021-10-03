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
        int n, d;
        cin >> n >> d;
        vector<int> A,B;
        bool flag=true;
        for(int i=0; i<n; i++){
            int x;
            cin >> x;
            if(i && x<A.back()) flag=false;
            A.push_back(x);
            B.push_back(x);
        }
        if(flag) {
            cout << "YES" << endl;
            continue;
        }
        int start=n-d, end=d-1;
        sort(B.begin(),B.end());
        flag=true;
        for(int i=start; i<=end; i++){
            if(A[i]!=B[i]){
                flag=false;
                break;
            }
        }
        if(flag) puts("YES");
        else puts("NO");

    }

    return 0;
}