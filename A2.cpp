#include <bits/stdc++.h>
// tiom4eg's precompiler options
// POGGERS POGGERS POGGERS POGGERS POGGERS POGGERS POGGERS
// IO settings
#define fastIO ios_base::sync_with_stdio(false); cin.tie(0)
// Quick types
#define ll long long
#define ld long double
#define ull unsigned long long
#define pii pair <int, int>
#define vi vector <int>
#define mi vector <vector <int>>
// Quick functions
#define endl '\n'
#define F first
#define S second
#define all(a) a.begin(), a.end()
#define sz(a) (int)(a.size())
#define pb push_back
#define mp make_pair
// Quick fors
#define FOR(i, a, b) for (int i = a; i < b; ++i)
#define FORS(i, a, b, c) for (int i = a; i < b; i += c)
#define RFOR(i, a, b) for (int i = a; i >= b; --i)
#define EACH(e, a) for (auto& e : a)
// Pragmas
#ifndef TIOM4EG
#pragma GCC optimize("O3") // let the chaos begin!
#pragma GCC target("avx,avx2,tune=native")
#pragma GCC comment(linker, "/stack:200000000")
#endif
// PBDS
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define pbds tree <int, null_type, less <int>, rb_tree_tag, tree_order_statistics_node_update>
using namespace __gnu_pbds;
// POGGERS POGGERS POGGERS POGGERS POGGERS POGGERS POGGERS
using namespace std;
mt19937 rng(chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count());
//#define int long long
constexpr int INF = 1e9 + 7, MD = 998244353, MAX = 200005, LG = 17, R = 1 << LG, MOD = 1e9 + 7, MOD2 = 1e9 + 9, RB = 158;
const ll INFLL = 1e18 + 7;

int dv, dd;
int deg2[MAX];
vi g[MAX];

inline int add(int a, int b) { return a + b - MOD * (a + b >= MOD); }
inline int sub(int a, int b) { return a - b + MOD * (a < b); }
inline int mul(int a, int b) { return a * 1LL * b % MOD; }

void ddfs(int v, int p = -1, int d = 0) {
    if (d > dd) dv = v, dd = d;
    EACH(u, g[v]) if (u != p) ddfs(u, v, d + 1);
}

vi dist1[MAX], dist2[MAX];
int used1[MAX], used2[MAX], cnt;

void calc1(int v, int p = -1, int d = 0) {
    dist1[d].pb(v);
    EACH(u, g[v]) if (u != p) calc1(u, v, d + 1);
}
void calc2(int v, int p = -1, int d = 0) {
    dist2[d].pb(v);
    EACH(u, g[v]) if (u != p) calc2(u, v, d + 1);
}

signed main() {
    deg2[0] = 1;
    FOR(i, 1, MAX) deg2[i] = add(deg2[i - 1], deg2[i - 1]);
    fastIO;
    int n; cin >> n;
    FOR(i, 1, n) {
        int u, v; cin >> u >> v, --u, --v;
        g[u].pb(v), g[v].pb(u);
    }
    ddfs(0);
    int v1 = dv;
    dd = -1;
    ddfs(v1);
    int v2 = dv, diam = dd;
    calc1(v1), calc2(v2);
    int ans = 0, rem = deg2[n - 1];
    RFOR(i, diam, 0) {
        int f = 0, pr = (i == diam ? 1 : cnt);
        EACH(v, dist1[i]) {
            if (used2[v]) f = 1, --cnt;
            used1[v] = 1, ++cnt;
        }
        EACH(v, dist2[i]) {
            if (used1[v]) f = 1, --cnt;
            used2[v] = 1, ++cnt;
        }
        if (f) {
            ans = add(ans, mul(rem, i));
            break;
        }
        int cur = sub(deg2[n - pr], deg2[n - cnt]);
        rem = sub(rem, cur), ans = add(ans, mul(cur, i));
    }
    cout << add(ans, ans);
}
