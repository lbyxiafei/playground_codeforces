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
        int n;
        cin >> n;
        vector<int> nums, arr;
        nums.push_back(-2e9);
        arr.push_back(-2e9);
        for(int i=1; i<=n; i++) {
            int x;
            cin >> x;
            nums.push_back(x);
            arr.push_back(x);
        }
        sort(nums.begin(),nums.end());

        int tot=0;
        vector<vector<int>> res;

        //for(auto x:arr) cout << x << ' ';
        //cout << endl << endl;

        for(int idx=1; idx<=n; idx++){
            if(arr[idx]==nums[idx]) continue;
            int t=nums[idx], l=idx, r=idx;
            while(r<=n && arr[r]!=t) r++;
            vector<int> tmp;
            tmp.push_back(-2e9);
            tmp.push_back(arr[r]);

            for(int i=l; i<r; i++) tmp.push_back(arr[i]);
            for(int i=l,j=1; i<=r; j++,i++) arr[i]=tmp[j];
            tot++;
            res.push_back({l,r,r-l});

            //cout << l << ',' << r << endl;
            //for(auto x:tmp) cout << x << ' ';
            //cout << endl;
            //for(auto x:arr) cout << x << ' ';
            //cout << endl << endl;
        }
        cout << tot << endl;
        for(auto&& e:res) cout << e[0] << ' ' << e[1] << ' ' << e[2] << endl;
    }

    return 0;
}