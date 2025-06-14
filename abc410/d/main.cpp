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
inline bool chmax(T& a, T b) {
    return ((a < b) ? (a = b, true) : (false));
}
template <typename T>
inline bool chmin(T& a, T b) {
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
vector<string> rotate90Right(const vector<string>& grid) {
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

    vector<vector<pii>> G(n + 1);

    rep(i, m) {
        int a, b, w;
        cin >> a >> b >> w;
        G[a].pb(mp(b, w));
    }

    vvb dist(n + 1, vb(1024, false));

    queue<pii> q;
    q.push(mp(1, 0));
    dist[1][0] = true;

    while (!q.empty()) {
        auto [v, xor_val] = q.front();
        q.pop();

        for (auto [nv, w] : G[v]) {
            int new_xor = xor_val ^ w;
            if (!dist[nv][new_xor]) {
                dist[nv][new_xor] = true;
                q.push(mp(nv, new_xor));
            }
        }
    }

    rep(x, 1024) {
        if (dist[n][x]) {
            out(x);
            return 0;
        }
    }

    out(-1);
    return 0;
}