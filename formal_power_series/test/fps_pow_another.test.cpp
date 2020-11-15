#define PROBLEM "https://judge.yosupo.jp/problem/pow_of_formal_power_series"
#include <iostream>
#include "modint.hpp"
#include "formal_power_series/formal_power_series.hpp"
using namespace std;

int main()
{
    cin.tie(nullptr), ios::sync_with_stdio(false);

    int N, M;
    cin >> N >> M;
    FormalPowerSeries<ModInt<998244353>> A(N);
    for (auto &a : A) cin >> a;
    int i = 0;
    int bias = 0;
    while (i < N and !A[i]) i++;
    if (i < N)
    {
        auto a0 = A[i];
        A /= a0;
        A = A >> i;
        A = (A.log(N + 10) * M).exp();
        bias += 1LL * i * M;
        A *= a0.power(M);
    }
    for (int i = 0; i < N; i++) cout << A.coeff(i - bias) << ' ';
}