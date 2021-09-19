#include <bits/stdc++.h>

using namespace std;

typedef pair<int,int> PII;

const int N=100010;

int A[N], B[N], C[N];

int main(){
#ifdef _LBY
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
#endif

    int k;
    cin >> k;
    while(k--){
        int n;
        cin >> n;
        int res=n, idx=n-1;
        for(int i=0; i<n; i++) scanf("%d",&A[i]);
        for(int i=0; i<n; i++) scanf("%d",&B[i]);
        for(int i=1; i<n; i++) A[i]=min(A[i],A[i-1]);
        for(int i=0; i<n; i++){
            while(idx>0 && B[i]>A[idx-1]) idx--;
            //if(B[i]>A[i-1])
            res=min(res,i+idx);
        }

        cout << res << endl;
    }

    return 0;
}