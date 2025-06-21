#include <bits/stdc++.h>
using namespace std;
/* alias */
using ull = unsigned long long;
using ll = long long;
using vi = vector<int>;
using vl = vector<long>;
using vll = vector<long long>;
using vvi = vector<vi>;
using vvl = vector<vl>;
using vvll = vector<vll>;
using vs = vector<string>;
using vvs = vector<vs>;
using vc = vector<char>;
using vvc = vector<vc>;
using vb = vector<bool>;
using vvb = vector<vb>;
using pii = pair<int, int>;
/* define short */
#define pb push_back
#define mp make_pair
#define all(obj) (obj).begin(), (obj).end()
#define YESNO(bool)            \
    if (bool) {                \
        cout << "YES" << endl; \
    } else {                   \
        cout << "NO" << endl;  \
    }
#define yesno(bool)            \
    if (bool) {                \
        cout << "yes" << endl; \
    } else {                   \
        cout << "no" << endl;  \
    }
#define YesNo(bool)            \
    if (bool) {                \
        cout << "Yes" << endl; \
    } else {                   \
        cout << "No" << endl;  \
    }
/* REP macro */
#define reps(i, a, n) for (ll i = (a); i < (ll)(n); ++i)
#define rep(i, n) reps(i, 0, n)
#define repp(i, n) reps(i, 0, n + 1)
#define rrep(i, n) reps(i, 1, n + 1)
#define repds(i, a, n) for (ll i = (a); i >= (ll)(n); i--)
#define repd(i, n) for (ll i = n - 1; i >= 0; i--)
#define rrepd(i, n) for (ll i = n; i >= 1; i--)
#define out(x) cout << x << endl
// 定数
#define INF32 2147483647
#define INF64 9223372036854775807

template <typename T>
inline bool chmax(T &a, T b) {
    return ((a < b) ? (a = b, true) : (false));
}
template <typename T>
inline bool chmin(T &a, T b) {
    return ((a > b) ? (a = b, true) : (false));
}
const vi dy4 = {-1, 0, 1, 0};
const vi dx4 = {0, 1, 0, -1};
const vi dy8 = {-1, -1, 0, 1, 1, 1, 0, -1};
const vi dx8 = {0, 1, 1, 1, 0, -1, -1, -1};

/* 10進法→n進法 */
string tobasen(ll num, ll n) {
    string ans = "";
    while (num >= 1) {
        ans += to_string(num % n) + ans;
        num /= n;
    }
    return ans;
}

/* vector<string>を90度時計回り*/
vector<string> rotate90Right(const vector<string> &grid) {
    int N = grid.size();
    vector<string> res(N, string(N, ' '));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            res[j][N - 1 - i] = grid[i][j];
        }
    }
    return res;
}

/* UnionFind */
struct UnionFind {
    vi par, siz;

    UnionFind(int n) : par(n, -1), siz(n, 1) {}

    int root(int x) {
        if (par[x] == -1)
            return x;
        else
            return par[x] = root(par[x]);
    }
    bool issame(int x, int y) { return root(x) == root(y); }
    bool unite(int x, int y) {
        x = root(x);
        y = root(y);
        if (x == y) return false;
        if (siz[x] < siz[y]) swap(x, y);
        par[y] = x;
        siz[x] += siz[y];
        return true;
    }
    int size(int x) { return siz[root(x)]; }
};

ll MOD = 998244353;

ll rec(ll base, ll exp, ll mod) {
    ll res = 1;
    while (exp > 0) {
        if (exp % 2 == 1) {
            res = (res * base) % mod;
        }
        base = (base * base) % mod;
        exp /= 2;
    }
    return res;
}

int main() {
    ll n;
    cin >> n;
    vvll a(n, vll(6));
    rep(i, n) {
        rep(j, 6) { cin >> a[i][j]; }
    }

    // 全ての可能な値を収集してソート - O(6N log(6N))
    set<ll> all_values;
    rep(i, n) {
        rep(j, 6) {
            all_values.insert(a[i][j]);
        }
    }
    vll values(all_values.begin(), all_values.end());
    ll m = values.size();

    ll ans = 0;
    ll inv6 = rec(6, MOD - 2, MOD); // 6の逆元 - O(log MOD)

    // 各サイコロの面を事前にソート - O(6N log 6) = O(N)
    rep(i, n) {
        sort(all(a[i]));
    }

    // 各値vについて、maxがv以上になる確率を計算 - O(m * N log 6)
    rep(i, m) {
        ll v = values[i];
        ll prob_ge = 1; // 全体でmax >= vになる確率

        rep(j, n) {
            // 二分探索でv以上の値の個数を計算 - O(log 6)
            ll cnt = a[j].end() - lower_bound(all(a[j]), v);
            // サイコロjでv以上が出る確率 = cnt/6
            prob_ge = (prob_ge * cnt % MOD * inv6) % MOD;
        }

        // P(max = v) = P(max >= v) - P(max >= next_v)
        ll prob_eq = prob_ge;
        if (i + 1 < m) {
            ll next_v = values[i + 1];
            ll prob_ge_next = 1;
            rep(j, n) {
                // 二分探索でnext_v以上の値の個数を計算 - O(log 6)
                ll cnt = a[j].end() - lower_bound(all(a[j]), next_v);
                prob_ge_next = (prob_ge_next * cnt % MOD * inv6) % MOD;
            }
            prob_eq = (prob_ge - prob_ge_next + MOD) % MOD;
        }

        // 期待値に加算
        ans = (ans + v % MOD * prob_eq) % MOD;
    }

    out(ans);
    return 0;
}
