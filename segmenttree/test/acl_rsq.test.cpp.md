---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: segmenttree/acl_segtree.hpp
    title: segmenttree/acl_segtree.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_B
    links:
    - http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_B
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.9.2/x64/lib/python3.9/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.9.2/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 193, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.9.2/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.9.2/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 355, in update\n    raise BundleErrorAt(path, i + 1, \"found codes out\
    \ of include guard\")\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt:\
    \ segmenttree/acl_segtree.hpp: line 37: found codes out of include guard\n"
  code: "#include \"../acl_segtree.hpp\"\n#include <iostream>\n#define PROBLEM \"\
    http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_B\"\nusing namespace\
    \ std;\n\nusing S = int;\nS op(S l, S r) { return l + r; }\nS e() { return 0;\
    \ }\n\nint main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n\n  \
    \  int N, Q;\n    cin >> N >> Q;\n\n    atcoder::segtree<S, op, e> segtree(N);\n\
    \    while (Q--) {\n        int q, x, y;\n        cin >> q >> x >> y;\n      \
    \  x--;\n        if (q) {\n            cout << segtree.prod(x, y) << '\\n';\n\
    \        } else {\n            segtree.set(x, segtree.get(x) + y);\n        }\n\
    \    }\n}\n"
  dependsOn:
  - segmenttree/acl_segtree.hpp
  isVerificationFile: true
  path: segmenttree/test/acl_rsq.test.cpp
  requiredBy: []
  timestamp: '2021-02-13 02:36:53+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: segmenttree/test/acl_rsq.test.cpp
layout: document
redirect_from:
- /verify/segmenttree/test/acl_rsq.test.cpp
- /verify/segmenttree/test/acl_rsq.test.cpp.html
title: segmenttree/test/acl_rsq.test.cpp
---