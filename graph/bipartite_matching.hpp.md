---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: graph/test/bipartite_matching.test.cpp
    title: graph/test/bipartite_matching.test.cpp
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links:
    - https://ei1333.github.io/luzhiled/snippets/graph/hopcroft-karp.html>
  bundledCode: "#line 2 \"graph/bipartite_matching.hpp\"\n#include <cassert>\n#include\
    \ <iostream>\n#include <vector>\n#include <queue>\n\n// CUT begin\n// Bipartite\
    \ matching of undirected bipartite graph (Hopcroft-Karp)\n// <https://ei1333.github.io/luzhiled/snippets/graph/hopcroft-karp.html>\n\
    // Comprexity: O(EsqrtV)\n// int solve(): enumerate maximum number of matching\
    \ / return -1 (if graph is not bipartite)\nstruct BipartiteMatching\n{\n    int\
    \ V;\n    std::vector<std::vector<int>> to; // Adjacency list\n    std::vector<int>\
    \ dist;            // dist[i] = (Distance from i'th node)\n    std::vector<int>\
    \ match;           // match[i] = (Partner of i'th node) or -1 (No parter)\n  \
    \  std::vector<int> used, vv;        //\n    std::vector<int> color;         \
    \  // color of each node(checking bipartition): 0/1/-1(not determined)\n\n   \
    \ BipartiteMatching() = default;\n    BipartiteMatching(int V_) : V(V_), to(V_),\
    \ match(V_, -1), used(V_), color(V_, -1) {}\n\n    void add_edge(int u, int v)\n\
    \    {\n        assert(u >= 0 and u < V and v >= 0 and v < V and u != v);\n  \
    \      to[u].push_back(v);\n        to[v].push_back(u);\n    }\n\n    void bfs()\n\
    \    {\n        dist.assign(V, -1);\n        std::queue<int> q;\n        for (int\
    \ i = 0; i < V; i++) {\n            if (!color[i] and !used[i]) {\n          \
    \      q.emplace(i), dist[i] = 0;\n            }\n        }\n\n        while (!q.empty())\
    \ {\n            int now = q.front();\n            q.pop();\n            for (auto\
    \ nxt : to[now]) {\n                int c = match[nxt];\n                if (c\
    \ >= 0 and dist[c] == -1) {\n                    q.emplace(c), dist[c] = dist[now]\
    \ + 1;\n                }\n            }\n        }\n    }\n\n    bool dfs(int\
    \ now)\n    {\n        vv[now] = true;\n        for (auto nxt : to[now]) {\n \
    \           int c = match[nxt];\n            if (c < 0 or (!vv[c] and dist[c]\
    \ == dist[now] + 1 and dfs(c))) {\n                match[nxt] = now, match[now]\
    \ = nxt;\n                used[now] = true;\n                return true;\n  \
    \          }\n        }\n        return false;\n    }\n\n    bool _color_bfs(int\
    \ root)\n    {\n        color[root] = 0;\n        std::queue<int> q;\n       \
    \ q.emplace(root);\n        while (!q.empty()) {\n            int now = q.front(),\
    \ c = color[now];\n            q.pop();\n            for (auto nxt : to[now])\n\
    \            if (color[nxt] == -1) color[nxt] = !c, q.emplace(nxt);\n        \
    \    else if (color[nxt] == c) return false;\n        }\n        return true;\n\
    \    }\n\n    int solve()\n    {\n        for (int i = 0; i < V; i++) if (color[i]\
    \ == -1) {\n            if (!_color_bfs(i)) return -1;\n        }\n        int\
    \ ret = 0;\n        while (true) {\n            bfs();\n            vv.assign(V,\
    \ false);\n            int flow = 0;\n            for (int i = 0; i < V; i++)\
    \ if (!color[i] and !used[i] and dfs(i)) flow++;\n            if (!flow) break;\n\
    \            ret += flow;\n        }\n        return ret;\n    }\n\n    friend\
    \ std::ostream &operator<<(std::ostream &os, const BipartiteMatching &bm)\n  \
    \  {\n        os << \"{N=\" << bm.V  << ':';\n        for (int i = 0; i < bm.V;\
    \ i++) if (bm.match[i] > i)\n        {\n            os << '(' << i << '-' << bm.match[i]\
    \ << \"),\";\n        }\n        os << '}';\n        return os;\n    }\n};\n"
  code: "#pragma once\n#include <cassert>\n#include <iostream>\n#include <vector>\n\
    #include <queue>\n\n// CUT begin\n// Bipartite matching of undirected bipartite\
    \ graph (Hopcroft-Karp)\n// <https://ei1333.github.io/luzhiled/snippets/graph/hopcroft-karp.html>\n\
    // Comprexity: O(EsqrtV)\n// int solve(): enumerate maximum number of matching\
    \ / return -1 (if graph is not bipartite)\nstruct BipartiteMatching\n{\n    int\
    \ V;\n    std::vector<std::vector<int>> to; // Adjacency list\n    std::vector<int>\
    \ dist;            // dist[i] = (Distance from i'th node)\n    std::vector<int>\
    \ match;           // match[i] = (Partner of i'th node) or -1 (No parter)\n  \
    \  std::vector<int> used, vv;        //\n    std::vector<int> color;         \
    \  // color of each node(checking bipartition): 0/1/-1(not determined)\n\n   \
    \ BipartiteMatching() = default;\n    BipartiteMatching(int V_) : V(V_), to(V_),\
    \ match(V_, -1), used(V_), color(V_, -1) {}\n\n    void add_edge(int u, int v)\n\
    \    {\n        assert(u >= 0 and u < V and v >= 0 and v < V and u != v);\n  \
    \      to[u].push_back(v);\n        to[v].push_back(u);\n    }\n\n    void bfs()\n\
    \    {\n        dist.assign(V, -1);\n        std::queue<int> q;\n        for (int\
    \ i = 0; i < V; i++) {\n            if (!color[i] and !used[i]) {\n          \
    \      q.emplace(i), dist[i] = 0;\n            }\n        }\n\n        while (!q.empty())\
    \ {\n            int now = q.front();\n            q.pop();\n            for (auto\
    \ nxt : to[now]) {\n                int c = match[nxt];\n                if (c\
    \ >= 0 and dist[c] == -1) {\n                    q.emplace(c), dist[c] = dist[now]\
    \ + 1;\n                }\n            }\n        }\n    }\n\n    bool dfs(int\
    \ now)\n    {\n        vv[now] = true;\n        for (auto nxt : to[now]) {\n \
    \           int c = match[nxt];\n            if (c < 0 or (!vv[c] and dist[c]\
    \ == dist[now] + 1 and dfs(c))) {\n                match[nxt] = now, match[now]\
    \ = nxt;\n                used[now] = true;\n                return true;\n  \
    \          }\n        }\n        return false;\n    }\n\n    bool _color_bfs(int\
    \ root)\n    {\n        color[root] = 0;\n        std::queue<int> q;\n       \
    \ q.emplace(root);\n        while (!q.empty()) {\n            int now = q.front(),\
    \ c = color[now];\n            q.pop();\n            for (auto nxt : to[now])\n\
    \            if (color[nxt] == -1) color[nxt] = !c, q.emplace(nxt);\n        \
    \    else if (color[nxt] == c) return false;\n        }\n        return true;\n\
    \    }\n\n    int solve()\n    {\n        for (int i = 0; i < V; i++) if (color[i]\
    \ == -1) {\n            if (!_color_bfs(i)) return -1;\n        }\n        int\
    \ ret = 0;\n        while (true) {\n            bfs();\n            vv.assign(V,\
    \ false);\n            int flow = 0;\n            for (int i = 0; i < V; i++)\
    \ if (!color[i] and !used[i] and dfs(i)) flow++;\n            if (!flow) break;\n\
    \            ret += flow;\n        }\n        return ret;\n    }\n\n    friend\
    \ std::ostream &operator<<(std::ostream &os, const BipartiteMatching &bm)\n  \
    \  {\n        os << \"{N=\" << bm.V  << ':';\n        for (int i = 0; i < bm.V;\
    \ i++) if (bm.match[i] > i)\n        {\n            os << '(' << i << '-' << bm.match[i]\
    \ << \"),\";\n        }\n        os << '}';\n        return os;\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: graph/bipartite_matching.hpp
  requiredBy: []
  timestamp: '2020-04-18 19:20:50+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - graph/test/bipartite_matching.test.cpp
documentation_of: graph/bipartite_matching.hpp
layout: document
redirect_from:
- /library/graph/bipartite_matching.hpp
- /library/graph/bipartite_matching.hpp.html
title: graph/bipartite_matching.hpp
---