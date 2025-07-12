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

bool isPalindrome(ll n, int base) {
    if (n == 0) {
        return true;
    }
    string s = "";
    ll tmp = n;
    while (tmp > 0) {
        s += (tmp % base) + '0';
        tmp /= base;
    }
    string reversed_s = s;
    reverse(all(reversed_s));
    return s == reversed_s;
}

int main() {
    int a;
    ll n;
    cin >> a >> n;

    ll sum = 0;

    set<ll> se;

    bool isLimit = false;
    reps(length, 1, 15) {
        ll lower_bound = (length == 1) ? 0 : pow(10, (length - 1) / 2);
        ll upper_bound = pow(10, (length + 1) / 2) - 1;

        if (lower_bound > upper_bound && length > 1) {
            break;
        }
        if (lower_bound == 0 && length > 1 && (length - 1) / 2 == 0) {
            lower_bound = 1;
        }

        reps(i, lower_bound, upper_bound + 1) {
            string s = to_string(i);
            string reversed_s = s;
            reverse(all(reversed_s));

            string pstring;
            if (length % 2 == 0) {
                pstring = s + reversed_s;
            } else {
                pstring = s + reversed_s.substr(1);
            }

            ll p = stoll(pstring);

            if (p > n) {
                isLimit = true;
                break;
            }
            if (p != 0) {
                se.insert(p);
            }
        }
        if (isLimit) {
            break;
        }
    }

    for (ll num : se) {
        if (isPalindrome(num, a)) {
            sum += num;
        }
    }

    out(sum);

    return 0;
}