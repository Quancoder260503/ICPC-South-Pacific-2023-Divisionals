#include "bits/stdc++.h"
using namespace std;
const int MAXN = 2000;
struct EulerDirected {
  EulerDirected(int _n) : n(_n), adj(n), in_deg(n, 0), out_deg(n, 0) {}

  void add_edge(int u, int v) {  // directed edge
    assert(0 <= u && u < n);
    assert(0 <= v && v < n);
    adj[u].push_front(v);
    in_deg[v]++;
    out_deg[u]++;
  }

  std::pair<bool, std::vector<int>> solve() {
    int start = -1, last = -1;
    for (int i = 0; i < n; i++) {
      // for all u, |in_deg(u) - out_deg(u)| <= 1
      if (std::abs(in_deg[i] - out_deg[i]) > 1) return {false, {}};

      if (out_deg[i] > in_deg[i]) {
        // At most 1 vertex with out_deg[u] - in_deg[u] = 1 (start vertex)
        if (start >= 0) return {false, {}};
        start = i;
      }

      if (in_deg[i] > out_deg[i]) {
        // At most 1 vertex with in_deg[u] - out_deg[u] = 1 (last vertex)
        if (last >= 0) return {false, {}};
        last = i;
      }
    }

    // can start at any vertex with degree > 0
    if (start < 0) {
      for (int i = 0; i < n; i++) {
        if (in_deg[i]) {
          start = i;
          break;
        }
      }
      // no start vertex --> all vertices have degree == 0
      if (start < 0) return {true, {}};
    }

    std::vector<int> path;
    find_path(start, path);
    std::reverse(path.begin(), path.end());

    // check that we visited all vertices with degree > 0
    std::vector<bool> visited(n, false);
    for (int u : path) visited[u] = true;

    for (int u = 0; u < n; u++) {
      if (in_deg[u] && !visited[u]) {
        return {false, {}};
      }
    }

    return {true, path};
  }

 private:
  int n;
  std::vector<std::list<int>> adj;
  std::vector<int> in_deg, out_deg;

  void find_path(int v, std::vector<int> &path) {
    while (adj[v].size() > 0) {
      int next = adj[v].front();
      adj[v].pop_front();
      find_path(next, path);
    }
    path.push_back(v);
  }
};
int n, k;
map<string, int> to;
string rev[MAXN];
signed main(void) {
  cin >> n >> k;
  int N = 0;
  vector<pair<int, int>> edge;
  for (int i = 0; i < n - k; i++) {
    string u, v;
    cin >> u >> v;
    if (!to.count(u)) {
      rev[N] = u;
      to[u] = N++;
    }
    if (!to.count(v)) {
      rev[N] = v;
      to[v] = N++;
    }
    edge.push_back({to[u], to[v]});
  }
  EulerDirected euler(N);
  for (auto [u, v] : edge) {
    euler.add_edge(u, v);
  }
  auto [g, path] = euler.solve();
  string ans = rev[path[0]];
  for (int i = 1; i < path.size(); i++) {
    ans += rev[path[i]].substr(k - 1, k);
  }
  cout << ans << '\n';
  return 0;
}