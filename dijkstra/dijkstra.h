#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <iostream>
#include <set>
#include <vector>

namespace dijkstra {

using std::vector;
using std::set;
using std::pair;
using ll = long long;
constexpr ll _INFINITY = LONG_LONG_MAX;  // ¯\_(ツ)_/¯

pair<ll, vector<int>> dijkstra(const vector<vector<pair<int, size_t>>>& graph,
                               int src, int dst) {
  /*
   * Description:
   * Dijkstra's algorithm is an algorithm for finding the shortest paths between
   * source node and all other nodes in the given graph with positive weights
   * of edges.
   *
   * Input:
   * :graph: graph represented as adjacency lists
   * :src: source vertex
   * :dst: destination vertex
   *
   * Output:
   * Pair of min length of the route and shortest path.
   * If there is no any path between than :src: and :dsc: then
   * min length of the route is -1.
   */

  // Initial vector of distances
  vector<ll> dist(graph.size(), _INFINITY);
  dist[src] = 0;

  // Vector for storing previous visited nodes
  vector<int> prev(graph.size(), -1);

  set<std::pair<ll, int>> S;
  S.insert({0, src});

  while (!S.empty()) {
    int u = S.begin()->second;
    S.erase(S.begin());

    for (int i = 0; i < graph[u].size(); ++i) {
      int v = graph[u][i].first;
      size_t uv_w = graph[u][i].second;
      if (dist[u] + uv_w < dist[v]) {
        S.erase({dist[v], v});
        dist[v] = dist[u] + static_cast<ll>(uv_w);
        prev[v] = u;
        S.insert({dist[v], v});
      }
    }
  }

  pair<ll, vector<int>> res;
  res.first = (dist[dst] == _INFINITY) ? -1 : dist[dst];

  // Restoring the shortest path
  if (prev[dst] != -1) res.second.push_back(dst);

  while (prev[dst] != -1) {
    res.second.push_back(prev[dst]);
    prev[dst] = prev[prev[dst]];
  }
  std::reverse(res.second.begin(), res.second.end());

  return res;
}

}  // namespace

#endif  // DIJKSTRA_H
