#pragma once

/*
algorithms.hpp
*/


#include <concepts>
#include "iterator_concepts.hpp"
#include "function_concepts.hpp"
#include "type_traits.hpp"
#include "relations.hpp"

namespace eop
{
    // Precondition: readable_bounded_range(f, l)
    template <readable_iterator I, unary_procedure Proc> 
        requires std::same_as<domain_t<Proc>, value_type_t<I>>
    constexpr
    Proc for_each(I f, I l, Proc proc)
    {
        while (f != l)
        {
            proc(*f++);
        }
        return proc;
    }


    // Precondition: readable_bounded_range(f, l)
    // TODO: should value_type_t be enforced as comparable?
    template <readable_iterator I>
    constexpr
    I find(I f, I l, const value_type_t<I>& x)
    {
        while (f != l && *f != x)
        {
            ++f;
        }

        return f;
    }

    // Precondition: readable_bounded_range(f, l)
    // TODO: should value_type_t be enforced as comparable?
    template <readable_iterator I>
    constexpr
    I find_not(I f, I l, const value_type_t<I>& x)
    {
        while (f != l && *f == x)
        {
            ++f;
        }

        return f;
    }


    // Precondition: readable_bounded_range(f, l)
    template <readable_iterator I, unary_predicate P>
        requires std::same_as<domain_t<P>, value_type_t<I>>
    constexpr
    I find_if(I f, I l, P p)
    {
        while (f != l && !p(*f))
        {
            ++f;
        }
        return f;
    }

    // Precondition: readable_bounded_range(f, l)
    template <readable_iterator I, unary_predicate P>
        requires std::same_as<domain_t<P>, value_type_t<I>>
    constexpr
    I find_if_not(I f, I l, P p)
    {
        while (f != l && p(*f))
        {
            ++f;
        }
        return f;
    }


    // Precondition: readable_bounded_range(f, l)
    template <readable_iterator I, unary_predicate P>
        requires std::same_as<domain_t<P>, value_type_t<I>>
    constexpr
    bool all(I f, I l, P p)
    {
        I r = find_if_not(f, l, p);
        return r == l;
    }

    // Precondition: readable_bounded_range(f, l)
    template <readable_iterator I, unary_predicate P>
        requires std::same_as<domain_t<P>, value_type_t<I>>
    constexpr
    bool not_all(I f, I l, P p)
    {
        return !all(f, l, p);
    }

    // Precondition: readable_bounded_range(f, l)
    template <readable_iterator I, unary_predicate P>
        requires std::same_as<domain_t<P>, value_type_t<I>>
    constexpr
    bool none(I f, I l, P p)
    {
        I r = find_if(f, l, p);
        return r == l;
    }

    // Precondition: readable_bounded_range(f, l)
    template <readable_iterator I, unary_predicate P>
        requires std::same_as<domain_t<P>, value_type_t<I>>
    constexpr
    bool some(I f, I l, P p)
    {
        return !none(f, l, p);
    }


    // Precondition: readable_bounded_range(f, l)
    template <readable_iterator I, unary_predicate P, iterator J>
        requires std::same_as<domain_t<P>, value_type_t<I>>
    constexpr
    J count_if(I f, I l, P p, J j)
    {
        while (f != l)
        {
            if (p(*f))
            {
                ++j;
            }
            ++f;
        }
        return j;
    }

    // Precondition: readable_bounded_range(f, l)
    template <readable_iterator I, unary_predicate P, iterator J>
        requires std::same_as<domain_t<P>, value_type_t<I>>
    constexpr
    J count_if_not(I f, I l, P p, J j)
    {
        while (f != l)
        {
            if (!p(*f))
            {
                ++j;
            }
            ++f;
        }
        return j;
    }

    // Precondition: readable_bounded_range(f, l)
    template <readable_iterator I, unary_predicate P>
        requires std::same_as<domain_t<P>, value_type_t<I>>
    constexpr
    distance_type_t<I> count_if(I f, I l, P p)
    {
        return count_if(f, l, p, distance_type_t<I>{0});
    }

    // Precondition: readable_bounded_range(f, l)
    template <readable_iterator I, unary_predicate P>
        requires std::same_as<domain_t<P>, value_type_t<I>>
    constexpr
    distance_type_t<I> count(I f, I l)
    {
        return count_if(f, l, equal<value_type_t<I>>{}, distance_type_t<I>{0});
    }

    // Precondition: readable_bounded_range(f, l)
    template <readable_iterator I, unary_predicate P>
        requires std::same_as<domain_t<P>, value_type_t<I>>
    constexpr
    distance_type_t<I> count_not(I f, I l)
    {
        return count_if_not(f, l, equal<value_type_t<I>>{}, distance_type_t<I>{0});
    }


    // Precondition: bounded_range(f, l)
    // Precondition: partially_associative(op)
    // Precondition: for every i £ [f, l), fun(i) is defined
    template <iterator I, binary_operation Op, unary_procedure F>
        requires std::same_as<value_type_t<I>, domain_t<F>> && std::same_as<domain_t<Op>, codomain_t<F>>
    constexpr
    domain_t<Op> reduce_nonempty(I f, I l, Op op, F fun)
    {
        domain_t<Op> r = fun(f);
        ++f;
        while (f != l)
        {
            r = op(r, fun(f));
            ++f;
        }
        return r;
    }


    // Precondition: bounded_range(f, l)
    // Precondition: partially_associative(op)
    // Precondition: for every i £ [f, l), fun(i) is defined
    // Precondition: z is the identity element.
    template <iterator I, binary_operation Op, unary_procedure F>
        requires std::same_as<value_type_t<I>, domain_t<F>> && std::same_as<domain_t<Op>, codomain_t<F>>
    constexpr
    domain_t<Op> reduce(I f, I l, Op op, F fun, const domain_t<Op>& z)
    {
        if (f == l)
        {
            return z;
        }

        return reduce_nonempty(f, l, op, fun);
    }

} // namespace eop
