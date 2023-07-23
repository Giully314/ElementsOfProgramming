#ifndef NUMBER_HPP
#define NUMBER_HPP


#include <concepts> 

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
            return n & I(1);
        }

        template <integer I>
        static constexpr
        bool is_even(I n)
        {
            return !is_odd(n);
        }


        template <integer I>
        static constexpr
        I divide_by_2(I n)
        {
            return n >> I(1);
        }

        template <integer I>
        static constexpr
        I multiply_by_2(I n)
        {
            return n << I(1);
        }

        template <integer I>
        static constexpr
        I half_nonnegative(I n)
        {
            return n >> I(1);
        }


        template <integer I>
        static constexpr
        bool positive(I n)
        {
            return n > I(0);
        }

        template <integer I>
        static constexpr
        bool negative(I n)
        {
            return n < I(0);
        }

        template <integer I>
        static constexpr
        bool is_zero(I n)
        {
            return n == I(0);
        }

        template <integer I>
        static constexpr
        bool is_one(I n)
        {
            return n == I(1);
        }


        // template <integer I>
        // static constexpr
        // I binary_scale_
        

    };

}


#endif 