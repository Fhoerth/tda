#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#include <array>
#include <cassert>
#include <iostream>
#include <set>
#include <type_traits>
#include <vector>

// Comparador especial para vector<vector<T>> o vector<array<T,N>>
template <typename T> struct VectorComparator
{
    bool operator()(const T &a, const T &b) const { return a < b; }
};

// Detectar si un tipo es iterable (tiene begin() y end())
template <typename T, typename = void> struct is_iterable : std::false_type
{
};

template <typename T>
struct is_iterable<
    T, std::void_t<decltype(std::declval<T>().begin()), decltype(std::declval<T>().end())>>
    : std::true_type
{
};

// Imprimir elementos no iterables (int, string, etc.)
template <typename T>
typename std::enable_if<!is_iterable<T>::value>::type print_element(const T &x)
{
    std::cerr << x << " ";
}

// Imprimir elementos iterables (vector, array, etc.)
template <typename T> typename std::enable_if<is_iterable<T>::value>::type print_element(const T &x)
{
    std::cerr << "{ ";
    for (const auto &elem : x)
        print_element(elem);
    std::cerr << "} ";
}

// assert_set_equals para tipos no iterables (como vector<int>)
template <typename T>
typename std::enable_if<!is_iterable<T>::value>::type assert_set_equals(const std::vector<T> &vec1,
                                                                        const std::vector<T> &vec2)
{
    std::set<T> set1(vec1.begin(), vec1.end());
    std::set<T> set2(vec2.begin(), vec2.end());

    if (set1 != set2)
    {
        std::cerr << "❌ assert_set_equals FAILED!\n";
        std::cerr << "Expected: { ";
        for (const auto &x : set2)
            std::cerr << x << " ";
        std::cerr << "}\nGot: { ";
        for (const auto &x : set1)
            std::cerr << x << " ";
        std::cerr << "}\n";
        assert(false);
    }
}

// assert_set_equals para tipos iterables (como vector<vector<int>>, vector<array<int,N>>)
template <typename T>
typename std::enable_if<is_iterable<T>::value>::type assert_set_equals(const std::vector<T> &vec1,
                                                                       const std::vector<T> &vec2)
{
    std::set<T, VectorComparator<T>> set1(vec1.begin(), vec1.end());
    std::set<T, VectorComparator<T>> set2(vec2.begin(), vec2.end());

    if (set1 != set2)
    {
        std::cerr << "❌ assert_set_equals FAILED!\n";
        std::cerr << "Expected: ";
        for (const auto &x : set2)
            print_element(x);
        std::cerr << "\nGot: ";
        for (const auto &x : set1)
            print_element(x);
        std::cerr << "\n";
        assert(false);
    }
}

#endif // TEST_UTILS_H
