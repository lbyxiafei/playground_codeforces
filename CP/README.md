[toc]
# Algorithm
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
## 排序
### 快速选择
- 给定无序数组，求从小到大的第k个数，例题：[AC.第k个数](https://www.acwing.com/activity/content/problem/content/820/)
  - 基本思路：套用快速排序的模板，在此基础上，根据k和r-start的比较进行下一层递归
  - 华点：这里与k进行比较的不是r，因为k是与start的相对距离，而r是与0的相对距离，需要对r进行一次处理确保一致性
    ```cpp
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
### Dijkstra
#### 朴素版Dijkstra & Prim最小生成树
- 两个算法几乎一模一样，唯一的不同是dist[i]的定义
  - Dijkstra的dist[i]：节点i到`起点`的最小距离
  - [朴素Dijkstra]()
    ```cpp
    int dijkstra(){
      dist[1]=0;
      for(int i=0; i<n; i++){
        int t=-1;
        for(int j=1; j<=n; j++){
          if(!st[j] && (t==-1 || dist[j]<dist[t]))
            t=j;
        }
        st[t]=true;
        if(dist[t]==INF) return -1;
        for(int j=1; j<=n; j++){
          dist[j]=min(dist[j],dist[t]+g[t][j]); // 唯一区别
        }
      }
      return dist[n];
    }
    ```
  - Prim的dist[i]：节点i到`当前最小生成树`的最小距离
  - [Prim最小生成树例题](https://www.acwing.com/activity/content/problem/content/924/)
    ```cpp
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
- no-op
### SPFA
- 算法核心：st状态数组表示的是in-queue
#### SPFA最短路
- [SPFA求最短路例题](https://www.acwing.com/activity/content/problem/content/922/)
  ```cpp
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
  ```cpp
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
- 算法核心：纯粹的以`边`为单位，进行遍历
- [有边数限制的最短路例题](https://www.acwing.com/activity/content/problem/content/922/)
  ```cpp
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
  ```cpp
  for(int k=1; k<=n; k++)
    for(int i=1; i<=n; i++)
      for(int j=1; j<=n; j++)
        if(f[i][k]<INF && f[k][j]<INF)
          f[i][j]=min(f[i][j],f[i][k]+f[k][j]);
  ```
## DP
### 背包
- 背包要诀：
  - 循环永远是：物品→体积→决策
  - `1维`状态数组下，只有`完全`背包的第二层循环是`从左往右`
    - 而二维情况下，体积层的循环一致遵循从左往右即可
- 背包属于是`组合类DP`。之前努力试图强记套路，然而从最原始的二维定义出发，这其实是一种相较于线性DP更高级复杂的DP
#### 完全背包
- 二维DP
  ```cpp
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
  ```
- 一维DP
  ```cpp
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
- 二进制优化法
  - 将物品个数(决策)进行`二进制分解、打散`，合并入一个新的V,W数组中，进而把问题转化成了0-1背包问题
  - 例题：[AC.多重背包](https://www.acwing.com/activity/content/problem/content/1000/)
    ```cpp
    int main(){
      int n,m;
      cin >> n >> m;
      vector<int> V,W;
      for(int i=0; i<n; i++){
        int v,w,s;
        cin >> v >> w >> s;
        for(int i=0; (1<<i)<=s; i++){
          int t=1<<i;
          V.push_back(t*v);
          W.push_back(t*w);
          s-=t;
        }
        if(s) V.push_back(s*v), W.push_back(s*w);
      }
      // 为展示作用，这里是二维版本，OJ中会MLE，转换成一维即可AC
      n=V.size();
      int f[n+1][m+1];
      memset(f,0,sizeof f);
      for(int i=1; i<=n; i++){
        int v=V[i-1], w=W[i-1];
        for(int j=0; j<=m; j++){
          f[i][j]=f[i-1][j];
          if(j>=v) f[i][j]=max(f[i][j],f[i-1][j-v]+w);
        }
      }
      cout << f[n][m] << endl;
      return 0;
    }
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
```cpp
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
    ```cpp
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
