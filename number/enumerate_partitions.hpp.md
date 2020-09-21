---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    links: []
  bundledCode: "#line 1 \"number/enumerate_partitions.hpp\"\n#include <algorithm>\n\
    #include <numeric>\n#include <vector>\n\n// CUT begin\n// Enumerate Partitions\
    \ of number <= N \uFF08\u81EA\u7136\u6570\u306E\u5206\u5272\u306E\u5217\u6319\uFF09\
    \n// - can be used for N less than ~50\n// - Example:\n//   - 1 => [[1,],]\n//\
    \   - 2 => [[1,],[1,1,],[2,],]\n//   - 3 => [[1,],[1,1,],[1,1,1,],[2,],[2,1,],[3,],]\n\
    struct\n{\n    std::vector<std::vector<int>> ret;\n    std::vector<int> now;\n\
    \    int num;\n    void _partition_dfs() {\n        int rem = num - std::accumulate(now.begin(),\
    \ now.end(), 0);\n        if (!now.empty()) rem = std::min(rem, now.back());\n\
    \n        now.push_back(0);\n        for (int j = 1; j <= rem; j++) {\n      \
    \      now.back() = j;\n            ret.push_back(now);\n            _partition_dfs();\n\
    \        }\n        now.pop_back();\n    }\n\n    std::vector<std::vector<int>>\
    \ operator()(int N) {\n        ret.clear();\n        now.clear();\n        num\
    \ = N;\n        _partition_dfs();\n        return ret;\n    }\n} EnumeratePartitions;\n"
  code: "#include <algorithm>\n#include <numeric>\n#include <vector>\n\n// CUT begin\n\
    // Enumerate Partitions of number <= N \uFF08\u81EA\u7136\u6570\u306E\u5206\u5272\
    \u306E\u5217\u6319\uFF09\n// - can be used for N less than ~50\n// - Example:\n\
    //   - 1 => [[1,],]\n//   - 2 => [[1,],[1,1,],[2,],]\n//   - 3 => [[1,],[1,1,],[1,1,1,],[2,],[2,1,],[3,],]\n\
    struct\n{\n    std::vector<std::vector<int>> ret;\n    std::vector<int> now;\n\
    \    int num;\n    void _partition_dfs() {\n        int rem = num - std::accumulate(now.begin(),\
    \ now.end(), 0);\n        if (!now.empty()) rem = std::min(rem, now.back());\n\
    \n        now.push_back(0);\n        for (int j = 1; j <= rem; j++) {\n      \
    \      now.back() = j;\n            ret.push_back(now);\n            _partition_dfs();\n\
    \        }\n        now.pop_back();\n    }\n\n    std::vector<std::vector<int>>\
    \ operator()(int N) {\n        ret.clear();\n        now.clear();\n        num\
    \ = N;\n        _partition_dfs();\n        return ret;\n    }\n} EnumeratePartitions;\n"
  dependsOn: []
  isVerificationFile: false
  path: number/enumerate_partitions.hpp
  requiredBy: []
  timestamp: '2020-03-07 22:32:10+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: number/enumerate_partitions.hpp
layout: document
redirect_from:
- /library/number/enumerate_partitions.hpp
- /library/number/enumerate_partitions.hpp.html
title: number/enumerate_partitions.hpp
---