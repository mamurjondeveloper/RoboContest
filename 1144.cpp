#include <bits/stdc++.h>
using namespace std;
#define int long long

int h, w, N, c;
vector<int> p, s, L, R;
vector<vector<int>> g;

int fnd(int x) {
    while (p[x] != x) {
        p[x] = p[p[x]];
        x = p[x];
    }
    return x;
}

void uni(int x, int y) {
    int rx = fnd(x), ry = fnd(y);
    if (rx == ry) return;
    if (s[rx] < s[ry]) swap(rx, ry);
    p[ry] = rx;
    s[rx] += s[ry];
    c--;
}

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    cin >> h >> w;
    g.resize(h, vector<int>(w));
    for (int i = 0; i < h; i++)
        for (int j = 0; j < w; j++)
            cin >> g[i][j];

    L.assign(w + 1, 0);
    N = h * w;
    p.resize(N);
    s.assign(N, 1);
    iota(p.begin(), p.end(), 0);
    c = 0;

    for (int j = 1; j <= w; j++) {
        for (int i = 0; i < h; i++) {
            int x = (j - 1) * h + i;
            p[x] = x;
            s[x] = 1;
            c++;
            if (i > 0 && g[i][j - 1] == g[i - 1][j - 1]) uni(x, x - 1);
            if (j > 1 && g[i][j - 1] == g[i][j - 2]) uni(x, (j - 2) * h + i);
        }
        L[j] = c;
    }

    R.assign(w + 1, 0);
    p.resize(N);
    s.assign(N, 1);
    iota(p.begin(), p.end(), 0);
    c = 0;

    for (int j = w; j >= 1; j--) {
        for (int i = 0; i < h; i++) {
            int x = (w - j) * h + i;
            p[x] = x;
            s[x] = 1;
            c++;
            if (i > 0 && g[i][j - 1] == g[i - 1][j - 1]) uni(x, x - 1);
            if (j < w && g[i][j - 1] == g[i][j]) uni(x, (w - (j + 1)) * h + i);
        }
        R[j] = c;
    }

    int a = 1e9;
    for (int k = 1; k < w; k++)
        a = min(a, L[k] + R[k + 1]);

    cout << a << '\n';
    return 0;
}
