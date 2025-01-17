/*
    author  : Mamurjon Mirzapo'latov
    contest : -
    site    : RoboContest
*/

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
 
ll f(ll x, ll c, ll mod) {
    return (__int128)x*x % mod + c % mod;
}
 
ll modm(ll a, ll b, ll mod) {
    ll r = 0;
    a %= mod;
    while(b) {
        if(b & 1) r = (r + a) % mod;
        a = (a + a) % mod;
        b >>= 1;
    }
    return r;
}
 
ll binpow(ll a, ll e, ll mod) {
    ll r = 1;
    a %= mod;
    while(e){
        if(e & 1) r = modm(r, a, mod);
        a = modm(a, a, mod);
        e >>= 1;
    }
    return r;
}
 
bool isprime(ll n) {
    if(n < 2) return false;
    static int tp[12] = {2,3,5,7,11,13,17,19,23,29,31,37};
    for (int i = 0; i < 12; i++){
        if(n == tp[i]) return true;
        if(n % tp[i] == 0) return false;
    }
    ll d = n - 1, s = 0;
    while((d & 1) == 0){ d >>= 1; s++; }
    for (int i = 0; i < 12; i++){
        ll a = tp[i] % n;
        if(a == 0) continue;
        ll x = binpow(a, d, n);
        if(x == 1 || x == n-1) continue;
        bool cont = false;
        for (ll j = 0; j < s-1; j++){
            x = modm(x, x, n);
            if(x == n-1){ cont = true; break; }
        }
        if(!cont) return false;
    }
    return true;
}
 
ll pollardRho(ll n) {
    if(n % 2 == 0) return 2;
    ll x = rand() % (n-2) + 2, y = x, c = rand() % (n-1) + 1, d = 1;
    while(d == 1) {
        x = (modm(x, x, n) + c) % n;
        y = (modm(y, y, n) + c) % n;
        y = (modm(y, y, n) + c) % n;
        ll diff = x > y ? x - y : y - x;
        d = __gcd(diff, n);
        if(d == n) return pollardRho(n);
    }
    return d;
}
 
void fac(ll n, vector<ll>& v) {
    if(n == 1)return;
    if(isprime(n)){
        v.push_back(n);
        return;
    }
    ll d = pollardRho(n);
    fac(d, v);
    fac(n/d, v);
}
 
void dfs(int i, ll x, vector<pair<ll,int>> &pf, vector<ll> &ds) {
    if(i == pf.size()){
        ds.push_back(x);
        return;
    }
    for (int j = 0; j <= pf[i].second; j++){
        dfs(i+1, x, pf, ds);
        x *= pf[i].first;
    }
}
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ll m;
    cin >> m;
    long double D = sqrt((long double)1 + 8*m);
    ll Lmx = floor((-1 + D)/2);
    vector<ll> v;
    fac(m, v);
    sort(v.begin(), v.end());
    vector<pair<ll,int>> pf;
    for(auto a: v){
        if(pf.empty() || pf.back().first != a)
            pf.push_back({a,1});
        else
            pf.back().second++;
    }
    vector<ll> ds;
    dfs(0, 1, pf, ds);
    ll mx = 1;
    for(auto d: ds){
        if(d <= Lmx && d % 2 == 1) mx = max(mx, d);
    }
    for(auto k: ds){
        ll L = 2 * k;
        if(L <= Lmx && (m/k) % 2 == 1) mx = max(mx, L);
    }
    ll a = (m - (mx*(mx-1))/2) / mx;
    cout << a << " " << mx << "\n";
    return 0;
}
