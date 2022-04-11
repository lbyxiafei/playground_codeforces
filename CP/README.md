[toc]
# Algorithm
## 双指针
### 左右指针
- i从左往右，j从右往左
### 快慢指针
- i每次走一格，j每次走两格
### sliding window/追赶式指针
- r先移动，l在其后追赶
### 数组嵌套/站肩式指针
- i先移动，idx控制嵌套的数组随i的变化而变
  - 经典例题：[LC2008.出租车最高盈利](https://leetcode.com/problems/maximum-earnings-from-taxi/)
### 矩阵计数
- 给定矩阵`从左往右、从上往下均递增`,则可以再`O(m+n)`时间内求出矩阵内小于等于给定数值的个数
- 本题运用的是矩阵的单调性
```cpp template_matrix_count
int count(vector<vector<int>>& g, int target){
    int m=g.size(), n=g[0].size(), res=0;
    for(int i=0, j=n-1; i<m; i++){
        while(j>=0 && g[i][j]>target) j--;
        res+=j+1;
    }
    return res;
}
```
- 经常性的和二分、求第k大/小数绑定
- [LC.2040](https://leetcode.com/submissions/detail/578354674/)
## 前缀和、差分
### 前缀和
### 差分
- 差分操作：在一个范围[a,b]加上一个增量x：`arr[a]+=x, arr[b+1]+=-x`
- 差分性质：对差分数组进行前缀和操作，可得原数组
- 例题：[LC.数组互补的最小操作](https://leetcode.com/problems/minimum-moves-to-make-array-complementary/)
  - 这道题目有难度，且有些偏：核心是一个松弛贪心式的思路，还需要额外的映射到差分数组上，不易想到：
    - ${(逆向)松弛操作}\stackrel{映射}{\longrightarrow}{差分数组}$
    ```cpp
    int minMoves(vector<int>& nums, int limit) {
      vector<int> arr(2*limit+2);
      int res=1e9,l=0,r=nums.size()-1, t=0;
      while(l<r){
        int a=nums[l++], b=nums[r--];
        arr[2]+=2, arr[2*limit+1]+=-2;
        arr[1+min(a,b)]+=-1, arr[limit+max(a,b)+1]+=1;
        arr[a+b]+=-1, arr[a+b+1]+=1;
      }
      for(int i=2; i<arr.size()-1; i++)
        t+=arr[i], res=min(res,t);
      return res;
    }
    ```
## 回文数
- 求下一个（更大）回文数
```cpp template_next_palindrome
    int half=1, upper=100;
    while(true){
        set<int> S;
        for(int i=0; i<10; i++){
            string s=to_string(half), t=to_string(half);
            reverse(t.begin(),t.end());
            int x=stoi(s+t.substr(1));
            S.insert(x);
            int y=stoi(s+t);
            S.insert(y);
            half++;
        }
        for(auto x:S)
            cout << x << ' ';
        
        if(half>upper) break;
    }
```
## 区间
### 单点区间插入
- 可以运用二分、set进行查询优化，由于插入的点只会和前后两个区间有关联，所以时间复杂度是`O(log(n))`
### 连续区间插入
- 先插入，再合并
- 查询、插入的时间复杂度可以达到`O(log(n))`（二分），但由于连续区间可以覆盖n个区间，所以合并过程时间复杂度`O(N)`
## 排序
### 快速选择
- 给定无序数组，求从小到大的第k个数，例题：[AC.第k个数](https://www.acwing.com/activity/content/problem/content/820/)
  - 基本思路：套用快速排序的模板，在此基础上，根据k和r-start的比较进行下一层递归
  - 华点：这里与k进行比较的不是r，因为k是与start的相对距离，而r是与0的相对距离，需要对r进行一次处理确保一致性
    ```cpp template_quick_sort
    int quick_select(vector<int>& arr, int start, int end, int k){
        if(start==end) return arr[start];
        int l=start-1, r=end+1, mid=start+end>>1, x=arr[mid];
        while(l<r){
            do l++;
            while(arr[l]<x);
            do r--;
            while(arr[r]>x);
            if(l<r) swap(arr[l],arr[r]);
        }
        int t=r-start;
        if(t>=k) return quick_select(arr, start, r, k);
        else return quick_select(arr,r+1,end,k-t-1); // 注意这里需要额外k--，因为k是0-indexed
    }
    ```
## String
### KMP
```cpp template_kmp
void kmp(string s, string p){
    int m, n;
    m=p.size(), n=s.size();
    p=' '+p, s=' '+s;
    vector<int> ne(m+1);
    for(int l=0,r=2; r<=m; r++){
        while(l && p[l+1]!=p[r]) l=ne[l];
        if(p[l+1]==p[r]) l++;
        ne[r]=l;
    }
    
    for(int l=0,r=1; r<=n; r++){
        while(l && p[l+1]!=s[r]) l=ne[l];
        if(p[l+1]==s[r]) l++;
        if(l==m){
            cout << r-m << ' ';
            l=ne[l];
        }
    }
}
```
## Array
### 算两次原理
- 经典算法，很多数组类问题都可以套用：
  - 问题的一般表现形式：计数，求数组内的subarray个数，使得subarry满足某些条件
  - 这些条件一般有多个，但是最重要的是，可以通过转换，将条件之间进行decouple
  - 即，条件的`独立性`，是这个算法的关键钥匙
  - 从另一个角度，算一个和某个位置对总和的贡献
- 例题：[LC.Vowels of all substrings](https://leetcode.com/problems/vowels-of-all-substrings/), [LC.子序列宽度之和](https://leetcode.com/problems/sum-of-subsequence-widths/)
  ```cpp
  int mod=1e9+7, res=0, n=nums.size();
  vector<int> p(n);
  p[0]=1;
  for(int i=1; i<n; i++) p[i]=(long long)p[i-1]*2%mod;
  sort(nums.begin(),nums.end());
  for(int i=0; i<n; i++)
      // 这里左边和右边是分别单独计算的
      res=((long long)res+(long long)p[i]*nums[i]-(long long)p[n-i-1]*nums[i])%mod;
  return res;
  ```
### Subarray
- 求一个数组中的subarray的个数，使得subarray某个属性满足一个范围
  - 例题：[LC.区间子数组个数](https://leetcode.com/problems/number-of-subarrays-with-bounded-maximum/)
  - 基本思路：降维，更具体的：把求范围转化成count(r)-count(l-1)即可
  - 关于count subarray的求法，有两种方法：单调栈和双指针
    - 单调栈
      - 注意可能出现的重复：[2,2]，小于等于2的subarray[2,2]出现了两次，处理方法：对于两侧的单调栈的单调性判断进行一闭一开的处理
        ```cpp
        int n=nums.size();
        vector<int> stk,L(n),R(n);
        vector<long long> f(n);
        for(int i=0; i<n; i++){
            // 此处为大于等于
            while(stk.size() && nums[i]>=nums[stk.back()])
                stk.pop_back();
            L[i]=stk.empty()?-1:stk.back();
            stk.push_back(i);
        }
        stk.clear();
        for(int i=n-1; i>=0; i--){
            // 相应的，由于一闭一开，上面是大于等于，这里显然就要是大于
            while(stk.size() && nums[i]>nums[stk.back()])
                stk.pop_back();
            R[i]=stk.empty()?n:stk.back();
            stk.push_back(i);
        }
        for(int i=0; i<n; i++)
            f[i]=(long long)(i-L[i])*(R[i]-i);
        
        auto calc=[&](int maxx){
            long long cnt=0;
            for(int i=0; i<n; i++)
                if(nums[i]<=maxx)
                    cnt+=f[i];
            return cnt;
        };
        ```
    - 双指针
      - 一个指针负责遍历，另一个指针随遍历指针当前元素的变化而`单调性`变化，当元素符合条件时，进行累加计数
        ```cpp
        int n=nums.size();
        auto calc=[&](int maxx){
            Lres=0;
            int l,r;
            for(l=0,r=0; r<n; r++){
                if(nums[r]>maxx){
                    res+=(LL)(r-l+1)*(r-l)/2;
                    l=r+1;
                }
            }
            // 华点：结尾处需累加最后一次
            return res+(LL)(r-l+1)*(r-l)/2;
        };
        return calc(right)-calc(left-1);
        ```
## DFS
### 折半DFS
- 如果数据范围在3、40的样子，基本已经是明示了
- 算法的思路和实现也比较直接
- 可能存在的华点是如何实现`两半边的互动`来找到答案
- 举例：[LC.Split array with same average](https://leetcode.com/problems/split-array-with-same-average/)
  - 算是遇到的折半DFS的难题：包括`平均值的传递公式`，以及全集边界情况的互动处理
  - 平均值传递公式：$\frac{\sum_1^k{a_i}}{k}=\frac{\sum_{k+1}^n{a_i}}{n-k}=\frac{\sum_1^n{a_i}}{n }$
    ```cpp
    bool splitArraySameAverage(vector<int>& nums) {
        if(nums.size()==1) return false;
        int tot=accumulate(nums.begin(),nums.end(),0), n=nums.size(), m=n/2;
        for(int i=0; i<n; i++) nums[i]=nums[i]*n-tot;
        multiset<int> S;
        auto dfs=[&](auto&& self, int u, int cur){
            if(cur) S.insert(cur);
            if(u==m) return false;
            if(self(self,u+1,cur)) return true;
            if(cur+nums[u]==0) return true;
            if(self(self,u+1,cur+nums[u])) return true;
            return false;
        };
        
        if(dfs(dfs,0,0)) return true;
        int t=accumulate(nums.begin(),nums.begin()+m,0);
        S.erase(S.find(t));
        
        auto dfs2=[&](auto&& self, int u, int cur){
            if(S.count(-cur)) return true;
            if(u==n) return false;
            if(self(self,u+1,cur)) return true;
            if(cur+nums[u]==0) return true;
            if(self(self,u+1,cur+nums[u])) return true;
            return false;
        };
        return dfs2(dfs2,m,0);
    }
    ```
## 图论
### 拓扑排序
- Topological sort，整体框架既可以是DFS，也可以是BFS
- 从遍历的角度看，DFS是`从后往前`，BFS则`从前往后`
#### BFS-Topo
```cpp template_topo_bfs
void topo_bfs(){
    vector<int> arr;
    queue<int> q;
    unordered_map<int,int> cnt;
    for(auto&& [a,B]:g){
        for(auto b:B){
            cnt[b]++;
        }
    }
    for(int i=0; i<n; i++)
        if(!cnt[i])
            q.push(i);
    if(q.empty()){
        cout << "Circle!";
        return;
    }
    while(q.size()){
        auto u=q.front(); q.pop();
        // do stuff...
        arr.push_back(u);
        for(int v:g[u]){
            cnt[v]--;
            if(!cnt[v]){
                q.push(v);
            }
        }
    }
    if(q.size()) cout << "Circle!";
    else{
        cout << "BFS traverse: ";
        out();
    }
}
```
#### DFS-Topo
```cpp template_topo_dfs
// unordered_set<int> st: node already in stack
// unordered_set<int> S: node already been visited before(not this round)
bool dfs(int u){
    if(st.count(u)) return false;
    if(S.count(u)) return true;

    st.insert(u), S.insert(u);

    for(int v:g[u]){
        if(!dfs(v)) return false;
        // do stuff...
    }

    st.erase(u);
    // do stuff...
    arr.push_back(u);
    return true;
}

void topo_dfs(){
    arr.clear(), st.clear(), S.clear();
    for(int i=0; i<n; i++){
        if(!dfs(i)){
            cout << "Circle!" << endl;
            break;
        }
    }
    reverse(arr.begin(),arr.end());
    cout << "DFS traverse: ";
    out();
}
```
### Dijkstra
#### 朴素版Dijkstra & Prim最小生成树
- 两个算法几乎一模一样，唯一的不同是dist[i]的定义
  - Dijkstra的dist[i]：节点i到`起点`的最小距离
  - [朴素Dijkstra]()
    ```cpp template_dijkstra_plain
    int dijkstra(){
        dist[1]=0;
        for(int i=0; i<n; i++){
            int t=-1;
            for(int j=1; j<=n; j++){
                // 这里t的行为类比堆优化版出队：同样遵守Dij出队去重原则
                if(!st[j] && (t==-1 || dist[j]<dist[t]))
                    t=j;
            }
            st[t]=true;
            if(dist[t]==INF) return -1;
            for(int j=1; j<=n; j++){
                dist[j]=min(dist[j],dist[t]+g[t][j]); 
            }
        }
        return dist[n];
    }
    ```
  - Prim的dist[i]：节点i到`当前最小生成树`的最小距离
  - [Prim最小生成树例题](https://www.acwing.com/activity/content/problem/content/924/)
    ```cpp template_prim
    int prim(){
      dist[1]=0;
      int res=0;
      for(int i=0; i<n; i++){
        int t=-1;
        for(int j=1; j<=n; j++){
          if(!st[j] && (!~t || dist[t]>dist[j]))
            t=j;
        }
        st[t]=true;
        if(dist[t]==INF) return INF;
        res+=dist[t];
        for(int j=1; j<=n; j++){
          dist[j]=min(dist[j], g[t][j]); //唯一区别
        }
      }
      return res;
    }
    ```
#### 堆优化版Dijkstra
- 去重(`if st[u]: continue`)原则：
    - BFS入队时去重
    - Dij出队时去重
    - A*不去重
- 时间复杂度`M*log(N)`
```cpp template_dijkstra
int dijkstra(int start=1, int end=n){
    memset(dist, 0x3f, sizeof dist);
    memset(st, false, sizeof st);
    priority_queue<pii,vector<pii>,greater<>> q;
    q.push({0,start});
    dist[start]=0;
    while(q.size()){
        auto cur=q.top(); q.pop();
        int u=cur.second;
        if(st[u]) continue;
        st[u]=true;
        for(int i=g[u]; ~i; i=ne[i]){
            int v=e[i];
            if(dist[u]+w[i]<dist[v]){
                dist[v]=dist[u]+w[i];
                q.push({dist[v],v});
            }
        }
    }
    if(dist[end]==INF) return -1;
    return dist[end];
}
```
### SPFA
- 算法核心：st状态数组表示的是in-queue
#### SPFA最短路
- [SPFA求最短路例题](https://www.acwing.com/activity/content/problem/content/922/)
    ```cpp template_spfa
    int spfa(){
        queue<int> q;
        q.push(1);
        dist[1]=0;
        st[1]=true;
        while(q.size()){
            int u=q.front(); q.pop();
            st[u]=false;
            for(int i=g[u]; ~i; i=ne[i]){
                int v=e[i];
                if(dist[v]>dist[u]+w[i]){
                    dist[v]=dist[u]+w[i];
                    if(!st[v]){
                        q.push(v);
                        st[v]=true;
                    }
                }
            }
        }
        return dist[n];
    }
    ```
#### SPFA判断负回路
- 在最短路的基础上，加上另一个状态数组cnt[i]，表示当前节点i被其直接邻居以更小距离更新形式访问到的次数
  - 当cnt[i]==n时，即为负环，因为i的邻居上限最多为n-1
- [SPFA判断负环例题](https://www.acwing.com/activity/content/problem/content/921/)
    ```cpp spfa_negative_circle
    bool spfa(){
        queue<int> q;
        for(int i=1; i<=n; i++) q.push(i), st[i]=true;
        while(q.size()){
            int u=q.front(); q.pop();
            st[u]=false;
            for(int i=g[u]; ~i; i=ne[i]){
                int v=e[i];
                if(dist[v]>dist[u]+w[i]){
                    dist[v]=dist[u]+w[i];
                    cnt[v]=cnt[u]+1;
                    if(cnt[v]==n) return true;
                    if(!st[v]){
                        st[v]=true;
                        q.push(v);
                    }
                }
            }
        }
        return false;
    }
    ```
### BellmanFord
- 算法核心：纯粹的以`边`为单位，遍历更新每个点的最短距离
- [有边数限制的最短路例题](https://www.acwing.com/activity/content/problem/content/922/)
    ```cpp template_bellmanford_v2
    int bellmanford(){
        vector<int> dist(n+1, INF);
        dist[1]=0;
        for(int i=0; i<k; i++){
            vector<int> t(dist);
            for(auto&& e:edges){
                int a=e[0], b=e[1], c=e[2];
                if(dist[a]!=INF){
                    t[b]=min(t[b],dist[a]+c);
                }
            }
            dist=t;
        }
        return dist[n];
    }
    ```

    ```cpp template_bellmanford
    int bellmanford(){
        dist[1]=0;
        for(int i=0; i<k; i++){
            memcpy(pr, dist, sizeof dist);
            for(auto&& e:edges){
                int a=e[0], b=e[1], c=e[2];
                if(pr[a]!=INF && pr[a]+c<dist[b]){
                    dist[b]=pr[a]+c;
                }
            }
        }
        return dist[n];
    }
    ```
### Floyd
- 暴力三重循环，循环顺序：k-i-j
- 例题：[AC.Floyd求最短路](https://www.acwing.com/problem/content/description/856/)
    ```cpp template_floyd
    for(int k=1; k<=n; k++)
        for(int i=1; i<=n; i++)
            for(int j=1; j<=n; j++)
                if(f[i][k]<INF && f[k][j]<INF)
                f[i][j]=min(f[i][j],f[i][k]+f[k][j]);
    ```
### 哈密顿最短路径
- [AC.哈密顿最短路](https://www.acwing.com/activity/content/problem/content/1011/)
```cpp template_Hamilton
int n;
cin >> n;
int g[n][n];
for(int i=0; i<n; i++)
    for(int j=0; j<n; j++)
        cin >> g[i][j];
int f[n][1<<n];
memset(f,0x3f,sizeof f);
f[0][1]=0; // NOT f[0][0]=0;
for(int j=0; j<1<<n; j++){
    for(int i=0; i<n; i++){
        if((j>>i)&1) continue;
        int ns=j|(1<<i);
        for(int k=0; k<n; k++)
            if((j>>k)&1)
                f[i][ns]=min(f[i][ns],f[k][j]+g[k][i]);
    }
}
cout << f[n-1][(1<<n)-1];
```
## DP
### 背包
- 背包要诀：
  - 循环永远(一般)是：物品→体积→决策（分组背包是：分组→体积→当前组物品）
  - `1维`状态数组下，只有`完全`背包的第二层循环是`从左往右`
    - 而二维情况下，体积层的循环一致遵循从左往右即可
- 背包属于是`组合类DP`。之前努力试图强记套路，然而从最原始的二维定义出发，这其实是一种相较于线性DP更高级复杂的DP
#### 01背包
- [AC.01背包](https://www.acwing.com/activity/content/problem/content/997/)
``` cpp template_ZeroOnePack
// 朴素版
int n, m;
cin >> n >> m;
vector<vector<int>> f(n+1,vector<int>(m+1));
for(int i=1; i<=n; i++){
    int v,w;
    cin >> v >> w;
    // 这里需要从0开始
    for(int j=0; j<=m; j++){
        f[i][j]=f[i-1][j];
        if(j>=v) f[i][j]=max(f[i][j],f[i-1][j-v]+w);
    }
}
cout << f[n][m] << endl;

// 一维优化版
int n,m;
cin >> n >> m;
vector<int> f(m+1);

for(int i=0; i<n; i++){
    int v,w;
    cin >> v >> w;
    // 这里则只要循环到当前v即可
    for(int j=m; j>=v; j--)
        f[j]=max(f[j],f[j-v]+w);
}
cout << f[m];
```
#### 完全背包
- [AC.完全背包](https://www.acwing.com/activity/content/problem/content/998/)
```cpp template_CompletePack
// 朴素版
int n,V;
cin >> n >> V;
vector<vector<int>> f(n+1, vector<int>(V+1));
for(int i=1; i<=n; i++){
    int v,w;
    cin >> v >> w;
    // 这里需要从0开始循环，因为再后面一行需要取值
    for(int j=0; j<=V; j++){
        f[i][j]=f[i-1][j];
        if(j>=v) f[i][j]=max(f[i][j],f[i][j-v]+w);
    }
}
cout << f[n][V] << endl;

// 一维优化版
cin >> n >> m;
for(int i=1; i<=n; i++)
    scanf("%d%d",&v[i],&w[i]);
for(int i=1; i<=n; i++){
    for(int j=v[i]; j<=m; j++) // 这里不再需要从0开始循环
        f[j]=max(f[j],f[j-v[i]]+w[i]);
}
cout << f[m];
```
#### 多重背包
- 朴素做法
  - 以二维0-1背包模板，按照`物品-体积-决策`的顺序进行循环即可
  - 例题：[AC.多重背包](https://www.acwing.com/activity/content/problem/content/999/)
- 二进制优化
    - 将物品个数(决策)进行`二进制优化、分解`，合并入一个新的V,W数组中，进而把问题转化成了0-1背包问题
        > 此处的**二进制优化**和**快速幂**共享一个知识点：`任意自然数都可以分解成二进制数之和`，但又有所不同：`快速幂只需分解目标值为二进制之和；多重背包的二进制优化相比更进一步地强调累加的二进制之和不能大于给定目标值(证明参看：背包九讲)`
- 例题：[AC.庆功宴会](https://www.acwing.com/activity/content/problem/content/1275/)
```cpp template_MultiplePack
// 朴素版：二维+线性遍历
int m, n;
cin >> n >> m;
vector<vector<int>> f(n+1,vector<int>(m+1));
for(int i=1; i<=n; i++){
    int v, w, s;
    cin >> v >> w >> s;
    for(int j=0; j<=m; j++){
        f[i][j]=f[i-1][j];
        for(int k=1; k<=s; k++){
            if(k*v<=j){
                f[i][j]=max(f[i][j],f[i-1][j-k*v]+k*w);
            }
         }
     }
}
cout << f[n][m] << endl;

// 升级版：二维+二进制优化
int n, m;
cin >> n >> m;
vector<int> V, W;
for(int i=0; i<n; i++){
    int v, w, s;
    cin >> v >> w >> s;
    int cur=0;
    for(int j=1; j+cur<=s; j<<=1){
        V.push_back(v*j);
        W.push_back(w*j);
        cur+=j;
    }
    if(cur<s){
        int t=s-cur;
        V.push_back(v*t);
        W.push_back(w*t);
    }
}
int N=V.size();
vector<vector<int>> f(N+1,vector<int>(m+1));
for(int i=1; i<=N; i++){
    int v=V[i-1], w=W[i-1];
    for(int j=0; j<=m; j++){
        f[i][j]=f[i-1][j];
        if(j>=v) f[i][j]=max(f[i][j],f[i-1][j-v]+w);
    }
}
cout << f[N][m] << endl;

// 终极版I：一维+二进制优化
int n, m;
cin >> n >> m;
vector<int> V,W;
while(n--){
    int v,w,s;
    cin >> v >> w >> s;
    int cur=0;
    for(int j=1; j+cur<=s; j<<=1){
        V.push_back(v*j);
        W.push_back(w*j);
        cur+=j;
    }
    if(cur<s){
        int t=s-cur;
        V.push_back(v*t);
        W.push_back(w*t);
    }
}
vector<int> f(m+1);
for(int i=0; i<V.size(); i++)
    for(int j=m; j>=V[i]; j--)
        f[j]=max(f[j],f[j-V[i]]+W[i]);
cout << f[m] << endl;

// 终极版II：针对I做出了代码简化调整
int n,m;
cin >> n >> m;
vector<int> f(m+1);
for(int i=0; i<n; i++){
    int v, w, s;
    cin >> v >> w >> s;
    int cur=0;
    for(int j=1; j+cur<=s; j<<=1){
        for(int k=m; k>=v*j; k--){
            f[k]=max(f[k],f[k-v*j]+w*j);
        }
        cur+=j;
    }
    if(cur<s){
        int t=s-cur;
        for(int k=m; k>=t*t; k--){
            f[k]=max(f[k],f[k-v*t]+w*t);
        }
    }
}
cout << f[m];
```
#### 混合背包
- [AC.混合背包](https://www.acwing.com/activity/content/problem/content/1276/)
``` cpp template_MixedPacks
int n,m;

void ZeroOnePack(vector<int>& f, int v, int w){
    for(int j=m; j>=v; j--)
        f[j]=max(f[j],f[j-v]+w);
}

void CompletePack(vector<int>& f, int v, int w){
    for(int j=v; j<=m; j++)
        f[j]=max(f[j],f[j-v]+w);
}

void MultiplePack(vector<int>& f, int v, int w, int s){
    if(m/v>=s) {
        CompletePack(f,v,w);
        return;
    }
    int cur=0;
    for(int i=1; i+cur<=s; i<<=1){
        ZeroOnePack(f,v*i,w*i);
        cur+=i;
    }
    if(cur<s) {
        int t=s-cur;
        ZeroOnePack(f,v*t,w*t);
    }
}

void solve(){
    cin >> n >> m;
    vector<int> f(m+1);
    for(int i=0; i<n; i++){
        int v,w,s;
        cin >> v >> w >> s;
        if(!~s) ZeroOnePack(f,v,w);
        else if(!s) CompletePack(f,v,w);
        else MultiplePack(f,v,w,s);
    }
    cout << f[m];
}
```
#### 二维费用背包
- [AC.二维费用背包](https://www.acwing.com/activity/content/problem/content/1277/)
```cpp template_TwoDimensionalPack
int n,V,M;
cin >> n >> V >> M;
vector<vector<int>> f(V+1,vector<int>(M+1));
for(int i=0; i<n; i++){
    int v,m,w;
    cin >> v >> m >> w;
    for(int j=V; j>=v; j--)
        for(int k=M; k>=m; k--){
            f[j][k]=max(f[j][k],f[j-v][k-m]+w);
        }
}
cout << f[V][M];
```
#### 分组背包
``` cpp template_GroupPack
// 此处i为分组index，即共n组
for(int i=1; i<=n; i++){
    for(int j=m; j>=0; j--){
        // 这里表示i组内的K个不同组合，相互互斥
        for(int k=1; k<=K; k++){
            // 注意此处j与V[i][k]，巧妙
            f[j]=max(f[j], f[j-V[i][k]]+W[i][k]);
        }
    }
}
```
#### 有依赖背包 
- [AC.金明的预算](https://www.acwing.com/activity/content/code/content/2616487/)
``` cpp template_DependentPack
```
## 几何
- 常用算法：
  - 扫描线
  - 区间数组求和
### 矩阵面积
- 给定多个矩阵（平行于x、y轴），求所有矩阵的面积之和，要求去重。
- 解法：收集每个矩阵的x轴坐标，对该数组排序去重，从左往右2个一对儿扫描数组。对每组x坐标对儿：找到所有包含x对儿的矩阵，并记录矩阵的y轴起始点，而后求出y轴起始点组成的区间数组的总长度，与x对儿长度相乘。如此累加所有x对儿的值，就是总面积
  - 该解法具有通用性，适用一切平行x、y轴的矩阵求面积
  - 简单概括为：映射矩阵x轴坐标，针对x对儿，扫描矩阵集合找出包含、重合的所有矩阵的y区间，计算对应y轴区间和，累加求出面积
- 华点：横扫x轴的方式是以`x对儿`为单位，而非单一坐标；对于每个x对儿，需要再次扫描矩阵集合以找到y轴区间数组，这里有种`x对儿和矩阵整体集合互相独立、decouple的感觉`
- 涉及其他算法：y轴区间数组求和，是经典的区间贪心问题
- 例题：[LC.Rectangle Area II](https://leetcode.com/problems/rectangle-area-ii/)
  ```cpp
  int rectangleArea(vector<vector<int>>& rts) {
    vector<int> X;
    for(auto&& e:rts) X.push_back(e[0]), X.push_back(e[2]);
    sort(X.begin(),X.end());
    X.erase(unique(X.begin(),X.end()),X.end());
    auto calc=[&](int a, int b){
      vector<pair<int,int>> arr;
      for(auto&& e:rts)
        if(e[0]<=a && e[2]>=b)
          arr.emplace_back(e[1],e[3]);
      sort(arr.begin(),arr.end());
      int t=0, start=0, end=0;
      for(auto&& e:arr){
        int l=e.first, r=e.second;
        if(l>end){
          t+=end-start;
          start=l;
          end=r;
        }
        else end=max(end,r);
      }
      t+=end-start;
      return (long long)t*(b-a);
    };
    int res=0;
    for(int i=1; i<X.size(); i++){
      int a=X[i-1], b=X[i];
      res=((long long)res+calc(a,b))%1000000007;
    }
    return res;
  }
  ```
### 向量叉积、凸包
#### 向量叉积与平行四边形面积
- 二维叉积公式：$\vec{a}\times\vec{b}=\mid{\vec{a}}\mid\times\mid{\vec{b}}\mid\times\sin{\theta}=2S_{\triangle}={x_1}{y_2}-{x_2}{y_1}$
  - 两个向量始于同一起点，他们的叉积等于他们所覆盖的三角形面积的两倍（即平行四边形）
  - 如果起点为原点（0,0），则有以上计算公式
  - 向量b如果在向量a的逆时针方向，则$\sin{\theta}$为正
#### 凸包
- 所有坐标按x、y轴排序
- stack收录前两个点，对当前点和stack内的点进行叉积计算
- 保持stack内的点的$\sin{\theta}$正负符号一致
- 清空stack，从后往前再来一遍
```cpp
int cross(int x1, int y1, int x2, int y2){
  return x1*y2-x2*y1;
}

int area(vector<int>& a, vector<int>& b, vector<int>& c){
  return cross(b[0]-a[0], b[1]-a[1], c[0]-a[0], c[1]-a[1]);
}

vector<vector<int>> outerTrees(vector<vector<int>>& trees) {
  vector<vector<int>> stk;
  set<vector<int>> S;
  sort(trees.begin(),trees.end());
  for(auto&& e:trees){
    while(stk.size()>1 && area(stk[stk.size()-2],stk.back(),e)>0) stk.pop_back();
    stk.push_back(e);
  }
  for(auto&& e:stk) S.insert(e);
  stk.clear();
  for(int i=trees.size()-1; i>=0; i--){
    auto e=trees[i];
    while(stk.size()>1 && area(stk[stk.size()-2],stk.back(),e)>0) stk.pop_back();
    stk.push_back(e);
  }
  for(auto&& e:stk) S.insert(e);
  return vector<vector<int>>(S.begin(),S.end());
}
```
## 博弈论
- 看似思维复杂，然现阶段遇到的题目均只有2名玩家互动，而这个互动的关系与结果可以用一个相对简单的方程表示出来
- 因此，找到互动方程，后对其套用一些常规算法的iteration，基本可以算作应对此一大类博弈论的套路
- 华点：对于互动方程+常规iteration为何能够play optimal是最大的思维跳跃
- 总结：`互动方程+iteration`
## 数学
### 质因数分解
  ```cpp
  unordered_map<int,int> freq;
  for(int i=2; i*i<=x; i++){
    while(x%i==0){ 
      x/=i;
      freq[i]++;
    }
  }
  if(x>1) freq[x]++;
  ```
#### 约数问题
- 对于任意自然数n，都可以分解为：$n=p_{1}^{\alpha_{1}}p_{2}^{\alpha_{2}}...p_{k}^{\alpha_{k}}$
  - 对于任意n，求约数个数：$(1+\alpha_1)(1+\alpha_2)...(1+\alpha_k)$
  - 对于任意n，求约数之和：$(p_1^0+p_1^1+...+p_1^{\alpha_1})(p_2^0+p_2^1+...+p_2^{\alpha_2})...(p_k^0+p_k^1+...+p_k^{\alpha_k})$
# Data Structure
## 手搓数据结构
### BIT
- Binary Indexed Tree，树状数组，又，fenwick tree
- 实用简洁，logN时间内的insert和range query，经典应用场合：index offset
- 华点：index从`1`开始；
  ```cpp
  const int N=100010;

  int tr[N];

  int lowbit(int x){
    return x&-x;
  }

  void add(int idx, int x){
    for(int i=idx; i<N; i+=lowbit(x)) tr[i]+=x;
  }

  int query(int idx){
    int res=0;
    for(int i=idx; i; i-=lowbit(x)) res+=tr[i];
    return res;
  }
  ```
### Union Find
- UF的模板极尽简单，难度在于如何运用上：尽量掌握经典用法。
- 模板
```cpp template_union_find
// 并查集模板
class UnionFind {
public:
  vector<int> parent;
  vector<int> size;
  int n;
  // 当前连通分量数目
  int setCount;

public:
  UnionFind(int _n): n(_n), setCount(_n), parent(_n), size(_n, 1) {
    iota(parent.begin(), parent.end(), 0);
  }

  int findset(int x) {
    return parent[x] == x ? x : parent[x] = findset(parent[x]);
  }

  bool unite(int x, int y) {
    x = findset(x);
    y = findset(y);
    if (x == y) {
      return false;
    }
    if (size[x] < size[y]) {
      swap(x, y);
    }
    parent[y] = x;
    size[x] += size[y];
    --setCount;
    return true;
  }

  bool connected(int x, int y) {
    x = findset(x);
    y = findset(y);
    return x == y;
  }
  void isolate(int x) {
    if(x != parent[x]){
      parent[x] = x;
      size[x] = 1;
      ++setCount;
    }
  }
};
```
- [经典例题：找出知晓秘密的所有专家](https://leetcode-cn.com/problems/find-all-people-with-secret/)
  - 本题关键在于，相同时间开会的情形如何处理，解决方法就是两两连接同一时间开会的专家，会开完之后，孤立所有没知道秘密的专家
  - 这是第一次出现孤立(isolate)操作的题目，核心十分简单：`p[x]=x`
## 高级数据结构
### 平板电视/pbds
  - Member functions:
    - `order_of_key(x)`：返回x的排名
    - `find_by_order(k)`：返回第k小的元素的iterator
    ```cpp template_pbds
    #include <ext/pb_ds/assoc_container.hpp>
    #include <ext/pb_ds/tree_policy.hpp>

    using namespace __gnu_pbds;

    typedef tree<
        int,
        null_type,
        less<int>,
        rb_tree_tag,
        tree_order_statistics_node_update>
        ordered_set;
    typedef tree<
        pair<int, int>,
        null_type,
        less<pair<int, int>>,
        rb_tree_tag,
        tree_order_statistics_node_update>
        ordered_multiset;

    int main{
      ordered_set S;
      // {4}
      S.insert(4);
      assert(4==*S.find_by_order(0));
      assert(S.end()==S.find_by_order(100));
      // {1,4}
      S.insert(1);
      assert(0==S.order_of_key(1));
      // {1,3,4}
      S.insert(3);
      assert(1==S.order_of_key(2));
      assert(1==S.order_of_key(3));
      assert(3==*S.lower_bound(2));
      assert(3==S.order_of_key(1e9));

      return 0;
    }
    ```
