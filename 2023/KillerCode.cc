#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  vector<string> s(n);
  for (int i = 0; i < n; i++) {
    cin >> s[i];
  }
  vector<int> l(n, -1), r(n, -1), stk;
  for (int i = 0; i < n; i++) {
    if (s[i] == "else") {
      assert(sz(stk));
      l[i] = stk.back();
      stk.pop_back();
    } else if (s[i] == "if") {
      stk.push_back(i);
    }
  }
  stk.clear();
  for (int i = n - 1; i >= 0; i--) {
    if (s[i] == "else") {
      assert(sz(stk));
      r[i] = stk.back();
      stk.pop_back();
    } else if (s[i] == "endif") {
      stk.push_back(i);
    }
  }
  vector<vector<int>> ga(n), gb(n);
  vector<int> dyn(n, -1);
  for (int i = 0; i < n; i++)
    if (s[i] == "else") {
      for (int j = 0; j < n; j++)
        if (s[j] == "else") {
          if (l[i] < l[j] && r[j] < i) {
            ga[i].push_back(j);
          }
          if (i < l[j] && r[j] < r[i]) {
            gb[i].push_back(j);
          }
        }
    }
  function<int(int)> doit = [&](int x) -> int {
    if (r[x] - l[x] == 2) {
      return 2;
    }
    if (dyn[x] != -1) return dyn[x];
    int &ret = dyn[x];
    ret = 0;
    int left = 1, right = 1;
    for (auto &v : ga[x]) left = max(left, doit(v));
    for (auto &v : gb[x]) right = max(right, doit(v));
    return ret = left + right;
  };
  int ret = 0;
  for (int i = 0; i < n; i++)
    if (s[i] == "else" && dyn[i] == -1) {
      ret = max(ret, doit(i));
    }
  cout << ret << '\n';
  return 0;
}