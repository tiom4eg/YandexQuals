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

int won, ops;
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
    bool operator==(fig o) { return (x == o.x) && (y == o.y); }
};

vector <fig> a[2];

void shift(fig& f, int d, int k) { // moves by k on d-diag, OK
    if (won) return;
    if (!k) return;
    EACH(e, a[0]) if (!(f == e) && f.diag(d) == e.diag(d) && e.x >= min(f.x, f.x + k) && e.x <= max(f.x, f.x + k)) {
        cout << "move collision" << endl;
        EACH(e, a[0]) cout << e.x << ' ' << e.y << endl;
        EACH(e, a[1]) cout << e.x << ' ' << e.y << endl;
        cout << "---" << endl;
        cout << f.x << ' ' << f.y << ' ' << f.x + k << ' ' << f.y + (d ? 1 : -1) * k << endl;
        exit(0);
    }
    EACH(e, a[1]) if (!(f == e) && f.diag(d) == e.diag(d) && e.x >= min(f.x, f.x + k) && e.x <= max(f.x, f.x + k)) {
        cout << "move collision" << endl;
        EACH(e, a[0]) cout << e.x << ' ' << e.y << endl;
        EACH(e, a[1]) cout << e.x << ' ' << e.y << endl;
        cout << "---" << endl;
        cout << f.x << ' ' << f.y << ' ' << f.x + k << ' ' << f.y + (d ? 1 : -1) * k << endl;
        exit(0);
    }
    /*if (ops++ == 25) {
        cout << "move limit exceeded" << endl;
        exit(0);
    }*/
    ++ops;
    f.x += k, f.y += (d ? 1 : -1) * k;
    auto_interact();
    if (!ax && !ay && !kx && !ky) won = 1;
}

void move_to(fig& f, int d, int k) { shift(f, !d, (k - f.diag(d)) / 2); } // moves figure to d-diag with value k, OK
void jump_to(fig& f, int k) { // jump to 0-diag with value k saving the same x coord, OK
    int x = f.diag(0);
    shift(f, 1, (k - x) / 2), shift(f, 0, (x - k) / 2);
}

void auto_interact() {
    FOR(dx, -1, 2) FOR(dy, -1, 2) if (dx != 0 || dy != 0) {
        int f = 1;
        kx += dx, ky += dy;
        EACH(e, a[0]) if (kx + ky == e.diag(0) || kx - ky == e.diag(1)) f = 0;
        EACH(e, a[1]) if (kx + ky == e.diag(0) || kx - ky == e.diag(1)) f = 0;
        kx -= dx, ky -= dy;
        if (f) {
            ax = kx, ay = ky;
            //cout << "interactor: " << kx << ' ' << ky << ' ';
            kx += dx, ky += dy;
            //cout << kx << ' ' << ky << endl;
            return;
        }
    }
    ax = ay = kx = ky = 0;
    //cout << "interactor: 0 0 0 0" << endl;
}



