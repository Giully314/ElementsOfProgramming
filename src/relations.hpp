#pragma once



/*
relations.hpp
*/

#include "relation_concepts.hpp"

namespace eop
{
    template <typename T>
        requires has_less_op<T>
    struct less
    {
        bool operator<(T a, T b)
        {
            return a < b;
        }
    };


    template <typename T>
        requires has_less_or_equal_op<T>
    struct less_or_equal
    {
        bool operator<(T a, T b)
        {
            return a <= b;
        }
    };


    template <typename T>
        requires has_greater_op<T>
    struct greater
    {
        bool operator<(T a, T b)
        {
            return a > b;
        }
    };


    template <typename T>
        requires has_greater_or_equal_op<T>
    struct greater_or_equal
    {
        bool operator<(T a, T b)
        {
            return a >= b;
        }
    };


    template <typename T>
        requires has_equal_op<T>
    struct equal
    {
        bool operator==(T a, T b)
        {
            return a == b;
        }
    };


    template <typename T>
        requires has_not_equal_op<T>
    struct not_equal
    {
        bool operator!=(T a, T b)
        {
            return a != b;
        }
    };
} // namespace eop
