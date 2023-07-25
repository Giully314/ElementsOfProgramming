#pragma once


/*
division.hpp

PURPOSE:


*/
#include "type_traits.hpp"
#include "algebraic_concepts.hpp"
#include "number.hpp"

namespace eop
{
    struct Remainder
    {
        // Precondition: a >= 0 && b > 0
        template <cancellable_monoid T>
        static constexpr
        T slow_remainder(T a, T b)
        {
            while (b <= a)
            {
                a = a - b;
            }

            return a;
        }

        // Precondition: a >= 0 && b > 0
        template <archimedean_monoid T>
        static constexpr
        T slow_quotient(T a, T b)
        {
            quotient_type_t<T> n{0};
            while (b <= a)
            {
                a = a - b;
                n = Integer::successor(n);
            }

            return n;
        }

        // Precondition: a >= 0 && b > 0
        template <archimedean_monoid T>
        static constexpr
        T remainder_recursive(T a, T b)
        {
            // Testing a - b >= b instaed of a >= b + b avoid overflow of b + b
            if (a - b >= b)
            {
                a = remainder_recursive(a, b + b);
                if (a < b) return a;
            }
            return a - b;
        }


        // Precondition: a >= 0 && b > 0
        template <archimedean_monoid T>
        static constexpr
        T remainder_nonnegative(T a, T b)
        {
            if (a < b) return a;
            return remainder_recursive(a, b);
        }


        // Precondition: a >= 0 && b > 0
        template <archimedean_monoid T>
        T largest_doubling(T a, T b)
        {
            while (b <= a - b)
            {
                b = b + b;
            }
            return b;
        }


        // Precondition: a >= 0 && b > 0
        template <halvable_monoid T>
        static constexpr
        T remainder_nonnegative_iterative(T a, T b)
        {
            if (a < b) return a;
            T c = largest_doubling(a, b);
            a = a - c;
            while (c != b)
            {
                c = Integer::half(c);
                if (c <= a)
                {
                    a = a - c;
                }
            }
            return a;
        }
    };

} // namespace eop
