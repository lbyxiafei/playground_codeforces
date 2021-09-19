#include <bits/stdc++.h>

using namespace std;

int main(){
#ifdef _LBY
    freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
#endif

    int k;
    cin >> k;
    while(k--){
        int n, res=0;
        string s;
        cin >> n >> s;
        for(int i=n-1; i>=0; i--){
            char ch=s[i];
            if(ch!='0'){
                res+=ch-'0';
                if(i!=n-1) res++;
            }
        }
        cout << res << endl;
    }

    return 0;
}