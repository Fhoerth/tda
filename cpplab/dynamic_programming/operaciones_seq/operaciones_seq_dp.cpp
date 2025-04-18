#include <cmath>
#include <iostream>
#include <string>
#include <vector>

#include <optional>
#include <utility>

#include "../../test_utils.h"
#include "./operaciones_seq.h"

using Index = int;
using Value = int;

void print_dp(const std::vector<std::optional<std::pair<Index, Value>>> &dp)
{
    std::cout << "[\n";
    for (std::size_t i = 0; i < dp.size(); ++i)
    {
        std::cout << "  " << i << ": ";
        if (dp[i].has_value())
        {
            auto [idx, val] = dp[i].value();
            std::cout << "(" << idx << ", " << val << ")";
        }
        else
        {
            std::cout << "nullopt";
        }
        std::cout << '\n';
    }
    std::cout << "]\n";
}

class Solution
{
  public:
    bool operaciones_seq(std::vector<int> v, int w)
    {
        std::vector<std::optional<std::pair<Index, Value>>> dp(w + 1, std::nullopt);

        std::pair<Index, Value> fst = std::make_pair(0, v[0]);
        dp[v[0]] = fst;

        for (int j = 0; j <= w; j += 1)
        {
            if (dp[j].has_value())
            {
                auto [idx, value] = dp[j].value();
                int next_idx = idx + 1;

                if (next_idx == v.size())
                {
                    continue;
                }

                int add_res = value + v[next_idx];
                int mult_res = value * v[next_idx];
                int pow_res = std::pow(value, v[next_idx]);

                if (add_res <= w)
                    dp[add_res] = std::make_pair(next_idx, add_res);

                if (mult_res <= w)
                    dp[mult_res] = std::make_pair(next_idx, mult_res);

                if (pow_res <= w)
                    dp[pow_res] = std::make_pair(next_idx, pow_res);
            }
        }

        return dp[w].has_value();
    }
};

int main()
{
    Solution solution;

    std::vector<int> v_1 = {3, 1, 5, 2, 1};
    int w_1 = 400;
    bool expected_1 = true;
    bool actual_1 = solution.operaciones_seq(v_1, w_1);
    assert(actual_1 == expected_1);

    std::vector<int> v_2(20, 1);
    int w_2 = 20;
    bool expected_2 = true;
    bool actual_2 = solution.operaciones_seq(v_2, w_2);
    assert(actual_2 == expected_2);

    std::vector<int> v_3(600, 2);
    int w_3 = 2001;
    bool expected_3 = false;
    bool actual_3 = solution.operaciones_seq(v_3, w_3);
    assert(actual_3 == expected_3);

    std::cout << "✅ Todos los tests pasaron" << std::endl;
}