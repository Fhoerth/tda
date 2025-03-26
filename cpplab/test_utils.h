#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#include <cassert>
#include <iostream>
#include <set>
#include <vector>

template <typename T> struct VectorComparator
{
    bool operator()(const std::vector<T> &a, const std::vector<T> &b) const { return a < b; }
};

template <typename T> void assert_set_equals(const std::vector<T> &vec1, const std::vector<T> &vec2)
{
    using Comparator =
        typename std::conditional<std::is_same<T, std::vector<typename T::value_type>>::value,
                                  VectorComparator<typename T::value_type>, std::less<T>>::type;

    std::set<T, Comparator> set1(vec1.begin(), vec1.end());
    std::set<T, Comparator> set2(vec2.begin(), vec2.end());

    if (vec1.size() != set1.size() || vec2.size() != set2.size())
    {
        std::cerr << "❌ assert_set_equals FAILED: sizes don't match!\n";
        assert(false);
    }

    if (set1 != set2)
    {
        std::cerr << "❌ assert_set_equals FAILED!\n";
        std::cerr << "Expected: { ";
        for (const auto &x : set1)
        {
            std::cerr << "{ ";
            for (const auto &elem : x)
                std::cerr << elem << " ";
            std::cerr << "} ";
        }
        std::cerr << "}\n";

        std::cerr << "Got: { ";
        for (const auto &x : set2)
        {
            std::cerr << "{ ";
            for (const auto &elem : x)
                std::cerr << elem << " ";
            std::cerr << "} ";
        }
        std::cerr << "}\n";

        assert(false);
    }
}

#endif // TEST_UTILS_H
