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

struct fig {
    int x, y;
    fig() {}
    fig(int a, int b) : x(a), y(b) {}
    int diag(int d) {
        if (d == 0) return x + y;
        if (d == 1) return x - y;
    }
    bool operator<(fig o) {
        if (diag(0) == o.diag(0)) return diag(1) < o.diag(1);
        return diag(0) < o.diag(0);
    }
    bool operator==(const fig o) const {
        return (x == o.x) && (y == o.y);
    }
    bool connected(fig o) {
        if (diag(0) == o.diag(0)) return 1;
        if (diag(1) == o.diag(1)) return 1;
        return 0;
    }
};

int ax, ay, kx, ky, won;
vector <fig> figs[2];

void judge_gen() {
    FOR(i, 0, 5) {
        int x, y; cin >> x >> y;
        figs[(x + y) & 1].pb(fig(x, y));
    }
    cin >> kx >> ky;
}

void rand_gen() {
    
}

void judge_in() {
    cin >> ax >> ay >> kx >> ky;
    if (ax == 0 && ay == 0 && kx == 0 && ky == 0) won = 1;
    else {
        auto it0 = find(all(figs[0]), fig(kx, ky));
        if (it0 != figs[0].end()) figs[0].erase(it0);
        auto it1 = find(all(figs[1]), fig(kx, ky));
        if (it1 != figs[1].end()) figs[1].erase(it0);
        assert((sz(figs[0]) >= 2 && sz(figs[1]) >= 2, "Not enough figures"));
    }
}
void judge_out(int a, int b, int c, int d) {
    cout << a << ' ' << b << ' ' << c << ' ' << d << endl;
}

pii mv[8] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
void bot_in() {
    shuffle(mv, mv + 8, rng);

    int found = 0;
    FOR(i, 0, 8) {
        int dx = mv[i].F, dy = mv[i].S, ok = 1;
        kx += dx, ky += dy;

        EACH(f, figs[0]) {
            if (kx + ky == f.diag(0) || kx - ky == f.diag(1)) {
                ok = 0;
            }
        }
        EACH(f, figs[1]) {
            if (kx + ky == f.diag(0) || kx - ky == f.diag(1)) {
                ok = 0;
            }
        }

        kx -= dx, ky -= dy;
        if (ok) {
            ax = kx, ay = ky;
            kx += dx, ky += dy;
            found = 1;
            break;
        }
    }

    if (found) {
        auto it0 = find(all(figs[0]), fig(kx, ky));
        if (it0 != figs[0].end()) figs[0].erase(it0);
        auto it1 = find(all(figs[1]), fig(kx, ky));
        if (it1 != figs[1].end()) figs[1].erase(it0);
        assert((sz(figs[0]) >= 2 && sz(figs[1]) >= 2, "Not enough figures"));

        cout << "bot move" << endl;
        cout << "from: " << ax << ' ' << ay << " (0-diag " << ax + ay << ", 1-diag " << ax - ay << ")" << endl;
        cout << "to: " << kx << ' ' << ky << " (0-diag " << kx + ky << ", 1-diag " << kx - ky << ")" << endl;
    }
    else {
        cout << "you won!" << endl;
        won = 1;
    }
}
void bot_out(int a, int b, int c, int d) {
    cout << "algo move" << endl;
    cout << "from: " << a << ' ' << b << " (0-diag " << a + b << ", 1-diag " << a - b << ")" << endl;
    cout << "to: " << c << ' ' << d << " (0-diag " << c + d << ", 1-diag " << c - d << ")" << endl;
}

void brute_in() {
    shuffle(mv, mv + 8, rng);

    int found = 0;
    FOR(i, 0, 8) {
        int dx = mv[i].F, dy = mv[i].S, ok = 1;
        kx += dx, ky += dy;

        EACH(f, figs[0]) {
            if (kx + ky == f.diag(0) || kx - ky == f.diag(1)) {
                ok = 0;
            }
        }
        EACH(f, figs[1]) {
            if (kx + ky == f.diag(0) || kx - ky == f.diag(1)) {
                ok = 0;
            }
        }

        kx -= dx, ky -= dy;
        if (ok) {
            ax = kx, ay = ky;
            kx += dx, ky += dy;
            found = 1;
            break;
        }
    }

    if (found) {
        auto it0 = find(all(figs[0]), fig(kx, ky));
        if (it0 != figs[0].end()) figs[0].erase(it0);
        auto it1 = find(all(figs[1]), fig(kx, ky));
        if (it1 != figs[1].end()) figs[1].erase(it0);
        assert((sz(figs[0]) >= 2 && sz(figs[1]) >= 2, "Not enough figures"));
    }
    else {
        won = 1;
    }
}
void brute_out(int a, int b, int c, int d) {

}

