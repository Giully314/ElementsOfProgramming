#pragma once

/*
algorithms.hpp

PURPOSE:

FUNCTIONS
    for_each:
    for_each_n:
    
    find:
    find_n:
    find_not:
    find_not_n:

    find_if:
    find_if_n:
    find_if_unguarded:
    find_if_not:
    find_if_not_n:
    find_if_not_unguarded:

    all:
    all_n:
    not_all:
    not_all_n:
    none:
    none_n:
    some:
    some_n:

    count_if:
    count_if_n:
    count_if_not:
    count_if_not_n:
    count:

    reduce_nonempty:
    reduce_nonempty_n:
    reduce:
    reduce_n:
    reduce_nonzeros:
    reduce_nonzeros_n:
    
    find_mismatch:
    find_mismatch_n:
    find_adjacent_mismatch:


DESCRIPTION:


*/


#include <concepts>
#include "iterator_concepts.hpp"
#include "function_concepts.hpp"
#include "type_traits.hpp"
#include "relations.hpp"
#include "pair.hpp"
#include "number.hpp"
#include "iterator.hpp"

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


    // Precondition: readable_weak_range(f, l)
    template <readable_iterator I, unary_procedure Proc> 
        requires std::same_as<domain_t<Proc>, value_type_t<I>>
    constexpr
    Pair<Proc, I> for_each_n(I f, distance_type_t<I> n, Proc proc)
    {
        while (!Integer::is_zero(n))
        {
            --n;
            proc(*f++);
        }
        return Pair<Proc, I>{proc, f};
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

    // Precondition: readable_weak_range(f, n)
    // TODO: should value_type_t be enforced as comparable?
    template <readable_iterator I>
    constexpr
    Pair<I, distance_type_t<I>> find_n(I f, distance_type_t<I> n, const value_type_t<I>& x)
    {
        while (!Integer::is_zero(n) && *f != x)
        {
            --n;
            ++f;
        }

        return Pair<I, distance_type_t<I>>{f, n};
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

    // Precondition: readable_weak_range(f, n)
    // TODO: should value_type_t be enforced as comparable?
    template <readable_iterator I>
    constexpr
    Pair<I, distance_type_t<I>> find_not_n(I f, distance_type_t<I> n, const value_type_t<I>& x)
    {
        while (!Integer::is_zero(n) && *f == x)
        {
            --n;
            ++f;
        }

        return Pair<I, distance_type_t<I>>{f, n};
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

    // Precondition: readable_bounded_range(f, l) && some(f, l, p)
    template <readable_iterator I, unary_predicate P>
        requires std::same_as<domain_t<P>, value_type_t<I>>
    constexpr
    I find_if_unguarded(I f, I l, P p)
    {
        while (!p(*f))
        {
            ++f;
        }
        return f;
    }


    // Precondition: readable_weak_range(f, n)
    template <readable_iterator I, unary_predicate P>
        requires std::same_as<domain_t<P>, value_type_t<I>>
    constexpr
    Pair<I, distance_type_t<I>> find_if_n(I f, distance_type_t<I> n, P p)
    {
        while (!Integer::is_zero(n) && !p(*f))
        {
            --n;
            ++f;
        }

        return Pair<I, distance_type_t<I>>{f, n};
    }


    // Wrong, make it right.
    // Precondition: readable_bounded_range(f, l)
    // Postcondition: if not found return f, if found return successor(i)
    template <bidirectional_iterator I, unary_predicate P>
        requires std::same_as<domain_t<P>, value_type_t<I>>
    constexpr
    I find_backward_if(I f, I l, P p)
    {
        while (l != f && !p(*(--l)));
        return l;
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


    // Precondition: readable_bounded_range(f, l) && not_all(f, l, p)
    template <readable_iterator I, unary_predicate P>
        requires std::same_as<domain_t<P>, value_type_t<I>>
    constexpr
    I find_if_not_unguarded(I f, I l, P p)
    {
        while (p(*f))
        {
            ++f;
        }
        return f;
    }

    // Precondition: readable_weak_range(f, n)
    template <readable_iterator I, unary_predicate P>
        requires std::same_as<domain_t<P>, value_type_t<I>>
    constexpr
    Pair<I, distance_type_t<I>> find_if_not_n(I f, distance_type_t<I> n, P p)
    {
        while (!Integer::is_zero(n) && p(*f))
        {
            --n;
            ++f;
        }

        return Pair<I, distance_type_t<I>>{f, n};
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

    // Precondition: readable_weak_range(f, n)
    template <readable_iterator I, unary_predicate P>
        requires std::same_as<domain_t<P>, value_type_t<I>>
    constexpr
    Pair<I, bool> all_n(I f, distance_type_t<I> n, P p)
    {
        constexpr auto r = find_if_not_n(f, n, p);
        return Pair<I, bool>{r.first, Integer::is_zero(r.second)};
    }


    // Precondition: readable_bounded_range(f, l)
    template <readable_iterator I, unary_predicate P>
        requires std::same_as<domain_t<P>, value_type_t<I>>
    constexpr
    bool not_all(I f, I l, P p)
    {
        return !all(f, l, p);
    }


    // Precondition: readable_weak_range(f, n)
    template <readable_iterator I, unary_predicate P>
        requires std::same_as<domain_t<P>, value_type_t<I>>
    constexpr
    Pair<I, bool> not_all_n(I f, distance_type_t<I> n, P p)
    {
        constexpr auto r = all_n(f, n, p);
        return Pair<I, bool>{r.first, !r.second};
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


    // Precondition: readable_weak_range(f, n)
    template <readable_iterator I, unary_predicate P>
        requires std::same_as<domain_t<P>, value_type_t<I>>
    constexpr
    Pair<I, bool> none_n(I f, distance_type_t<I> n, P p)
    {
        constexpr auto r = find_if_n(f, n, p);
        return Pair<I, bool>{r.first, Integer::is_zero(r.second)};
    }


    // Precondition: readable_bounded_range(f, l)
    template <readable_iterator I, unary_predicate P>
        requires std::same_as<domain_t<P>, value_type_t<I>>
    constexpr
    bool some(I f, I l, P p)
    {
        return !none(f, l, p);
    }


    // Precondition: readable_weak_range(f, n)
    template <readable_iterator I, unary_predicate P>
        requires std::same_as<domain_t<P>, value_type_t<I>>
    constexpr
    Pair<I, bool> some_n(I f, distance_type_t<I> n, P p)
    {
        constexpr auto r = none_n(f, n, p);
        return Pair<I, bool>{r.first, !r.second};
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
    template <readable_iterator I, unary_predicate P>
        requires std::same_as<domain_t<P>, value_type_t<I>>
    constexpr
    distance_type_t<I> count_if(I f, I l, P p)
    {
        return count_if(f, l, p, distance_type_t<I>{0});
    }


    // Precondition: readable_weak_range(f, n)
    template <readable_iterator I, unary_predicate P, iterator J>
        requires std::same_as<domain_t<P>, value_type_t<I>>
    constexpr
    Pair<I, J> count_if_n(I f, distance_type_t<I> n, P p, J j)
    {
        while (!Integer::is_zero(n))
        {
            if (p(*f))
            {
                ++j;
            }
            --n;
            ++f;
        }
        return Pair<I, J>{f, j};
    }


    // Precondition: readable_waek_range(f, n)
    template <readable_iterator I, unary_predicate P>
        requires std::same_as<domain_t<P>, value_type_t<I>>
    constexpr
    Pair<I, distance_type_t<I>> count_if_n(I f, distance_type_t<I> n, P p)
    {
        return count_if_n(f, n, p, distance_type_t<I>{0});
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


    // Precondition: readable_weak_range(f, n)
    template <readable_iterator I, unary_predicate P, iterator J>
        requires std::same_as<domain_t<P>, value_type_t<I>>
    constexpr
    Pair<I, J> count_if_not_n(I f, distance_type_t<I> n, P p, J j)
    {
        while (!Integer::is_zero(n))
        {
            if (!p(*f))
            {
                ++j;
            }
            --n
            ++f;
        }
        return Pair<I, J>{f, j};
    }


    // Precondition: readable_bounded_range(f, l)
    template <readable_iterator I, unary_predicate P>
        requires std::same_as<domain_t<P>, value_type_t<I>>
    constexpr
    distance_type_t<I> count(I f, I l, const value_type_t<I>& x)
    {
        return count_if(f, l, 
            [&x](const value_type_t<I>& i) { return i == x }, 
            distance_type_t<I>{0});
    }


    // Precondition: readable_weak_range(f, n)
    template <readable_iterator I, unary_predicate P>
        requires std::same_as<domain_t<P>, value_type_t<I>>
    constexpr
    Pair<I, distance_type_t<I>> count_n(I f, distance_type_t<I> n, const value_type_t<I>& x)
    {
        return count_if_n(f, n, 
            [&x](const value_type_t<I>& i) { return i == x }, 
            distance_type_t<I>{0});
    }


    // Precondition: readable_bounded_range(f, l)
    template <readable_iterator I, unary_predicate P>
        requires std::same_as<domain_t<P>, value_type_t<I>>
    constexpr
    distance_type_t<I> count_not(I f, I l, const value_type_t<I>& x)
    {
        return count_if_not(f, l, 
            [&x](const value_type_t<I>& i) { return i == x }, 
            distance_type_t<I>{0});
    }


    // Precondition: readable_weak_range(f, n)
    template <readable_iterator I, unary_predicate P>
        requires std::same_as<domain_t<P>, value_type_t<I>>
    constexpr
    Pair<I, distance_type_t<I>> count_not_n(I f, distance_type_t<I> n)
    {
        return count_if_not_n(f, n, 
            [&x](const value_type_t<I>& i) { return i == x }, 
            distance_type_t<I>{0});
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


    // Precondition: weak_range(f, n)
    // Precondition: partially_associative(op)
    // Precondition: for every 0 <= i <= n, fun(successor^i(f)) is defined
    template <iterator I, binary_operation Op, unary_procedure F>
        requires std::same_as<value_type_t<I>, domain_t<F>> && std::same_as<domain_t<Op>, codomain_t<F>>
    constexpr
    Pair<I, domain_t<Op>> reduce_nonempty_n(I f, distance_type_t<I> n, Op op, F fun)
    {
        domain_t<Op> r = fun(f);
        --n
        ++f;
        while (!Integer::is_zero(n))
        {
            r = op(r, fun(f));
            --n;
            ++f;
        }
        return Pair<I, domain_t<Op>>{f, r};
    }


    // Precondition: bounded_range(f, l)
    // Precondition: partially_associative(op)
    // Precondition: for every i £ [f, l), fun(i) is defined
    // Precondition: z is the identity element returned in case of f == l.
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


    // Precondition: weak_range(f, n)
    // Precondition: partially_associative(op)
    // Precondition: for every 0 <= i <= n, fun(successor^i(f)) is defined
    // Precondition: z is the identity element returned in case of f == l.
    template <iterator I, binary_operation Op, unary_procedure F>
        requires std::same_as<value_type_t<I>, domain_t<F>> && std::same_as<domain_t<Op>, codomain_t<F>>
    constexpr
    Pair<I, domain_t<Op>> reduce_n(I f, distance_type_t<I> n, Op op, F fun, const domain_t<Op>& z)
    {
        if (Integer::is_zero(n))
        {
            return Pair<I, domain_t<Op>> {f, z};
        }

        return reduce_nonempty_n(f, n, op, fun);
    }


    // Precondition: bounded_range(f, l)
    // Precondition: partially_associative(op)
    // Precondition: for every i £ [f, l), fun(i) is defined
    // Precondition: z is the identity element.
    template <iterator I, binary_operation Op, unary_procedure F>
        requires std::same_as<value_type_t<I>, domain_t<F>> && std::same_as<domain_t<Op>, codomain_t<F>>
    constexpr
    domain_t<Op> reduce_nonzeros(I f, I l, Op op, F fun, const domain_t<Op>& z)
    {
        domain_t<Op> x;
        do
        {
            if (f == l)
            {
                return z;
            }

            x = fun(x);
            ++f;
        } while (x == z);


        while (f != l)
        {
            domain_t<Op> y = fun(f);
            if (y != z)
            {
                x = op(x, y);
            }
            ++f;
        }

        return x;
    }


    // Precondition: weak_range(f, n)
    // Precondition: partially_associative(op)
    // Precondition: for every 0 <= i <= n, fun(successor^i(f)) is defined
    // Precondition: z is the identity element.
    template <iterator I, binary_operation Op, unary_procedure F>
        requires std::same_as<value_type_t<I>, domain_t<F>> && std::same_as<domain_t<Op>, codomain_t<F>>
    constexpr
    Pair<I, domain_t<Op>> reduce_nonzeros_n(I f, distance_type_t<I> n, Op op, F fun, const domain_t<Op>& z)
    {
        domain_t<Op> x;
        do
        {
            if (Integer::is_zero(n))
            {
                return Pair<I, domain_t<Op>>{f, z};
            }

            x = fun(x);
            --n;
            ++f;
        } while (x == z);


        while (Integer::is_zero(n))
        {
            domain_t<Op> y = fun(f);
            if (y != z)
            {
                x = op(x, y);
            }
            --n;
            ++f;
        }

        return Pair<I, domain_t<Op>>{f, x};
    }


    // Precondition: readable_bounded_range(f0, l0)
    // Precondition: readable_bounded_range(f1, l1)
    // Postcondition: f0 and f1 are the first mismatch or 
    //                one of the two iterators reached the end or
    //                no mismatch found if f0 = l0 and f1 = l1. 
    template <readable_iterator I0, readable_iterator I1, relation R>
        requires std::same_as<value_type_t<I0>, value_type_t<I1>> && 
                std::same_as<value_type_t<I0>, domain_t<R>>
    constexpr 
    Pair<I0, I1> find_mismatch(I0 f0, I0 l0, I1 f1, I1 l1, R r)
    {
        while (f0 != l0 && f1 != l1 && r(*f0, *f1))
        {
            ++f0;
            ++f1;
        }
        return Pair<I0, I1>{f0, f1};
    } 


    // Precondition: readable_weak_range(f0, n0)
    // Precondition: readable_bounded_range(f1, l1)
    // Postcondition: f0 and f1 are the first mismatch or 
    //                one of the two iterators reached the end or
    //                no mismatch found if f0 = l0 and f1 = l1. 
    template <readable_iterator I0, readable_iterator I1, relation R>
        requires std::same_as<value_type_t<I0>, value_type_t<I1>> && 
                std::same_as<value_type_t<I0>, domain_t<R>>
    constexpr 
    Pair<I0, I1> find_mismatch_n0(I0 f0, distance_type_t<I0>, I1 f1, I1 l1, R r)
    {
        while (!Integer::is_zero(n) && f1 != l1 && r(*f0, *f1))
        {
            --n;
            ++f1;
        }
        return Pair<I0, I1>{f0, f1};
    }

    // Precondition: readable_weak_range(f0, n0)
    // Precondition: readable_bounded_range(f1, l1)
    // Postcondition: f0 and f1 are the first mismatch or 
    //                one of the two iterators reached the end or
    //                no mismatch found if n0 = 0 and f1 = l1. 
    template <readable_iterator I0, readable_iterator I1, relation R>
        requires std::same_as<value_type_t<I0>, value_type_t<I1>> && 
                std::same_as<value_type_t<I0>, domain_t<R>>
    constexpr
    Pair<Pair<I0, distance_type_t<I0>>, I1> find_mismatch_n(I0 f0, distance_type_t<I0> n0, I1 f1, I1 l1, R r)
    {
        while (!Integer::is_zero(n0) && f1 != l1 && r(*f0, *f1))
        {
            --n0;
            ++f1;
        }
        return Pair<Pair<I0, distance_type_t<I0>>, I1>{{f0, n0}, f1};
    }


    // Precondition: readable_bounded_range(f0, l0)
    // Precondition: readable_weak_range(f1, n1)
    // Postcondition: f0 and f1 are the first mismatch or 
    //                one of the two iterators reached the end or
    //                no mismatch found if f0 = l0 and n1 = 0. 
    template <readable_iterator I0, readable_iterator I1, relation R>
        requires std::same_as<value_type_t<I0>, value_type_t<I1>> && 
                std::same_as<value_type_t<I0>, domain_t<R>>
    constexpr 
    Pair<I0, Pair<I1, distance_type_t<I1>>> find_mismatch_n(I0 f0, I0 l0, I1 f1, distance_type_t<I1> n1, R r)
    {
        while (f0 != l0 && !Integer::is_zero(n1) && r(*f0, *f1))
        {
            ++f0;
            --n1;
        }
        return Pair<I0, Pair<I1, distance_type_t<I1>>>{f0, {f1, n1}};
    }


    // Precondition: readable_weak_range(f0, n0)
    // Precondition: readable_weak_range(f1, n1)
    // Postcondition: f0 and f1 are the first mismatch or 
    //                one of the two iterators reached the end or (so nomismatch in the first n0 or n1 elements)
    //                no mismatch found if n0 = 0 and n1 = 0. 
    template <readable_iterator I0, readable_iterator I1, relation R>
        requires std::same_as<value_type_t<I0>, value_type_t<I1>> && 
                std::same_as<value_type_t<I0>, domain_t<R>>
    constexpr
    Pair<Pair<I0, distance_type_t<I0>>, Pair<I1, distance_type_t<I1>>> 
    find_mismatch_n(I0 f0, distance_type_t<I0> n0, I1 f1, distance_type_t<I1> n1, R r)
    {
        while (!Integer::is_zero(n0) && !Integer::is_zero(n1) && r(*f0, *f1))
        {
            --n0;
            --n1;
        }
        return Pair<Pair<I0, distance_type_t<I0>>, Pair<I1, distance_type_t<I1>>>{{f0, n0}, {f1, n1}};
    }


    // Precondition: readable_bounded_range(f, l)
    template <readable_iterator I, relation R>
        requires std::same_as<value_type_t<I>, domain_t<R>>
    constexpr 
    I find_adjacent_mismatch(I f, I l, R r)
    {
        if (f == l)
        {
            return l;
        }

        // Note that we do a copy here because of the weak requirement of I. After applying successor, the previous value
        // could be ill-formed (for example if we use a reference for x and I is an input iterator from std::cin we would have UB).
        value_type_t<I> x = *f;
        ++f;
        while (f != l && r(x, *f))
        {
            x = *f;
            ++f;
        }
        return f;
    }

     // Precondition: readable_bounded_range(f, l)
    template <forward_iterator I, relation R>
        requires std::same_as<value_type_t<I>, domain_t<R>>
    constexpr 
    I find_adjacent_mismatch(I f, I l, R r)
    {
        if (f == l)
        {
            return l;
        }

        // Note that we can do a copy of the iterator because we are using the overloaded version with 
        // forward_iterator which assures the regularity of the successor function.         
        I t;
        do
        {
            t = f;
            ++f;
        } while (f != l && r(*t, *f));
        return f;
    }


    // Precondition: readable_weak_range(f, n)
    template <readable_iterator I, relation R>
        requires std::same_as<value_type_t<I>, domain_t<R>>
    constexpr 
    Pair<I, distance_type_t<I>> find_adjacent_mismatch_n(I f, distance_type_t<I> n, R r)
    {
        if (Integer::is_zero(n))
        {
            return f;
        }

        // Note that we do a copy here because of the weak requirement of I. After applying successor, the previous value
        // could be ill-formed (for example if we use a reference for x and I is an input iterator from std::cin we would have UB).
        value_type_t<I> x = *f;
        ++f;
        while (!Integer::is_zero(n) && r(x, *f))
        {
            x = *f;
            ++f;
            --n;
        }

        return Pair<I, distance_type_t<I>>{f, n};
    }

    
    // Precondition: readable_bounded_range(f, l)
    template <readable_iterator I, relation R> 
        requires std::same_as<value_type_t<I>, domain_t<R>>
    constexpr 
    bool relation_preserving(I f, I l, R r)
    {
        return l == find_adjancent_mismatch(f, l, r);
    }

    // Precondition: readable_weak_range(f, n)
    template <readable_iterator I, relation R> 
        requires std::same_as<value_type_t<I>, domain_t<R>>
    constexpr 
    bool relation_preserving_n(I f, distance_type_t<I> n, R r)
    {
        auto res = find_adjancent_mismatch_n(f, n, r);
        return Integer::is_zero(res.second);
    }


    // Precondition: readable_bounded_range(f, l) && weak_order(r)
    template <readable_iterator I, weak_ordering_relation R>
        requires std::same_as<value_type_t<I>, domain_t<R>>
    constexpr
    bool strictly_increasing_range(I f, I l, R r)
    {
        return relation_preserving(f, l, r);      
    }

    // Precondition: readable_counted_range(f, l) && weak_relation(r)
    template <readable_iterator I, weak_ordering_relation R> 
        requires std::same_as<value_type_t<I>, domain_t<R>>
    constexpr
    bool strictly_increasing_range_n(I f, distance_type_t<I> n, R r)
    {
        return relation_preserving_n(f, n, r);
    }

    // Precondition: readable_bounded_range(f, l) && weak_relation(r)
    template <readable_iterator I, weak_ordering_relation R> 
        requires std::same_as<value_type_t<I>, domain_t<R>>
    constexpr 
    bool increasing_range(I f, I l, R r)
    {
        return relation_preserving(f, l, complement_of_converse<R>(r));
    }

    // Precondition: readable_counted_range(f, l) && weak_relation(r)
    template <readable_iterator I, weak_ordering_relation R> 
        requires std::same_as<value_type_t<I>, domain_t<R>>
    constexpr
    bool increasing_range_n(I f, distance_type_t<I> n, R r)
    {
        return relation_preserving_n(f, n, complement_of_converse<R>(r));
    }

    
    // Note: in the book, partitioned returns true if any value satisfying the predicate follows any 
    // value not satisfying the predicate. I find it a little bit counterintuitive because usually we want 
    // the first part of the range to be the one who satisfies the predicate and then remove the other part 
    // at the end. In the STL is implemented in this way.
    // Precondition: readable_bounded_range(f, l)
    // Returns true if any value that satisfies the predicate follow every value that doesn't satisfy 
    // the predicate.
    template <readable_iterator I, unary_predicate P> 
        requires std::same_as<value_type_t<I>, domain_t<P>>
    constexpr
    bool partitioned(I f, I l, P r)
    {
        return l == find_if_not(find_if(f, l, p), l, p);
    }

    // Precondition: readable_counted_range(f, l)
    template <readable_iterator I, unary_predicate P> 
        requires std::same_as<value_type_t<I>, domain_t<P>>
    constexpr
    bool partitioned_n(I f, distance_type_t<I> n, P r)
    {
        auto res_f = find_if_n(f, n, p);

        // The whole range is made of elements that don't satisfy the predicate.
        if (Integer::is_zero(res_f.second))
        {
            return true;
        }

        auto res_fn = find_if_not_n(res_f.first, n - res_f.second, p);
        // The other part of the range contains elements that satisfy the predicate. 
        if (Integer::is_zero(res_fn.second))
        {
            return true;
        }

        return false;
    }


    // Precondition: readable_counted_range(f, n) && partitioned_n(f, n, p)
    template <forward_iterator I, unary_predicate P>
        requires std::same_as<value_type_t<I>, domain_t<P>>
    constexpr
    I partition_point_n(I f, distance_type_t<I> n, P p)
    {
        while (!Integer::is_zero(n))
        {
            distance_type_t<I> h = Integer::half_nonnegative(n);
            I m = f + h;   
            if (p(*m))
            {
                n = h;
            }
            else
            {
                n = n - (h + 1);
                f = ++m;
            }
        }
        return f;
    }


    // Precondition: readable_bounded_range(f, n) && partitioned_n(f, n, p)
    template <forward_iterator I, unary_predicate P>
        requires std::same_as<value_type_t<I>, domain_t<P>>
    constexpr
    I partition_point(I f, distance_type_t<I> n, P p)
    {
        return partition_point_n(f, l - f, p);
    }


    // Precondition: increasing_counted_range(f, n, r) && weak_ordering(r)
    template <forward_iterator I, weak_ordering_relation R>
        requires std::same_as<value_type_t<I>, domain_t<R>>
    constexpr 
    I lower_bound_n(I f, distance_type_t<I> n, const value_type_t<I>& a, R r)
    {
        lower_bound_predicate<R> p(a, r);
        return partition_point_n(f, n, p);
    }   
    

    // Precondition: increasing_bounded_range(f, l, r) && weak_ordering(r)
    template <forward_iterator I, weak_ordering_relation R>
        requires std::same_as<value_type_t<I>, domain_t<R>>
    constexpr 
    I lower_bound(I f, I l, const value_type_t<I>& a, R r)
    {
        lower_bound_predicate<R> p(a, r);
        return partition_point_n(f, l - f, p);
    }


    // Precondition: increasing_counted_range(f, n, r) && weak_ordering(r)
    template <forward_iterator I, weak_ordering_relation R>
        requires std::same_as<value_type_t<I>, domain_t<R>>
    constexpr 
    I upper_bound_n(I f, distance_type_t<I> n, const value_type_t<I>& a, R r)
    {
        upper_bound_predicate<R> p(a, r);
        return partition_point_n(f, n, p);
    }   
    

    // Precondition: increasing_bounded_range(f, l, r) && weak_ordering(r)
    template <forward_iterator I, weak_ordering_relation R>
        requires std::same_as<value_type_t<I>, domain_t<R>>
    constexpr
    I upper_bound(I f, I l, const value_type_t<I>& a, R r)
    {
        upper_bound_predicate<R> p(a, r);
        return partition_point_n(f, l - f, p);
    }


    // Precondition: increasing_counted_range(f, n, r) && weak_ordering(r)
    template <forward_iterator I, weak_ordering_relation R>
        requires std::same_as<value_type_t<I>, domain_t<R>>
    Pair<I, I> lower_upper_bound_n(I f, distance_type_t<I> n, const value_type_t<I>& a, R r)
    {
        lower_bound_predicate<R> lp(a, r);
        upper_bound_predicate<R> up(a, r);
        
        while (!Integer::is_zero(n))
        {
            distance_type_t<I> h = Integer::half_nonnegative(n);
            I m = f + h;   
            if (p(*m))
            {
                n = h;
            }
            else
            {
                n = n - (h + 1);
                f = ++m;
            }
        }
    }


    template <bidirectional_iterator I>
    constexpr
    bool is_palindrome(I f, I l)
    {
        if (f == l)
        {
            return true;
        }

        --l;
        while (f != l)
        {
            if (*f++ != *l)
            {
                return false;
            }
            if (f == l--)
            {
                return true;
            }
        }
    }

} // namespace eop
