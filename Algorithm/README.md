[toc]
## Algorithm
### 排序
#### 快速选择
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
### Array
#### Subarray
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
### DP
#### 背包
- 背包要诀：
  - 循环永远是：物品→体积→决策
  - `1维`状态数组下，只有`完全`背包的第二层循环是`从左往右`
    - 而二维情况下，体积层的循环一致遵循从左往右即可
- 背包属于是`组合类DP`。之前努力试图强记套路，然而从最原始的二维定义出发，这其实是一种相较于线性DP更高级复杂的DP
##### 完全背包
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