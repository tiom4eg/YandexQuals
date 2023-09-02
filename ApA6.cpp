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

int n, m, L, fin;
int worm[MAX];

vi g[MAX];
int es[MAX];

int tt, used_b[MAX], tin[MAX], fup[MAX], is_bridge[MAX];

void bridge_dfs(int v, int p = -1) {
    used_b[v] = 1, tin[v] = fup[v] = tt++;
    EACH(id, g[v]) {
        int u = es[id] - v;
        if (u == p) continue;
        if (used_b[u]) fup[v] = min(fup[v], tin[u]);
		else {
			bridge_dfs(u, v);
			fup[v] = min(fup[v], fup[u]);
			if (fup[u] > tin[v]) is_bridge[id] = 1;
		}
    }
}

void find_bridges() { FOR(i, 0, n) if (!used_b[i]) bridge_dfs(i); }

int cc = 1, used_c[MAX], cyc_num[MAX];
vi cyc[MAX];

void cycle_dfs(int v) {
    used_c[v] = 1, cyc[cyc_num[v]].pb(v);
    EACH(id, g[v]) if (!is_bridge[id]) {
        int u = es[id] - v;
        if (!used_c[u]) {
            cyc_num[u] = cyc_num[v];
            return cycle_dfs(u);
        }
    }
}

void find_cycles() {
    FOR(i, 0, n) if (!used_c[i]) {
        EACH(id, g[i]) if (!is_bridge[id]) {
            cyc_num[i] = cc++;
            cycle_dfs(i);
            break;
        }
    }
}

int ban[MAX];

vi bfs(int s) {
    vi dist(n, INF);
    deque <int> q;
    q.pb(s), dist[s] = 0;
    if (ban[s]) return dist; // fucking test 8
    while (!q.empty()) {
        int v = q.front();
        q.pop_front();
        EACH(id, g[v]) {
            int u = es[id] - v;
            if (ban[u]) continue;
            if (dist[u] == INF) dist[u] = dist[v] + 1, q.pb(u);
        }
    }
    return dist;
}

int used_ch[MAX];
void check_comp(int v) {
    used_ch[v] = 1;
    EACH(id, g[v]) {
        int u = es[id] - v;
        if (!used_ch[u]) check_comp(u);
    }
}

signed main() {
    fastIO;
    cin >> n >> m;
    FOR(i, 0, m) {
        int u, v; cin >> u >> v, --u, --v;
        es[i] = u + v;
        g[u].pb(i), g[v].pb(i);
    }
    find_bridges();
    find_cycles();
    cin >> L;
    FOR(i, 0, L + 1) cin >> worm[i], --worm[i];
    cin >> fin, --fin;
    check_comp(worm[0]);
    if (!used_ch[fin]) return !(cout << -1);

    if (!cyc_num[worm[0]] || !cyc_num[worm[1]] || cyc_num[worm[0]] != cyc_num[worm[1]]) { // head aren't on the cycle or head can go in both directions
        ban[worm[1]] = 1;
        vi ds = bfs(worm[0]);
        ban[worm[1]] = 0;
        vi df = bfs(fin);
        if (ds[fin] != INF) return !(cout << ds[fin]);
        int mind = INF;
        FOR(i, 0, n) if (cyc_num[i] && sz(cyc[cyc_num[i]]) >= L) mind = min(mind, ds[i] + df[i] + sz(cyc[cyc_num[i]]));
        return !(cout << (mind == INF ? -1 : mind));
    }

    int mind = INF;
    FOR(i, 1, L + 1) ban[worm[i]] = 1;
    vi ds = bfs(worm[0]);
    mind = min(mind, ds[fin]);
    FOR(i, 2, L + 1) ban[worm[i]] = 0;
    vi df = bfs(fin);
    ban[worm[1]] = 0;
    vi dfu = bfs(fin);
    if (sz(cyc[cyc_num[worm[0]]]) >= L) { // we can go through current cycle
        if (df[worm[0]] == INF) mind = min(mind, dfu[worm[1]] + sz(cyc[cyc_num[worm[0]]]) - 1); // fin is blocked by worm[1]
        else mind = min(mind, df[worm[0]]);
    }
    // we can go somewhere reachable and try to reverse here
    FOR(i, 0, n) if (cyc_num[i] && cyc_num[i] != cyc_num[worm[0]] && sz(cyc[cyc_num[i]]) >= L) mind = min(mind, ds[i] + sz(cyc[cyc_num[i]]) + dfu[i]);
    cout << (mind == INF ? -1 : mind);
}
