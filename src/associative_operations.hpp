#ifndef ASSOCIATIVE_OPERATIONS_HPP
#define ASSOCIATIVE_OPERATIONS_HPP


/*
associative_operations.hpp

PURPOSE:



*/

#include <concepts> 

#include "utility_concepts.hpp"
#include "function_concepts.hpp"
#include "type_traits.hpp"
#include "number.hpp"

namespace eop
{
    struct AssociativeOp
    {

        //TODO: strictly tail recursive, can be transformed into iterative.
        template <typename I, typename Op>
            requires integer<I> && binary_operation<Op>
        static constexpr
        domain_t<Op> power_left_associated(domain_t<Op> a, I n, Op op)
        {
            if (n == I(1)) return a;
            return op(power_left_associated(a, n - I(1), op), a);
        }

        //TODO: strictly tail recursive, can be transformed into iterative.
        template <typename I, typename Op>
            requires integer<I> && binary_operation<Op>
        static constexpr
        domain_t<Op> power_right_associated(domain_t<Op> a, I n, Op op)
        {
            if (n == I(1)) return a;
            return op(a, power_left_associated(a, n - I(1), op));
        }


        /*
        We start with the basic power recursive algorithm.
        */
        // Precondition: n > 0.
        template <typename I, typename Op>
            requires integer<I> && associative_operation<Op>
        static constexpr
        domain_t<Op> power_0(domain_t<Op> a, I n, Op op)
        {
            if (n == I(1)) return a;
            if (Integer::is_even(n))
            {
                return power_0(op(a, a), n / I(2), op);
            }
            return op(power_0(op(a, a), n / I(2), op), a);
        }


        /*
        Then we see that the 2 recursive cases are similar except for one application of op.
        Just compute only recursive call and check the condition to apply op one time.
        */
        // Precondition: n > 0.
        template <typename I, typename Op>
            requires integer<I> && associative_operation<Op>
        static constexpr
        domain_t<Op> power_1(domain_t<Op> a, I n, Op op)
        {
            if (n == I(1)) return a;

            domain_t<Op> r = return power_1(op(a, a), n / I(2), op);
            if (!Integer::is_even(n))
            {
                r = op(r, a);
            }
            return r;
        }


        /*
        Using an accumulator, we can transform the previous recursive function into a tail recursive,
        where the recursion is only at the end of the function.
        */
        // Precondition: n >= 0.
        template <typename I, typename Op>
            requires integer<I> && associative_operation<Op>
        static constexpr
        domain_t<Op> power_accumulate_0(domain_t<Op> r, domain_t<Op> a, I n, Op op)
        {
            if (n == I(0)) return r;
            
            if (!Integer::is_even(n))
            {
                r = op(r, a);
            }
            return power_accumulate_0(r, op(a, a), n / I(2), op);
        }


        /*
        Add a condition for n == 1 to avoid a square computation (op(a, a)) when n goes from 1 to 0.
        */
        // Precondition: n >= 0.
        template <typename I, typename Op>
            requires integer<I> && associative_operation<Op>
        static constexpr
        domain_t<Op> power_accumulate_1(domain_t<Op> r, domain_t<Op> a, I n, Op op)
        {
            if (n == I(0)) return r;
            if (n == I(1)) return op(r, a);

            if (!Integer::is_even(n))
            {
                r = op(r, a);
            }
            return power_accumulate_1(r, op(a, a), n / I(2), op);
        }


        /*
        Check for cases dependency, in this case n == 1 and n is odd are dependent.
        Reorder the cases based on expected frequency.
        */
        // Precondition: n >= 0.
        template <typename I, typename Op>
            requires integer<I> && associative_operation<Op>
        static constexpr
        domain_t<Op> power_accumulate_2(domain_t<Op> r, domain_t<Op> a, I n, Op op)
        {
            if (!Integer::is_even(n))
            {
                r = op(r, a);
                if (n == I(1)) return r;
            }
            else if (n == I(0)) return r;

            return power_accumulate_2(r, op(a, a), n / I(2), op);
        }


