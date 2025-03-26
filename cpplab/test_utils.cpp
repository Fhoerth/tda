#include <cassert>
#include <iostream>
#include <set>
#include <vector>

template <typename T> void assert_set_equals(const std::vector<T> &vec1, const std::vector<T> &vec2)
{
    std::set<T> set1(vec1.begin(), vec1.end());
    std::set<T> set2(vec2.begin(), vec2.end());

    if (set1 != set2)
    {
        std::cerr << "❌ assert_set_equals FAILED!\n";
        std::cerr << "Expected: { ";
        for (const auto &x : set1)
            std::cerr << x << " ";
        std::cerr << "}\n";

        std::cerr << "Got: { ";
        for (const auto &x : set2)
            std::cerr << x << " ";
        std::cerr << "}\n";

        assert(false); // Corta el programa si los sets no son iguales
    }
}