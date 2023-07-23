// EXERCISE 4.7


#include <array>
#include <utility>
#include <iostream>

#include "../type_concepts.hpp"
#include "../linear_ordering.hpp"


template <typename T, size_t N> 
constexpr std::array<T, N> all_equals(T x)
{
    std::array<T, N> a;
    a.fill(x);
    return a;
}

template <typename T, size_t N> 
constexpr std::array<std::pair<T, T>, N> all_equals()
{
    std::array<std::pair<T, T>, N> a;
    
    for (int i = 0, j = 1; i < N; ++i)
    {
        a[i] = std::make_pair(j, i);
    }

    return a;
}



constexpr 
void test_select_2()
{
    using namespace eop;

    constexpr auto a = all_equals<int, 2>();
    // a[1].second = 2;

    using type_el = std::pair<int, int>;
    auto cmp_less = [](const type_el& a, const type_el& b) -> bool
    {
        return a.first < b.first;   
    };

    auto cmp_greater = [](const type_el& a, const type_el& b) -> bool
    {
        return a.first > b.first;   
    };

    static_assert(a[0] == Ordering::select_0_2(a[0], a[1], cmp_less), "Select 0 2 failed");
    static_assert(a[1] == Ordering::select_1_2(a[0], a[1], cmp_less), "Select 1 2 failed");

    static_assert(a[0] == Ordering::select_0_2(a[0], a[1], cmp_greater), "Select 0 2 failed comp_greater");
    static_assert(a[1] == Ordering::select_1_2(a[0], a[1], cmp_greater), "Select 1 2 failed comp_greater");
}


constexpr 
void test_select_3()
{
    using namespace eop;
    
    constexpr auto a = all_equals<int, 3>();

    using type_el = std::pair<int, int>;
    auto cmp_less = [](const type_el& a, const type_el& b) -> bool
    {
        return a.first < b.first;   
    };

    auto cmp_greater = [](const type_el& a, const type_el& b) -> bool
    {
        return a.first > b.first;   
    };

    static_assert(a[0] == Ordering::select_0_3(a[0], a[1], a[2], cmp_less), "Select 0 3 failed cmp_less");
    static_assert(a[1] == Ordering::select_1_3(a[0], a[1], a[2], cmp_less), "Select 1 3 failed cmp_less");
    static_assert(a[2] == Ordering::select_2_3(a[0], a[1], a[2], cmp_less), "Select 2 3 failed cmp_less");

    static_assert(a[0] == Ordering::select_0_3(a[0], a[1], a[2], cmp_greater), "Select 0 3 failed cmp_greater");
    static_assert(a[1] == Ordering::select_1_3(a[0], a[1], a[2], cmp_greater), "Select 1 3 failed cmp_greater");
    static_assert(a[2] == Ordering::select_2_3(a[0], a[1], a[2], cmp_greater), "Select 2 3 failed cmp_greater");
}


constexpr
void test_select_4()
{
    using namespace eop;
    
    constexpr auto a = all_equals<int, 4>();

    using type_el = std::pair<int, int>;
    auto cmp_less = [](const type_el& a, const type_el& b) -> bool
    {
        return a.first < b.first;   
    };

    auto cmp_greater = [](const type_el& a, const type_el& b) -> bool
    {
        return a.first > b.first;   
    };


    static_assert(a[1] == Ordering::select_1_4(a[0], a[1], a[2], a[3], cmp_less), "Select 1 4 failed cmp_less");
    static_assert(a[1] == Ordering::select_1_4(a[0], a[1], a[2], a[3], cmp_less), "Select 1 4 failed cmp_less");
    static_assert(a[1] == Ordering::select_1_4(a[0], a[1], a[2], a[3], cmp_less), "Select 1 4 failed cmp_less");
    static_assert(a[1] == Ordering::select_1_4(a[0], a[1], a[2], a[3], cmp_less), "Select 1 4 failed cmp_less");

    static_assert(a[1] == Ordering::select_1_4(a[0], a[1], a[2], a[3], cmp_greater), "Select 1 4 failed cmp_greater");
    static_assert(a[1] == Ordering::select_1_4(a[0], a[1], a[2], a[3], cmp_greater), "Select 1 4 failed cmp_greater");
    static_assert(a[1] == Ordering::select_1_4(a[0], a[1], a[2], a[3], cmp_greater), "Select 1 4 failed cmp_greater");
    static_assert(a[1] == Ordering::select_1_4(a[0], a[1], a[2], a[3], cmp_greater), "Select 1 4 failed cmp_greater");
}


constexpr
void test_select_5()
{
    using namespace eop;
    
    constexpr auto a = all_equals<int, 5>();

    using type_el = std::pair<int, int>;
    auto cmp_less = [](const type_el& a, const type_el& b) -> bool
    {
        return a.first < b.first;   
    };

    auto cmp_greater = [](const type_el& a, const type_el& b) -> bool
    {
        return a.first > b.first;   
    };


    static_assert(a[2] == Ordering::median_5(a[0], a[1], a[2], a[3], a[4], cmp_less), "Median 5 failed cmp_less");
    static_assert(a[2] == Ordering::median_5(a[0], a[1], a[2], a[3], a[4], cmp_less), "Median 5 failed cmp_less");
    static_assert(a[2] == Ordering::median_5(a[0], a[1], a[2], a[3], a[4], cmp_less), "Median 5 failed cmp_less");
    static_assert(a[2] == Ordering::median_5(a[0], a[1], a[2], a[3], a[4], cmp_less), "Median 5 failed cmp_less");

    static_assert(a[2] == Ordering::median_5(a[0], a[1], a[2], a[3], a[4], cmp_greater), "Median 5 failed cmp_greater");
    static_assert(a[2] == Ordering::median_5(a[0], a[1], a[2], a[3], a[4], cmp_greater), "Median 5 failed cmp_greater");
    static_assert(a[2] == Ordering::median_5(a[0], a[1], a[2], a[3], a[4], cmp_greater), "Median 5 failed cmp_greater");
    static_assert(a[2] == Ordering::median_5(a[0], a[1], a[2], a[3], a[4], cmp_greater), "Median 5 failed cmp_greater");
}


int main()
{
    test_select_2();
    test_select_3();
    test_select_4();
    test_select_5();

    return 0;
}