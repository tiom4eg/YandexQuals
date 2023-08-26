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
constexpr int INF = 1e9 + 7, MD = 998244353, MAX = 200005, LG = 18, R = 1 << LG, MOD = 1e9 + 7, MOD2 = 1e9 + 9, RB = 158;
const ll INFLL = 1e18 + 7;

int a[MAX], used[MAX];

signed main() {
    fastIO;
    int n, k; cin >> n >> k;
    pbds unused;
    FOR(i, 0, n) cin >> a[i], unused.insert(--a[i]);
    if (a[0] < k) {
        vector <pii> ans;
        int p = 0;
        FOR(i, 1, n) if (a[i] < k) ans.pb({p, i}), p = i;
        ans.pb({p, n});
        sort(all(ans), [&](auto p1, auto p2){ return a[p1.F] > a[p2.F]; });
        EACH(e, ans) FOR(i, e.F, e.S) cout << a[i] + 1 << ' ';
        return 0;
    }
    k = n - k;
    FOR(i, a[0], n) used[i] = 1, unused.erase(i);
    k -= n - 1 - a[0];
    int p;
    for (p = 1; p < n; ++p) {
        if (used[p]) continue;
        int v = unused.order_of_key(a[p]);
        if (v == sz(unused) - 1) continue;
        if (!k) break;
        --k;
        if (v == sz(unused) - 2) {
            int w = *prev(unused.end());
            used[w] = 1, unused.erase(w);
        }
        else used[a[p]] = 1, unused.erase(a[p]);
    }
    vector <pii> ans;
    int z = p;
    FOR(i, p + 1, n) if (!used[a[i]]) ans.pb({z, i}), z = i;
    ans.pb({z, n});
    sort(all(ans), [&](auto p1, auto p2){ return a[p1.F] > a[p2.F]; });
    FOR(i, 0, p) cout << a[i] + 1 << ' ';
    EACH(e, ans) FOR(i, e.F, e.S) cout << a[i] + 1 << ' ';
}
