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


# :heavy_check_mark: formal_power_series/multipoint_evaluation.hpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#f0e336561d1c18f84cd3e0ce52a956cf">formal_power_series</a>
* <a href="{{ site.github.repository_url }}/blob/master/formal_power_series/multipoint_evaluation.hpp">View this file on GitHub</a>
    - Last commit date: 2020-05-06 03:46:21+09:00




## Depends on

* :heavy_check_mark: <a href="../convolution/ntt.hpp.html">convolution/ntt.hpp</a>
* :heavy_check_mark: <a href="formal_power_series.hpp.html">formal_power_series/formal_power_series.hpp</a>
* :heavy_check_mark: <a href="../modulus/modint_fixed.hpp.html">modulus/modint_fixed.hpp</a>


## Verified with

* :heavy_check_mark: <a href="../../verify/formal_power_series/test/multipoint_evaluation_arbitrary_mod.test.cpp.html">formal_power_series/test/multipoint_evaluation_arbitrary_mod.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once
#include "formal_power_series/formal_power_series.hpp"
#include <vector>

// multipoint polynomial evaluation
// input: xs = [x_0, ..., x_{N - 1}]: points to evaluate
//        f = \sum_i^M f_i x^i
// Complexity: O(N (lgN)^2) building, O(N (lgN)^2 + M lg M) evaluation
template <typename _Tfield>
struct ArbitraryModMultipointEvaluation
{
    int nx;
    int head;
    using polynomial = FormalPowerSeries<_Tfield>;
    std::vector<polynomial> segtree;
    ArbitraryModMultipointEvaluation(const std::vector<_Tfield> &xs) : nx(xs.size())
    {
        head = 1;
        while (1 << head < nx) head++;
        segtree.resize(2 << head);
        for (int i = 0; i < 1 << head; i++)
        {
            segtree[(1 << head) + i] = {i < nx ? -xs[i] : 0, 1};
        }
        for (int i = 1 << head; --i;)
        {
            segtree[i] = segtree[2 * i] * segtree[2 * i + 1];
        }
    }
    std::vector<_Tfield> ret;
    void _dfs_eval(polynomial f, int now)
    {
        f %= segtree[now];
        if (now - (1 << head) >= 0)
        {
            if ((now - (1 << head)) < nx) ret[now - (1 << head)] = f.coeff(0);
            return;
        }
        _dfs_eval(f, 2 * now);
        _dfs_eval(f, 2 * now + 1);
    }
    std::vector<_Tfield> evaluate_polynomial(polynomial f)
    {
        ret.resize(nx);
        _dfs_eval(f, 1);
        return ret;
    }
};

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "modulus/modint_fixed.hpp"
#include <iostream>
#include <vector>
#include <set>

