#include "bits/stdc++.h"
using namespace std;
#define lint long long
const lint INF = 1e14;
signed main(void) {
  lint s, c, t, N, M;
  string a, b;
  cin >> c >> s >> t;
  cin >> a >> b;
  a = " " + a;
  b = " " + b;
  N = a.length();
  M = b.length();
  vector<vector<lint>> dp(N, vector<lint>(M, INF));
  vector<lint> pref(M, INF);
  vector<lint> Tpref(M, INF);
  pref[0] = Tpref[0] = 0;
  for (int i = 0; i < N; i++) {
    dp[i][0] = 1LL * s * i + c;
  }
  for (int i = 0; i < M; i++) {
    dp[0][i] = 1LL * s * i + c;
  }
  dp[0][0] = 0;
  for (int i = 1; i < N; i++) {
    lint min_so_far = INF;
    for (int j = 1; j < M; j++) {
      dp[i][j] = dp[i - 1][j - 1] + (a[i] == b[j] ? 0 : 1) * t;
      dp[i][j] = min(dp[i][j], Tpref[j - 1] + 1LL * s * (i + j) + 2 * c);
      dp[i][j] = min(dp[i][j], min_so_far + 1LL * s * j + c);
      dp[i][j] = min(dp[i][j], pref[j] + 1LL * s * i + c);
      min_so_far = min(min_so_far, dp[i][j] - 1LL * s * j);
      pref[j] = min(pref[j], dp[i][j] - s * i);
      Tpref[j] = min(min(Tpref[j], Tpref[j - 1]), dp[i][j] - 1LL * s * (i + j));
    }
  }
  cout << dp[N - 1][M - 1] << '\n';
  return 0;
}
/*
dp[i][j] = dp[i - 1][j - 1] + (a[i] != b[j]) * (T)
         = min(dp[ii][jj] - S * (ii + jj)) + S * (i + j) + 2 * C for ii < i &&
jj < j = dp[i][jj] + S * (j - jj) + C for jj < j = dp[ii][j] + S * (i - ii) + C
for ii < i

         -> prefix_minT[jj] = min(dp[ii][jj] - S * (ii + jj))
         -> at index ith, that is cur_max
         -> prefix_min[j] = min(dp[ii][j] + C - S * ii) V ii < i
 -> Complexity : O(N ^ 2)
*/