---
layout: default
---

<!-- mathjax config similar to math.stackexchange -->
<script type="text/javascript" async
  src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.5/MathJax.js?config=TeX-MML-AM_CHTML">
</script>
<script type="text/x-mathjax-config">
  MathJax.Hub.Config({
    TeX: { equationNumbers: { autoNumber: "AMS" }},
    tex2jax: {
      inlineMath: [ ['$','$'] ],
      processEscapes: true
    },
    "HTML-CSS": { matchFontHeight: false },
    displayAlign: "left",
    displayIndent: "2em"
  });
</script>

<script type="text/javascript" src="https://cdnjs.cloudflare.com/ajax/libs/jquery/3.4.1/jquery.min.js"></script>
<script src="https://cdn.jsdelivr.net/npm/jquery-balloon-js@1.1.2/jquery.balloon.min.js" integrity="sha256-ZEYs9VrgAeNuPvs15E39OsyOJaIkXEEt10fzxJ20+2I=" crossorigin="anonymous"></script>
<script type="text/javascript" src="../../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../../assets/css/copy-button.css" />


# :heavy_check_mark: segmenttree/range-update-range-get.hpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#4d78bd1b354012e24586b247dc164462">segmenttree</a>
* <a href="{{ site.github.repository_url }}/blob/master/segmenttree/range-update-range-get.hpp">View this file on GitHub</a>
    - Last commit date: 2020-04-18 03:35:35+09:00




## Verified with

* :heavy_check_mark: <a href="../../verify/segmenttree/test/range-affine-range-sum.test.cpp.html">segmenttree/test/range-affine-range-sum.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once
#include <algorithm>
#include <iostream>
#include <vector>

// CUT begin
template<typename TDATA, typename TLAZY, typename TRET, typename TQUERY>
struct LazySegmentTree
{
    TLAZY zero_lazy;
    TRET zero_ret;
    int N;
    int head;
    std::vector<TDATA> data;
    std::vector<TLAZY> lazy;

    // Here, you have to calculate data[pos] from children (data[l], data[r]),
    // Assumptions: `lazy[pos] = lazy[l] = lazy[r] = zero_lazy`
    virtual void merge_data(int pos) = 0;

    // Here, you must propagate lazy[pos] and update data[pos] by reflecting lazy[pos], without inconsistency
    // After this, lazy[pos] must be zero_lazy.
    virtual void reflect_lazy(int pos) = 0;

    // operate d to lazy[pos] (merge two TLAZY's)
    virtual void overlap_lazy(int pos, const TLAZY &d) = 0;

    // Assumption: `lazy[pos] = zero_lazy`
    virtual TRET data2ret(int pos, const TQUERY &query) = 0;

    virtual TRET merge_ret(const TRET &l, const TRET &r, const TQUERY &query) = 0;

    ////// general description //////
    LazySegmentTree() = default;
    void initialize(const std::vector<TDATA> &data_init, const TDATA &zero_data, const TLAZY &zero_lazy_, const TRET &zero_ret_)
    {
        N = data_init.size();
        head = 1;
        while (head < N) head <<= 1;
        zero_lazy = zero_lazy_;
        zero_ret = zero_ret_;
        data.assign(head * 2, zero_data);
        lazy.assign(head * 2, zero_lazy);
        std::copy(data_init.begin(), data_init.end(), data.begin() + head);
        for (int pos = head; --pos;) merge_data(pos);
    }

    void _update(int begin, int end, const TLAZY &delay, int pos, int l, int r)
    {
        // Operate `delay` to the node pos
        // After this, lazy[pos] MUST be zero so that merge_data() works correctly
        if (begin <= l and r <= end) { // Update whole [l, r) by delay
            overlap_lazy(pos, delay);
            reflect_lazy(pos);
        }
        else if (begin < r and l < end) { // Update somewhere in [l, r)
            reflect_lazy(pos);
            _update(begin, end, delay, pos * 2, l, (l + r) / 2);
            _update(begin, end, delay, pos * 2 + 1, (l + r) / 2, r);
            merge_data(pos);
        }
        else reflect_lazy(pos);
    }

