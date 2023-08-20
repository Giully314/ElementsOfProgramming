#pragma once



/*
relations.hpp
*/

#include "function_concepts.hpp"
#include "relation_concepts.hpp"
#include "type_traits.hpp"

namespace eop
{
    template <typename T>
        requires has_less_op<T>
    struct less
    {
        constexpr
        bool operator<(T a, T b)
        {
            return a < b;
        }
    };


    template <typename T>
        requires has_less_or_equal_op<T>
    struct less_or_equal
    {
        constexpr
        bool operator<(T a, T b)
        {
            return a <= b;
        }
    };


    template <typename T>
        requires has_greater_op<T>
    struct greater
    {
        constexpr
        bool operator<(T a, T b)
        {
            return a > b;
        }
    };


    template <typename T>
        requires has_greater_or_equal_op<T>
    struct greater_or_equal
    {
        constexpr
        bool operator<(T a, T b)
        {
            return a >= b;
        }
    };


    template <typename T>
        requires has_equal_op<T>
    struct equal
    {  
        constexpr
        bool operator==(T a, T b)
        {
            return a == b;
        }
    };


    template <typename T>
        requires has_not_equal_op<T>
    struct not_equal
    {
        constexpr
        bool operator!=(T a, T b)
        {
            return a != b;
        }
    };



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



    template <relation R> 
    struct complement_of_converse
    {
        using T = domain_t<R>;
        R r;

        constexpr
        complement_of_converse(const R& r_) : r(r_)
        {

        }

        constexpr
        bool operator()(const T& a, const T& b)
        {
            return !r(b, a);
        }
    };


    template <relation R>
    struct lower_bound_predicate
    {
        using T = domain_t<R>;
        const T& a;
        R r;

        constexpr 
        lower_bound_predicate(const T& a_, R r_) : a(a_), r(r_)
        {

        }

        constexpr
        bool operator()(const T& x)
        {
            return !r(x, a);
        }
    };


    template <relation R>
    struct upper_bound_predicate
    {
        using T = domain_t<R>;
        const T& a;
        R r;

        constexpr 
        upper_bound_predicate(const T& a_, R r_) : a(a_), r(r_)
        {

        }

        constexpr
        bool operator()(const T& x)
        {
            return r(a, x);
        }
    };

} // namespace eop
