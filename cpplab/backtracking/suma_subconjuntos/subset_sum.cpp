#include <cassert>
#include <iostream>

class Solution
{

  public:
    int subset_sum(const std::vector<int> &C, int k) { return backtrack(C, k, 0, 0); }

  private:
    int backtrack(const std::vector<int> &C, int k, int current_idx, int current_sum)
    {
        if (current_sum == k)
            return 1;

        if (current_idx == C.size())
            return 0;

        int skip = backtrack(C, k, current_idx + 1, current_sum);
        int take = backtrack(C, k, current_idx + 1, current_sum + C[current_idx]);

        return skip + take;
    }
};

int main()
{
    Solution solution;

    int actual_1 = solution.subset_sum({6, 6, 12}, 12);
    int expected_1 = 2;
    assert(actual_1 == expected_1);

    int actual_2 = solution.subset_sum({6, 6, 12}, 13);
    int expected_2 = 0;
    assert(actual_2 == expected_2);

    return 0;
}
