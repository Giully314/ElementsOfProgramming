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



    struct GCD
    {
        // Note that this algorithm doesn't terminate for real numbers.
        // Precondition: a > 0 and b > 0.
        template <archimedean_monoid T>
        T subtractive_gcd_nonzero(T a, T b)
        {
            while (true)
            {
                if (b < a) 
                {
                    a = a - b;
                }
                else if (a < b)
                {
                    b = b - a;
                }
                else
                {
                    return a;
                }
            }
        }


        // Precondition: a >= 0 && b >= 0 && !(a = 0 && b = 0)
        template <euclidean_monoid T>
        T subtractive_gcd(T a, T b)
        {
            while (true)
            {
                if (b == T{0}) 
                {
                    return a;
                }
                
                while (b <= a)
                {
                    a = a - b;
                }

                if (a == T{0})
                {
                    return b;
                }

                while (a <= b)
                {
                    b = b - a;
                }
            }
        }


        // Using remainder_nonnegative it's faster for log complexity instead of linear.
        // Precondition: a >= 0 && b >= 0 && !(a = 0 && b = 0)
        template <euclidean_monoid T>
        T fast_subtractive_gcd(T a, T b)
        {
            while (true)
            {
                if (b == T{0}) 
                {
                    return a;
                }
                
                a = Remainder::remainder_nonnegative(a, b);

                if (a == T{0})
                {
                    return b;
                }

                b = Remainder::remainder_nonnegative(b, a);
            }
        }


        
    };

} // namespace eop
