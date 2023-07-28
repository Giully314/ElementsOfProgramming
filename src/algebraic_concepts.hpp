#pragma once

/*
algebraic_concepts.hpp

PURPOSE:

CONCEPTS:
    magma:              a closed set under an operation.
    commutative_magma:  a closed set under a commutative operation.

    semigroup:                  a magma with an associative operation.
    commutative_semigroup:      a magma with an associative and commutative operation.
    additive_semigroup:         a commutative semigroup with + as operator.
    multiplicative_semigroup:   a semigroup with * as operator.

    monoid:                 a semigroup with an identity element.
    commutative_monoid:     a commutative semigroup with an identity element.
    additive_monoid:        a commutative_monoid with + as operator.
    multiplicative_monoid:  a monoid with * as operator.

    group:                  a monoid 
    commutative_group:
    additive_group:
    multiplicative_group:

    semiring:
    commutative_semiring:

    ring:
    commutative_ring:

    semimodule:

    ordered_additive_semigroup:
    ordered_additive_monoid:
    ordered_additive_group:
    cancellable_monoid:


DESCRIPTION:
    The algebraic concepts try to model the algebraic structures studied in universal algebra 
    https://en.wikipedia.org/wiki/Universal_algebra .

    One thing to note is that the definitions are partial because of the finite memory of the computer.

*/ 



#include <concepts>
#include "type_traits.hpp"
#include "type_concepts.hpp"
#include "function_concepts.hpp"
#include "ordering_concepts.hpp"
#include "algebraic_operations.hpp"

namespace eop
{
    template <typename T, typename Op>
    concept magma = regular<T> && binary_operation<Op> && std::same_as<T, domain_t<Op>>;

    template <typename T, typename Op>
    concept commutative_magma = magma<T, Op> && commutative_operation<Op>;

    template <typename T, typename Op>
    concept semigroup = magma<T, Op> && associative_operation<Op>;

    template <typename T, typename Op>
    concept commutative_semigroup = semigroup<T, Op> && commutative_operation<Op>;

    template <typename T>
    concept additive_semigroup = commutative_semigroup<T, plus<T>>;

    template <typename T>
    concept multiplicative_semigroup = semigroup<T, multiply<T>>;


    template <typename T, typename Op, T identity>
    concept monoid = semigroup<T, Op> && requires (T a, Op op)
    {
        {op(a, identity)}; // returns a
        {op(identity, a)}; // returns a
    };


    template <typename T, typename Op, T identity>
    concept commutative_monoid = monoid<T, Op, identity> && commutative_operation<Op>;

    template <typename T>
    concept additive_monoid = commutative_monoid<T, plus<T>, T{0}>;

    template <typename T>
    concept multiplicative_monoid = monoid<T, multiply<T>, T{1}>;


    template <typename T, typename Op, typename InverseOp, T identity>
    concept group = monoid<T, Op, identity> && std::same_as<T, domain_t<InverseOp>> && 
    requires(T a, T b, Op op, InverseOp inv_op)
    {
        {inv_op(a, a)}; // returns identity
        {op(a, inv_op(identity, a))}; // returns identity

        {inv_op.inverse(a)} -> std::same_as<T>;

        // These 2 gives equal result.
        {op(a, inv_op.inverse(b))};
        {inv_op(a, b)}; 
    };


    template <typename T, typename Op, typename InverseOp, T identity>
    concept commutative_group = group<T, Op, InverseOp, identity> && commutative_operation<Op>;

    template <typename T>
    concept additive_group = commutative_group<T, plus<T>, minus<T>, T{0}>;

    template <typename T>
    concept multiplicative_group = group<T, multiply<T>, divide<T>, T{1}>;


    template <typename T, typename Op1, T identity1, typename Op2, T identity2>
    concept semiring = commutative_monoid<T, Op1, identity1> && monoid<T, Op2, identity2> && (identity1 != identity2) &&
        distributive_operation<Op2, Op1> && requires (T a, Op2 op2)
        {
            // Applied with Op1 = + and Op2 with * we get that a * 0 = 0.
            // This rule links the identity of the addition with the multiplication operation.
            {op2(a, identity1)}; // identity1
        };

    template <typename T, typename Op1, T identity1, typename Op2, T identity2>
    concept commutative_semiring = semiring<T, Op1, identity1, Op2, identity2> && commutative_operation<Op2>;

    
    template <typename T, typename Op1, typename InverseOp1, T identity1, typename Op2, T identity2>
    concept ring = commutative_group<T, Op1, InverseOp1, identity1> && monoid<T, Op2, identity2> && distributive_operation<Op2, Op1>;

    template <typename T, typename Op1, typename InverseOp1, T identity1, typename Op2, T identity2>
    concept commutative_ring = ring<T, Op1, InverseOp1, identity1, Op2, identity2> && commutative_operation<Op2>;


    // TODO: add the other axioms in the require clausoles.
    template <typename T, typename TOp, T Tidentity, 
        typename S, typename SOp1, S Sidentity1, typename SOp2, S Sidentity2, typename LinkOp>
    concept semimodule = commutative_monoid<T, TOp, Tidentity> && semiring<S, SOp1, Sidentity1, SOp2, Sidentity2> &&
                            associative_operation<LinkOp> && commutative_operation<LinkOp> &&
                            requires (T a, T b, S q, S w, TOp top, SOp1 sop1, SOp2 sop2, LinkOp lop)
                            {
                                lop(q, a);
                                lop(a, q);
                                
                                lop(sop1(q,w), a);
                                lop(q, lop(w, a));
                                

                                lop(Sidentity2, a); // for example 1 * a where a is a vector
                            };


    // TODO: module concept 
    

    template <typename T>
    concept ordered_additive_semigroup = additive_semigroup<T> && totally_ordered<T> && requires (T a, T b, T c)
    {
        /* if */ {a < b}; /* then */ {a + c < b + c};
    };

    template <typename T>
    concept ordered_additive_monoid = ordered_additive_semigroup<T> && additive_monoid<T>;

    template <typename T>
    concept ordered_additive_group = ordered_additive_monoid<T> && additive_group<T>;


    template <typename T>
    concept cancellable_monoid = ordered_additive_monoid<T> && requires (T a, T b)
    {
        { a - b } -> std::same_as<T>;
        
        // b <= a -> a - b is defined and (a - b) + b = a 
    };


    template <typename T>
    concept archimedean_monoid = cancellable_monoid<T> && requires (T a, T b)
    {
        // Has quotient type = int
        typename quotient_type_t<T>;
        requires std::signed_integral<quotient_type_t<T>>;
        
        // for every a >= 0 and b > 0 requires slow_remainder(a, b) to terminate. 
    };


    template <typename T>
    concept halvable_monoid = archimedean_monoid<T> && requires (T a)
    {
        // for every a, b, b > 0 and a = b + b then a / 2 = b
        {a / 2} -> std::same_as<T>;
    };


    template <typename T>
    concept euclidean_monoid = archimedean_monoid<T> && requires (T a, T b)
    {
        // for every a > 0 and b > 0, subtractive_gcd_non_zero(a, b) terminates.
        { true };   
    };
} // namespace eop
