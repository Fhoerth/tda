#include <cassert>
#include <climits>
#include <iostream>

#include "../../test_utils.h"

class Solution
{

  public:
    std::vector<int> ruta_minima(const std::vector<std::vector<int>> &M)
    {
        std::vector<int> π(M.size());
        std::vector<int> current_π(M.size());

        int π_sum = INT_MAX;

        for (int j = 0; j < M.size(); j += 1)
            current_π[j] = j;

        backtrack(M, π, π_sum, current_π, 0, 0);

        for (int j = 0; j < M.size(); j += 1)
            π[j] += 1;

        return π;
    }

  private:
    void swap(std::vector<int> &π, int i, int j)
    {
        int tmp = π[i];
        π[i] = π[j];
        π[j] = tmp;
    }

    void backtrack(const std::vector<std::vector<int>> &M, std::vector<int> &π, int &π_sum,
                   std::vector<int> &current_π, int current_π_sum, int current_idx)
    {
        if (current_idx == M.size())
        {
            int current_π_total_sum = current_π_sum + M[current_π[M.size() - 1]][current_π[0]];
            if (current_π_total_sum < π_sum)
            {
                π_sum = current_π_sum;
                π = current_π;
            }
        }

        for (int j = current_idx; j < M.size(); j += 1)
        {
            swap(current_π, j, current_idx);
            if (current_idx > 0)
                current_π_sum += M[current_π[current_idx - 1]][current_π[current_idx]];

            backtrack(M, π, π_sum, current_π, current_π_sum, current_idx + 1);

            if (current_idx > 0)
                current_π_sum -= M[current_π[current_idx - 1]][current_π[current_idx]];
            swap(current_π, current_idx, j);
        }
    }
};

int main()
{
    Solution solution;

    std::vector<int> actual_1 =
        solution.ruta_minima({{0, 1, 10, 10}, {10, 0, 3, 15}, {21, 17, 0, 2}, {3, 22, 30, 0}});
    std::cout << "Actual_1: {";
    for (int j = 0; j < actual_1.size() - 1; j += 1)
        std::cout << actual_1[j] << ", ";
    std::cout << actual_1[actual_1.size() - 1] << "}" << std::endl;

    return 0;
}
