/*
    author  : Mamurjon Mirzapo'latov
    contest : -
    site    : RoboContest
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int M = 1e9+7;

vector<ll> f(const vector<ll>& a, const vector<ll>& b, int m) {
    vector<ll> r(m, 0);
    for (int i = 0; i < m; i++) {
        if (a[i] == 0) continue;
        for (int j = 0; j < m; j++) {
            if (b[j] == 0) continue;
            r[(i + j) % m] = (r[(i + j) % m] + a[i] * b[j]) % M;
        }
    }
    return r;
}

vector<ll> g(vector<ll> a, ll p, int m) {
    vector<ll> r(m, 0);
    r[0] = 1;
    while (p > 0) {
        if (p & 1) {
            r = f(r, a, m);
        }
        a = f(a, a, m);
        p >>= 1;
    }
    return r;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n;
    int m;
    cin >> n >> m;

    ll c = n / m;
    vector<ll> d(m, 0);
    d[0] = c;
    ll r = n % m;
    for (int i = 1; i < m; i++) {
        d[i] = (i <= r) ? n / m + 1 : n / m;
    }

    vector<ll> v(m, 0);
    v[0] = 1;
    for (int i = 1; i < m; i++) {
        if (d[i] == 0) continue;
        vector<ll> b(m, 0);
        b[0] = 1;
        b[i] = 1;
        vector<ll> t = g(b, d[i], m);
        v = f(v, t, m);
    }

    ll x = 1, y = 2, z = c;
    while (z > 0) {
        if (z & 1) {
            x = x * y % M;
        }
        y = y * y % M;
        z >>= 1;
    }

    for (int i = 0; i < m; i++) {
        v[i] = v[i] * x % M;
    }

    cout << v[0] << "\n";

    return 0;
}
