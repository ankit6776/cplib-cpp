---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/lowlink.hpp
    title: graph/lowlink.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_3_A
    links:
    - http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_3_A
  bundledCode: "#line 1 \"graph/test/articulation_points.test.cpp\"\n#include <iostream>\n\
    #line 2 \"graph/lowlink.hpp\"\n#include <algorithm>\n#include <cassert>\n#include\
    \ <queue>\n#include <utility>\n#include <vector>\n\n\n// CUT begin\nstruct UndirectedGraph\n\
    {\n    using pint = std::pair<int, int>;\n    int V; // # of vertices\n    int\
    \ E; // # of edges\n    int k;\n    std::vector<std::vector<pint>> to;\n    std::vector<pint>\
    \ edges;\n    std::vector<int> root_ids; // DFS forest\u306E\u69CB\u7BC9\u3067\
    \u6839\u306B\u306A\u3063\u305F\u9802\u70B9\n\n    std::vector<int> is_bridge;\
    \ // Whether edge i is bridge or not, size = E\n    std::vector<int> is_articulation;\
    \ // whether vertex i is articulation point or not, size = V\n\n    // lowlink\n\
    \    std::vector<int> order;   // visiting order of DFS tree, size = V\n    std::vector<int>\
    \ lowlink; // size = V\n    std::vector<int> is_dfstree_edge; // size = E\n\n\
    \    int tecc_num; // \u5206\u5272\u3055\u308C\u305F\u4E8C\u91CD\u8FBA\u9023\u7D50\
    \u6210\u5206\u6570\n    std::vector<int> tecc_id; // \u5404\u9802\u70B9\u304C\u4F55\
    \u500B\u76EE\u306E\u4E8C\u91CD\u8FBA\u9023\u7D50\u6210\u5206\u304B\n\n    UndirectedGraph(int\
    \ V) : V(V), E(0), k(0), to(V),  order(V, -1), lowlink(V, -1) {}\n\n    void add_edge(int\
    \ v1, int v2)\n    {\n        assert(v1 >= 0 and v1 < V);\n        assert(v2 >=\
    \ 0 and v2 < V);\n        to[v1].emplace_back(v2, E);\n        to[v2].emplace_back(v1,\
    \ E);\n        edges.emplace_back(v1, v2);\n        is_bridge.push_back(0);\n\
    \        is_dfstree_edge.push_back(0);\n        E++;\n    }\n\n    // Build DFS\
    \ tree\n    // Complexity: O(V + E)\n    void dfs_lowlink(int now, int prv_eid\
    \ = -1)\n    {\n        if (prv_eid == -1) root_ids.push_back(now);\n        order[now]\
    \ = lowlink[now] = k++;\n        for (const auto &nxt : to[now]) if (nxt.second\
    \ != prv_eid)\n        {\n            if (order[nxt.first] >= 0)\n           \
    \ {\n                lowlink[now] = std::min(lowlink[now], order[nxt.first]);\n\
    \            }\n            else\n            {\n                is_dfstree_edge[nxt.second]\
    \ = 1;\n                dfs_lowlink(nxt.first, nxt.second);\n                lowlink[now]\
    \ = std::min(lowlink[now], lowlink[nxt.first]);\n            }\n        }\n  \
    \  }\n\n    // Find all bridges\n    // Complexity: O(V + E)\n    void detectBridge()\n\
    \    {\n        for (int i = 0; i < E; i++)\n        {\n            int v1 = edges[i].first,\
    \ v2 = edges[i].second;\n            if (order[v1] < 0) dfs_lowlink(v1);\n   \
    \         if (order[v1] > order[v2]) std::swap(v1, v2);\n            if (order[v1]\
    \ < lowlink[v2]) is_bridge[i] = 1;\n        }\n    }\n\n    // Find two-edge-connected\
    \ components and classify all vertices\n    // Complexity:  O(V + E)\n    void\
    \ two_edge_connected_components()\n    {\n        tecc_num = 0;\n        tecc_id.assign(V,\
    \ -1);\n\n        for (int i = 0; i < V; i++) if (tecc_id[i] == -1)\n        {\n\
    \            tecc_id[i] = tecc_num;\n            std::queue<int> que;\n      \
    \      que.push(i);\n            while (!que.empty())\n            {\n       \
    \         int now = que.front();\n                que.pop();\n               \
    \ for (const auto &edge : to[now])\n                {\n                    int\
    \ nxt = edge.first;\n                    if (tecc_id[nxt] >= 0 or is_bridge[edge.second])\
    \ continue;\n                    tecc_id[nxt] = tecc_num;\n                  \
    \  que.push(nxt);\n                }\n            }\n            tecc_num++;\n\
    \        }\n    }\n\n\n    void detectArticulation()\n    {\n        std::sort(root_ids.begin(),\
    \ root_ids.end());\n        is_articulation.assign(V, 0);\n        for (int v\
    \ = 0; v < V; v++)\n        {\n            if (std::binary_search(root_ids.begin(),\
    \ root_ids.end(), v))\n            {\n                int n = 0;\n           \
    \     for (auto edge : to[v]) n += is_dfstree_edge[edge.second];\n           \
    \     if (n > 1) is_articulation[v] = 1;\n            }\n            else\n  \
    \          {\n                for (auto e : to[v])\n                {\n      \
    \              if (is_dfstree_edge[e.second] and order[v] <= lowlink[e.first])\
    \ is_articulation[v] = 1;\n                }\n            }\n        }\n    }\n\
    };\n#line 3 \"graph/test/articulation_points.test.cpp\"\n#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_3_A\"\
    \n\nint main()\n{\n    int V, E;\n    std::cin >> V >> E;\n    UndirectedGraph\
    \ graph(V);\n    for (int i = 0; i < E; i++) {\n        int s, t;\n        std::cin\
    \ >> s >> t;\n        graph.add_edge(s, t);\n    }\n    graph.dfs_lowlink(0);\n\
    \    graph.detectArticulation();\n    for (int i = 0; i < V; i++) {\n        if\
    \ (graph.is_articulation[i]) {\n            printf(\"%d\\n\", i);\n        }\n\
    \    }\n}\n"
  code: "#include <iostream>\n#include \"graph/lowlink.hpp\"\n#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_3_A\"\
    \n\nint main()\n{\n    int V, E;\n    std::cin >> V >> E;\n    UndirectedGraph\
    \ graph(V);\n    for (int i = 0; i < E; i++) {\n        int s, t;\n        std::cin\
    \ >> s >> t;\n        graph.add_edge(s, t);\n    }\n    graph.dfs_lowlink(0);\n\
    \    graph.detectArticulation();\n    for (int i = 0; i < V; i++) {\n        if\
    \ (graph.is_articulation[i]) {\n            printf(\"%d\\n\", i);\n        }\n\
    \    }\n}\n"
  dependsOn:
  - graph/lowlink.hpp
  isVerificationFile: true
  path: graph/test/articulation_points.test.cpp
  requiredBy: []
  timestamp: '2020-05-06 01:35:47+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: graph/test/articulation_points.test.cpp
layout: document
redirect_from:
- /verify/graph/test/articulation_points.test.cpp
- /verify/graph/test/articulation_points.test.cpp.html
title: graph/test/articulation_points.test.cpp
---