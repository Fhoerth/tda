#include <cassert>
#include <iostream>

class Solution
{

  public:
    int cd(const std::vector<int> &p, int t) { return backtrack(p, t, 0); }

  private:
    int backtrack(const std::vector<int> &p, int t, int i)
    {
        if (t < 0)
            return std::numeric_limits<int>::min();

        if (i == p.size())
            return 0;

        int skip = backtrack(p, t, i + 1);
        int take = backtrack(p, t - p[i], i + 1) + p[i];

        return std::max(skip, take);
    }
};

int main()
{
    Solution solution;

    int actual_1 = solution.cd({3, 4, 4}, 10);
    int expected_1 = 8;
    assert(actual_1 == expected_1);

    int actual_2 = solution.cd({3, 4, 4, 8}, 12);
    int expected_2 = 12;
    assert(actual_2 == expected_2);

    return 0;
}
