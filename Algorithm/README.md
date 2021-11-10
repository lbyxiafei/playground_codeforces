[toc]
## Algorithm
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
