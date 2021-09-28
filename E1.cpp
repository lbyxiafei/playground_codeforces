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
        while(q.size()){
            cout << q.front() << ' ';
            q.pop_front();
        }
        cout << endl;
    }

    return 0;
}