// CUT begin
template <int mod>
struct ModInt
{
    using lint = long long;
    static int get_mod() { return mod; }
    static int get_primitive_root() {
        static int primitive_root = 0;
        if (!primitive_root) {
            primitive_root = [&](){
                std::set<int> fac;
                int v = mod - 1;
                for (lint i = 2; i * i <= v; i++) while (v % i == 0) fac.insert(i), v /= i;
                if (v > 1) fac.insert(v);
                for (int g = 1; g < mod; g++) {
                    bool ok = true;
                    for (auto i : fac) if (ModInt(g).power((mod - 1) / i) == 1) { ok = false; break; }
                    if (ok) return g;
                }
                return -1;
            }();
        }
        return primitive_root;
    }
    int val;
    constexpr ModInt() : val(0) {}
    constexpr ModInt &_setval(lint v) { val = (v >= mod ? v - mod : v); return *this; }
    constexpr ModInt(lint v) { _setval(v % mod + mod); }
    explicit operator bool() const { return val != 0; }
    constexpr ModInt operator+(const ModInt &x) const { return ModInt()._setval((lint)val + x.val); }
    constexpr ModInt operator-(const ModInt &x) const { return ModInt()._setval((lint)val - x.val + mod); }
    constexpr ModInt operator*(const ModInt &x) const { return ModInt()._setval((lint)val * x.val % mod); }
    constexpr ModInt operator/(const ModInt &x) const { return ModInt()._setval((lint)val * x.inv() % mod); }
    constexpr ModInt operator-() const { return ModInt()._setval(mod - val); }
    constexpr ModInt &operator+=(const ModInt &x) { return *this = *this + x; }
    constexpr ModInt &operator-=(const ModInt &x) { return *this = *this - x; }
    constexpr ModInt &operator*=(const ModInt &x) { return *this = *this * x; }
    constexpr ModInt &operator/=(const ModInt &x) { return *this = *this / x; }
    friend constexpr ModInt operator+(lint a, const ModInt &x) { return ModInt()._setval(a % mod + x.val); }
    friend constexpr ModInt operator-(lint a, const ModInt &x) { return ModInt()._setval(a % mod - x.val + mod); }
    friend constexpr ModInt operator*(lint a, const ModInt &x) { return ModInt()._setval(a % mod * x.val % mod); }
    friend constexpr ModInt operator/(lint a, const ModInt &x) { return ModInt()._setval(a % mod * x.inv() % mod); }
    constexpr bool operator==(const ModInt &x) const { return val == x.val; }
    constexpr bool operator!=(const ModInt &x) const { return val != x.val; }
    bool operator<(const ModInt &x) const { return val < x.val; }  // To use std::map<ModInt, T>
    friend std::istream &operator>>(std::istream &is, ModInt &x) { lint t; is >> t; x = ModInt(t); return is; }
    friend std::ostream &operator<<(std::ostream &os, const ModInt &x) { os << x.val;  return os; }
    constexpr lint power(lint n) const {
        lint ans = 1, tmp = this->val;
        while (n) {
            if (n & 1) ans = ans * tmp % mod;
            tmp = tmp * tmp % mod;
            n /= 2;
        }
        return ans;
    }
    constexpr lint inv() const { return this->power(mod - 2); }
    constexpr ModInt operator^(lint n) const { return ModInt(this->power(n)); }
    constexpr ModInt &operator^=(lint n) { return *this = *this ^ n; }

    inline ModInt fac() const {
        static std::vector<ModInt> facs;
        int l0 = facs.size();
        if (l0 > this->val) return facs[this->val];

        facs.resize(this->val + 1);
        for (int i = l0; i <= this->val; i++) facs[i] = (i == 0 ? ModInt(1) : facs[i - 1] * ModInt(i));
        return facs[this->val];
    }

    ModInt doublefac() const {
        lint k = (this->val + 1) / 2;
        if (this->val & 1) return ModInt(k * 2).fac() / ModInt(2).power(k) / ModInt(k).fac();
        else return ModInt(k).fac() * ModInt(2).power(k);
    }

    ModInt nCr(const ModInt &r) const {
        if (this->val < r.val) return ModInt(0);
        return this->fac() / ((*this - r).fac() * r.fac());
    }

    ModInt sqrt() const {
        if (val == 0) return 0;
        if (mod == 2) return val;
        if (power((mod - 1) / 2) != 1) return 0;
        ModInt b = 1;
        while (b.power((mod - 1) / 2) == 1) b += 1;
        int e = 0, m = mod - 1;
        while (m % 2 == 0) m >>= 1, e++;
        ModInt x = power((m - 1) / 2), y = (*this) * x * x;
        x *= (*this);
        ModInt z = b.power(m);
        while (y != 1) {
            int j = 0;
            ModInt t = y;
            while (t != 1) j++, t *= t;
            z = z.power(1LL << (e - j - 1));
            x *= z, z *= z, y *= z;
            e = j;
        }
        return ModInt(std::min(x.val, mod - x.val));
    }
};

// constexpr lint MOD = 998244353;
// using mint = ModInt<MOD>;
#line 3 "convolution/ntt.hpp"

#include <algorithm>
#include <array>
#include <cassert>
#line 8 "convolution/ntt.hpp"
using namespace std;

// CUT begin
// Integer convolution for arbitrary mod
// with NTT (and Garner's algorithm) for ModInt / ModIntRuntime class.
// We skip Garner's algorithm if `skip_garner` is true or mod is in `nttprimes`.
// input: a (size: n), b (size: m)
// return: vector (size: n + m - 1)
template <typename MODINT>
vector<MODINT> nttconv(vector<MODINT> a, vector<MODINT> b, bool skip_garner = false);

constexpr int nttprimes[3] = {998244353, 167772161, 469762049};

