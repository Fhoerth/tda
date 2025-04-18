#include <cmath>
#include <iostream>
#include <string>
#include <vector>

#include "../../test_utils.h"
#include "./operaciones_seq.h"

class Solution
{
  public:
    bool operaciones_seq(std::vector<int> v, int w) { return backtrack(v, w, 1, v[0]); }

  private:
    bool backtrack(std::vector<int> &v, int w, int current_idx, int acc)
    {
        if (current_idx == v.size())
        {
            if (acc == w)
                return true;
            return false;
        }

        if (backtrack(v, w, current_idx + 1, std::pow(acc, v[current_idx])) ||
            backtrack(v, w, current_idx + 1, acc * v[current_idx]) ||
            backtrack(v, w, current_idx + 1, acc + v[current_idx]))
            return true;

        return false;
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

    std::cout << "✅ Todos los tests pasaron" << std::endl;
}