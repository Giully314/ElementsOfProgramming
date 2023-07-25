#pragma once


/*
ordering_operations.hpp
*/



namespace eop
{
    template <typename T>
    struct less
    {
        bool operator<(T a, T b)
        {
            return a < b;
        }
    };

    template <typename T>
    struct less_or_equal
    {
        bool operator<(T a, T b)
        {
            return a <= b;
        }
    };

    template <typename T>
    struct greater
    {
        bool operator<(T a, T b)
        {
            return a > b;
        }
    };

    template <typename T>
    struct greater_or_equal
    {
        bool operator<(T a, T b)
        {
            return a >= b;
        }
    };

    
} // namespace eop
