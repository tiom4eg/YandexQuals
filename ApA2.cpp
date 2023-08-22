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
constexpr int INF = 1e9 + 7, MD = 998244353, LG = 16, R = 1 << LG, MOD = 1040015701, MOD2 = 1e9 + 9, RB = 158;
const ll INFLL = 1e18 + 7;

const unsigned MAX = 40002, MAX2 = 80004;

int w[MAX2];
int uncalc[MAX2];
vi g[MAX2];
unordered_map <unsigned, unsigned> dp;

unsigned hh(int a, int b) { return a * MAX2 + b; }

unsigned dfs(int v, int c) {
    unsigned h = hh(v, c);
    if (dp.find(h) != dp.end()) return w[v] + dp[h];
    int p = lower_bound(all(g[v]), c) - g[v].begin();
    if (uncalc[v] > p) {
        RFOR(i, uncalc[v] - 1, p) {
            dp[hh(v, g[v][i])] = dfs(g[v][i], v + 1);
            if (i < sz(g[v]) - 1) dp[hh(v, g[v][i])] = max(dp[hh(v, g[v][i])], dp[hh(v, g[v][i + 1])]);
        }
        uncalc[v] = p;
    }
    return w[v] + (p == sz(g[v]) ? 0 : dp[hh(v, g[v][p])]);
}

signed main() {
    fastIO;
    int n, m, p; cin >> n >> m >> p;
    FOR(i, 0, n) cin >> w[i];
    FOR(i, 0, m) cin >> w[MAX + i];
    FOR(i, 0, p) {
        int u, v; cin >> u >> v, --u, --v;
        g[u].pb(MAX + v), g[MAX + v].pb(u);
    }
    FOR(i, 0, 2 * MAX) sort(all(g[i])), uncalc[i] = sz(g[i]);
    unsigned ans = 0;
    FOR(i, 0, n) ans = max(ans, dfs(i, 0));
    FOR(i, 0, m) ans = max(ans, dfs(MAX + i, 0));
    cout << ans;
}
