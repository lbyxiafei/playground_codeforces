#include <bits/stdc++.h>

using namespace std;

typedef long long LL;
typedef unsigned long long ULL;
typedef pair<int,int> PII;

LL calc(vector<int>& arr, int l, int r){
    vector<int> tmp(arr.size());
    if(l>=r) return 0L;
    int mid=l+r>>1, i=l, j=mid+1, k=l;
    LL res=calc(arr, l, mid)+calc(arr, mid+1, r);
    while(i<=mid && j<=r)
        if(arr[i]>arr[j]) {
            res+=mid-i+1;
            tmp[k++]=arr[j++];
        }
        else tmp[k++]=arr[i++];
    while(i<=mid) tmp[k++]=arr[i++];
    while(j<=r) tmp[k++]=arr[j++];
    for(k=l; k<=r; k++) arr[k]=tmp[k];
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
        int n;
        cin >> n;
        vector<int> arr(n);
        for(int i=0; i<n; i++) cin >> arr[i];
        deque<int> q;
        for(auto x:arr){
            if(q.empty()) q.push_back(x);
            else{
                if(x>q.front()) q.push_back(x);
                else q.push_front(x);
            }
        }
        vector<int> nums;
        while(q.size()){
            nums.push_back(q.front());
            q.pop_front();
        }

        for(auto x:nums) cout << x << ' ';
        cout << endl;
        
        cout << calc(nums,0,nums.size()-1) << endl;
    }

    return 0;
}