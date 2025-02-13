#include <bits/stdc++.h>
using namespace std;
#define int long long
const int mod = 998244353;

int binpow(int a, int b, int m) {
    int res = 1;
    while (b) {
        if (b % 2) res = res * a % m;
        a = a * a % m;
        b /= 2;
    }
    return res;
}

int binom(int N, int R, vector<int>& ft, vector<int>& inft) {
    if (R < 0 || R > N) return 0;
    return ft[N] * (inft[R] * inft[N - R] % mod) % mod;
}

int T(int k, vector<int>& ft, vector<int>& inft) {
    if (k == 0) return 1;
    int J = (9 * k) / 10, res = 0;
    for (int j = 0; j <= J; j++) {
        int s = (j % 2 == 0 ? 1 : mod - 1);
        s = s * binom(2 * k, j, ft, inft) % mod;
        s = s * binom(11 * k - 10 * j - 1, 2 * k - 1, ft, inft) % mod;
        res = (res + s) % mod;
    }
    return res;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    int m = n / 2;
    int k1 = (m % 2 == 0) ? (m / 2) : (m + 1) / 2;
    int k2 = m / 2;
    int K = max(k1, k2);
    int N = 11 * K;
    vector<int> ft(N + 1, 1), inft(N + 1, 1);
    for (int i = 1; i <= N; i++) ft[i] = ft[i - 1] * i % mod;
    inft[N] = binpow(ft[N], mod - 2, mod);
    for (int i = N; i > 0; i--) inft[i - 1] = inft[i] * i % mod;
    int ans = (m % 2 == 0) ? (T(m / 2, ft, inft) * T(m / 2, ft, inft)) % mod 
                           : (T((m + 1) / 2, ft, inft) * T(m / 2, ft, inft)) % mod;
    cout << ans << '\n';
    return 0;
}
