#include <iostream>
#include <vector>

using namespace std;

void out(vector<int>& arr){
    for(auto x:arr)
        cout << x << ' ';
    cout << endl;
}

void out2d(vector<vector<int>>& g){
    int m=g.size(), n=g[0].size();
    for(int i=0; i<m; i++){
        for(int j=0; j<n; j++)
            cout << g[i][j] << ' ';
        cout << endl;
    }
}

int main(){
    vector<int> arr{1,2,3,4,5,6,7};
    auto l=arr.begin()+1, r=arr.begin()+3;
    cout << *l << ' ' << *r << endl;
    //arr.erase(l);
    for(auto it=l; it!=r; it++){
        arr.erase(it);
    }
    out(arr);

    return 0;
}