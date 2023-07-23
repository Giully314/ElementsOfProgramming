#pragma once


/*
algebraic_operations.hpp

PURPOSE:

OPERATORS:

DESCRIPTION:

*/


#include "type_concepts.hpp"


namespace eop
{

    // The + operator is usually used to specify that the binary operation is associative and commutative.
    template <regular T>
    struct plus
    {
        T operator+(const T& a, const T& b)
        {
            return a + b;
        }
    };


    // The * operator is usually used to specify that the binary operation is associative.
    template <regular T>
    struct multiply
    {
        T operator*(const T& a, const T& b)
        {
            return a * b;
        }
    };


    template <regular T>
    struct minus
    {
        T operator-(const T& a, const T& b)
        {
            return a - b;
        }

        T operator-(const T& a)
        {
            return -a;
        }

        T inverse(const T& a)
        {
            return operator-(a);
        }
    };


    template <regular T>
    struct divide
    {
        T operator/(const T& a, const T& b)
        {
            return a / b;
        }

        T inverse(const T& a)
        {
            return 1 / a;
        }
    };

} // namespace eop
