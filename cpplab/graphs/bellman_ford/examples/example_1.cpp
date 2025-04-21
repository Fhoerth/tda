// Graph A->B->C->D

#include <iostream>

#include "../../../print_utils.h"

class Solution
{
  public:
    std::vector<std::vector<int>> bellman_ford(std::vector<int> &vertex,
                                               std::vector<std::tuple<int, int, int>> &edges,
                                               int from_node)
    {
        std::vector<std::vector<int>> dp(vertex.size(), std::vector<int>(vertex.size(), 1e9));

        dp[0][from_node] = 0;

        for (int j = 1; j < vertex.size(); j += 1)
            for (const auto &[u, v, w] : edges)
                dp[j][v] = std::min(dp[j][v], dp[j - 1][u] + w);

        return dp;
    }
};

int main()
{
    Solution solution;
    std::vector<int> vertex_1 = {0, 1, 2, 3};
    std::vector<std::tuple<int, int, int>> edges_1 = {{0, 1, 1}, {1, 2, 1}, {2, 3, 1}};
    std::vector<std::vector<int>> min_distances_1 = solution.bellman_ford(vertex_1, edges_1, 0);

    print_int_matrix(min_distances_1);
}