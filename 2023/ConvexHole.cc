#include "bits/stdc++.h"
using namespace std;
#define double long double
#ifndef EPS  // allow test files to overwrite EPS
#define EPS 1e-6
#endif
const double PI = acos(-1.0);

double DEG_to_RAD(double d) { return d * PI / 180.0; }
double RAD_to_DEG(double r) { return r * 180.0 / PI; }

inline int cmp(double a, double b) {
  return (a < b - EPS) ? -1 : ((a > b + EPS) ? 1 : 0);
}

// for int types
template <typename T, typename std::enable_if<
                          !std::is_floating_point<T>::value>::type * = nullptr>
inline int cmp(T a, T b) {
  return (a == b) ? 0 : (a < b) ? -1 : 1;
}

template <typename T>
struct P {
  T x, y;
  P() { x = y = T(0); }
  P(T _x, T _y) : x(_x), y(_y) {}

  P operator+(const P &a) const { return P(x + a.x, y + a.y); }
  P operator-(const P &a) const { return P(x - a.x, y - a.y); }
  P operator*(T k) const { return P(x * k, y * k); }
  P<double> operator/(double k) const { return P(x / k, y / k); }

  T operator*(const P &a) const { return x * a.x + y * a.y; }  // dot product
  T operator%(const P &a) const { return x * a.y - y * a.x; }  // cross product

  int cmp(const P<T> &q) const {
    if (int t = ::cmp(x, q.x)) return t;
    return ::cmp(y, q.y);
  }

#define Comp(x) \
  bool operator x(const P &q) const { return cmp(q) x 0; }
  Comp(>) Comp(<) Comp(==) Comp(>=) Comp(<=) Comp(!=)
#undef Comp

      T norm() {
    return x * x + y * y;
  }

  // Note: There are 2 ways for implementing len():
  // 1. sqrt(norm()) --> fast, but inaccurate (produce some values that are of
  // order X^2)
  // 2. hypot(x, y) --> slow, but much more accurate
  double len() { return hypot(x, y); }

  P<double> rotate(double alpha) {
    double cosa = cos(alpha), sina = sin(alpha);
    return P(x * cosa - y * sina, x * sina + y * cosa);
  }
};
using Point = P<double>;

// Compare points by (y, x)
template <typename T = double>
bool cmpy(const P<T> &a, const P<T> &b) {
  if (cmp(a.y, b.y)) return a.y < b.y;
  return a.x < b.x;
};

template <typename T>
int ccw(P<T> a, P<T> b, P<T> c) {
  return cmp((b - a) % (c - a), T(0));
}

int RE_TRAI = ccw(P<int>(0, 0), P<int>(0, 1), P<int>(-1, 1));
int RE_PHAI = ccw(P<int>(0, 0), P<int>(0, 1), P<int>(1, 1));

template <typename T>
istream &operator>>(istream &cin, P<T> &p) {
  cin >> p.x >> p.y;
  return cin;
}
template <typename T>
ostream &operator<<(ostream &cout, const P<T> &p) {
  cout << p.x << ' ' << p.y;
  return cout;
}

double angle(Point a, Point o, Point b) {  // min of directed angle AOB & BOA
  a = a - o;
  b = b - o;
  return acos((a * b) / sqrt(a.norm()) / sqrt(b.norm()));
}

double directed_angle(Point a, Point o,
                      Point b) {  // angle AOB, in range [0, 2*PI)
  double t = -atan2(a.y - o.y, a.x - o.x) + atan2(b.y - o.y, b.x - o.x);
  while (t < 0) t += 2 * PI;
  return t;
}

// Distance from p to Line ab (closest Point --> c)
// i.e. c is projection of p on AB
double distToLine(Point p, Point a, Point b, Point &c) {
  Point ap = p - a, ab = b - a;
  double u = (ap * ab) / ab.norm();
  c = a + (ab * u);
  return (p - c).len();
}

// Distance from p to segment ab (closest Point --> c)
double distToLineSegment(Point p, Point a, Point b, Point &c) {
  Point ap = p - a, ab = b - a;
  double u = (ap * ab) / ab.norm();
  if (u < 0.0) {
    c = Point(a.x, a.y);
    return (p - a).len();
  }
  if (u > 1.0) {
    c = Point(b.x, b.y);
    return (p - b).len();
  }
  return distToLine(p, a, b, c);
}

// NOTE: WILL NOT WORK WHEN a = b = 0.
struct Line {
  double a, b, c;  // ax + by + c = 0
  Point A, B;  // Added for polygon intersect line. Do not rely on assumption
               // that these are valid

  Line(double _a, double _b, double _c) : a(_a), b(_b), c(_c) {}

