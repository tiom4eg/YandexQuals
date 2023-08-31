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
constexpr int INF = 1e9 + 7, MD = 998244353, MAX = 50005, LG = 17, R = 1 << LG, MOD = 1e9 + 7, MOD2 = 1e9 + 9, RB = 158;
const ll INFLL = 1e18 + 7;

const ld EPS = 1e-11;

int sign(ld x) {
    if (x > 0) return 1;
    if (x < 0) return -1;
    return 0;
}
ld sq(ld x) { return x * x; }

struct point {
    ld x, y;
    point() {}
    point(ld x, ld y) : x(x), y(y) {}
    point operator+(const point& o) const { return point(x + o.x, y + o.y); }
    point operator-(const point& o) const { return point(x - o.x, y - o.y); }
    point operator*(const ld a) const { return point(x * a, y * a); }
    ld operator*(const point& o) const { return x * o.x + y * o.y; }
    ld operator^(const point& o) const { return x * o.y - y * o.x; }
    bool operator<(const point& o) const {
        if (sign(x - o.x)) return sign(x - o.x) < 0;
        return sign(y - o.y) < 0;
    }
    bool operator==(const point& o) const { return !sign(x - o.x) && !sign(y - o.y);  }
    ld len2() const { return sq(x) + sq(y); }
    point ort() const { return point(-y, x); }
    void print() { cout << '(' << x << ',' << y << ')' << endl; }
};

vector <point> intersect(ld r, point a, point b) {
    vector <point> res;
    ld A = b * b, B = a * b, C = (a * a) - sq(r), D = B * B - A * C;
    if (sign(D) < 0) return res;
    if (!sign(D)) {
        res.pb(a + b * (-B / A));
        return res;
    }
    res.pb(a + b * ((-B + sqrt(D)) / A));
    res.pb(a + b * ((-B - sqrt(D)) / A));
    return res;
}

struct fenwick {
    vi t;
    int S;
    fenwick(int n) {
        S = n + 1;
        t.assign(S, 0);
    }
    void upd(int p, int x) { for (; p < S; p += p & -p) t[p] += x; }
    int get(int p) {
        int s = 0;
        for (; p; p -= p & -p) s += t[p];
        return s;
    }
    int sum(int l, int r) { return get(r) - get(l - 1); } // [l; r]
};

bool half(point p) { return sign(p.y) > 0 || (!sign(p.y) && sign(p.x) < 0); }
bool cmp(point a, point b) { return make_tuple(half(a), 0.0, a * a) < make_tuple(half(b), a ^ b, b * b); }

int n;
ll k;
pair <point, point> ls[MAX];

int point_lower_bound(vector <point>& a, point x) {
    int l = 0, r = sz(a) - 1;
    while (l < r - 1) {
        int m = (l + r) / 2;
        (cmp(a[m], x) == 1 ? l : r) = m;
    }
    return r;
}

bool check(ld d) {
    vector <pair <point, point>> segs;
    vector <pii> evs;
    vector <point> vals;
    vals.pb(point(0, 0));
    FOR(i, 0, n) {
        vector <point> cur = intersect(d, ls[i].F, ls[i].S);
        if (cur.empty()) continue;
        if (sz(cur) == 1) {
            segs.pb({cur[0], cur[0]});
            vals.pb(cur[0]);
        }
        else {
            if (cmp(cur[1], cur[0])) swap(cur[0], cur[1]);
            segs.pb({cur[0], cur[1]});
            vals.pb(cur[0]), vals.pb(cur[1]);
        }
    }
    sort(all(vals), cmp);
    EACH(e, segs) evs.pb({point_lower_bound(vals, e.F), point_lower_bound(vals, e.S)});
    sort(all(evs));
    //EACH(e, evs) cout << e.F << ' ' << e.S << endl;
    fenwick t(sz(vals));
    ll cnt = 0;
    int l;
    while (l < sz(evs)) {
        int r = l + 1;
        while (r < sz(evs) && evs[r].F == evs[l].F) ++r;
        cnt += (r - l) * (r - l - 1) / 2;
        FOR(i, l, r) cnt += t.sum(evs[i].F, evs[i].S);
        FOR(i, l, r) t.upd(evs[i].S, 1);
        l = r;
    }
    return cnt >= k;
}

signed main() {
    fastIO;
    cout << fixed << setprecision(12);
    cin >> n >> k;
    FOR(i, 0, n) {
        ld a, b, c; cin >> a >> b >> c;
		if (!sign(a)) ls[i].F = point(0, c / b), ls[i].S = point(1, c / b);
		else if (!sign(b)) ls[i].F = point(c / a, 0), ls[i].S = point(c / a, 1);
		else ls[i].F = point(0, c / b), ls[i].S = point(1, (c - a) / b);
		ls[i].S = ls[i].S - ls[i].F;
    }
    ld l = 0, r = 10000000;
    FOR(iters, 0, 45) {
        ld m = (l + r) / 2;
        (check(m) ? r : l) = m;
    }
    cout << r;
}
