#include <cassert>
#include <iostream>
#include <vector>

struct BacktrackState
{
    int n;
    int current_idx = 0;

    std::vector<int> row_sum;
    std::vector<int> column_sum;
    std::vector<std::vector<int>> current_solution;

    int main_diagonal_sum = 0;
    int anti_diagonal_sum = 0;

    int magic_constant = 0;

    BacktrackState(int n_)
        : n(n_), row_sum(n_, 0), column_sum(n_, 0), current_solution(n_, std::vector<int>(n_, 0))
    {
        int value = 1;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                current_solution[i][j] = value++;

        magic_constant = (n * n * n + n) / 2;
    }
};

void print_matrix(const std::vector<std::vector<int>> &matrix)
{
    for (const auto &row : matrix)
    {
        for (int val : row)
        {
            std::cout << val << "\t";
        }
        std::cout << "\n";
    }
    std::cout << "----------------------\n";
}

class Solution
{
  public:
    int magi_cuadrados(const int n)
    {
        BacktrackState backtrack_state(n);
        return backtrack(backtrack_state);
    }

  private:
    void swap(int n, std::vector<std::vector<int>> &current_solution, int current_idx, int next_idx)
    {
        auto [i1, j1] = to_ij(n, current_idx);
        auto [i2, j2] = to_ij(n, next_idx);
        int tmp = current_solution[i1][j1];
        current_solution[i1][j1] = current_solution[i2][j2];
        current_solution[i2][j2] = tmp;
    }

    std::pair<int, int> to_ij(int n, int idx) { return {idx / n, idx % n}; }

    bool is_st_valid(BacktrackState &st)
    {
        auto [i, j] = to_ij(st.n, st.current_idx);

        bool is_in_main_diagonal = i == j;
        bool is_in_anti_diagonal = i + j == st.n - 1;

        bool completes_row = j == st.n - 1;
        bool completes_col = i == st.n - 1;
        bool completes_main_diag = is_in_main_diagonal && i == st.n - 1;
        bool completes_anti_diag = is_in_anti_diagonal && i == st.n - 1;

        return st.row_sum[i] <= st.magic_constant &&
               (!completes_row || st.row_sum[i] == st.magic_constant) &&
               st.column_sum[j] <= st.magic_constant &&
               (!completes_col || st.column_sum[j] == st.magic_constant) &&
               st.main_diagonal_sum <= st.magic_constant &&
               (!completes_main_diag || st.main_diagonal_sum == st.magic_constant) &&
               st.anti_diagonal_sum <= st.magic_constant &&
               (!completes_anti_diag || st.anti_diagonal_sum == st.magic_constant);
    }

    void update_sums(BacktrackState &st, int factor)
    {
        auto [i, j] = to_ij(st.n, st.current_idx);
        int value = st.current_solution[i][j] * factor;

        bool is_in_main_diagonal = i == j;
        bool is_in_anti_diagonal = i + j == st.n - 1;

        st.row_sum[i] += value;
        st.column_sum[j] += value;

        if (is_in_main_diagonal)
            st.main_diagonal_sum += value;

        if (is_in_anti_diagonal)
            st.anti_diagonal_sum += value;
    }

    int backtrack(BacktrackState &st)
    {
        if (st.current_idx == st.n * st.n)
        {
            print_matrix(st.current_solution);
            return 1;
        }

        int total = 0;

        for (int next_idx = st.current_idx; next_idx < st.n * st.n; next_idx += 1)
        {
            swap(st.n, st.current_solution, st.current_idx, next_idx);
            update_sums(st, 1);

            if (is_st_valid(st))
            {
                st.current_idx++;
                total += backtrack(st);
                st.current_idx--;
            }

            update_sums(st, -1);
            swap(st.n, st.current_solution, st.current_idx, next_idx);
        }

        return total;
    }
};

int main()
{
    Solution solution;
    int actual_1 = solution.magi_cuadrados(3);
    std::cout << "Actual_1: " << actual_1 << std::endl;
    return 0;
}
