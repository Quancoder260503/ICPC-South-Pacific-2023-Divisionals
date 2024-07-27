#include "bits/stdc++.h"
using namespace std;
signed main(void) {
  int N;
  while (cin >> N) {
    vector<string> A(N), B(N), C(N), D(N);
    for (int i = 0; i < N; i++) cin >> A[i] >> B[i] >> C[i] >> D[i];
    for (int i = 0; i < N; i++) {
      for (int j = i + 1; j < N; j++) {
        for (int k = j + 1; k < N; k++) {
          if ((A[i] == A[j] || A[i] == A[k] || A[k] == A[j]) &&
              !(A[i] == A[j] && A[j] == A[k]))
            continue;
          if ((B[i] == B[j] || B[i] == B[k] || B[k] == B[j]) &&
              !(B[i] == B[j] && B[j] == B[k]))
            continue;
          if ((C[i] == C[j] || C[i] == C[k] || C[k] == C[j]) &&
              !(C[i] == C[j] && C[j] == C[k]))
            continue;
          if ((D[i] == D[j] || D[i] == D[k] || D[k] == D[j]) &&
              !(D[i] == D[j] && D[j] == D[k]))
            continue;
          cout << i + 1 << " " << j + 1 << " " << k + 1 << '\n';
          goto done;
        }
      }
    }
    cout << '0' << '\n';
  done:
    continue;
  }
  return 0;
}