void validate_move(fig& f, int d, int k) {
    int cnt = 0;
    EACH(g, figs[f.diag(d) & 1]) {
        if (f.diag(d) == g.diag(d) && min(f.x, f.x + k) <= g.x && g.x <= max(f.x, f.x + k)) {
            ++cnt;
        }
    }
    assert((cnt == 1, "Bad move"));
}

void move_by(fig& f, int d, int k) {
    if (won || !k) return;
    validate_move(f, d, k);

    int ox = f.x, oy = f.y;
    f.x += k, f.y += (d == 1 ? k : -k);

    judge_out(ox, oy, f.x, f.y);
    judge_in();
    //brute_out(ox, oy, f.x, f.y);
    //brute_in();
}
void move_to(fig& f, int d, int k) {
    int c = f.diag(d);
    move_by(f, !d, (k - c) / 2);
}

void phase1() {
    int fir = (sz(figs[0]) < sz(figs[1]) ? 0 : 1);

    sort(all(figs[0]));
    if (!figs[fir][0].connected(figs[fir][1])) {
        move_to(figs[fir][1], 0, figs[fir][0].diag(0));
    }

    sort(all(figs[1]));
    if (!figs[!fir][0].connected(figs[!fir][1])) {
        move_to(figs[!fir][1], 0, figs[!fir][0].diag(0));
    }
}

void phase2() {
    sort(all(figs[0]));
    if (figs[0][0].diag(0) == figs[0][1].diag(0)) {
        move_by(figs[0][0], 0, -20000000);
        move_by(figs[0][1], 0, -2000000);
        move_by(figs[0][1], 1, -1488);
    }
    else {
        move_by(figs[0][0], 1, -20000000);
        move_by(figs[0][1], 1, -2000000);
        move_by(figs[0][1], 0, -1488);
    }

    sort(all(figs[1]));
    if (figs[1][0].diag(0) == figs[1][1].diag(0)) {
        move_by(figs[1][0], 0, -20000000);
        move_by(figs[1][1], 0, -2000000);
        move_by(figs[1][1], 1, -1488);
    }
    else {
        move_by(figs[1][0], 1, -20000000);
        move_by(figs[1][1], 1, -2000000);
        move_by(figs[1][1], 0, -1488);
    }

    if (sz(figs[0]) > 2) {
        move_by(figs[0][2], 0, 228228228);
    }
    if (sz(figs[1]) > 2) {
        move_by(figs[1][2], 0, 228228228);
    }
}

void phase3() {
    int kd = kx + ky;
    int l = kd - 3;
    move_to(figs[kd & 1][0], 0, kd - 2);
    move_to(figs[!(kd & 1)][0], 0, kd - 3);

    kd = kx + ky;
    int r = kd + 3;
    move_to(figs[kd & 1][1], 0, kd + 2);
    move_to(figs[!(kd & 1)][1], 0, kd + 3);

    while (l + 4 < r) {
        if (won) return;
        kd = kx + ky;
        if (kd > l + 2) {
            move_to(figs[l & 1][0], 0, l + 2);
            l++;
        }
        else {
            move_to(figs[r & 1][1], 0, r - 2);
            r--;
        }
    }
}

void phase4() {
    int kd = kx - ky;
    move_to(figs[kd & 1][0], 1, kd - 2);
    move_to(figs[kd & 1][1], 1, kd + 4);
    move_to(figs[kd & 1][1], 1, kd + 2);
}

void solve() {
    won = 0;
    figs[0].clear();
    figs[1].clear();

    judge_gen();
    if (sz(figs[0]) < 2 || sz(figs[1]) < 2) {
        judge_out(0, 0, 0, 0);
        return;
    }

    phase1();
    if (won) return;

    phase2();
    if (won) return;

    phase3();
    if (won) return;

    phase4();
    if (won) return;

    assert((won, "Bad strategy"));
}

signed main() {
    //fastIO;
    int tc = -1; cin >> tc;
    while (tc--) solve();
}
