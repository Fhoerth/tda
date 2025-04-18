#include <cassert>
#include <iostream>
#include <limits.h>
#include <vector>

class Solution
{
  public:
    int solve(std::vector<std::vector<int>> &M)
    {
        std::string path;
        std::vector<std::vector<int>> memo(M.size(), std::vector<int>(M[0].size()));

        int m = M.size() - 1;
        int n = M[0].size() - 1;

        while (m > 0 || n > 0)
        {
            m -= 1;
        }

        return backtrack(M, memo, 0, 0);
    }

  private:
    int backtrack(std::vector<std::vector<int>> &M, std::vector<std::vector<int>> &memo, int i,
                  int j)
    {
        int m = M.size();
        int n = M[0].size();

        if (i == m - 1 && j == n - 1)
            return M[i][j] >= 1 ? 1 : -1 * M[i][j] + 1;

        if (i == m || j == n)
            return INT_MAX;

        if (memo[i][j] > 0)
            return memo[i][j];

        int a = backtrack(M, memo, i + 1, j);
        int b = backtrack(M, memo, i, j + 1);

        memo[i][j] = std::max(std::min(a, b) - M[i][j], 1);

        return memo[i][j];
    }
};

int main()
{
    Solution solution;

    std::vector<std::vector<int>> M_1 = {{-2, -3, 3}, {-5, -10, 1}, {10, 30, -5}};
    int actual_1 = solution.solve(M_1);
    int expected_1 = 7;
    assert(actual_1 == expected_1);

    std::vector<std::vector<int>> M_2 = {
        {-2, -3, 3, -1}, {-5, -10, 1, 1}, {10, 30, -5, -2}, {1, 1, 1, -5}};
    int actual_2 = solution.solve(M_2);
    int expected_2 = 8;
    assert(actual_2 == expected_2);
}