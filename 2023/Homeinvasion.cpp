/*
   Author : MINH QUAN LE
*/
#include "bits/stdc++.h"
using namespace std;
const int INF = 1000000000;
#define lint long long
struct Edge {
  int a, b;
  lint cap, flow;
};
struct MaxFlow {
  int n, s, t;
  vector<int> d, ptr, q;
  vector<Edge> e;
  vector<vector<int>> g;

  MaxFlow(int _n) : n(_n), d(_n), ptr(_n), q(_n), g(_n) {
    e.clear();
    for (int i = 0; i < n; i++) {
      g[i].clear();
      ptr[i] = 0;
    }
  }

  void addEdge(int a, int b, lint cap) {
    // cout << a << " " << b << " " << cap << endl;
    Edge e1 = {a, b, cap, 0};
    Edge e2 = {b, a, 0, 0};
    g[a].push_back((int)e.size());
    e.push_back(e1);
    g[b].push_back((int)e.size());
    e.push_back(e2);
  }
  lint getMaxFlow(int _s, int _t) {
    s = _s;
    t = _t;
    lint flow = 0;
    for (;;) {
      if (!bfs()) break;
      std::fill(ptr.begin(), ptr.end(), 0);
      while (lint pushed = dfs(s, INF)) flow += pushed;
    }
    return flow;
  }

 private:
  bool bfs() {
    lint qh = 0, qt = 0;
    q[qt++] = s;
    std::fill(d.begin(), d.end(), -1);
    d[s] = 0;

    while (qh < qt && d[t] == -1) {
      lint v = q[qh++];
      for (int i = 0; i < (int)g[v].size(); i++) {
        lint id = g[v][i], to = e[id].b;
        if (d[to] == -1 && e[id].flow < e[id].cap) {
          q[qt++] = to;
          d[to] = d[v] + 1;
        }
      }
    }
    return d[t] != -1;
  }

  lint dfs(int v, lint flow) {
    if (!flow) return 0;
    if (v == t) return flow;
    for (; ptr[v] < (int)g[v].size(); ++ptr[v]) {
      int id = g[v][ptr[v]], to = e[id].b;
      if (d[to] != d[v] + 1) continue;
      lint pushed = dfs(to, min(flow, e[id].cap - e[id].flow));
      if (pushed) {
        e[id].flow += pushed;
        e[id ^ 1].flow -= pushed;
        return pushed;
      }
    }
    return 0;
  }
};
const int MAXN = 20;
int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, -1, 1};
char g[MAXN][MAXN][MAXN];
int n, m;
signed main(void) {
  cin >> n;
  for (int k = 0; k < n; k++) {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        cin >> g[i][j][k];
      }
    }
  }
  int N = n * n * n;
  MaxFlow mf(2 * N + 3);
  auto to = [&](int i, int j, int k) { return k * n * n + i * n + j; };
  auto valid = [&](int i, int j, int k) {
    return (0 <= i && i < n && 0 <= j && j < n && 0 <= k && k < n &&
            g[i][j][k] != '#');
  };
  int src = (2 * N + 1);
  int sink = (2 * N + 2);
  // cout << src << " " << sink << '\n';
  // graph construction
  vector<tuple<int, int, int>> edge;
  for (int k = 0; k < n; k++) {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        if (g[i][j][k] == '#') continue;
        if (k == 0 || k == n - 1) edge.push_back({i, j, k});
        if (i == 0 || i == n - 1) edge.push_back({i, j, k});
        if (j == 0 || j == n - 1) edge.push_back({i, j, k});
        mf.addEdge(to(i, j, k), to(i, j, k) + N, (g[i][j][k] == '.' ? 1 : INF));
        if (g[i][j][k] == 'S') {
          mf.addEdge(to(i, j, k) + N, sink, INF);
        }
        if (g[i][j][k] == 'R') {
          mf.addEdge(src, to(i, j, k), INF);
        }
        if (valid(i, j, k + 1)) {
          mf.addEdge(to(i, j, k) + N, to(i, j, k + 1),
                     g[i][j][k] == '.' ? 1 : INF);
        }
        if (valid(i, j, k - 1)) {
          mf.addEdge(to(i, j, k) + N, to(i, j, k - 1),
                     g[i][j][k] == '.' ? 1 : INF);
        }
        for (int dir = 0; dir < 4; dir++) {
          int px = dx[dir] + i;
          int py = dy[dir] + j;
          if (valid(px, py, k)) {
            mf.addEdge(to(i, j, k) + N, to(px, py, k),
                       g[i][j][k] == '.' ? 1 : INF);
          }
        }
      }
    }
  }
  // Adding holes from the edge
  edge.erase(unique(edge.begin(), edge.end()), edge.end());
  for (int i = 0; i < edge.size(); i++) {
    auto [x, y, z] = edge[i];
    for (int j = i + 1; j < edge.size(); j++) {
      auto [x2, y2, z2] = edge[j];
      mf.addEdge(to(x, y, z) + N, to(x2, y2, z2), g[x][y][z] == '.' ? 1 : INF);
      mf.addEdge(to(x2, y2, z2) + N, to(x, y, z),
                 g[x2][y2][z2] == '.' ? 1 : INF);
    }
  }
  auto maxf = mf.getMaxFlow(src, sink);
  cout << (maxf >= INF ? -1 : maxf) << '\n';
  return 0;
}
// This is just a min cut - max flow problem