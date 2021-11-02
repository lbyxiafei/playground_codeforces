#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

typedef tree<
    int,
    null_type,
    less<int>,
    rb_tree_tag,
    tree_order_statistics_node_update> ordered_set;
typedef tree<
    pair<int,int>,
    null_type,
    less<pair<int,int>>,
    rb_tree_tag,
    tree_order_statistics_node_update> ordered_multiset;
typedef long long LL;
typedef unsigned long long ULL;
typedef pair<int,int> PII;

const int N=100010;

int tr[N];

int lowbit(int x){
    return x&-x;
}

int add(int idx, int x){
    for(int i=idx; i<N; i+=lowbit(i))
        tr[i]+=x;
}

int query(int idx){
    int res=0;
    for(int i=idx; i; i-=lowbit(i))
        res+=tr[i];
    return res;
}

int main(){
#ifdef _LBY
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
#endif

    int T;
    cin >> T;
    while(T--){
        unordered_map<int,int> D,U;
        memset(tr,0,sizeof tr);
        int n;
        cin >> n;
        vector<int> arr(n);
        for(int i=0; i<n; i++) cin >> arr[i];
        string s;
        cin >> s;
        for(int i=0; i<n; i++){
            if(s[i]=='R'){
                if(arr[i]>n) continue;
                int x=max(1,arr[i]);
                U[x]++;
                add(x,1), add(n+1,-1);
            }
            else{
                if(arr[i]<1) continue;
                int x=min(n,arr[i]);
                D[x]++;
                add(1,1), add(x+1,-1);
            }
        }
        bool flag=true;
        int rd=0;

        for(int i=1; i<=n; i++){
            int t=query(i);
            if(D[i]) rd++;
            if(U[i]) rd++;
            //cout << t << ',' << rd << ' ';
            if(t+rd<i){
                flag=false;
                break;
            }
        }
        //cout << endl;
        if(flag) puts("YES");
        else puts("NO");


    }
    

    return 0;
}