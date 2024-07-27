#include "bits/stdc++.h"
using namespace std;
#define lint long long
int sc, ec, n, m, k, fmask;
map<int, lint> dp[30][30];
const int mod = 1e9 + 7;
int bit[30][30];
lint ans;
void f(int r, int c, int mask, int depth, int H) {
  if (depth == H) {
    dp[r][c][mask]++;
    // cout << "f: " << r << " " << c << " " << mask << " " << dp[r][c][mask] <<
    // endl;
    return;
  }
  if ((mask & bit[r + 1][c]) == 0) {
    f(r + 1, c, mask | bit[r + 1][c], depth + 1, H);
  }
  if (1 < c && ((mask & bit[r + 1][c - 1]) == 0)) {
    f(r + 1, c - 1, mask | bit[r + 1][c - 1], depth + 1, H);
  }
  if (c < m && ((mask & bit[r + 1][c + 1]) == 0)) {
    f(r + 1, c + 1, mask | bit[r + 1][c + 1], depth + 1, H);
  }
}
void g(int r, int c, int mask, int depth, int H) {
  if (depth == H) {
    // cout << "g: " << r << " " << c << " " << mask << " " << (mask xor fmask)
    // << " " << dp[r][c][mask xor fmask] << endl;
    /// dp[r][c][mask]++;
    ans = (ans + dp[r - 1][c][mask xor fmask] + mod) % mod;
    if (c < m) ans = (ans + dp[r - 1][c + 1][mask xor fmask] + mod) % mod;
    if (c > 1) ans = (ans + dp[r - 1][c - 1][mask xor fmask] + mod) % mod;
    return;
  }
  if ((mask & bit[r - 1][c]) == 0) {
    g(r - 1, c, mask | bit[r - 1][c], depth - 1, H);
  }
  if (1 < c && ((mask & bit[r - 1][c - 1]) == 0)) {
    g(r - 1, c - 1, mask | bit[r - 1][c - 1], depth - 1, H);
  }
  if (c < m && ((mask & bit[r - 1][c + 1]) == 0)) {
    g(r - 1, c + 1, mask | bit[r - 1][c + 1], depth - 1, H);
  }
}
signed main(void) {
  cin >> n >> m >> k >> sc >> ec;
  memset(bit, 0, sizeof(bit));
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      string curr;
      cin >> curr;
      for (int k = 0; k < curr.size(); k++) {
        if (65 <= curr[k] && curr[k] <= 90) {
          bit[i][j] |= (1 << (curr[k] - 'A'));
        }
      }
    }
  }
  fmask = (1 << k) - 1;
  ans = 0;
  f(1, sc, bit[1][sc], 1, n / 2);
  g(n, ec, bit[n][ec], n, n / 2 + 1);
  cout << ans << '\n';
  return 0;
}