// Integer FFT (Fast Fourier Transform) for ModInt class
// (Also known as Number Theoretic Transform, NTT)
// is_inverse: inverse transform
// ** Input size must be 2^n **
template <typename MODINT>
void ntt(vector<MODINT> &a, bool is_inverse = false)
{
    int n = a.size();
    assert(__builtin_popcount(n) == 1);
    MODINT h = MODINT(MODINT::get_primitive_root()).power((MODINT::get_mod() - 1) / n);
    if (is_inverse) h = 1 / h;

    int i = 0;
    for (int j = 1; j < n - 1; j++) {
        for (int k = n >> 1; k > (i ^= k); k >>= 1);
        if (j < i) swap(a[i], a[j]);
    }

    for (int m = 1; m < n; m *= 2) {
        int m2 = 2 * m;
        long long int base = h.power(n / m2);
        MODINT w(1);
        for(int x = 0; x < m; x++) {
            for (int s = x; s < n; s += m2) {
                MODINT u = a[s], d = a[s + m] * w;
                a[s] = u + d, a[s + m] = u - d;
            }
            w *= base;
        }
    }
    if (is_inverse) {
        long long int n_inv = MODINT(n).inv();
        for (auto &v : a) v *= n_inv;
    }
}
template<int MOD>
vector<ModInt<MOD>> nttconv_(const vector<int> &a, const vector<int> &b) {
    int sz = a.size();
    assert(a.size() == b.size() and __builtin_popcount(sz) == 1);
    vector<ModInt<MOD>> ap(sz), bp(sz);
    for (int i = 0; i < sz; i++) ap[i] = a[i], bp[i] = b[i];
    if (a == b) {
        ntt(ap, false);
        bp = ap;
    }
    else {
        ntt(ap, false);
        ntt(bp, false);
    }
    for (int i = 0; i < sz; i++) ap[i] *= bp[i];
    ntt(ap, true);
    return ap;
}
long long int extgcd_ntt_(long long int a, long long int b, long long int &x, long long int &y)
{
    long long int d = a;
    if (b != 0) d = extgcd_ntt_(b, a % b, y, x), y -= (a / b) * x;
    else x = 1, y = 0;
    return d;
}
long long int modinv_ntt_(long long int a, long long int m)
{
    long long int x, y;
    extgcd_ntt_(a, m, x, y);
    return (m + x % m) % m;
}
long long int garner_ntt_(int r0, int r1, int r2, int mod)
{
    array<long long int, 4> rs = {r0, r1, r2, 0};
    vector<long long int> coffs(4, 1), constants(4, 0);
    for (int i = 0; i < 3; i++) {
        long long int v = (rs[i] - constants[i]) * modinv_ntt_(coffs[i], nttprimes[i]) % nttprimes[i];
        if (v < 0) v += nttprimes[i];
        for (int j = i + 1; j < 4; j++) {
            (constants[j] += coffs[j] * v) %= (j < 3 ? nttprimes[j] : mod);
            (coffs[j] *= nttprimes[i]) %= (j < 3 ? nttprimes[j] : mod);
        }
    }
    return constants.back();
}
template <typename MODINT>
vector<MODINT> nttconv(vector<MODINT> a, vector<MODINT> b, bool skip_garner)
{
    int sz = 1, n = a.size(), m = b.size();
    while (sz < n + m) sz <<= 1;
    int mod = MODINT::get_mod();
    if (skip_garner or find(begin(nttprimes), end(nttprimes), mod) != end(nttprimes)) {
        a.resize(sz), b.resize(sz);
        if (a == b) { ntt(a, false); b = a; }
        else ntt(a, false), ntt(b, false);
        for (int i = 0; i < sz; i++) a[i] *= b[i];
        ntt(a, true);
        a.resize(n + m - 1);
    }
    else {
        vector<int> ai(sz), bi(sz);
        for (int i = 0; i < n; i++) ai[i] = a[i].val;
        for (int i = 0; i < m; i++) bi[i] = b[i].val;
        auto ntt0 = nttconv_<nttprimes[0]>(ai, bi);
        auto ntt1 = nttconv_<nttprimes[1]>(ai, bi);
        auto ntt2 = nttconv_<nttprimes[2]>(ai, bi);
        a.resize(n + m - 1);
        for (int i = 0; i < n + m - 1; i++) {
            a[i] = garner_ntt_(ntt0[i].val, ntt1[i].val, ntt2[i].val, mod);
        }
    }
    return a;
}
#line 6 "formal_power_series/formal_power_series.hpp"
using namespace std;

