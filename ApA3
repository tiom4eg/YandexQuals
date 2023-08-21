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
#define int long long
constexpr int INF = 1e9 + 7, MD = 998244353, MAX = 500007, LG = 19, R = 1 << LG, MOD = 1040015701, MOD2 = 1e9 + 9, RB = 158;
const ll INFLL = 1e18 + 7;

signed main() {
    fastIO;
    int n; cin >> n;
    vi a(n); EACH(e, a) cin >> e;
    stack <pii> mn, mx; // {value, sum on seg}
    int prval = 0, curval = 0, gmn = INF, gmx = -INF, allmn = 0, allmx = 0;
    FOR(i, 0, n) {
        int mns = prval, mxs = prval;
        while (!mn.empty() && mn.top().F > a[i]) {
            allmn = (allmn + MD - (mn.top().F * mn.top().S) % MD) % MD;
            mns = (mns + mn.top().S) % MD;
            curval = (curval + mn.top().S * (mn.top().F - a[i])) % MD;
            mn.pop();
        }
        allmn = (allmn + a[i] * mns) % MD;
        mn.push({a[i], mns});
        while (!mx.empty() && mx.top().F < a[i]) {
            allmx = (allmx + MD - (mx.top().F * mx.top().S) % MD) % MD;
            mxs = (mxs + mx.top().S) % MD;
            curval = (curval + mx.top().S * (a[i] - mx.top().F)) % MD;
            mx.pop();
        }
        allmx = (allmx + a[i] * mxs) % MD;
        mx.push({a[i], mxs});
        gmn = min(gmn, a[i]), gmx = max(gmx, a[i]);
        curval = (curval + gmx - gmn) % MD;
        prval = curval, curval = (allmx - allmn + MD) % MD;
    }
    cout << prval;
}
