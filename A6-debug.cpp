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
constexpr int INF = 1e9 + 7, MD = 998244353, MAX = 1000005, LG = 31, R = 1 << LG, MOD = 1e9 + 7, MOD2 = 1e9 + 9, RB = 158;
const ll INFLL = 1e18 + 7;

#undef endl

int won;
int ax, ay; // aux
int kx, ky; // king pos

void auto_interact();

struct fig {
    int x, y;
    fig() {}
    fig(int x, int y) : x(x), y(y) {}
    int color() { return (x + y) & 1; } // OK
    int diag(int d) { return d ? (x - y) : (x + y); } // OK
    bool same(fig o, int d) { return diag(d) == o.diag(d); } // OK
    bool operator<(fig o) { return (diag(0) == o.diag(0)) ? (diag(1) < o.diag(1)) : (diag(0) < o.diag(0)); } // OK
    void shift(int d, int k) { // moves by k on d-diag, OK
        if (won) return;
        if (!k) return;
        cout << "algo: " << x << ' ' << y << ", diags: " << diag(0) << ' ' << diag(1) << " | ";
        x += k, y += (d ? 1 : -1) * k;
        cout << x << ' ' << y << ", diags: " << diag(0) << ' ' << diag(1) << endl;
        auto_interact();
        //cin >> ax >> ay >> kx >> ky;
        if (!ax && !ay && !kx && !ky) won = 1;
    }
    void move_to(int d, int k) { shift(!d, (k - diag(d)) / 2); } // moves figure to d-diag with value k, OK
    void jump_to(int k) { // jump to 0-diag with value k saving the same x coord, OK
        int x = diag(0);
        if (x < k) shift(0, (x - k) / 2), shift(1, (k - x) / 2);
        if (x > k) shift(1, (k - x) / 2), shift(0, (x - k) / 2);
    }
};

vector <fig> a[2];

void auto_interact() {
    FOR(dx, -1, 2) FOR(dy, -1, 2) if (dx != 0 || dy != 0) {
        int f = 1;
        kx += dx, ky += dy;
        EACH(e, a[0]) if (kx + ky == e.diag(0) || kx - ky == e.diag(1)) f = 0;
        EACH(e, a[1]) if (kx + ky == e.diag(0) || kx - ky == e.diag(1)) f = 0;
        kx -= dx, ky -= dy;
        if (f) {
            ax = kx, ay = ky;
            cout << "interactor: " << kx << ' ' << ky << ' ';
            kx += dx, ky += dy;
            cout << kx << ' ' << ky << endl;
            return;
        }
    }
    ax = ay = kx = ky = 0;
    cout << "interactor: 0 0 0 0" << endl;
}


void solve() {
    won = 0;
    a[0].clear(), a[1].clear();
    FOR(i, 0, 5) {
        int x, y; cin >> x >> y;
        fig f(x, y);
        a[f.color()].pb(f);
    }
    cin >> kx >> ky;
    if (sz(a[0]) < 2 || sz(a[1]) < 2) return void(cout << "algo: 0 0 0 0" << endl);
    /// phase 1 (2 moves max)
    int f = (sz(a[0]) > sz(a[1]));
    if (f) swap(a[0], a[1]); // we need to ensure that 2 figures of same color are secured first
    sort(all(a[0]));
    if (!a[0][0].same(a[0][1], 0) && !a[0][0].same(a[0][1], 1)) a[0][1].move_to(0, a[0][0].diag(0));
    if (won) return;
    FOR(i, 0, 3) if (kx == a[1][i].x && ky == a[1][i].y) a[1].erase(a[1].begin() + i); // if king eaten smth
    sort(all(a[1]));
    if (!a[1][0].same(a[1][1], 0) && !a[1][0].same(a[1][1], 1)) a[1][1].move_to(0, a[1][0].diag(0));
    if (won) return;
    cout << "PHASE 1 END" << endl;
    if (f) swap(a[0], a[1]);
    sort(all(a[0])), sort(all(a[1]));
    /// phase 2 (7 moves max)
    a[0][0].move_to((a[0][0].diag(0) == a[0][1].diag(0)), -100000000);
    if (won) return;
    a[0][1].move_to((a[0][0].diag(0) == a[0][1].diag(0)), -10000000);
    if (won) return;
    a[0][1].move_to((a[0][0].diag(0) != a[0][1].diag(0)), a[0][1].diag(a[0][0].diag(0) != a[0][1].diag(0)) - 1000000);
    if (won) return;
    a[1][0].move_to((a[1][0].diag(0) == a[1][1].diag(0)), -100000001);
    if (won) return;
    a[1][1].move_to((a[1][0].diag(0) == a[1][1].diag(0)), -10000001);
    if (won) return;
    a[1][1].move_to((a[1][0].diag(0) != a[1][1].diag(0)), a[1][1].diag(a[1][0].diag(0) != a[1][1].diag(0)) - 1000000);
    if (won) return;
    // third is useless and may fuck us up
    if (sz(a[0]) > 2) {
        a[0][2].move_to(0, 200000000);
        if (won) return;
    }
    if (sz(a[1]) > 2) {
        a[1][2].move_to(0, 200000001);
        if (won) return;
    }
    cout << "PHASE 2 END" << endl;
    /// phase 3 (block by 0-diag, 28 moves max)
    int d0 = kx + ky;
    int l = d0 - 8;
    a[!(d0 & 1)][0].jump_to(d0 - 7);
    if (won) return;
    a[d0 & 1][0].jump_to(d0 - 8);
    if (won) return;
    d0 = kx + ky;
    int r = d0 + 8;
    a[!(d0 & 1)][1].jump_to(d0 + 7);
    if (won) return;
    a[d0 & 1][1].jump_to(d0 + 8);
    if (won) return;
    while (l + 4 < r) {
        if (kx + ky > l + 2) a[l & 1][0].shift(1, 1), ++l;
        else a[r & 1][1].shift(1, -1), --r;
        if (won) return;
    }
    cout << "PHASE 3 END" << endl;
    /// phase 4 (block by 1-diag, 3 moves max)
    int col = (kx + ky) & 1;
    a[col][0].move_to(1, (kx - ky) - 2); // block bottom
    if (won) return;
    a[col][1].move_to(1, (kx - ky) + 2); // block top
    if (won) return;
    a[col][1].move_to(1, (kx - ky) + 2); // stalemate
    if (!won) {
        cout << "IM DEAD LMAO" << endl;
    }
}

signed main() {
    //fastIO;
    int tc; cin >> tc;
    while (tc--) solve();
}