    void update(int begin, int end, const TLAZY &delay) {
        _update(begin, end, delay, 1, 0, head);
    }

    TRET _get(int begin, int end, int pos, int l, int r, const TQUERY &query) // Get value in [begin, end)
    {
        reflect_lazy(pos);
        if (begin <= l and r <= end) return data2ret(pos, query);
        else if (begin < r and l < end) {
            TRET vl = _get(begin, end, pos * 2, l, (l + r) / 2, query);
            TRET vr = _get(begin, end, pos * 2 + 1, (l + r) / 2, r, query);
            return merge_ret(vl, vr, query);
        }
        else return zero_ret;
    }
    TRET get(int begin, int end, const TQUERY &query = NULL)
    {
        return _get(begin, end, 1, 0, head, query);
    }
};

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "segmenttree/range-update-range-get.hpp"
#include <algorithm>
#include <iostream>
#include <vector>

// CUT begin
template<typename TDATA, typename TLAZY, typename TRET, typename TQUERY>
struct LazySegmentTree
{
    TLAZY zero_lazy;
    TRET zero_ret;
    int N;
    int head;
    std::vector<TDATA> data;
    std::vector<TLAZY> lazy;

    // Here, you have to calculate data[pos] from children (data[l], data[r]),
    // Assumptions: `lazy[pos] = lazy[l] = lazy[r] = zero_lazy`
    virtual void merge_data(int pos) = 0;

    // Here, you must propagate lazy[pos] and update data[pos] by reflecting lazy[pos], without inconsistency
    // After this, lazy[pos] must be zero_lazy.
    virtual void reflect_lazy(int pos) = 0;

    // operate d to lazy[pos] (merge two TLAZY's)
    virtual void overlap_lazy(int pos, const TLAZY &d) = 0;

    // Assumption: `lazy[pos] = zero_lazy`
    virtual TRET data2ret(int pos, const TQUERY &query) = 0;

    virtual TRET merge_ret(const TRET &l, const TRET &r, const TQUERY &query) = 0;

    ////// general description //////
    LazySegmentTree() = default;
    void initialize(const std::vector<TDATA> &data_init, const TDATA &zero_data, const TLAZY &zero_lazy_, const TRET &zero_ret_)
    {
        N = data_init.size();
        head = 1;
        while (head < N) head <<= 1;
        zero_lazy = zero_lazy_;
        zero_ret = zero_ret_;
        data.assign(head * 2, zero_data);
        lazy.assign(head * 2, zero_lazy);
        std::copy(data_init.begin(), data_init.end(), data.begin() + head);
        for (int pos = head; --pos;) merge_data(pos);
    }

    void _update(int begin, int end, const TLAZY &delay, int pos, int l, int r)
    {
        // Operate `delay` to the node pos
        // After this, lazy[pos] MUST be zero so that merge_data() works correctly
        if (begin <= l and r <= end) { // Update whole [l, r) by delay
            overlap_lazy(pos, delay);
            reflect_lazy(pos);
        }
        else if (begin < r and l < end) { // Update somewhere in [l, r)
            reflect_lazy(pos);
            _update(begin, end, delay, pos * 2, l, (l + r) / 2);
            _update(begin, end, delay, pos * 2 + 1, (l + r) / 2, r);
            merge_data(pos);
        }
        else reflect_lazy(pos);
    }

    void update(int begin, int end, const TLAZY &delay) {
        _update(begin, end, delay, 1, 0, head);
    }

    TRET _get(int begin, int end, int pos, int l, int r, const TQUERY &query) // Get value in [begin, end)
    {
        reflect_lazy(pos);
        if (begin <= l and r <= end) return data2ret(pos, query);
        else if (begin < r and l < end) {
            TRET vl = _get(begin, end, pos * 2, l, (l + r) / 2, query);
            TRET vr = _get(begin, end, pos * 2 + 1, (l + r) / 2, r, query);
            return merge_ret(vl, vr, query);
        }
        else return zero_ret;
    }
    TRET get(int begin, int end, const TQUERY &query = NULL)
    {
        return _get(begin, end, 1, 0, head, query);
    }
};

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

