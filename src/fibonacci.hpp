#ifndef FIBONACCI_HPP
#define FIBONACCI_HPP


#include "pair.hpp"
#include "number.hpp"
#include "associative_operations.hpp"

namespace eop
{
    struct Fib
    {
        template <integer I>
        static constexpr
        Pair<I, I> matrix_multiply(const Pair<I, I>& x, const Pair<I, I>& y)
        {
            return Pair<I, I>{
                x.first * (y.second + y.first) + x.second * y.first,
                x.first * y.first + x.second * y.second
            };
        }


        template <typename I>
        static constexpr
        I fibonacci(I n)
        {
            if (n == I(0)) return 0;
            return AssociativeOp::power(Pair<I, I>{I(1), I(0)},
                n,
                matrix_multiply<I>
            ).first;
        }
    };

} // namespace eop


#endif 