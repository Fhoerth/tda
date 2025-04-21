// ┌──┐        ┌──┐       ┌──┐
// │A ├────────┤B ├───────┤C │
// └─┬┘    10  └─┬┘   10  └┬─┘
//   │           │         │
//   │           │         │
//   │           │         │
// 2 │           │         │
//   │           │         │
//   │           │         │
// ┌─┴┐     2    │         │
// │  ├──────────┘         │
// │D │     2              │
// │  │────────────────────┘
// └──┘

// En este ejemplo se busca reducir al máximo las complejidades en memoria
// para optimizar el algoritmo que nos permita obtener el camino mas barato
// entre un origen y un destino.
// Se utiliza un solo vector dp, ya que no se necesitan valores previos,
// el mismo vector ya tiene los mejores valores para j-1 aristas de cada nodo
// de la iteración anterior.

#include <iostream>

#include "../../../print_utils.h"

class Solution
{
  public:
    std::vector<int> bellman_ford(std::vector<int> &vertex,
                                  std::vector<std::tuple<int, int, int>> &edges, int origin,
                                  int destination)
    {
        std::vector<int> dp(vertex.size(), 1e9);
        std::vector<int> parents(vertex.size(), -1);

        dp[origin] = 0;

        for (int j = 1; j < vertex.size(); j += 1)
        {
            for (const auto &[u, v, w] : edges)
                if (dp[u] + w < dp[v])
                {
                    dp[v] = dp[u] + w;
                    parents[v] = u;
                }
        }

        std::vector<int> path;
        int current = destination;

        while (current != origin)
        {
            path.push_back(current);
            current = parents[current];
        }
        path.push_back(origin);
        std::reverse(path.begin(), path.end());

        return path;
    }
};

int main()
{
    Solution solution;
    std::vector<int> vertex_1 = {0, 1, 2, 3};
    std::vector<std::tuple<int, int, int>> edges_1 = {
        {0, 1, 10}, {1, 2, 10}, {0, 3, 2}, {3, 1, 2}, {3, 2, 2}};
    int origin_1 = 0;      // A
    int destination_1 = 2; // C
    std::vector<int> path_1 = solution.bellman_ford(vertex_1, edges_1, origin_1, destination_1);

    std::cout << "El camino más barato para llegar de A a C es:" << std::endl;
    print_path(path_1);
}