#include <bits/stdc++.h>

using namespace std;

const int N=10010;

int main(){
    //ifstream cin("input.txt");
    //ofstream cout("output.txt");
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);

    int k;
    cin >> k;
    while(k--){
        int n; 
        string s;
        cin >> n >> s;
        unordered_map<int,int> v2i;
        int a=0, b=0;
        v2i[0]=0;
        bool flag=false;
        for(int i=1; i<=n; i++){
            char ch=s[i-1];
            if(ch=='a') a++;
            else b++;
            int len=min(a,b);
            while(len>0){
                int t=(a-len)*N+(b-len);
                if(v2i.count(t)){
                    printf("%d %d\n", v2i[t]+1,i);
                    flag=true;
                    break;
                }
                len--;
            }
            if(flag) break;
            v2i[a*N+b]=i;
        }
        if(!flag) cout << "-1 -1" << endl;
    }
    return 0;
}