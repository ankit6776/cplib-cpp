---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: string/rolling_hash_1d.hpp
    title: string/rolling_hash_1d.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://yukicoder.me/problems/1408
    links:
    - https://yukicoder.me/problems/1408
  bundledCode: "#line 2 \"string/rolling_hash_1d.hpp\"\n#include <algorithm>\n#include\
    \ <chrono>\n#include <random>\n#include <string>\n#include <vector>\n\n// CUT\
    \ begin\nstruct DoubleHash : public std::pair<unsigned, unsigned> {\n    using\
    \ ull = unsigned long long;\n    using pair = std::pair<unsigned, unsigned>;\n\
    \    static std::pair<unsigned, unsigned> MODs;\n    DoubleHash(std::pair<unsigned,\
    \ unsigned> x) : pair(x) {}\n    DoubleHash(unsigned x, unsigned y) : pair(x,\
    \ y) {}\n    DoubleHash(unsigned x) : DoubleHash(x, x) {}\n    DoubleHash() :\
    \ DoubleHash(0) {}\n    static inline DoubleHash mod_subtract(pair x) {\n    \
    \    if (x.first >= MODs.first) x.first -= MODs.first;\n        if (x.second >=\
    \ MODs.second) x.second -= MODs.second;\n        return x;\n    }\n    DoubleHash\
    \ operator+(const DoubleHash &x) const {\n        return mod_subtract({this->first\
    \ + x.first, this->second + x.second});\n    }\n    DoubleHash operator+(unsigned\
    \ x) const { return mod_subtract({this->first + x, this->second + x}); }\n   \
    \ DoubleHash operator-(const DoubleHash &x) const {\n        return mod_subtract({this->first\
    \ + MODs.first - x.first, this->second + MODs.second - x.second});\n    }\n  \
    \  DoubleHash operator*(const DoubleHash &x) const {\n        return {unsigned(ull(this->first)\
    \ * x.first % MODs.first), unsigned(ull(this->second) * x.second % MODs.second)};\n\
    \    }\n    DoubleHash operator*(unsigned x) const {\n        return {unsigned(ull(this->first)\
    \ * x % MODs.first), unsigned(ull(this->second) * x % MODs.second)};\n    }\n\
    \    static DoubleHash gen_b(bool force_update = false) {\n        static DoubleHash\
    \ b{0, 0};\n        if (b == DoubleHash{0, 0} or force_update) {\n           \
    \ std::mt19937 mt(std::chrono::steady_clock::now().time_since_epoch().count());\n\
    \            std::uniform_int_distribution<unsigned> d(1 << 16, 1 << 29);\n  \
    \          b = {d(mt), d(mt)};\n        }\n        return b;\n    }\n};\nstd::pair<unsigned,\
    \ unsigned> DoubleHash::MODs{1000000007, 998244353};\n\n// Rolling Hash (Rabin-Karp),\
    \ 1dim\ntemplate <typename V = DoubleHash> struct rolling_hash {\n    int N;\n\
    \    const V B;\n    std::vector<V> hash;         // hash[i] = s[0] * B^(i - 1)\
    \ + ... + s[i - 1]\n    static std::vector<V> power; // power[i] = B^i\n    void\
    \ _extend_powvec() {\n        while (static_cast<int>(power.size()) <= N) {\n\
    \            auto tmp = power.back() * B;\n            power.push_back(tmp);\n\
    \        }\n    }\n    template <typename Int> rolling_hash(const std::vector<Int>\
    \ &s, V b = V::gen_b()) : N(s.size()), B(b), hash(N + 1) {\n        for (int i\
    \ = 0; i < N; i++) hash[i + 1] = hash[i] * B + s[i];\n        _extend_powvec();\n\
    \    }\n    rolling_hash(const std::string &s = \"\", V b = V::gen_b()) : N(s.size()),\
    \ B(b), hash(N + 1) {\n        for (int i = 0; i < N; i++) hash[i + 1] = hash[i]\
    \ * B + s[i];\n        _extend_powvec();\n    }\n    void addchar(const char &c)\
    \ {\n        V hnew = hash[N] * B + c;\n        N++, hash.emplace_back(hnew);\n\
    \        _extend_powvec();\n    }\n    V get(int l, int r) const { // s[l] * B^(r\
    \ - l - 1) + ... + s[r - 1]\n        return hash[r] - hash[l] * power[r - l];\n\
    \    }\n    int lcplen(int l1, int l2) const {\n        return longest_common_prefix(*this,\
    \ l1, *this, l2);\n    }\n};\ntemplate <typename V> std::vector<V> rolling_hash<V>::power{1};\n\
    \n// Longest common prerfix between s1[l1, N1) and s2[l2, N2)\ntemplate <typename\
    \ T>\nint longest_common_prefix(const rolling_hash<T> &rh1, int l1, const rolling_hash<T>\
    \ &rh2, int l2) {\n    int lo = 0, hi = std::min(rh1.N + 1 - l1, rh2.N + 1 - l2);\n\
    \    while (hi - lo > 1) {\n        const int c = (lo + hi) / 2;\n        auto\
    \ h1 = rh1.get(l1, l1 + c), h2 = rh2.get(l2, l2 + c);\n        (h1 == h2 ? lo\
    \ : hi) = c;\n    }\n    return lo;\n}\n// Longest common suffix between s1[0,\
    \ r1) and s2[0, r2)\ntemplate <typename T>\nint longest_common_suffix(const rolling_hash<T>\
    \ &rh1, int r1, const rolling_hash<T> &rh2, int r2) {\n    int lo = 0, hi = std::min(r1,\
    \ r2) + 1;\n    while (hi - lo > 1) {\n        const int c = (lo + hi) / 2;\n\
    \        auto h1 = rh1.get(r1 - c, r1), h2 = rh2.get(r2 - c, r2);\n        (h1\
    \ == h2 ? lo : hi) = c;\n    }\n    return lo;\n}\n#line 2 \"string/test/rolling_hash_lcp.test.cpp\"\
    \n#include <cassert>\n#include <iostream>\n#line 5 \"string/test/rolling_hash_lcp.test.cpp\"\
    \n#define PROBLEM \"https://yukicoder.me/problems/1408\"\nusing namespace std;\n\
    \nint main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n    int N;\n\
    \    cin >> N;\n    vector<rolling_hash<DoubleHash>> rhs, rhs_rev;\n    for (int\
    \ i = 0; i < N; i++) {\n        string s;\n        cin >> s;\n        rhs.emplace_back(s);\n\
    \        reverse(s.begin(), s.end());\n        rhs_rev.emplace_back(s);\n    }\n\
    \n    int M;\n    long long x, d, ret = 0;\n    cin >> M >> x >> d;\n\n    while\
    \ (M--) {\n        int i = x / (N - 1);\n        int j = x % (N - 1);\n      \
    \  if (i <= j) j++;\n        x = (x + d) % (static_cast<long long>(N) * (N - 1));\n\
    \        auto tmp = longest_common_prefix(rhs[i], 0, rhs[j], 0);\n        assert(tmp\
    \ == longest_common_suffix(rhs_rev[i], rhs_rev[i].N, rhs_rev[j], rhs_rev[j].N));\n\
    \        ret += tmp;\n    }\n    cout << ret << '\\n';\n}\n"
  code: "#include \"../rolling_hash_1d.hpp\"\n#include <cassert>\n#include <iostream>\n\
    #include <string>\n#define PROBLEM \"https://yukicoder.me/problems/1408\"\nusing\
    \ namespace std;\n\nint main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n\
    \    int N;\n    cin >> N;\n    vector<rolling_hash<DoubleHash>> rhs, rhs_rev;\n\
    \    for (int i = 0; i < N; i++) {\n        string s;\n        cin >> s;\n   \
    \     rhs.emplace_back(s);\n        reverse(s.begin(), s.end());\n        rhs_rev.emplace_back(s);\n\
    \    }\n\n    int M;\n    long long x, d, ret = 0;\n    cin >> M >> x >> d;\n\n\
    \    while (M--) {\n        int i = x / (N - 1);\n        int j = x % (N - 1);\n\
    \        if (i <= j) j++;\n        x = (x + d) % (static_cast<long long>(N) *\
    \ (N - 1));\n        auto tmp = longest_common_prefix(rhs[i], 0, rhs[j], 0);\n\
    \        assert(tmp == longest_common_suffix(rhs_rev[i], rhs_rev[i].N, rhs_rev[j],\
    \ rhs_rev[j].N));\n        ret += tmp;\n    }\n    cout << ret << '\\n';\n}\n"
  dependsOn:
  - string/rolling_hash_1d.hpp
  isVerificationFile: true
  path: string/test/rolling_hash_lcp.test.cpp
  requiredBy: []
  timestamp: '2021-03-13 17:28:18+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: string/test/rolling_hash_lcp.test.cpp
layout: document
redirect_from:
- /verify/string/test/rolling_hash_lcp.test.cpp
- /verify/string/test/rolling_hash_lcp.test.cpp.html
title: string/test/rolling_hash_lcp.test.cpp
---