// CUT begin
// Formal Power Series (形式的冪級数) based on ModInt<mod> / ModIntRuntime
// Reference: <https://ei1333.github.io/luzhiled/snippets/math/formal-power-series.html>
template<typename T>
struct FormalPowerSeries : vector<T>
{
    using vector<T>::vector;
    using P = FormalPowerSeries;

    void shrink() { while (this->size() and this->back() == T(0)) this->pop_back(); }

    P operator+(const P &r) const { return P(*this) += r; }
    P operator+(const T &v) const { return P(*this) += v; }
    P operator-(const P &r) const { return P(*this) -= r; }
    P operator-(const T &v) const { return P(*this) -= v; }
    P operator*(const P &r) const { return P(*this) *= r; }
    P operator*(const T &v) const { return P(*this) *= v; }
    P operator/(const P &r) const { return P(*this) /= r; }
    P operator/(const T &v) const { return P(*this) /= v; }
    P operator%(const P &r) const { return P(*this) %= r; }

    P &operator+=(const P &r) {
        if (r.size() > this->size()) this->resize(r.size());
        for (int i = 0; i < (int)r.size(); i++) (*this)[i] += r[i];
        shrink();
        return *this;
    }
    P &operator+=(const T &v) {
        if (this->empty()) this->resize(1);
        (*this)[0] += v;
        shrink();
        return *this;
    }
    P &operator-=(const P &r) {
        if (r.size() > this->size()) this->resize(r.size());
        for (int i = 0; i < (int)r.size(); i++) (*this)[i] -= r[i];
        shrink();
        return *this;
    }
    P &operator-=(const T &v) {
        if (this->empty()) this->resize(1);
        (*this)[0] -= v;
        shrink();
        return *this;
    }
    P &operator*=(const T &v) {
        for (auto &x : (*this)) x *= v;
        shrink();
        return *this;
    }
    P &operator*=(const P &r) {
        if (this->empty() || r.empty()) this->clear();
        else {
            auto ret = nttconv(*this, r);
            *this = P(ret.begin(), ret.end());
        }
        return *this;
    }
    P &operator%=(const P &r) {
        *this -= *this / r * r;
        shrink();
        return *this;
    }
    P operator-() const {
        P ret = *this;
        for (auto &v : ret) v = -v;
        return ret;
    }
    P &operator/=(const T &v) {
        assert(v != T(0));
        for (auto &x : (*this)) x /= v;
        return *this;
    }
    P &operator/=(const P &r) {
        if (this->size() < r.size()) {
            this->clear();
            return *this;
        }
        int n = (int)this->size() - r.size() + 1;
        return *this = (reversed().pre(n) * r.reversed().inv(n)).pre(n).reversed(n);
    }
    P pre(int sz) const {
         P ret(this->begin(), this->begin() + min((int)this->size(), sz));
         ret.shrink();
         return ret;
    }
    P operator>>(int sz) const {
        if ((int)this->size() <= sz) return {};
        return P(this->begin() + sz, this->end());
    }
    P operator<<(int sz) const {
        if (this->empty()) return {};
        P ret(*this);
        ret.insert(ret.begin(), sz, T(0));
        return ret;
    }

    P reversed(int deg = -1) const {
        assert(deg >= -1);
        P ret(*this);
        if (deg != -1) ret.resize(deg, T(0));
        reverse(ret.begin(), ret.end());
        ret.shrink();
        return ret;
    }

    P differential() const { // formal derivative (differential) of f.p.s.
        const int n = (int)this->size();
        P ret(max(0, n - 1));
        for (int i = 1; i < n; i++) ret[i - 1] = (*this)[i] * T(i);
        return ret;
    }

    P integral() const {
        const int n = (int)this->size();
        P ret(n + 1);
        ret[0] = T(0);
        for (int i = 0; i < n; i++) ret[i + 1] = (*this)[i] / T(i + 1);
        return ret;
    }

    P inv(int deg) const {
        assert(deg >= -1);
        assert(this->size() and ((*this)[0]) != T(0)); // Requirement: F(0) != 0
        const int n = this->size();
        if (deg == -1) deg = n;
        P ret({T(1) / (*this)[0]});
        for (int i = 1; i < deg; i <<= 1) {
            ret = (ret + ret - ret * ret * pre(i << 1)).pre(i << 1);
        }
        ret = ret.pre(deg);
        ret.shrink();
        return ret;
    }

