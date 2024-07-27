#include "bits/stdc++.h"
using namespace std;
signed main(void) {
  string S;
  int N = 20;
  while (cin >> S) {
    set<int> s2;
    for (int i = 0; i < min(N, (int)S.length()); i++) {
      for (int j = 0; j + i < S.length(); j++) {
        if (S[j] == '0') continue;
        int64_t curr = 0;
        for (int k = j; k <= j + i; k++) {
          curr += (S[(j + i) - (k - j)] - '0') * (1 << (k - j));
        }
        s2.insert(curr);
      }
    }
    for (int i = 1; i < (1 << N); i++) {
      if (s2.count(i) == 0) {
        string ret;
        for (int j = 0; j < N; j++) {
          ret += ('0' + ((i >> j) & 1));
        }
        int j;
        for (j = ret.size() - 1; j >= 0 && ret[j] == '0'; j--)
          ;
        auto res = ret.substr(0, j + 1);
        reverse(res.begin(), res.end());
        cout << res << '\n';
        goto done;
      }
    }
  done:
    continue;
  }
  return 0;
}