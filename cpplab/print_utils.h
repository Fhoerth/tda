#ifndef PRINT_UTILS_H
#define PRINT_UTILS_H

#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

inline void print_int_matrix(const std::vector<std::vector<int>> &matrix)
{
    const int cell_width = 5;
    for (const auto &row : matrix)
    {
        for (const auto &val : row)
        {
            if (val >= 1e9)
                std::cout << std::left << std::setw(cell_width) << "inf";
            else
                std::cout << std::left << std::setw(cell_width) << val;
        }
        std::cout << "\n";
    }
}

inline void print_path(const std::vector<int> &path)
{
    for (size_t i = 0; i < path.size(); ++i)
    {
        std::cout << path[i];
        if (i + 1 < path.size())
            std::cout << " -> ";
    }
    std::cout << "\n";
}

inline void print_int_vector(const std::vector<int> &vc)
{
    for (const auto &val : vc)
        std::cout << val << " " << val;
    std::cout << "\n";
}

inline void print_bool_vector(const std::vector<bool> &vc)
{
    for (const auto &val : vc)
        std::cout << std::setw(5) << val;
    std::cout << "\n";
}

#endif // PRINT_UTILS_H