        /*
        A stricly tail-recursive function is one in which all the tail-recursive calls are done with
        the formal parameters of the function being the corresponding arguments.
        Compute a^2 and n in place and pass them to the function.
        */
        // Precondition: n >= 0.
        template <typename I, typename Op>
            requires integer<I> && associative_operation<Op>
        static constexpr
        domain_t<Op> power_accumulate_3(domain_t<Op> r, domain_t<Op> a, I n, Op op)
        {
            if (!Integer::is_even(n))
            {
                r = op(r, a);
                if (n == I(1)) return r;
            }
            else if (n == I(0)) return r;

            a = op(a, a);
            n = n / I(2);

            return power_accumulate_3(r, a, n, op);
        }


        /*
        A strictly tail-recursive function can be transformed in an iterative function with a goto
        to the start of the function. In this case we use a loop.
        */
        // Precondition: n >= 0.
        template <typename I, typename Op>
            requires integer<I> && associative_operation<Op>
        static constexpr
        domain_t<Op> power_accumulate_4(domain_t<Op> r, domain_t<Op> a, I n, Op op)
        {
            while (true)
            {
                if (!Integer::is_even(n))
                {
                    r = op(r, a);
                    if (n == I(1)) return r;
                }
                else if (n == I(0)) return r;

                a = op(a, a);
                n = n / I(2);
            }
        }


        // Precondition: n > 0.
        template <typename I, typename Op>
            requires integer<I> && associative_operation<Op>
        static constexpr
        domain_t<Op> power_accumulate_positive_0(domain_t<Op> r, domain_t<Op> a, I n, Op op)
        {
            while (true)
            {
                if (!Integer::is_even(n))
                {
                    r = op(r, a);
                    if (n == I(1)) return r;
                }

                a = op(a, a);
                n = n / I(2);
            }
        }


        // Precondition: n >= 0.
        template <typename I, typename Op>
            requires integer<I> && associative_operation<Op>
        static constexpr
        domain_t<Op> power_accumulate_5(domain_t<Op> r, domain_t<Op> a, I n, Op op)
        {
            if (n == I(0)) return r;
            return power_accumulate_4(r, a, n, op);
        }


        // Precondition: n > 0.
        template <typename I, typename Op>
            requires integer<I> && associative_operation<Op>
        static constexpr
        domain_t<Op> power_2(domain_t<Op> a, I n, Op op)
        {
            return power_accumulate_5(a, a, n - I(1), op);
        }


        /*
        Because the algorithm power_accumulate is based on the number of 1's in n, we can make it optimal
        passing an odd number. Do a precomputation until n is even and then call power_accumulate.
        */
        // Precondition: n > 0.
        template <typename I, typename Op>
            requires integer<I> && associative_operation<Op>
        static constexpr
        domain_t<Op> power_3(domain_t<Op> a, I n, Op op)
        {
            while (Integer::is_even(n))
            {
                a = op(a, a);
                n = n / I(2);
            }
            
            n = n / I(2);
            if (n == I(0)) return a;
            return power_accumulate_positive_0(a, op(a, a), n, op);
        }


        // Precondition: positive(n).
        template <integer I, associative_operation Op>
        static constexpr
        domain_t<Op> power_accumulate_positive(domain_t<Op> r, domain_t<Op> a, I n, Op op)
        {
            while (true)
            {
                if (Integer::is_odd(n))
                {
                    r = op(r, a);
                    if (Integer::is_one(n)) return r;
                }
                a = op(a, a);
                n = Integer::half_nonnegative(n);
            }
        }


        // Precondition: !negative(n).
        template <integer I, associative_operation Op>
        static constexpr
        domain_t<Op> power_accumulate(domain_t<Op> r, domain_t<Op> a, I n, Op op)
        {
            if (Integer::is_zero(n)) return r;
            return power_accumulate_positive(r, a, n , op);
        }


        // Precondition: positive(n).
        template <integer I, associative_operation Op>
        static constexpr
        domain_t<Op> power(domain_t<Op> a, I n, Op op)
        {
            while (Integer::is_even(n))
            {
                a = op(a, a);
                n = Integer::half_nonnegative(n);
            }
            n = Integer::half_nonnegative(n);
            if (Integer::is_zero(n)) return a;
            return power_accumulate_positive(a, op(a, a), n, op);
        }


        // Precondition: !negative(n).
        template <integer I, associative_operation Op>
        static constexpr
        domain_t<Op> power(domain_t<Op> a, I n, Op op, domain_t<Op> id)
        {
            if (Integer::is_zero(n)) return id;
            return power(a, n, op);
        }

    };


} // namespace eop




#endif