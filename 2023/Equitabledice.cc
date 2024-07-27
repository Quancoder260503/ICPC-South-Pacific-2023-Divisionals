#include "bits/stdc++.h"

using namespace std;

const double eps = 1e-6;

int main(void) {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int n;
  cin >> n;
  vector<vector<int>> dice(n, vector<int>(6));
  vector<int> mx_dice(n), mn_dice(n, int(1e9));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < 6; j++) {
      cin >> dice[i][j];
      mx_dice[i] = max(mx_dice[i], dice[i][j]);
      mn_dice[i] = min(mn_dice[i], dice[i][j]);
    }
  }
  vector<int> ord(n);
  vector<double> ret(n);
  vector<vector<double>> ans(n, vector<double>(6, 0.0));
  iota(ord.begin(), ord.end(), 0);
  sort(ord.begin(), ord.end(),
       [&](int i, int j) { return mx_dice[i] > mx_dice[j]; });
  int curr_dice = n;
  for (auto &u : ord) {
    ret[u] = 1.0 / (curr_dice--);
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < 6; j++) {
      if (dice[i][j] == mx_dice[i]) {
        ans[i][j] = ret[i];
      } else if (dice[i][j] == mn_dice[i]) {
        ans[i][j] = 1.0 - ret[i];
      }
    }
  }
  bool check = true;
  vector<double> psum(n);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < 6; j++) {
      double sprob = ans[i][j];
      for (int ni = 0; ni < n; ni++)
        if (ni != i) {
          double prob = 0.0;
          for (int nj = 0; nj < 6; nj++)
            if (dice[ni][nj] < dice[i][j]) {
              prob += ans[ni][nj];
            }
          sprob *= prob;
        }
      psum[i] += sprob;
    }
  }
  for (int i = 0; i < n; i++) {
    check &= (fabs(1.0 / n - psum[i]) < eps);
  }
  cout << fixed << setprecision(10);
  if (check) {
    cout << "POSSIBLE\n";
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < 6; j++) {
        cout << ans[i][j] << " ";
      }
      cout << '\n';
    }
  } else {
    cout << "IMPOSSIBLE\n";
  }
  return 0;
}