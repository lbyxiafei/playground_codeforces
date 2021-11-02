#include <bits/stdc++.h>

using namespace std;

typedef long long LL;
typedef unsigned long long ULL;
typedef pair<int,int> PII;

const int N=50;

vector<vector<int>> ds{{-1,-1},{-1,1}};

void out(vector<vector<char>>& g){
    int m=g.size(), n=g[0].size();
    for(int i=0; i<m; i++){
        for(int j=0; j<n; j++)
            cout << g[i][j];
        cout << endl;
    }
}

int main(){
#ifdef _LBY
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
#endif
    int T;
    cin >> T;
    while(T--){
        int m, n, k;
        cin >> m >> n >> k;
        vector<vector<char>> g(m, vector<char>(n)), board(m,vector<char>(n));
        for(int i=0; i<m; i++)
            for(int j=0; j<n; j++)
                cin >> g[i][j], board[i][j]='.'; 
        
        for(int i=0; i<m; i++){
            for(int j=0; j<n; j++){
                if(board[i][j]=='.' && g[i][j]=='*'){
                    for(int h=k; h<=min(m,n); h++){
                        vector<int> arr;
                        bool flag=true;
                        for(int hh=1; hh<=h; hh++){
                            int a=i+hh*ds[0][0], b=j+hh*ds[0][1];
                            int c=i+hh*ds[1][0], d=j+hh*ds[1][1];
                            if(a>=0 && a<m && b>=0 && b<n && c>=0 && c<m && d>=0 && d<n
                                    && g[a][b]=='*' && g[c][d]=='*'){
                                arr.push_back(a*N+b);
                                arr.push_back(c*N+d);
                            }
                            else{
                                flag=false;
                                break;
                            }
                        }
                        if(flag){
                            board[i][j]='*';
                            for(auto x:arr){
                                int r=x/N, c=x%N;
                                board[r][c]='*';
                            }
                        }
                    }
                }
            }
        }
        bool flag=true;
        for(int i=0; i<m; i++){
            for(int j=0; j<n; j++){
                if(board[i][j]!=g[i][j]){
                    flag=false;
                    break;
                }
            }
            if(!flag) break;
        }
        if(flag) puts("YES");
        else puts("NO");

        //out(board);
    }

    string s;
    cin >> s;
    cout << s;

    return 0;
}