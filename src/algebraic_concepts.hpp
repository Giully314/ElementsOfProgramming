#pragma once

/*
algebraic_concepts.hpp

PURPOSE:

CONCEPTS:


DESCRIPTION:
    The algebraic concepts try to model the algebraic structures studied in universal algebra 
    https://en.wikipedia.org/wiki/Universal_algebra .

*/ 



#include <concepts>
#include "type_traits.hpp"
#include "type_concepts.hpp"
#include "function_concepts.hpp"
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


    
    

} // namespace eop
