#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n, c;
  cin >> c >> n;
  map<int, vector<int>> cor;
  for (int i = 0, x, y; i < n; i++) {
    cin >> x >> y;
    cor[x].push_back(y);
  }
  vector<int> rx;
  vector<array<int, 4>> ret;
  for (auto [u, cc] : cor) {
    rx.push_back(u);
    sort(cc.begin(), cc.end());
    cc.erase(unique(cc.begin(), cc.end()), cc.end());
    if (0 < cc[0]) {
      ret.push_back({u, 0, 1, cc[0]});
    }
    for (int i = 1; i < sz(cc); i++) {
      if (i < sz(cc) && cc[i] - cc[i - 1] == 1) {
        continue;
      }
      ret.push_back({u, cc[i - 1] + 1, 1, cc[i] - cc[i - 1] - 1});
    }
    if (cc.back() + 1 < c) {
      ret.push_back({u, cc.back() + 1, 1, c - cc.back() - 1});
    }
  }
  if (sz(rx)) {
    if (0 < rx[0]) ret.push_back({0, 0, rx[0], c});
    for (int i = 1; i < sz(rx); i++) {
      if (rx[i] > rx[i - 1] + 1) {
        ret.push_back({rx[i - 1] + 1, 0, rx[i] - rx[i - 1] - 1, c});
      }
    }
    if (rx.back() + 1 < c)
      ret.push_back({rx.back() + 1, 0, c - rx.back() - 1, c});
  }
  cout << sz(ret) << '\n';
  for (auto [x, y, dx, dy] : ret) {
    cout << x << " " << y << " " << dx << " " << dy << '\n';
  }
  return 0;
}
