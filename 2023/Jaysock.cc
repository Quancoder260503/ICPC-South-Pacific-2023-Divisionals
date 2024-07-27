#include "bits/stdc++.h"

using namespace std;

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  map<int, int> ctr, ctr2;
  for (int i = 0, state = true; i < n; i++) {
    string s;
    int x;
    cin >> s;
    if (s == "WEARSOCK") {
      cin >> x;
      (state ? ctr : ctr2)[x]++;
      if (state) cout << "SOCK " << x << " " << ctr[x] << '\n';
    } else if (s == "WASHSOCK") {
      cin >> x;
      (state ? ctr : ctr2)[x]--;
      if (state) cout << "SOCK " << x << " " << ctr[x] << '\n';
    } else if (s == "SLEEP") {
      state = false;
    } else if (s == "WAKE") {
      state = true;
      for (const auto &[u, v] : ctr2) {
        ctr[u] += v;
        if (v) cout << "SOCK " << u << " " << ctr[u] << '\n';
      }
      ctr2.clear();
    }
  }
  return 0;
}
