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

pii t1[2 * R]; // max, pos
int prv[MAX];

void upd1(int p, int x) {
    for (t1[p += R].F = x; p >>= 1; t1[p] = max(t1[2 * p], t1[2 * p + 1])) {}
}
pii get1(int l, int r = R - 1) {
    pii res = {-1, -1};
    for (l += R, r += R; l < r; l >>= 1, r >>= 1) {
        if (l & 1) res = max(res, t1[l++]);
        if (!(r & 1)) res = max(res, t1[r--]);
    }
    if (l == r) res = max(res, t1[l]);
    return res;
}

int t2[2 * R];

void upd2(int p, int x) {
    for (t2[p += R] += x; p >>= 1; t2[p] = t2[2 * p] + t2[2 * p + 1]) {}
}
int get2(int k, int v = 1, int nl = 0, int nr = R) {
    if (nl + 1 == nr) return nl;
    int nm = (nl + nr) / 2;
    if (k < nm - nl - t2[2 * v]) return get2(k, 2 * v, nl, nm);
    return get2(k - (nm - nl - t2[2 * v]), 2 * v + 1, nm, nr);
}
int sum2(int l, int r) {
    int res = 0;
    for (l += R, r += R; l < r; l >>= 1, r >>= 1) {
        if (l & 1) res += t2[l++];
        if (!(r & 1)) res += t2[r--];
    }
    if (l == r) res += t2[l];
    return res;
}

int a[MAX], pos[MAX];

signed main() {
    FOR(i, 0, R) t1[R + i].S = i;
    fastIO;
    int n, k; cin >> n >> k;
    FOR(i, 0, n) cin >> a[i], pos[--a[i]] = i;

    if (a[0] < k) {
        vector <pii> ans;
        int p = 0;
        FOR(i, 1, n) if (a[i] < k) ans.pb({p, i}), p = i;
        ans.pb({p, n});
        sort(all(ans), [&](auto p1, auto p2){ return a[p1.F] > a[p2.F]; });
        EACH(e, ans) FOR(i, e.F, e.S) cout << a[i] + 1 << ' ';
        return 0;
    }

    upd1(a[0], 1), prv[a[0]] = -1;
    FOR(i, 1, n) if (a[i] < a[0]) {
        pii x = get1(a[i]);
        upd1(a[i], x.F + 1), prv[a[i]] = x.S;
    }

    k = n - k;
    RFOR(i, n - 1, a[0] + 1) upd2(pos[i], 1);
    int best = -1, bestat;
    RFOR(i, a[0], 0) {
        int used = pos[i] + 1 - t1[R + i].F + sum2(pos[i] + 1, R - 1);
        if (used <= k) {
            int cur = min(n, get2((pos[i] + 1 - sum2(0, pos[i])) + (k - used)));
            if (cur >= best) best = cur, bestat = i;
        }
        upd2(pos[i], 1);
    }

    vi link(n);
    FOR(i, 0, n) {
        if (i < best) link[i] = 1;
        else if (a[i] > bestat) link[i] = 1;
    }
    int u = bestat;
    while (u != -1) {
        link[pos[u]] = 0;
        u = prv[u];
    }

    vector <pii> ans;
    int p = 0;
    FOR(i, 1, n) if (!link[i]) ans.pb({p, i}), p = i;
    ans.pb({p, n});
    sort(all(ans), [&](auto p1, auto p2){ return a[p1.F] > a[p2.F]; });
    EACH(e, ans) FOR(i, e.F, e.S) cout << a[i] + 1 << ' ';
}

