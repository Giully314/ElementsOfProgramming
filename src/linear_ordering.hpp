#ifndef LINEAR_ORDERING_HPP
#define LINEAR_ORDERING_HPP

/*

PURPOSE: define ordering

FUNCTIONS: 


DESCRIPTION: the notation select_i_j means that we select the ith order of j elements.
For example select_0_2 means that we select the min of 2 elements.
The notation select_i_j_ab add a precondition (assumption) on the fact that the first 2 elements are ordered,
so we can write a better algorithm using the assumption. 

*/

#include "function_concepts.hpp"
#include "type_traits.hpp"

namespace eop
{   
    // if strict true we just use the relation R
    // if strict is false we use the complement of converse !r(b, a).
    template <bool strict, typename R>
        requires relation<R>
    struct compare_strict_or_reflexive;


    template <typename R>
        requires relation<R>
    struct compare_strict_or_reflexive<true, R> // strict
    {   
        constexpr
        bool operator()(const domain_t<R>& a, const domain_t<R>& b, R r)
        {
            return r(a, b);
        }
    };


    template <typename R>
        requires relation<R>
    struct compare_strict_or_reflexive<false, R> // reflexive
    {   
        constexpr
        bool operator()(const domain_t<R>& a, const domain_t<R>& b, R r)
        {
            return !r(b, a);
        }
    };


    
    struct Ordering
    {
        template <weak_ordering_relation R>
        static constexpr
        const domain_t<R>& select_0_2(const domain_t<R>& a, const domain_t<R>& b, R r)
        {
            if (r(b, a)) return b;
            return a;
        }


        template <weak_ordering_relation R>
        static constexpr
        const domain_t<R>& select_1_2(const domain_t<R>& a, const domain_t<R>& b, R r)
        {
            if (r(b, a)) return a;
            return b;
        }


        template <weak_ordering_relation R>
        static constexpr
        const domain_t<R>& select_0_3(const domain_t<R>& a, const domain_t<R>& b, const domain_t<R>& c, R r)
        {
            return select_0_2(select_0_2(a, b, r), c, r);
        }


        template <weak_ordering_relation R>
        static constexpr
        const domain_t<R>& select_2_3(const domain_t<R>& a, const domain_t<R>& b, const domain_t<R>& c, R r)
        {
            return select_1_2(select_1_2(a, b, r), c, r);
        }


        // Median
        template <weak_ordering_relation R>
        static constexpr
        const domain_t<R>& select_1_3_ab(const domain_t<R>& a, const domain_t<R>& b, const domain_t<R>& c, R r)
        {
            if (!r(c, b)) return b;
            return select_1_2(a, c, r);   
        }


        template <weak_ordering_relation R>
        static constexpr
        const domain_t<R>& select_1_3(const domain_t<R>& a, const domain_t<R>& b, const domain_t<R>& c, R r)
        {
            if (r(b, a)) return select_1_3_ab(b, a, c, r);
            return select_1_3_ab(a, b, c, r);
        }

        

        template <weak_ordering_relation R>
        static constexpr
        const domain_t<R>& select_1_4_ab_cd(const domain_t<R>& a, const domain_t<R>& b, const domain_t<R>& c, const domain_t<R>&d, R r)
        {
            if (r(c, a)) return select_0_2(a, d, r);
            return select_0_2(b, c, r);   
        }

        template <weak_ordering_relation R>
        static constexpr
        const domain_t<R>& select_1_4_ab(const domain_t<R>& a, const domain_t<R>& b, const domain_t<R>& c, const domain_t<R>&d, R r)
        {
            if (r(d, c)) return select_1_4_ab_cd(a, b, d, c, r);
            return select_1_4_ab_cd(a, b, c, d, r);
        }

        template <weak_ordering_relation R>
        static constexpr
        const domain_t<R>& select_1_4(const domain_t<R>& a, const domain_t<R>& b, const domain_t<R>& c, const domain_t<R>&d, R r)
        {
            if (r(b, a)) return select_1_4_ab(b, a, c, d, r);
            return select_1_4_ab(a, b, c, d, r);
        }


        // Exercise 4.4
        template <weak_ordering_relation R>
        static constexpr
        const domain_t<R>& select_2_4_ab_cd(const domain_t<R>& a, const domain_t<R>& b, const domain_t<R>& c, const domain_t<R>&d, R r)
        {
            if (r(d, b)) return select_1_2(a, d, r);
            return select_1_2(b, c, r);
        }

        template <weak_ordering_relation R>
        static constexpr
        const domain_t<R>& select_2_4_ab(const domain_t<R>& a, const domain_t<R>& b, const domain_t<R>& c, const domain_t<R>&d, R r)
        {
            if (r(d, c)) select_2_4_ab_cd(a, b, d, c, r);
            return select_2_4_ab_cd(a, b, c, d, r);
        }

