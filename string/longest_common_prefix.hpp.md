---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: sparse_table/rmq_sparse_table.hpp
    title: sparse_table/rmq_sparse_table.hpp
  - icon: ':heavy_check_mark:'
    path: string/suffix_array.hpp
    title: string/suffix_array.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: string/test/run_enumerate_lyndon_rmq.test.cpp
    title: string/test/run_enumerate_lyndon_rmq.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"string/suffix_array.hpp\"\n#include <algorithm>\n#include\
    \ <cassert>\n#include <numeric>\n#include <string>\n#include <vector>\n\n// CUT\
    \ begin\n// Suffix array algorithms from AtCoder Library\n// Document: <https://atcoder.github.io/ac-library/master/document_ja/string.html>\n\
    namespace internal {\n\nstd::vector<int> sa_naive(const std::vector<int>& s) {\n\
    \    int n = int(s.size());\n    std::vector<int> sa(n);\n    std::iota(sa.begin(),\
    \ sa.end(), 0);\n    std::sort(sa.begin(), sa.end(), [&](int l, int r) {\n   \
    \     if (l == r) return false;\n        while (l < n && r < n) {\n          \
    \  if (s[l] != s[r]) return s[l] < s[r];\n            l++, r++;\n        }\n \
    \       return l == n;\n    });\n    return sa;\n}\n\nstd::vector<int> sa_doubling(const\
    \ std::vector<int>& s) {\n    int n = int(s.size());\n    std::vector<int> sa(n),\
    \ rnk = s, tmp(n);\n    std::iota(sa.begin(), sa.end(), 0);\n    for (int k =\
    \ 1; k < n; k *= 2) {\n        auto cmp = [&](int x, int y) {\n            if\
    \ (rnk[x] != rnk[y]) return rnk[x] < rnk[y];\n            int rx = x + k < n ?\
    \ rnk[x + k] : -1;\n            int ry = y + k < n ? rnk[y + k] : -1;\n      \
    \      return rx < ry;\n        };\n        std::sort(sa.begin(), sa.end(), cmp);\n\
    \        tmp[sa[0]] = 0;\n        for (int i = 1; i < n; i++) { tmp[sa[i]] = tmp[sa[i\
    \ - 1]] + (cmp(sa[i - 1], sa[i]) ? 1 : 0); }\n        std::swap(tmp, rnk);\n \
    \   }\n    return sa;\n}\n\n// SA-IS, linear-time suffix array construction\n\
    // Reference:\n// G. Nong, S. Zhang, and W. H. Chan,\n// Two Efficient Algorithms\
    \ for Linear Time Suffix Array Construction\ntemplate <int THRESHOLD_NAIVE = 10,\
    \ int THRESHOLD_DOUBLING = 40> std::vector<int> sa_is(const std::vector<int>&\
    \ s, int upper) {\n    int n = int(s.size());\n    if (n == 0) return {};\n  \
    \  if (n == 1) return {0};\n    if (n == 2) {\n        if (s[0] < s[1]) {\n  \
    \          return {0, 1};\n        } else {\n            return {1, 0};\n    \
    \    }\n    }\n    if (n < THRESHOLD_NAIVE) { return sa_naive(s); }\n    if (n\
    \ < THRESHOLD_DOUBLING) { return sa_doubling(s); }\n\n    std::vector<int> sa(n);\n\
    \    std::vector<bool> ls(n);\n    for (int i = n - 2; i >= 0; i--) { ls[i] =\
    \ (s[i] == s[i + 1]) ? ls[i + 1] : (s[i] < s[i + 1]); }\n    std::vector<int>\
    \ sum_l(upper + 1), sum_s(upper + 1);\n    for (int i = 0; i < n; i++) {\n   \
    \     if (!ls[i]) {\n            sum_s[s[i]]++;\n        } else {\n          \
    \  sum_l[s[i] + 1]++;\n        }\n    }\n    for (int i = 0; i <= upper; i++)\
    \ {\n        sum_s[i] += sum_l[i];\n        if (i < upper) sum_l[i + 1] += sum_s[i];\n\
    \    }\n\n    auto induce = [&](const std::vector<int>& lms) {\n        std::fill(sa.begin(),\
    \ sa.end(), -1);\n        std::vector<int> buf(upper + 1);\n        std::copy(sum_s.begin(),\
    \ sum_s.end(), buf.begin());\n        for (auto d : lms) {\n            if (d\
    \ == n) continue;\n            sa[buf[s[d]]++] = d;\n        }\n        std::copy(sum_l.begin(),\
    \ sum_l.end(), buf.begin());\n        sa[buf[s[n - 1]]++] = n - 1;\n        for\
    \ (int i = 0; i < n; i++) {\n            int v = sa[i];\n            if (v >=\
    \ 1 && !ls[v - 1]) { sa[buf[s[v - 1]]++] = v - 1; }\n        }\n        std::copy(sum_l.begin(),\
    \ sum_l.end(), buf.begin());\n        for (int i = n - 1; i >= 0; i--) {\n   \
    \         int v = sa[i];\n            if (v >= 1 && ls[v - 1]) { sa[--buf[s[v\
    \ - 1] + 1]] = v - 1; }\n        }\n    };\n\n    std::vector<int> lms_map(n +\
    \ 1, -1);\n    int m = 0;\n    for (int i = 1; i < n; i++) {\n        if (!ls[i\
    \ - 1] && ls[i]) { lms_map[i] = m++; }\n    }\n    std::vector<int> lms;\n   \
    \ lms.reserve(m);\n    for (int i = 1; i < n; i++) {\n        if (!ls[i - 1] &&\
    \ ls[i]) { lms.push_back(i); }\n    }\n\n    induce(lms);\n\n    if (m) {\n  \
    \      std::vector<int> sorted_lms;\n        sorted_lms.reserve(m);\n        for\
    \ (int v : sa) {\n            if (lms_map[v] != -1) sorted_lms.push_back(v);\n\
    \        }\n        std::vector<int> rec_s(m);\n        int rec_upper = 0;\n \
    \       rec_s[lms_map[sorted_lms[0]]] = 0;\n        for (int i = 1; i < m; i++)\
    \ {\n            int l = sorted_lms[i - 1], r = sorted_lms[i];\n            int\
    \ end_l = (lms_map[l] + 1 < m) ? lms[lms_map[l] + 1] : n;\n            int end_r\
    \ = (lms_map[r] + 1 < m) ? lms[lms_map[r] + 1] : n;\n            bool same = true;\n\
    \            if (end_l - l != end_r - r) {\n                same = false;\n  \
    \          } else {\n                while (l < end_l) {\n                   \
    \ if (s[l] != s[r]) { break; }\n                    l++;\n                   \
    \ r++;\n                }\n                if (l == n || s[l] != s[r]) same =\
    \ false;\n            }\n            if (!same) rec_upper++;\n            rec_s[lms_map[sorted_lms[i]]]\
    \ = rec_upper;\n        }\n\n        auto rec_sa = sa_is<THRESHOLD_NAIVE, THRESHOLD_DOUBLING>(rec_s,\
    \ rec_upper);\n\n        for (int i = 0; i < m; i++) { sorted_lms[i] = lms[rec_sa[i]];\
    \ }\n        induce(sorted_lms);\n    }\n    return sa;\n}\n\n} // namespace internal\n\
    \nstd::vector<int> suffix_array(const std::vector<int>& s, int upper) {\n    assert(0\
    \ <= upper);\n    for (int d : s) { assert(0 <= d && d <= upper); }\n    auto\
    \ sa = internal::sa_is(s, upper);\n    return sa;\n}\n\ntemplate <class T> std::vector<int>\
    \ suffix_array(const std::vector<T>& s) {\n    int n = int(s.size());\n    std::vector<int>\
    \ idx(n);\n    iota(idx.begin(), idx.end(), 0);\n    sort(idx.begin(), idx.end(),\
    \ [&](int l, int r) { return s[l] < s[r]; });\n    std::vector<int> s2(n);\n \
    \   int now = 0;\n    for (int i = 0; i < n; i++) {\n        if (i && s[idx[i\
    \ - 1]] != s[idx[i]]) now++;\n        s2[idx[i]] = now;\n    }\n    return internal::sa_is(s2,\
    \ now);\n}\n\nstd::vector<int> suffix_array(const std::string& s) {\n    int n\
    \ = int(s.size());\n    std::vector<int> s2(n);\n    for (int i = 0; i < n; i++)\
    \ { s2[i] = s[i]; }\n    return internal::sa_is(s2, 255);\n}\n\n// Reference:\n\
    // T. Kasai, G. Lee, H. Arimura, S. Arikawa, and K. Park,\n// Linear-Time Longest-Common-Prefix\
    \ Computation in Suffix Arrays and Its\n// Applications\ntemplate <class T> std::vector<int>\
    \ lcp_array(const std::vector<T>& s, const std::vector<int>& sa) {\n    int n\
    \ = int(s.size());\n    assert(n >= 1);\n    std::vector<int> rnk(n);\n    for\
    \ (int i = 0; i < n; i++) { rnk[sa[i]] = i; }\n    std::vector<int> lcp(n - 1);\n\
    \    int h = 0;\n    for (int i = 0; i < n; i++) {\n        if (h > 0) h--;\n\
    \        if (rnk[i] == 0) continue;\n        int j = sa[rnk[i] - 1];\n       \
    \ for (; j + h < n && i + h < n; h++) {\n            if (s[j + h] != s[i + h])\
    \ break;\n        }\n        lcp[rnk[i] - 1] = h;\n    }\n    return lcp;\n}\n\
    \nstd::vector<int> lcp_array(const std::string& s, const std::vector<int>& sa)\
    \ {\n    int n = int(s.size());\n    std::vector<int> s2(n);\n    for (int i =\
    \ 0; i < n; i++) { s2[i] = s[i]; }\n    return lcp_array(s2, sa);\n}\n\n// Count\
    \ keyword occurence in str\n// Complexity: O(min(|str|, |keyword|) * lg |str|)\n\
    int count_keyword_occurence(const std::string& str, const std::vector<int>& suffarr,\
    \ const std::string& keyword) {\n    const int n = str.size(), m = keyword.size();\n\
    \    assert(n == suffarr.size());\n    if (n < m) return 0;\n    auto f1 = [&](int\
    \ h) {\n        for (int j = 0; h + j < n and j < m; j++) {\n            if (str[h\
    \ + j] < keyword[j]) return true;\n            if (str[h + j] > keyword[j]) return\
    \ false;\n        }\n        return n - h < m;\n    };\n    auto f2 = [&](int\
    \ h) {\n        for (int j = 0; h + j < n and j < m; j++) {\n            // if\
    \ (str[h + j] < keyword[j]) return true;\n            if (str[h + j] > keyword[j])\
    \ return false;\n        }\n        return true;\n    };\n    const auto L = std::partition_point(suffarr.begin(),\
    \ suffarr.end(), f1);\n    const auto R = std::partition_point(L, suffarr.end(),\
    \ f2);\n    return std::distance(L, R);\n    // return std::vector<int>(L, R);\
    \ // if you need occurence positions\n}\n#line 5 \"sparse_table/rmq_sparse_table.hpp\"\
    \n\n// CUT begin\n// Range Minimum Query for static sequence by sparse table\n\
    // Complexity: $O(N \\log N)$ for precalculation, $O(1)$ per query\ntemplate <typename\
    \ T> struct StaticRMQ {\n    inline T func(const T &l, const T &r) const noexcept\
    \ { return std::min<T>(l, r); }\n    int N, lgN;\n    T defaultT;\n    std::vector<std::vector<T>>\
    \ data;\n    std::vector<int> lgx_table;\n    StaticRMQ() = default;\n    StaticRMQ(const\
    \ std::vector<T> &sequence, T defaultT) : N(sequence.size()), defaultT(defaultT)\
    \ {\n        lgx_table.resize(N + 1);\n        for (int i = 2; i < N + 1; i++)\
    \ lgx_table[i] = lgx_table[i >> 1] + 1;\n        lgN = lgx_table[N] + 1;\n   \
    \     data.assign(lgN, std::vector<T>(N, defaultT));\n        data[0] = sequence;\n\
    \        for (int d = 1; d < lgN; d++) {\n            for (int i = 0; i + (1 <<\
    \ d) <= N; i++) {\n                data[d][i] = func(data[d - 1][i], data[d -\
    \ 1][i + (1 << (d - 1))]);\n            }\n        }\n    }\n    T get(int l,\
    \ int r) const { // [l, r), 0-indexed\n        assert(l >= 0 and r <= N);\n  \
    \      if (l >= r) return defaultT;\n        int d = lgx_table[r - l];\n     \
    \   return func(data[d][l], data[d][r - (1 << d)]);\n    }\n};\n#line 5 \"string/longest_common_prefix.hpp\"\
    \n#include <utility>\n#line 8 \"string/longest_common_prefix.hpp\"\n\nstruct LCPsparsetable\
    \ {\n    const int N;\n    std::vector<int> sainv; // len = N\n    StaticRMQ<int>\
    \ rmq;\n    template <typename String> LCPsparsetable(const String &s) : N(s.size())\
    \ {\n        auto sa = suffix_array(s);\n        auto lcp = lcp_array(s, sa);\n\
    \        sainv.resize(N);\n        for (int i = 0; i < N; i++) sainv[sa[i]] =\
    \ i;\n        rmq = {lcp, N};\n    }\n    int lcplen(int l1, int l2) const {\n\
    \        if (l1 == l2) return N - l1;\n        if (l1 == N or l2 == N) return\
    \ 0;\n        l1 = sainv[l1], l2 = sainv[l2];\n        if (l1 > l2) std::swap(l1,\
    \ l2);\n        return rmq.get(l1, l2);\n    }\n};\n"
  code: "#pragma once\n#include \"suffix_array.hpp\"\n#include \"../sparse_table/rmq_sparse_table.hpp\"\
    \n#include <algorithm>\n#include <utility>\n#include <vector>\n#include <string>\n\
    \nstruct LCPsparsetable {\n    const int N;\n    std::vector<int> sainv; // len\
    \ = N\n    StaticRMQ<int> rmq;\n    template <typename String> LCPsparsetable(const\
    \ String &s) : N(s.size()) {\n        auto sa = suffix_array(s);\n        auto\
    \ lcp = lcp_array(s, sa);\n        sainv.resize(N);\n        for (int i = 0; i\
    \ < N; i++) sainv[sa[i]] = i;\n        rmq = {lcp, N};\n    }\n    int lcplen(int\
    \ l1, int l2) const {\n        if (l1 == l2) return N - l1;\n        if (l1 ==\
    \ N or l2 == N) return 0;\n        l1 = sainv[l1], l2 = sainv[l2];\n        if\
    \ (l1 > l2) std::swap(l1, l2);\n        return rmq.get(l1, l2);\n    }\n};\n"
  dependsOn:
  - string/suffix_array.hpp
  - sparse_table/rmq_sparse_table.hpp
  isVerificationFile: false
  path: string/longest_common_prefix.hpp
  requiredBy: []
  timestamp: '2021-03-13 17:28:18+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - string/test/run_enumerate_lyndon_rmq.test.cpp
documentation_of: string/longest_common_prefix.hpp
layout: document
redirect_from:
- /library/string/longest_common_prefix.hpp
- /library/string/longest_common_prefix.hpp.html
title: string/longest_common_prefix.hpp
---