  Line(Point _A, Point _B) : A(_A), B(_B) {
    a = B.y - A.y;
    b = A.x - B.x;
    c = -(a * A.x + b * A.y);
  }
  Line(Point P, double m) {
    a = -m;
    b = 1;
    c = -((a * P.x) + (b * P.y));
  }
  double f(Point p) { return a * p.x + b * p.y + c; }
};
ostream &operator>>(ostream &cout, const Line &l) {
  cout << l.a << "*x + " << l.b << "*y + " << l.c;
  return cout;
}

bool areParallel(Line l1, Line l2) {
  return cmp(l1.a * l2.b, l1.b * l2.a) == 0;
}

bool areSame(Line l1, Line l2) {
  return areParallel(l1, l2) && cmp(l1.c * l2.a, l2.c * l1.a) == 0 &&
         cmp(l1.c * l2.b, l1.b * l2.c) == 0;
}

bool areIntersect(Line l1, Line l2, Point &p) {
  if (areParallel(l1, l2)) return false;
  double dx = l1.b * l2.c - l2.b * l1.c;
  double dy = l1.c * l2.a - l2.c * l1.a;
  double d = l1.a * l2.b - l2.a * l1.b;
  p = Point(dx / d, dy / d);
  return true;
}

// closest point from p in line l.
void closestPoint(Line l, Point p, Point &ans) {
  if (fabs(l.b) < EPS) {
    ans.x = -(l.c) / l.a;
    ans.y = p.y;
    return;
  }
  if (fabs(l.a) < EPS) {
    ans.x = p.x;
    ans.y = -(l.c) / l.b;
    return;
  }
  Line perp(l.b, -l.a, -(l.b * p.x - l.a * p.y));
  areIntersect(l, perp, ans);
}

// Segment intersect
// Tested:
// - https://cses.fi/problemset/task/2190/
// returns true if p is on segment [a, b]
template <typename T>
bool onSegment(const P<T> &a, const P<T> &b, const P<T> &p) {
  return ccw(a, b, p) == 0 && min(a.x, b.x) <= p.x && p.x <= max(a.x, b.x) &&
         min(a.y, b.y) <= p.y && p.y <= max(a.y, b.y);
}

// Returns true if segment [a, b] and [c, d] intersects
// End point also returns true
template <typename T>
bool segmentIntersect(const P<T> &a, const P<T> &b, const P<T> &c,
                      const P<T> &d) {
  if (onSegment(a, b, c) || onSegment(a, b, d) || onSegment(c, d, a) ||
      onSegment(c, d, b)) {
    return true;
  }

  return ccw(a, b, c) * ccw(a, b, d) < 0 && ccw(c, d, a) * ccw(c, d, b) < 0;
}
int sign(double num) {
  if (fabs(num) < EPS) return 0;
  return num < 0 ? -1 : 1;
}
signed main(void) {
  int T;
  T = 1;
  while (T--) {
    int N;
    cin >> N;
    vector<Point> P(N);
    for (int i = 0; i < N; i++) cin >> P[i];
    function<void(int)> doit;
    double ret = 0;
    doit = [&](int at) -> void {
      vector<Point> vset;
      for (int i = 0; i < N; i++) {
        if (cmpy(P[at], P[i])) vset.push_back(P[i] - P[at]);
      }
      auto cmp = [&](Point &a, Point &b) {
        int curr = sign(a % b);
        if (curr != 0) return a % b > 0;
        curr = sign(a.norm() - b.norm());
        return curr < 0;
      };
      sort(vset.begin(), vset.end(), cmp);
      int M = vset.size();
      vector<vector<double>> dyn(M + 1, vector<double>(M + 1, 0));
      for (int k = 1; k < M; k++) {
        vector<int> vset2;
        int i, j;
        for (i = k - 1; i >= 0 && (vset[k] % vset[i]) == 0; i--)
          ;
        while (i >= 0) {
          double curr = (vset[i] % vset[k]) / 2.0;
          vset2.push_back(i);
          for (j = i - 1;
               j >= 0 && sign((vset[i] - vset[k]) % (vset[j] - vset[k])) > 0;
               j--)
            ;
          if (j >= 0) curr += dyn[i][j];
          dyn[k][i] = curr;
          ret = max(ret, curr);
          i = j;
        }
        for (int p = vset2.size() - 2; p >= 0; p--) {
          dyn[k][vset2[p]] = max(dyn[k][vset2[p]], dyn[k][vset2[p + 1]]);
        }
      }
    };
    auto calc = [&](void) {
      for (int i = 0; i < N; i++) {
        doit(i);
      }
      return 0;
    };
    calc();
    int64_t res = ret * 2;
    cout << res << '\n';
  }
  return 0;
}