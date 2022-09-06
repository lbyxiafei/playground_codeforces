// ref: https://codeforces.com/blog/entry/82400
#include <bits/stdc++.h>

#define forn(i, n) for (int i = 0; i < int(n); i++)

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;

namespace internal {
    // @param n `0 <= n`
    // @return minimum non-negative `x` s.t. `n <= 2**x`
    int ceil_pow2(int n) {
        int x = 0;
        while((1U << x) < (unsigned int)(n))
            x++;
        return x;
    }
}

// 0-index based, 左闭右开 [l, r)
template <class S, S (*op)(S, S), S (*e)()> struct segtree {
  public:
    segtree() : segtree(0) {}
    segtree(int n) : segtree(std::vector<S>(n, e())) {}
    segtree(const std::vector<S>& v) : _n(int(v.size())) {
        log = internal::ceil_pow2(_n);
        size = 1 << log;
        d = std::vector<S>(2 * size, e());
        for (int i = 0; i < _n; i++) d[size + i] = v[i];
        for (int i = size - 1; i >= 1; i--) {
            update(i);
        }
    }

    void set(int p, S x) {
        assert(0 <= p && p < _n);
        p += size;
        d[p] = x;
        for (int i = 1; i <= log; i++) update(p >> i);
    }

    S get(int p) {
        assert(0 <= p && p < _n);
        return d[p + size];
    }

    S prod(int l, int r) {
        assert(0 <= l && l <= r && r <= _n);
        S sml = e(), smr = e();
        l += size;
        r += size;

        while (l < r) {
            if (l & 1) sml = op(sml, d[l++]);
            if (r & 1) smr = op(d[--r], smr);
            l >>= 1;
            r >>= 1;
        }
        return op(sml, smr);
    }

    S all_prod() { return d[1]; }

    template <bool (*f)(S)> int max_right(int l) {
        return max_right(l, [](S x) { return f(x); });
    }
    template <class F> int max_right(int l, F f) {
        assert(0 <= l && l <= _n);
        assert(f(e()));
        if (l == _n) return _n;
        l += size;
        S sm = e();
        do {
            while (l % 2 == 0) l >>= 1;
            if (!f(op(sm, d[l]))) {
                while (l < size) {
                    l = (2 * l);
                    if (f(op(sm, d[l]))) {
                        sm = op(sm, d[l]);
                        l++;
                    }
                }
                return l - size;
            }
            sm = op(sm, d[l]);
            l++;
        } while ((l & -l) != l);
        return _n;
    }

    template <bool (*f)(S)> int min_left(int r) {
        return min_left(r, [](S x) { return f(x); });
    }
    template <class F> int min_left(int r, F f) {
        assert(0 <= r && r <= _n);
        assert(f(e()));
        if (r == 0) return 0;
        r += size;
        S sm = e();
        do {
            r--;
            while (r > 1 && (r % 2)) r >>= 1;
            if (!f(op(d[r], sm))) {
                while (r < size) {
                    r = (2 * r + 1);
                    if (f(op(d[r], sm))) {
                        sm = op(d[r], sm);
                        r--;
                    }
                }
                return r + 1 - size;
            }
            sm = op(d[r], sm);
        } while ((r & -r) != r);
        return 0;
    }

  private:
    int _n, size, log;
    std::vector<S> d;

    void update(int k) { d[k] = op(d[2 * k], d[2 * k + 1]); }
};

// prod(l,r) will return max element from [l,r)
int op(int a, int b) { return max(a, b); }

// prod(i,i) will return -1
int e() { return -1; }

// helper func for max_right(l) and min_left(r)
int target;
bool check(int v) { return v < target; }

int main() {
#ifdef _LBY
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    vector<int> arr{1,3,2,5,4,8,7,10};

    segtree<int, op, e> seg(arr);

    // op定义：求区间最大值
    cout << seg.all_prod() << endl; // 10
    cout << seg.prod(0,0) << endl;  // e(): -1
    cout << seg.prod(0,1) << endl;  // 1
    cout << seg.prod(0,2) << endl;  // 3
    cout << seg.prod(0,3) << endl;  // 3
    cout << seg.prod(0,4) << endl;  // 5

    cout << endl;

    // max_right(l): 给定bool check(x)，返回r，使得：[l,r)区间内的元素统统满足check(x)
    // 注：check函数必须满足check(e())===true
    target = 5;
    cout << seg.max_right<check>(0) << endl; // 3 -> [0,3)内所有元素均小于target(5)


    // 类似的，min_left(r)：给定bool check(x)，返回l，使得[l,r)内所有元素满足check(x)
    target = 6;
    cout << seg.min_left<check>(4) << endl; // 0 -> [0,4)内所有元素均小于target(6)

    // set
    cout << endl;
    seg.set(0,11);
    cout << seg.all_prod() << endl; // 11

    // out
    for(int i=0; i<arr.size(); i++) cout << seg.get(i) << ' ';
    cout << endl;

    return 0;
}