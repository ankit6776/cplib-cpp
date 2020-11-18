---
data:
  _extendedDependsOn:
  - icon: ':x:'
    path: sparse_table/disjoint_sparse_table.hpp
    title: sparse_table/disjoint_sparse_table.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/static_range_sum
    links:
    - https://judge.yosupo.jp/problem/static_range_sum
  bundledCode: "#line 2 \"sparse_table/disjoint_sparse_table.hpp\"\n#include <algorithm>\n\
    #include <cassert>\n#include <vector>\n\n// CUT begin\n// Disjoint sparse table\n\
    // <https://discuss.codechef.com/t/tutorial-disjoint-sparse-table/17404>\n// <https://drken1215.hatenablog.com/entry/2018/09/08/162600>\n\
    // Complexity: O(NlogN) for precalculation, O(1) per query\n// - get(l, r): return\
    \ op(x_l, ..., x_{r - 1})\ntemplate <typename T, typename F> struct DisjointSparseTable\
    \ {\n    int N, sz;\n    F f;\n    std::vector<std::vector<T>> data;\n    static\
    \ int _msb(int x) noexcept { return x == 0 ? 0 : (__builtin_clz(x) ^ 31); }\n\
    \    DisjointSparseTable() = default;\n    DisjointSparseTable(const std::vector<T>\
    \ &seq, F op) : N(seq.size()), f(op) {\n        sz = 1 << (_msb(N - 1) + 1);\n\
    \        data.assign(_msb(sz) + 1, std::vector<T>(sz));\n        std::copy(seq.begin(),\
    \ seq.end(), data[0].begin());\n\n        for (int h = 1, half = 2; half < N;\
    \ h++, half <<= 1) {\n            for (int i = half; i < sz; i += half * 2) {\n\
    \                data[h][i - 1] = data[0][i - 1];\n                for (int j\
    \ = i - 2; j >= i - half; j--) { data[h][j] = f(data[0][j], data[h][j + 1]); }\n\
    \                data[h][i] = data[0][i];\n                for (int j = i + 1;\
    \ j < i + half; j++) { data[h][j] = f(data[h][j - 1], data[0][j]); }\n       \
    \     }\n        }\n    }\n    // [l, r), 0-indexed\n    T get(int l, int r) {\n\
    \        assert(l >= 0 and r <= N and l < r);\n        if (l + 1 == r) return\
    \ data[0][l];\n        int h = _msb(l ^ (r - 1));\n        return f(data[h][l],\
    \ data[h][r - 1]);\n    }\n};\n#line 3 \"sparse_table/test/disjoint_sparse_table_rsq.test.cpp\"\
    \n#include <cstdio>\n#define PROBLEM \"https://judge.yosupo.jp/problem/static_range_sum\"\
    \n\nint main() {\n    int N, Q;\n    scanf(\"%d %d\", &N, &Q);\n    std::vector<long\
    \ long> A(N);\n    for (int i = 0; i < N; i++) { scanf(\"%lld\", &A[i]); }\n \
    \   auto f = [](long long l, long long r) { return l + r; };\n    DisjointSparseTable<long\
    \ long, decltype(f)> st(A, f);\n    while (Q--) {\n        int l, r;\n       \
    \ scanf(\"%d %d\", &l, &r);\n        long long a = st.get(l, r);\n        printf(\"\
    %lld\\n\", a);\n    }\n}\n"
  code: "#include \"sparse_table/disjoint_sparse_table.hpp\"\n#include <cassert>\n\
    #include <cstdio>\n#define PROBLEM \"https://judge.yosupo.jp/problem/static_range_sum\"\
    \n\nint main() {\n    int N, Q;\n    scanf(\"%d %d\", &N, &Q);\n    std::vector<long\
    \ long> A(N);\n    for (int i = 0; i < N; i++) { scanf(\"%lld\", &A[i]); }\n \
    \   auto f = [](long long l, long long r) { return l + r; };\n    DisjointSparseTable<long\
    \ long, decltype(f)> st(A, f);\n    while (Q--) {\n        int l, r;\n       \
    \ scanf(\"%d %d\", &l, &r);\n        long long a = st.get(l, r);\n        printf(\"\
    %lld\\n\", a);\n    }\n}\n"
  dependsOn:
  - sparse_table/disjoint_sparse_table.hpp
  isVerificationFile: true
  path: sparse_table/test/disjoint_sparse_table_rsq.test.cpp
  requiredBy: []
  timestamp: '2020-11-18 20:25:12+09:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: sparse_table/test/disjoint_sparse_table_rsq.test.cpp
layout: document
redirect_from:
- /verify/sparse_table/test/disjoint_sparse_table_rsq.test.cpp
- /verify/sparse_table/test/disjoint_sparse_table_rsq.test.cpp.html
title: sparse_table/test/disjoint_sparse_table_rsq.test.cpp
---