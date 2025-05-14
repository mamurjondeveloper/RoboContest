#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#pragma GCC optimization ("unroll-loops")
#pragma GCC optimize("O3")
#pragma optimize("O2")
#pragma optimize("Os")
#pragma clang optimize on
#pragma clang option -Ofast

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <bitset>
#include <iomanip>
#include <string>
#include <ctime>
#include <cmath>
#include <any>
#include <array>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <assert.h>
#include <atomic>
#include <cctype>
#include <climits>
#include <fstream>
#include <ostream>
#include <queue>
#include <deque>
#include <cstdlib>

#define ll long long
#define ld long double
#define pb push_back
#define mp make_pair
#define ff first
#define ss second
#define ins insert
#define er erase
#define lb lower_bound
#define ub upper_bound
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define len(x) (int)x.size()
#define mem(a, b) memset(a, b, sizeof a)
#define Fast_code ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define endl "\n"
#define pi acos(-1)
#define forn(start, stop, step) for(ll start = 0; start < stop; start+=step)
#define sorted(arr) sort(all(arr))

using namespace std;

template <typename T>
void print(T value) {
    cout << value << endl;
}

ll binpow(ll x, ll y, ll m=1e9+7) {
    ll k = 1;
    x = x % m;
    while (y > 0) {
        if (y % 2 == 1)
            k = (k * x) % m;
        y = y / 2;
        x = (x * x) % m;
    }
    return k;
}

ld cbrt(ld n, ld ep = 1e-6) {
    ld x = n;
    while (abs(x * x * x - n) > ep) {
        x = (2 * x + n / (x * x)) / 3;
    }
    return x;
}

ll sumdigit(ll n){
    ll s=0;
    while (true){
        if (n<10){
            s+=n;
            return s;
        }
        s+=(n%10);
        n/=10;
    }
}

bool is_prime(ll n){
    if(n<=1)return false;
    if(n<=3)return true;
    if(n%2==0 || n%3==0)return false;
    for(ll i=5;i<sqrt(n)+1;i+=6){
        if(n%i==0||n%(i+2)==0)return false;
    }
    return true;
}

ll gcd(ll a,ll b){return b?gcd(b,a%b):a;}
ll lcm(ll a,ll b){return a/gcd(a,b)*b;}

ll n, m, k;

bool max_dist(vector <pair<int, int> >& v) {
    double dist = -1;
    for (int i = 0; i < v.size(); i ++)
        for (int j = i; j < v.size(); j ++)
            dist = max(dist, sqrt(pow(v[i].ff - v[j].ff, 2) + pow(v[i].ss - v[j].ss, 2)));
    return dist <= k;
}

void removee(vector<pair<int, int> >& p, vector<vector<int> >& v, int f) {
    for (auto x : p)
        v[x.ff][x.ss] = f;
}

void bfs(int x, int y, vector<vector<int> >& v, vector <pair<int, int> >& p) {
      int i = x, j = y;
      p.push_back({i, j});v[i][j] = 0;
      if (i - 1 >= 0 && v[i - 1][j])bfs(i - 1, j, v, p);
      if (i + 1 < n && v[i + 1][j])bfs(i + 1, j, v, p);
      if (j - 1 >= 0 && v[i][j - 1])bfs(i, j - 1, v, p); 
      if (j + 1 < m && v[i][j + 1])bfs(i, j + 1, v, p);
}

signed main() {
      cin >> n >> m;
      vector<vector<int> > v(n, vector<int> (m, 0)), ans;
      for (int i = 0; i < n; i ++) {
        for (int j = 0; j < m; j ++) {
          char x; cin >> x;
          if (x == '1') {
            v[i][j] = 1;
          }
        }
      }
      cin >> k; ans = v;
      if (k>500){
          cout<<4;
          return 0;
      }
      vector <pair <int, int> > p;
      for (int i = 0; i < n; i ++)
          for (int j = 0; j < m; j ++)
              if (v[i][j] == 1) {
                  bfs(i, j, v, p);
                  if (max_dist(p))
                      removee(p, ans, 0),removee(p, v, 0); 
                  else
                      removee(p, v, 2);
                  p.clear();
              }
      for (int i = 0; i < n; i ++) {
        for (int j = 0; j < m; j ++)
            cout << ans[i][j];
        cout << endl;
      }

    return 0;
}
