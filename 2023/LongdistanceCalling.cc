#include "bits/stdc++.h"

using namespace std;

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int x, y, he, me, ht, mt, d, m, h;
  cin >> x >> y >> he >> me >> ht >> mt >> d >> h >> m;
  int ste = he * 60 + me;
  int total_minute;
  int stc = m + h * 60;
  total_minute = d * 60 * 24 + stc - ste;
  total_minute += ht * y + mt;
  int mday = total_minute / (x * y), mhour = (total_minute % (x * y)) / y,
      mmin = ((total_minute % (x * y)) % y);
  cout << mday << " " << mhour << " " << mmin << '\n';
  return 0;
}