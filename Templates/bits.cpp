#include <algorithm>
#include <bitset>
#include <iostream>
#include <vector>

using namespace std;

vector<int> find_subsets(int val){
    vector<int> res{val};
    for(int i=(val-1)&val; i!=val; i=(i-1)&val){
        res.push_back(i);
    }
    return res;
}

string to_binary(int val){
    string s= bitset<32>(val).to_string();
    s.erase(0, min(s.find_first_not_of('0'), s.size()-1));
    return s;
}

int main(){
    for(int i=0; i<=7; i++)
        cout << to_binary(i) << endl;

    return 0;
}