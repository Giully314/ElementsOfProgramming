#ifndef NUMBER_HPP
#define NUMBER_HPP


#include <concepts> 
#include "algebraic_concepts.hpp"

namespace eop
{
    template <typename I>
    concept integer = std::same_as<long long, I> && std::same_as<int, I> && std::same_as<short, I>;


    struct Integer
    {
        template <integer I>
        static constexpr
        bool is_odd(I n)
        {
            return n & I{1};
        }

        template <integer I>
        static constexpr
        bool is_even(I n)
        {
            return !is_odd{n};
        }


        template <integer I>
        static constexpr
        I divide_by_2(I n)
        {
            return n >> I{1};
        }

        template <integer I>
        static constexpr
        I multiply_by_2(I n)
        {
            return n << I{1};
        }

        template <integer I>
        static constexpr
        I half_nonnegative(I n)
        {
            return n >> I{1};
        }


        template <integer I>
        static constexpr
        I half(I n)
        {
            return n / I{2};
        }


        template <integer I>
        static constexpr
        bool positive(I n)
        {
            return n > I{0};
        }

        template <integer I>
        static constexpr
        bool negative(I n)
        {
            return n < I{0};
        }

        template <integer I>
        static constexpr
        bool is_zero(I n)
        {
            return n == I{0};
        }

        template <integer I>
        static constexpr
        bool is_one(I n)
        {
            return n == I{1};
        }


        template <integer I>
        static constexpr
        I successor(I n)
        {
            return n + I{1};
        }

        // template <integer I>
        // static constexpr
        // I binary_scale_
        
        template <ordered_additive_semigroup I>
        static constexpr
        I abs(const I& n)
        {
            if (n < I{0}) return -n;
            return n;
        }


        template <totally_ordered N>
        static constexpr 
        [[nodiscard]]
        N max(N a, N b)
        {
            return a < b ? b : a;
        }

        template <totally_ordered N>
        static constexpr 
        [[nodiscard]]
        N min(N a, N b)
        {
            return b < a ? b : a;
        }
        
    };

}


#endif 