    P log(int deg = -1) const {
        assert(deg >= -1);
        assert(this->size() and ((*this)[0]) == T(1)); // Requirement: F(0) = 1
        const int n = (int)this->size();
        if (deg == 0) return {};
        if (deg == -1) deg = n;
        return (this->differential() * this->inv(deg)).pre(deg - 1).integral();
    }

    P sqrt(int deg = -1) const {
        assert(deg >= -1);
        const int n = (int)this->size();
        if (deg == -1) deg = n;
        if (this->empty()) return {};
        if ((*this)[0] == T(0)) {
            for (int i = 1; i < n; i++) if ((*this)[i] != T(0)) {
                if ((i & 1) or deg - i / 2 <= 0) return {};
                return (*this >> i).sqrt(deg - i / 2) << (i / 2);
            }
            return {};
        }
        T sqrtf0 = (*this)[0].sqrt();
        if (sqrtf0 == T(0)) return {};

        P y = (*this) / (*this)[0], ret({T(1)});
        T inv2 = T(1) / T(2);
        for (int i = 1; i < deg; i <<= 1) {
            ret = (ret + y.pre(i << 1) * ret.inv(i << 1)) * inv2;
        }
        return ret.pre(deg) * sqrtf0;
    }

    P exp(int deg = -1) const {
        assert(deg >= -1);
        assert(this->empty() or ((*this)[0]) == T(0)); // Requirement: F(0) = 0
        const int n = (int)this->size();
        if (deg == -1) deg = n;
        P ret({T(1)});
        for (int i = 1; i < deg; i <<= 1) {
            ret = (ret * (pre(i << 1) + T(1) - ret.log(i << 1))).pre(i << 1);
        }
        return ret.pre(deg);
    }

    P pow(long long int k, int deg = -1) const {
        assert(deg >= -1);
        const int n = (int)this->size();
        if (deg == -1) deg = n;
        for (int i = 0; i < n; i++) {
            if ((*this)[i] != T(0)) {
                T rev = T(1) / (*this)[i];
                P C(*this * rev);
                P D(n - i);
                for (int j = i; j < n; j++) D[j - i] = C[j];
                D = (D.log(deg) * T(k)).exp(deg) * (*this)[i].power(k);
                P E(deg);
                if (k * (i > 0) > deg or k * i > deg) return {};
                long long int S = i * k;
                for (int j = 0; j + S < deg and j < (int)D.size(); j++) E[j + S] = D[j];
                E.shrink();
                return E;
            }
        }
        return *this;
    }

    T coeff(int i) const {
        if ((int)this->size() <= i) return T(0);
        return (*this)[i];
    }

    T eval(T x) const {
        T ret = 0, w = 1;
        for (auto &v : *this) ret += w * v, w *= x;
        return ret;
    }
};
#line 4 "formal_power_series/multipoint_evaluation.hpp"

// multipoint polynomial evaluation
// input: xs = [x_0, ..., x_{N - 1}]: points to evaluate
//        f = \sum_i^M f_i x^i
// Complexity: O(N (lgN)^2) building, O(N (lgN)^2 + M lg M) evaluation
template <typename _Tfield>
struct ArbitraryModMultipointEvaluation
{
    int nx;
    int head;
    using polynomial = FormalPowerSeries<_Tfield>;
    std::vector<polynomial> segtree;
    ArbitraryModMultipointEvaluation(const std::vector<_Tfield> &xs) : nx(xs.size())
    {
        head = 1;
        while (1 << head < nx) head++;
        segtree.resize(2 << head);
        for (int i = 0; i < 1 << head; i++)
        {
            segtree[(1 << head) + i] = {i < nx ? -xs[i] : 0, 1};
        }
        for (int i = 1 << head; --i;)
        {
            segtree[i] = segtree[2 * i] * segtree[2 * i + 1];
        }
    }
    std::vector<_Tfield> ret;
    void _dfs_eval(polynomial f, int now)
    {
        f %= segtree[now];
        if (now - (1 << head) >= 0)
        {
            if ((now - (1 << head)) < nx) ret[now - (1 << head)] = f.coeff(0);
            return;
        }
        _dfs_eval(f, 2 * now);
        _dfs_eval(f, 2 * now + 1);
    }
    std::vector<_Tfield> evaluate_polynomial(polynomial f)
    {
        ret.resize(nx);
        _dfs_eval(f, 1);
        return ret;
    }
};

```
{% endraw %}

<a href="../../index.html">Back to top page</a>
