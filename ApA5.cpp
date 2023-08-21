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
//#include <ext/pb_ds/assoc_container.hpp>
//#include <ext/pb_ds/tree_policy.hpp>
//#define pbds tree <int, null_type, less <int>, rb_tree_tag, tree_order_statistics_node_update>
//using namespace __gnu_pbds;
// POGGERS POGGERS POGGERS POGGERS POGGERS POGGERS POGGERS
using namespace std;
mt19937 rng(chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count());
#define int long long
constexpr int INF = 1e9 + 7, MD = 998244353, MAX = 500007, LG = 18, R = 1 << LG, MOD = 1040015701, MOD2 = 1e9 + 9, RB = 158;
const ll INFLL = 1e18 + 7;

int s[2 * R], mn[2 * R], d[2 * R];

void tag(int v, int x, int l) { s[v] = x * l, mn[v] = x, d[v] = x; }
void push(int v, int l) {
    if (!d[v]) return;
    if (l > 1) tag(2 * v, d[v], l / 2), tag(2 * v + 1, d[v], l / 2);
    d[v] = 0;
}

int first_leq(int x, int v = 1, int nl = 0, int nr = R) {
    push(v, nr - nl);
    if (nl + 1 == nr) return nl;
    int nm = (nl + nr) / 2;
    if (mn[2 * v] <= x) return first_leq(x, 2 * v, nl, nm);
    return first_leq(x, 2 * v + 1, nm, nr);
}

void upd(int ql, int qr, int x, int v = 1, int nl = 0, int nr = R) {
    push(v, nr - nl);
    if (ql == nl && qr == nr) return tag(v, x, nr - nl);
    int nm = (nl + nr) / 2;
    if (qr <= nm) upd(ql, qr, x, 2 * v, nl, nm);
    else if (ql >= nm) upd(ql, qr, x, 2 * v + 1, nm, nr);
    else upd(ql, nm, x, 2 * v, nl, nm), upd(nm, qr, x, 2 * v + 1, nm, nr);
    s[v] = s[2 * v] + s[2 * v + 1], mn[v] = mn[2 * v + 1];
}

int get_sum(int ql, int qr, int v = 1, int nl = 0, int nr = R) {
    push(v, nr - nl);
    if (ql == nl && qr == nr) return s[v];
    int nm = (nl + nr) / 2;
    if (qr <= nm) return get_sum(ql, qr, 2 * v, nl, nm);
    if (ql >= nm) return get_sum(ql, qr, 2 * v + 1, nm, nr);
    return get_sum(ql, nm, 2 * v, nl, nm) + get_sum(nm, qr, 2 * v + 1, nm, nr);
}

pii sum_lowerbound(int x, int v = 1, int nl = 0, int nr = R) {
    push(v, nr - nl);
    if (nl + 1 == nr) return {nl, x};
    int nm = (nl + nr) / 2;
    if (s[2 * v] <= x) return sum_lowerbound(x - s[2 * v], 2 * v + 1, nm, nr);
    return sum_lowerbound(x, 2 * v, nl, nm);
}


signed main() {
    fastIO;
    int n, q; cin >> n >> q;
    FOR(i, 0, n) cin >> s[R + i], mn[R + i] = s[R + i];
    RFOR(i, R - 1, 1) s[i] = s[2 * i] + s[2 * i + 1], mn[i] = mn[2 * i + 1];
    while (q--) {
        int t, k, x; cin >> t >> k >> x;
        if (t == 1) {
            int p = first_leq(x);
            if (p < k) upd(p, k, x);
        }
        else {
            int p = --k, s = 0, res = 0;
            while (p < n) { // <= log C iterations
                if (p) s = get_sum(0, p);
                pii q = sum_lowerbound(s + x);
                if (q.F >= n) {
                    res += n - p;
                    break;
                }
                res += q.F - p, x = q.S;
                p = first_leq(x);
            }
            cout << res << endl;
        }
    }
}
