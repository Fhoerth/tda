#include <cassert>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

#include "../../test_utils.h"
#include "./operaciones_seq.h"

class Solution
{
  public:
    std::vector<std::string> operaciones_seq(std::vector<int> v, int w)
    {
        std::vector<std::string> result;

        std::vector<std::vector<Op>> solutions;
        std::vector<Op> current_solution;

        backtrack(v, w, solutions, current_solution, 1, v[0]);

        for (int j = 0; j < solutions.size(); j += 1)
            result.push_back(build_expression(v, solutions[j]));

        return result;
    }

  private:
    void backtrack(std::vector<int> &v, int w, std::vector<std::vector<Op>> &solutions,
                   std::vector<Op> &current_solution, int current_idx, int acc)
    {
        if (current_idx == v.size())
        {
            if (acc == w)
                solutions.push_back(current_solution);
            return;
        }

        current_solution.push_back(Op::Pow);
        backtrack(v, w, solutions, current_solution, current_idx + 1,
                  std::pow(acc, v[current_idx]));
        current_solution.pop_back();

        current_solution.push_back(Op::Mul);
        backtrack(v, w, solutions, current_solution, current_idx + 1, acc * v[current_idx]);
        current_solution.pop_back();

        current_solution.push_back(Op::Add);
        backtrack(v, w, solutions, current_solution, current_idx + 1, acc + v[current_idx]);
        current_solution.pop_back();
    }
};

int main()
{
    Solution solution;

    std::vector<int> v_1 = {3, 1, 5, 2, 1};
    int w_1 = 400;
    std::vector<std::string> actual_1 = solution.operaciones_seq(v_1, w_1);
    std::vector<std::string> expected_1 = {"((((3+1)*5)^2)*1)", "((((3+1)*5)^2)^1)"};
    assert_set_equals(actual_1, expected_1);

    std::vector<int> v_2(20, 1);
    int w_2 = 20;
    std::vector<std::string> actual_2 = solution.operaciones_seq(v_2, w_2);
    std::vector<std::string> expected_2 = {
        "(((((((((((((((((((1+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)"};
    assert_set_equals(actual_2, expected_2);

    std::cout << "✅ Todos los tests pasaron" << std::endl;
}