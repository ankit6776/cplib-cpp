---
data:
  _extendedDependsOn:
  - icon: ':x:'
    path: graph/general_matching.hpp
    title: graph/general_matching.hpp
  - icon: ':x:'
    path: linear_algebra_matrix/linalg_modint.hpp
    title: linear_algebra_matrix/linalg_modint.hpp
  - icon: ':question:'
    path: modint.hpp
    title: modint.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/general_matching
    links:
    - https://judge.yosupo.jp/problem/general_matching
  bundledCode: "#line 2 \"modint.hpp\"\n#include <iostream>\n#include <vector>\n#include\
    \ <set>\n\n// CUT begin\ntemplate <int mod>\nstruct ModInt\n{\n    using lint\
    \ = long long;\n    static int get_mod() { return mod; }\n    static int get_primitive_root()\
    \ {\n        static int primitive_root = 0;\n        if (!primitive_root) {\n\
    \            primitive_root = [&](){\n                std::set<int> fac;\n   \
    \             int v = mod - 1;\n                for (lint i = 2; i * i <= v; i++)\
    \ while (v % i == 0) fac.insert(i), v /= i;\n                if (v > 1) fac.insert(v);\n\
    \                for (int g = 1; g < mod; g++) {\n                    bool ok\
    \ = true;\n                    for (auto i : fac) if (ModInt(g).power((mod - 1)\
    \ / i) == 1) { ok = false; break; }\n                    if (ok) return g;\n \
    \               }\n                return -1;\n            }();\n        }\n \
    \       return primitive_root;\n    }\n    int val;\n    constexpr ModInt() :\
    \ val(0) {}\n    constexpr ModInt &_setval(lint v) { val = (v >= mod ? v - mod\
    \ : v); return *this; }\n    constexpr ModInt(lint v) { _setval(v % mod + mod);\
    \ }\n    explicit operator bool() const { return val != 0; }\n    constexpr ModInt\
    \ operator+(const ModInt &x) const { return ModInt()._setval((lint)val + x.val);\
    \ }\n    constexpr ModInt operator-(const ModInt &x) const { return ModInt()._setval((lint)val\
    \ - x.val + mod); }\n    constexpr ModInt operator*(const ModInt &x) const { return\
    \ ModInt()._setval((lint)val * x.val % mod); }\n    constexpr ModInt operator/(const\
    \ ModInt &x) const { return ModInt()._setval((lint)val * x.inv() % mod); }\n \
    \   constexpr ModInt operator-() const { return ModInt()._setval(mod - val); }\n\
    \    constexpr ModInt &operator+=(const ModInt &x) { return *this = *this + x;\
    \ }\n    constexpr ModInt &operator-=(const ModInt &x) { return *this = *this\
    \ - x; }\n    constexpr ModInt &operator*=(const ModInt &x) { return *this = *this\
    \ * x; }\n    constexpr ModInt &operator/=(const ModInt &x) { return *this = *this\
    \ / x; }\n    friend constexpr ModInt operator+(lint a, const ModInt &x) { return\
    \ ModInt()._setval(a % mod + x.val); }\n    friend constexpr ModInt operator-(lint\
    \ a, const ModInt &x) { return ModInt()._setval(a % mod - x.val + mod); }\n  \
    \  friend constexpr ModInt operator*(lint a, const ModInt &x) { return ModInt()._setval(a\
    \ % mod * x.val % mod); }\n    friend constexpr ModInt operator/(lint a, const\
    \ ModInt &x) { return ModInt()._setval(a % mod * x.inv() % mod); }\n    constexpr\
    \ bool operator==(const ModInt &x) const { return val == x.val; }\n    constexpr\
    \ bool operator!=(const ModInt &x) const { return val != x.val; }\n    bool operator<(const\
    \ ModInt &x) const { return val < x.val; }  // To use std::map<ModInt, T>\n  \
    \  friend std::istream &operator>>(std::istream &is, ModInt &x) { lint t; is >>\
    \ t; x = ModInt(t); return is; }\n    friend std::ostream &operator<<(std::ostream\
    \ &os, const ModInt &x) { os << x.val;  return os; }\n    constexpr lint power(lint\
    \ n) const {\n        lint ans = 1, tmp = this->val;\n        while (n) {\n  \
    \          if (n & 1) ans = ans * tmp % mod;\n            tmp = tmp * tmp % mod;\n\
    \            n /= 2;\n        }\n        return ans;\n    }\n    constexpr ModInt\
    \ pow(lint n) const {\n        return power(n);\n    }\n    constexpr lint inv()\
    \ const { return this->power(mod - 2); }\n    constexpr ModInt operator^(lint\
    \ n) const { return ModInt(this->power(n)); }\n    constexpr ModInt &operator^=(lint\
    \ n) { return *this = *this ^ n; }\n\n    inline ModInt fac() const {\n      \
    \  static std::vector<ModInt> facs;\n        int l0 = facs.size();\n        if\
    \ (l0 > this->val) return facs[this->val];\n\n        facs.resize(this->val +\
    \ 1);\n        for (int i = l0; i <= this->val; i++) facs[i] = (i == 0 ? ModInt(1)\
    \ : facs[i - 1] * ModInt(i));\n        return facs[this->val];\n    }\n\n    ModInt\
    \ doublefac() const {\n        lint k = (this->val + 1) / 2;\n        if (this->val\
    \ & 1) return ModInt(k * 2).fac() / ModInt(2).power(k) / ModInt(k).fac();\n  \
    \      else return ModInt(k).fac() * ModInt(2).power(k);\n    }\n\n    ModInt\
    \ nCr(const ModInt &r) const {\n        if (this->val < r.val) return ModInt(0);\n\
    \        return this->fac() / ((*this - r).fac() * r.fac());\n    }\n\n    ModInt\
    \ sqrt() const {\n        if (val == 0) return 0;\n        if (mod == 2) return\
    \ val;\n        if (power((mod - 1) / 2) != 1) return 0;\n        ModInt b = 1;\n\
    \        while (b.power((mod - 1) / 2) == 1) b += 1;\n        int e = 0, m = mod\
    \ - 1;\n        while (m % 2 == 0) m >>= 1, e++;\n        ModInt x = power((m\
    \ - 1) / 2), y = (*this) * x * x;\n        x *= (*this);\n        ModInt z = b.power(m);\n\
    \        while (y != 1) {\n            int j = 0;\n            ModInt t = y;\n\
    \            while (t != 1) j++, t *= t;\n            z = z.power(1LL << (e -\
    \ j - 1));\n            x *= z, z *= z, y *= z;\n            e = j;\n        }\n\
    \        return ModInt(std::min(x.val, mod - x.val));\n    }\n};\n// using mint\
    \ = ModInt<998244353>;\n// using mint = ModInt<1000000007>;\n#line 2 \"linear_algebra_matrix/linalg_modint.hpp\"\
    \n#include <algorithm>\n#include <cassert>\n#line 5 \"linear_algebra_matrix/linalg_modint.hpp\"\
    \n#include <iterator>\n#line 7 \"linear_algebra_matrix/linalg_modint.hpp\"\n\n\
    // CUT begin\ntemplate <typename T>\nstruct matrix\n{\n    int H, W;\n    std::vector<T>\
    \ elem;\n    typename std::vector<T>::iterator operator[](int i) { return elem.begin()\
    \ + i * W; }\n    inline T &at(int i, int j) { return elem[i * W + j]; }\n   \
    \ inline T get(int i, int j) const { return elem[i * W + j]; }\n    operator std::vector<std::vector<T>>()\
    \ const {\n        std::vector<std::vector<T>> ret(H);\n        for (int i = 0;\
    \ i < H; i++) std::copy(elem.begin() + i * W, elem.begin() + (i + 1) * W, std::back_inserter(ret[i]));\n\
    \        return ret;\n    }\n\n    matrix() = default;\n    matrix(int H, int\
    \ W) : H(H), W(W), elem(H * W) {}\n    matrix(const std::vector<std::vector<T>>\
    \ &d) : H(d.size()), W(d.size() ? d[0].size() : 0) {\n        for (auto &raw :\
    \ d) std::copy(raw.begin(), raw.end(), std::back_inserter(elem));\n    }\n\n \
    \   static matrix Identity(int N) {\n        matrix ret(N, N);\n        for (int\
    \ i = 0; i < N; i++) ret.at(i, i) = 1;\n        return ret;\n    }\n\n    matrix\
    \ operator-() const { matrix ret(H, W); for (int i = 0; i < H * W; i++) ret.elem[i]\
    \ = -elem[i]; return ret; }\n    matrix operator*(const T &v) const { matrix ret\
    \ = *this; for (auto &x : ret.elem) x *= v; return ret; }\n    matrix operator/(const\
    \ T &v) const { matrix ret = *this; for (auto &x : ret.elem) x /= v; return ret;\
    \ }\n    matrix operator+(const matrix &r) const { matrix ret = *this; for (int\
    \ i = 0; i < H * W; i++) ret.elem[i] += r.elem[i]; return ret; }\n    matrix operator-(const\
    \ matrix &r) const { matrix ret = *this; for (int i = 0; i < H * W; i++) ret.elem[i]\
    \ -= r.elem[i]; return ret; }\n    matrix operator*(const matrix &r) const {\n\
    \        matrix ret(H, r.W);\n        for (int i = 0; i < H; i++) {\n        \
    \    for (int k = 0; k < W; k++) {\n                for (int j = 0; j < r.W; j++)\
    \ {\n                    ret.at(i, j) += this->get(i, k) * r.get(k, j);\n    \
    \            }\n            }\n        }\n        return ret;\n    }\n    matrix\
    \ &operator*=(const T &v) { return *this = *this * v; }\n    matrix &operator/=(const\
    \ T &v) { return *this = *this / v; }\n    matrix &operator+=(const matrix &r)\
    \ { return *this = *this + r; }\n    matrix &operator-=(const matrix &r) { return\
    \ *this = *this - r; }\n    matrix &operator*=(const matrix &r) { return *this\
    \ = *this * r; }\n    bool operator==(const matrix &r) const { return H == r.H\
    \ and W == r.W and elem == r.elem; }\n    bool operator!=(const matrix &r) const\
    \ { return H != r.H or W != r.W or elem != r.elem; }\n    bool operator<(const\
    \ matrix &r) const { return elem < r.elem; }\n    matrix pow(int64_t n) const\
    \ {\n        matrix ret = Identity(H);\n        if (n == 0) return ret;\n    \
    \    for (int i = 63 - __builtin_clzll(n); i >= 0; i--) {\n            ret *=\
    \ ret;\n            if ((n >> i) & 1) ret *= (*this);\n        }\n        return\
    \ ret;\n    }\n    matrix transpose() const {\n        matrix ret(W, H);\n   \
    \     for (int i = 0; i < H; i++) for (int j = 0; j < W; j++) ret.at(j, i) = this->get(i,\
    \ j);\n        return ret;\n    }\n    // Gauss-Jordan elimination\n    // - Require\
    \ inverse for every non-zero element\n    // - Complexity: O(H^2 W)\n    matrix\
    \ gauss_jordan() const {\n        int c = 0;\n        matrix mtr(*this);\n   \
    \     for (int h = 0; h < H; h++) {\n            if (c == W) break;\n        \
    \    int piv = -1;\n            for (int j = h; j < H; j++) if (mtr.get(j, c))\
    \ {\n                piv = j;\n                break;\n            }\n       \
    \     if (piv == -1) { c++; h--; continue; }\n            if (h != piv) {\n  \
    \              for (int w = 0; w < W; w++) {\n                    std::swap(mtr[piv][w],\
    \ mtr[h][w]);\n                    mtr.at(piv, w) *= -1; // To preserve sign of\
    \ determinant\n                }\n            }\n            for (int hh = 0;\
    \ hh < H; hh++) if (hh != h) {\n                T coeff = mtr.at(hh, c) * mtr.at(h,\
    \ c).inv();\n                for (int w = W - 1; w >= c; w--) {\n            \
    \        mtr.at(hh, w) -= mtr.at(h, w) * coeff;\n                }\n         \
    \   }\n            c++;\n        }\n        return mtr;\n    }\n    int rank_of_gauss_jordan()\
    \ const {\n        for (int i = H * W - 1; i >= 0; i--) if (elem[i]) return i\
    \ / W + 1;\n        return 0;\n    }\n    T determinant_of_upper_triangle() const\
    \ {\n        T ret = 1;\n        for (int i = 0; i < H; i++) ret *= get(i, i);\n\
    \        return ret;\n    }\n    int inverse() {\n        assert(H == W);\n  \
    \      std::vector<std::vector<T>> ret = Identity(H), tmp = *this;\n        int\
    \ rank = 0;\n        for (int i = 0; i < H; i++) {\n            int ti = i;\n\
    \            while (ti < H and tmp[ti][i] == 0) ti++;\n            if (ti == H)\
    \ continue;\n            else rank++;\n            ret[i].swap(ret[ti]), tmp[i].swap(tmp[ti]);\n\
    \            T inv = tmp[i][i].inv();\n            for (int j = 0; j < W; j++)\
    \ {\n                ret[i][j] *= inv;\n            }\n            for (int j\
    \ = i + 1; j < W; j++) {\n                tmp[i][j] *= inv;\n            }\n \
    \           for (int h = 0; h < H; h++) {\n                if (i == h) continue;\n\
    \                const T c = -tmp[h][i];\n                for (int j = 0; j <\
    \ W; j++) {\n                    ret[h][j] += ret[i][j] * c;\n               \
    \ }\n                for (int j = i + 1; j < W; j++) {\n                    tmp[h][j]\
    \ += tmp[i][j] * c;\n                }\n            }\n        }\n        *this\
    \ = ret;\n        return rank;\n    }\n    friend std::vector<T> operator*(const\
    \ matrix &m, const std::vector<T> &v) {\n        assert(m.W == int(v.size()));\n\
    \        std::vector<T> ret(m.H);\n        for (int i = 0; i < m.H; i++) {\n \
    \           for (int j = 0; j < m.W; j++) {\n                ret[i] += m.get(i,\
    \ j) * v[j];\n            }\n        }\n        return ret;\n    }\n    friend\
    \ std::vector<T> operator*(const std::vector<T> &v, const matrix &m) {\n     \
    \   assert(int(v.size()) == m.H);\n        std::vector<T> ret(m.W);\n        for\
    \ (int i = 0; i < m.H; i++) {\n            for (int j = 0; j < m.W; j++) {\n \
    \               ret[j] += v[i] * m.get(i, j);\n            }\n        }\n    \
    \    return ret;\n    }\n    friend std::ostream &operator<<(std::ostream &os,\
    \ const matrix &x) {\n        os << \"[(\" << x.H << \" * \" << x.W << \" matrix)\"\
    ;\n        os << \"\\n[column sums: \";\n        for (int j = 0; j < x.W; j++)\
    \ {\n            T s = 0;\n            for (int i = 0; i < x.H; i++) s += x.get(i,\
    \ j);\n            os << s << \",\";\n        }\n        os << \"]\";\n      \
    \  for (int i = 0; i < x.H; i++) {\n            os << \"\\n[\";\n            for\
    \ (int j = 0; j < x.W; j++) os << x.get(i, j) << \",\";\n            os << \"\
    ]\";\n        }\n        os << \"]\\n\";\n        return os;\n    }\n    friend\
    \ std::istream &operator>>(std::istream &is, matrix &x) {\n        for (auto &v\
    \ : x.elem) is >> v;\n        return is;\n    }\n};\n\n\n// Fibonacci numbers\
    \ f(n) = af(n - 1) + bf(n - 2)\n// Example (a = b = 1): 0=>1, 1=>1, 2=>2, 3=>3,\
    \ 4=>5, ...\ntemplate <typename T>\nT Fibonacci(long long int k, int a = 1, int\
    \ b = 1)\n{\n    matrix<T> mat(2, 2);\n    mat[0][1] = 1;\n    mat[1][0] = b;\n\
    \    mat[1][1] = a;\n    return mat.pow(k + 1)[0][1];\n}\n#line 5 \"graph/general_matching.hpp\"\
    \n#include <chrono>\n#include <queue>\n#include <random>\n#include <utility>\n\
    #line 10 \"graph/general_matching.hpp\"\n\n// CUT begin\n// Find maximum matchings\
    \ in general graph using the Tutte matrix (The Rabin-Vazirani algorithm)\n// Complexity:\
    \ O(N^3)\n// Reference: <https://github.com/kth-competitive-programming/kactl/blob/master/content/graph/GeneralMatching.h>\n\
    //            <https://kopricky.github.io/code/Academic/maximum_matching.html>\n\
    std::vector<std::pair<int, int>> generalMatching(int N, std::vector<std::pair<int,\
    \ int>> ed)\n{\n    using MODINT = ModInt<1000000007>;\n    std::vector<std::pair<int,\
    \ int>> ed_tmp;\n    for (auto p : ed) {\n        if (p.first != p.second) {\n\
    \            ed_tmp.emplace_back(std::minmax(p.first, p.second));\n        }\n\
    \    }\n    ed = ed_tmp, std::sort(ed.begin(), ed.end()), ed.erase(std::unique(ed.begin(),\
    \ ed.end()), ed.end());\n    std::vector<std::pair<int, int>> ret;\n\n    std::vector<int>\
    \ deg(N), used(N);\n    std::vector<std::vector<int>> conn(N);\n    for (auto\
    \ p : ed) {\n        deg[p.first]++, deg[p.second]++;\n        conn[p.first].emplace_back(p.second),\
    \ conn[p.second].emplace_back(p.first);\n    }\n    std::queue<int> q_deg1;\n\
    \    for (int i = 0; i < N; i++) {\n        if (deg[i] == 1) {\n            q_deg1.emplace(i);\n\
    \        }\n    }\n    while (q_deg1.size()) {\n        int i = q_deg1.front(),\
    \ j = -1;\n        q_deg1.pop();\n        if (!used[i]) {\n            for (auto\
    \ k : conn[i]) {\n                if (!used[k]) {\n                    j = k,\
    \ ret.emplace_back(i, j);\n                    break;\n                }\n   \
    \         }\n        }\n        for (int t = 0; t < 2; t++) {\n            if\
    \ (i >= 0 and !used[i]) {\n                used[i] = 1;\n                for (auto\
    \ k : conn[i]) {\n                    deg[k]--;\n                    if (deg[k]\
    \ == 1) {\n                        q_deg1.emplace(k);\n                    }\n\
    \                }\n            }\n            std::swap(i, j);\n        }\n \
    \   }\n\n    std::vector<int> idx(N, -1), idx_inv;\n    for (int i = 0; i < N;\
    \ i++) {\n        if (deg[i] > 0 and !used[i]) {\n            idx[i] = idx_inv.size(),\
    \ idx_inv.emplace_back(i);\n        }\n    }\n\n    const int D = idx_inv.size();\n\
    \    if (D == 0) {\n        return ret;\n    }\n    std::mt19937 mt(std::chrono::steady_clock::now().time_since_epoch().count());\n\
    \    std::uniform_int_distribution<int> d(MODINT::get_mod());\n\n    std::vector<std::vector<MODINT>>\
    \ mat(D, std::vector<MODINT>(D));\n    for (auto p : ed) {\n        int a = idx[p.first],\
    \ b = idx[p.second];\n        if (a < 0 or b < 0) continue;\n        mat[a][b]\
    \ = d(mt), mat[b][a] = -mat[a][b];\n    }\n    matrix<MODINT> A = mat;\n    const\
    \ int rank = A.inverse(), M = 2 * D - rank;\n    if (M != D) {\n        do {\n\
    \            mat.resize(M, std::vector<MODINT>(M));\n            for (int i =\
    \ 0; i < D; i++) {\n                mat[i].resize(M);\n                for (int\
    \ j = D; j < M; j++) {\n                    mat[i][j] = d(mt), mat[j][i] = -mat[i][j];\n\
    \                }\n            }\n            A = mat;\n        } while (A.inverse()\
    \ != M);\n    }\n\n    std::vector<int> has(M, 1);\n    int fi = -1, fj = -1;\n\
    \    for (int it = 0; it < M / 2; it++) {\n        [&]() {\n            for (int\
    \ i = 0; i < M; i++) {\n                if (has[i]) {\n                    for\
    \ (int j = i + 1; j < M; j++) {\n                        if (A[i][j] and mat[i][j])\
    \ {\n                            fi = i, fj = j;\n                           \
    \ return;\n                        }\n                    }\n                }\n\
    \            }\n        }();\n        if (fj < D) {\n            ret.emplace_back(idx_inv[fi],\
    \ idx_inv[fj]);\n        }\n        has[fi] = has[fj] = 0;\n        for (int sw\
    \ = 0; sw < 2; sw++) {\n            MODINT a = A[fi][fj].inv();\n            for\
    \ (int i = 0; i < M; i++) {\n                if (has[i] and A[i][fj]) {\n    \
    \                MODINT b = A[i][fj] * a;\n                    for (int j = 0;\
    \ j < M; j++) {\n                        A[i][j] -= A[fi][j] * b;\n          \
    \          }\n                }\n            }\n            std::swap(fi, fj);\n\
    \        }\n    }\n    return ret;\n}\n#line 5 \"graph/test/general_matching.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/general_matching\"\n\nusing\
    \ namespace std;\n\nint main()\n{\n    cin.tie(NULL), ios::sync_with_stdio(false);\n\
    \n    int N, M;\n    cin >> N >> M;\n    vector<pair<int, int>> edges;\n    while\
    \ (M--) {\n        int u, v;\n        cin >> u >> v;\n        edges.emplace_back(u,\
    \ v);\n    }\n    vector<pair<int, int>> ret = generalMatching(N, edges);\n  \
    \  cout << ret.size() << '\\n';\n    for (auto [a, b] : ret) {\n        cout <<\
    \ a << ' ' << b << '\\n';\n    }\n}\n"
  code: "#include \"graph/general_matching.hpp\"\n#include <iostream>\n#include <utility>\n\
    #include <vector>\n#define PROBLEM \"https://judge.yosupo.jp/problem/general_matching\"\
    \n\nusing namespace std;\n\nint main()\n{\n    cin.tie(NULL), ios::sync_with_stdio(false);\n\
    \n    int N, M;\n    cin >> N >> M;\n    vector<pair<int, int>> edges;\n    while\
    \ (M--) {\n        int u, v;\n        cin >> u >> v;\n        edges.emplace_back(u,\
    \ v);\n    }\n    vector<pair<int, int>> ret = generalMatching(N, edges);\n  \
    \  cout << ret.size() << '\\n';\n    for (auto [a, b] : ret) {\n        cout <<\
    \ a << ' ' << b << '\\n';\n    }\n}\n"
  dependsOn:
  - graph/general_matching.hpp
  - modint.hpp
  - linear_algebra_matrix/linalg_modint.hpp
  isVerificationFile: true
  path: graph/test/general_matching.test.cpp
  requiredBy: []
  timestamp: '2020-11-15 14:30:27+09:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: graph/test/general_matching.test.cpp
layout: document
redirect_from:
- /verify/graph/test/general_matching.test.cpp
- /verify/graph/test/general_matching.test.cpp.html
title: graph/test/general_matching.test.cpp
---