        template <weak_ordering_relation R>
        static constexpr
        const domain_t<R>& select_2_4(const domain_t<R>& a, const domain_t<R>& b, const domain_t<R>& c, const domain_t<R>&d, R r)
        {
            if (r(b, a)) select_2_4_ab(b, a, d, c, r);
            return select_2_4_ab(a, b, c, d, r);
        }


        template <int ia, int ib, weak_ordering_relation R>
        static constexpr
        const domain_t<R>& select_0_2(const domain_t<R>& a, const domain_t<R>& b, R r)
        {
            compare_strict_or_reflexive<ia < ib, R> cmp;
            if (cmp(b, a, r)) return b;
            return a;
        }


        template <int ia, int ib, weak_ordering_relation R>
        static constexpr
        const domain_t<R>& select_1_2(const domain_t<R>& a, const domain_t<R>& b, R r)
        {
            compare_strict_or_reflexive< (ia > ib), R> cmp;
            if (cmp(b, a, r)) return a;
            return b;
        }


        template <int ia, int ib, int ic, int id, weak_ordering_relation R>
        static constexpr
        const domain_t<R>& select_1_4_ab_cd(const domain_t<R>& a, const domain_t<R>& b, const domain_t<R>& c, const domain_t<R>&d, R r)
        {
            compare_strict_or_reflexive<ia < ic, R> cmp;
            if (cmp(c, a, r)) return select_0_2<ia, id>(a, d, r);
            return select_0_2<ib, ic>(b, c, r);   
        }

        template <int ia, int ib, int ic, int id, weak_ordering_relation R>
        static constexpr
        const domain_t<R>& select_1_4_ab(const domain_t<R>& a, const domain_t<R>& b, const domain_t<R>& c, const domain_t<R>&d, R r)
        {
            compare_strict_or_reflexive<ic < id, R> cmp;
            if (cmp(d, c, r)) return select_1_4_ab_cd<ia, ib, id, ic>(a, b, d, c, r);
            return select_1_4_ab_cd<ia, ib, ic, id>(a, b, c, d, r);
        }

        template <int ia, int ib, int ic, int id, weak_ordering_relation R>
        static constexpr
        const domain_t<R>& select_1_4(const domain_t<R>& a, const domain_t<R>& b, const domain_t<R>& c, const domain_t<R>&d, R r)
        {
            compare_strict_or_reflexive<ia < ib, R> cmp;
            if (cmp(b, a, r)) return select_1_4_ab<ib, ia, ic, id>(b, a, c, d, r);
            return select_1_4_ab<ia, ib, ic, id>(a, b, c, d, r);
        }



        template <int ia, int ib, int ic, int id, int ie, weak_ordering_relation R>
        static constexpr
        const domain_t<R>& select_2_5_ab_cd(const domain_t<R>& a, const domain_t<R>& b, const domain_t<R>& c, const domain_t<R>&d,
                                        const domain_t<R>&e, R r)
        {
            compare_strict_or_reflexive<ia < ic, R> cmp;
            if (cmp(c, a, r)) return select_1_4_ab<ia, ib, id, ie>(a, b, d, e, r);
            return select_1_4_ab<ic, id, ib, ie>(c, d, b, e, r);
        }


        template <int ia, int ib, int ic, int id, int ie, weak_ordering_relation R>
        static constexpr
        const domain_t<R>& select_2_5_ab(const domain_t<R>& a, const domain_t<R>& b, const domain_t<R>& c, const domain_t<R>&d,
                                        const domain_t<R>&e, R r)
        {
            compare_strict_or_reflexive<ic < id, R> cmp;
            if (cmp(d, c, r)) return select_2_5_ab_cd<ia, ib, id, ic, ie>(a, b, d, c, e, r);
            return select_2_5_ab_cd<ia, ib, ic, id, ie>(a, b, c, d, e, r);
        }


        template <int ia, int ib, int ic, int id, int ie, weak_ordering_relation R>
        static constexpr
        const domain_t<R>& select_2_5(const domain_t<R>& a, const domain_t<R>& b, const domain_t<R>& c, const domain_t<R>&d,
                                        const domain_t<R>&e, R r)
        {
            compare_strict_or_reflexive<ia < ib, R> cmp;
            if (cmp(b, a, r)) return select_2_5_ab<ib, ia, id, ic, ie>(b, a, c, d, e, r);
            return select_2_5_ab<ia, ib, ic, id, ie>(a, b, c, d, e, r);
        }


        template <weak_ordering_relation R>
        static constexpr
        const domain_t<R>& median_5(const domain_t<R>& a, const domain_t<R>& b, const domain_t<R>& c, const domain_t<R>& d, 
                                        const domain_t<R>& e, R r)
        {
            return select_2_5<0, 1, 2, 3, 4>(a, b, c, d, e, r);
        }
    };

} // namespace eop


#endif 