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

int main(){
#ifdef _LBY
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
#endif

    int T;
    cin >> T;
    while(T--){
        string s, p;
        cin >> s >> p;
        unordered_map<char,int> c2i;
        for(int i=0; i<s.size(); i++)
            c2i[s[i]]=i;
        int m=p.size(), res=0;
        for(int i=1; i<m; i++){
            char c1=p[i-1], c2=p[i];
            int a =c2i[c1], b=c2i[c2];
            //cout << c1 << ':' << a << '\t' << c2 << ':' << b << endl;
            res+=abs(c2i[c2]-c2i[c1]);
        }
        cout << res << endl;
    }
    

    return 0;
}