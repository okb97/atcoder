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
    int n, m;
    cin >> n >> m;
    vvb adj(n, vb(n, false));
    rep(i, m) {
        int u, v;
        cin >> u >> v;
        --u;
        --v;
        adj[u][v] = adj[v][u] = true;
    }
    vi cdp(1 << n, -1);

    reps(mask, 1, 1 << n) {
        if (__builtin_popcount(mask) < 3) continue;

        vi nodes;
        rep(i, n) {
            if ((mask >> i) & 1) nodes.pb(i);
        }

        int k = nodes.size();
        int start = nodes[0];
        vvi pdp(1 << k, vi(k, -1));

        pdp[1][0] = 0;
        reps(sub, 1, 1 << k) {
            rep(i, k) {
                if (pdp[sub][i] == -1) continue;
                rep(j, k) {
                    if (!((sub >> j) & 1)) {
                        int u = nodes[i];
                        int v = nodes[j];
                        int nsub = sub | (1 << j);
                        chmax(pdp[nsub][j], pdp[sub][i] + adj[u][v]);
                    }
                }
            }
        }

        int full = (1 << k) - 1;
        int max_w = -1;

        reps(i, 1, k) {
            if (pdp[full][i] != -1) {
                int u = nodes[i];
                chmax(max_w, pdp[full][i] + adj[u][start]);
            }
        }
        cdp[mask] = max_w;
    }

    vi fdp(1 << n, -1);
    fdp[0] = 0;

    reps(mask, 1, 1 << n) {
        int s = __builtin_ctz(mask);
        int rmask = mask ^ (1 << s);
        for (int sub = rmask;; sub = (sub - 1) & rmask) {
            int cmask = sub | (1 << s);
            int rem = mask ^ cmask;
            if (cdp[cmask] != -1 && fdp[rem] != -1) {
                chmax(fdp[mask], cdp[cmask] + fdp[rem]);
            }
            if (sub == 0) break;
        }
    }

    int max_w = fdp[(1 << n) - 1];
    int ans = m + n - 2 * max_w;
    out(ans);
    return 0;
}