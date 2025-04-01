#include <cassert>
#include <iostream>

#include "../../test_utils.h"
< -- -PONGO ALGO ACA QUE ROMPE LA COMPILACION--->class Solution
{

  public:
    std::vector<int> maxi_subconjunto(const std::vector<std::vector<int>> &M, int k)
    {
        std::vector<int> I(k);
        std::vector<int> current_I(k);
        int I_sum = 0;

        backtrack(M, k, I, I_sum, current_I, 0, 0);

        for (int j = 0; j < k; j += 1)
            I[j] += 1;

        return I;
    }

  private:
    void backtrack(const std::vector<std::vector<int>> &M, int k, std::vector<int> &I, int &I_sum,
                   std::vector<int> &current_I, int current_I_size, int current_idx)
    {
        if (current_I_size == k)
        {
            int current_I_sum = 0;

            for (int i = 0; i < k; ++i)
                for (int j = i + 1; j < k; ++j)
                    current_I_sum += M[current_I[i]][current_I[j]];

            if (current_I_sum > I_sum)
            {
                I_sum = current_I_sum;
                I = current_I;
            }

            return;
        }

        for (int n = current_idx; n < M.size(); n += 1)
        {
            current_I[current_idx] = n;
            backtrack(M, k, I, I_sum, current_I, current_I_size + 1, current_idx + 1);
        }
    }
};

int main()
{
    Solution solution;

    std::vector<int> actual_1 =
        solution.maxi_subconjunto({{0, 10, 10, 1}, {10, 0, 5, 2}, {10, 5, 0, 1}, {1, 2, 1, 0}}, 3);
    std::vector<int> expected_1 = {1, 2, 3};
    assert_set_equals(actual_1, expected_1);

    return 0;
}
