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
#define int long long
mt19937 rng(chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count());
constexpr int INF = 1e9 + 7, MD = 998244353, MAX = 600005, LG = 17, R = 1 << LG, MOD = 1e9 + 7, MOD2 = 1e9 + 9, RB = 158;
const ll INFLL = 7e18 + 7;

int n, m, s;

int not_inf[MAX], deg[MAX], cnt[MAX];
int status[MAX]; // 0 - not touched, 1 - touched but unsure, 2 - sure
ll dist[MAX];
vector <pii> g[MAX], ng[MAX];

signed main() {
    fastIO;
    cin >> n >> m >> s, --s;
    FOR(i, 0, m) {
        int u, v, w; cin >> u >> v >> w, --u, --v;
        ++deg[2 * u], g[2 * v + 1].pb({2 * u, w});
        ++deg[2 * u + 1], g[2 * v].pb({2 * u + 1, w});
    }

    deque <int> q;
    FOR(i, 0, 2 * n) if (!deg[i]) not_inf[i] = 1, q.pb(i);
    while (!q.empty()) {
        int v = q.front();
        q.pop_front();
        if (v & 1) {
            EACH(e, g[v]) if (!not_inf[e.F]) not_inf[e.F] = 1, q.pb(e.F);
        } else {
            EACH(e, g[v]) if (++cnt[e.F] == deg[e.F]) not_inf[e.F] = 1, q.pb(e.F);
        }
    }
    if (!not_inf[2 * s]) return !(cout << "Kaef!");

    FOR(i, 0, 2 * n) if (not_inf[i]) {
        EACH(e, g[i]) if (not_inf[e.F]) ng[i].pb(e);
    }
    set <pii> pq;

    auto relax2 = [&](int v) {
        EACH(e, ng[v]) {
            if (!status[e.F]) {
                dist[e.F] = dist[v] + e.S, status[e.F] = 1;
                pq.insert({dist[e.F], e.F});
            }
            else if (status[e.F] == 1 && dist[e.F] > dist[v] + e.S) {
                pq.erase({dist[e.F], e.F});
                dist[e.F] = dist[v] + e.S;
                pq.insert({dist[e.F], e.F});
            }
        }
    };
    auto relax = [&](int v) {
        status[v] = 2;
        EACH(e, ng[v]) {
            dist[e.F] = max(dist[e.F], dist[v] + e.S);
            if (++cnt[e.F] == deg[e.F]) relax2(e.F);
        }
    };

    FOR(i, 0, n) if (not_inf[2 * i]) {
        dist[2 * i] = INFLL;
        if (!deg[2 * i]) {
            dist[2 * i] = 0, status[2 * i] = 1;
            pq.insert({dist[2 * i], 2 * i});
        }
    }
    FOR(i, 0, n) if (not_inf[2 * i + 1]) {
        cnt[2 * i + 1] = 0, dist[2 * i + 1] = -1;
        if (!deg[2 * i + 1]) {
            dist[2 * i + 1] = 0;
            relax2(2 * i + 1);
        }
    }

    while (!pq.empty()) {
        int v = pq.begin()->S;
        pq.erase(pq.begin());
        relax(v);
    }

    cout << dist[2 * s];
}
