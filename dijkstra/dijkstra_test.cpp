#include "dijkstra.h"
#include <cassert>

int main() {
  std::vector<std::vector<std::pair<int, size_t>>> G = {
      {{1, 4}, {2, 2}},
      {{2, 2}, {3, 2}, {4, 3}},
      {{1, 1}, {4, 4}, {3, 4}},
      {},
      {{3, 1}}};
  auto res = dijkstra::dijkstra(G, 0, 4);

  assert(res.first == 6);
  assert(res.second == std::vector<int>({0, 2, 4}));

  res = dijkstra::dijkstra(G, 3, 4);

  assert(res.first == -1);
  assert(res.second == std::vector<int>({}));

  std::vector<std::vector<std::pair<int, size_t>>> G2 = {
      {{1, 7}, {2, 5}}, {{2, 2}}, {}};
  res = dijkstra::dijkstra(G2, 2, 1);
  assert(res.first == -1);
  assert(res.second == std::vector<int>({}));

  res = dijkstra::dijkstra(G2, 0, 2);
  assert(res.first == 5);
  assert(res.second == std::vector<int>({0, 2}));

  std::vector<std::vector<std::pair<int, size_t>>> G3 = {
      {{1, 1}, {2, 5}}, {{2, 2}}, {}, {{0, 2}}};
  res = dijkstra::dijkstra(G3, 0, 2);
  assert(res.first == 3);
  assert(res.second == std::vector<int>({0, 1, 2}));

  res = dijkstra::dijkstra(G3, 3, 2);
  assert(res.first == 5);
  assert(res.second == std::vector<int>({3, 0, 1, 2}));
  return 0;
}