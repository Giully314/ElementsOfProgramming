#pragma once


/*
relation_concepts.hpp
*/

#include <concepts>

namespace eop
{
    template <typename T>
    concept has_greater_op = requires (T a, T b)
    {
        {a > b} -> std::same_as<bool>;
    };

    template <typename T>
    concept has_greater_or_equal_op = requires (T a, T b)
    {
        {a >= b} -> std::same_as<bool>;
    };

    template <typename T>
    concept has_less_op = requires (T a, T b)
    {
        {a < b} -> std::same_as<bool>;
    };

    template <typename T>
    concept has_less_or_equal_op = requires (T a, T b)
    {
        {a <= b} -> std::same_as<bool>;
    };

    template <typename T>
    concept has_equal_op = requires (T a, T b)
    {
        {a == b} -> std::same_as<bool>;
    };

    template <typename T>
    concept has_not_equal_op = requires (T a, T b)
    {
        {a != b} -> std::same_as<bool>;
    };

} // namespace eop