int solve() {
    if (sz(a[0]) < 2 || sz(a[1]) < 2) return 0;
    /// phase 1 (2 moves max)
    int f = (sz(a[0]) > sz(a[1]));
    if (f) swap(a[0], a[1]); // we need to ensure that 2 figures of same color are secured first
    sort(all(a[0]));
    if (!a[0][0].same(a[0][1], 0) && !a[0][0].same(a[0][1], 1)) move_to(a[0][1], 0, a[0][0].diag(0));
    if (won) return 0;
    FOR(i, 0, 3) if (kx == a[1][i].x && ky == a[1][i].y) a[1].erase(a[1].begin() + i); // if king eaten smth
    sort(all(a[1]));
    if (!a[1][0].same(a[1][1], 0) && !a[1][0].same(a[1][1], 1)) move_to(a[1][1], 0, a[1][0].diag(0));
    if (won) return 0;
    if (f) swap(a[0], a[1]);
    sort(all(a[0])), sort(all(a[1]));
    /// phase 2 (7 moves max)
    move_to(a[0][0], (a[0][0].diag(0) == a[0][1].diag(0)), -100000000);
    if (won) return 0;
    move_to(a[0][1], (a[0][0].diag(0) == a[0][1].diag(0)), -10000000);
    if (won) return 0;
    move_to(a[0][1], (a[0][0].diag(0) != a[0][1].diag(0)), a[0][1].diag(a[0][0].diag(0) != a[0][1].diag(0)) - 1000000);
    if (won) return 0;
    move_to(a[1][0], (a[1][0].diag(0) == a[1][1].diag(0)), -100000001);
    if (won) return 0;
    move_to(a[1][1], (a[1][0].diag(0) == a[1][1].diag(0)), -10000001);
    if (won) return 0;
    move_to(a[1][1], (a[1][0].diag(0) != a[1][1].diag(0)), a[1][1].diag(a[1][0].diag(0) != a[1][1].diag(0)) - 1000000);
    if (won) return 0;
    // third is useless and may fuck us up
    if (sz(a[0]) > 2) {
        move_to(a[0][2], 0, 200000000);
        if (won) return 0;
    }
    if (sz(a[1]) > 2) {
        move_to(a[1][2], 0, 200000001);
        if (won) return 0;
    }
    /// phase 3 (block by 0-diag, ?? moves max)
    int d0 = kx + ky;
    int l = d0 - 8;
    jump_to(a[!(d0 & 1)][0], d0 - 7);
    if (won) return 0;
    jump_to(a[d0 & 1][0], d0 - 8);
    if (won) return 0;
    d0 = kx + ky;
    int r = d0 + 8;
    jump_to(a[!(d0 & 1)][1], d0 + 7);
    if (won) return 0;
    jump_to(a[d0 & 1][1], d0 + 8);
    if (won) return 0;
    while (l + 4 < r) {
        if (kx + ky > l + 2) shift(a[l & 1][0], 1, 1), ++l;
        else shift(a[r & 1][1], 1, -1), --r;
        if (won) return 0;
    }
    /// phase 4 (block by 1-diag, 3 moves max)
    int col = (kx + ky) & 1;
    move_to(a[col][0], 1, (kx - ky) - 2); // block bottom
    if (won) return 0;
    move_to(a[col][1], 1, (kx - ky) + 2); // block top
    if (won) return 0;
    move_to(a[col][1], 1, (kx - ky) + 2); // stalemate
    cout << ops << endl;
    if (won) return 0;
    return 1;
}

signed main() {
    //fastIO;
    while (true) {
        won = 0, ops = 0;
        a[0].clear(), a[1].clear();
        vi xs(5), ys(5);
        FOR(i, 0, 5) {
            int x = (rng() % 6) - 2, y = (rng() % 6) - 2;
            while (true) {
                int f = 1;
                FOR(j, 0, i) if (x == xs[j] && y == ys[j]) f = 0;
                if (f) break;
                x = (rng() % 6) - 2, y = (rng() % 6) - 2;
            }
            xs[i] = x, ys[i] = y;
            fig f(x, y);
            a[f.color()].pb(f);
        }
        int skx = (rng() % 6) - 2, sky = (rng() % 6) - 2;
        while (true) {
            int f = 1;
            EACH(e, a[0]) if (skx + sky == e.diag(0) || skx - sky == e.diag(1)) f = 0;
            EACH(e, a[1]) if (skx + sky == e.diag(0) || skx - sky == e.diag(1)) f = 0;
            if (f) break;
            skx = (rng() % 6) - 2, sky = (rng() % 6) - 2;
        }
        kx = skx, ky = sky;
        if (solve()) {
            FOR(i, 0, 5) cout << xs[i] << ' ' << ys[i] << ' ';
            cout << skx << ' ' << sky;
            return 0;
        }
    }
}
