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

#include <iostream>

#include "../../../print_utils.h"

class Solution
{
  public:
    std::vector<int> bellman_ford(std::vector<int> &vertex,
                                  std::vector<std::tuple<int, int, int>> &edges, int origin,
                                  int destination)
    {
        std::vector<std::vector<int>> dp(vertex.size(), std::vector<int>(vertex.size(), 1e9));
        std::vector<int> parents(vertex.size(), -1);
        std::vector<int> cheapes_values(vertex.size(), 1e9);

        cheapes_values[origin] = 0;
        dp[0][origin] = 0;

        for (int j = 1; j < vertex.size(); j += 1)
        {
            for (const auto &[u, v, w] : edges)
                if (dp[j - 1][u] + w < dp[j][v])
                {
                    dp[j][v] = dp[j - 1][u] + w;

                    if (dp[j - 1][u] + w < cheapes_values[v])
                    {
                        cheapes_values[v] = dp[j - 1][u] + w;
                        parents[v] = u;
                    }
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