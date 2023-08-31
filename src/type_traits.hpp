#ifndef TYPE_TRAITS_HPP
#define TYPE_TRAITS_HPP

/*
type_traits.hpp

PURPOSE: manipulate and check traits on types at compile time.

TRAITS:
    input_type: extract the ith type parameter of a callable.

DESCRIPTION:
type traits are the foundation of concepts. Manipulate and check properties on types at compile time,
define functions from a type to another and so on.


THOUGHTS:
Note that the focus of this project is not to learn the syntax or the tricks on how to implement concepts 
or type_traits but to understand the abstraction and the hierarchy of properties on types.
I will use the standard library for basic concepts and type_traits to avoid to move the focus on other things.

*/

#include <type_traits>
#include "mpl.hpp"

namespace eop
{
   
    //*************** INPUT TYPE *********************

    template <typename F, size_t I>
    struct input_type
    {
        using type = extract_t<params_of_function_t<F>, I>;
    };

    template <typename F, size_t I>
    using input_type_t = typename input_type<F, I>::type;

    //*************** INPUT TYPE *********************


     //**************** DOMAIN ***********************

    template <typename F>
    struct domain
    {
        using type = std::remove_cvref_t<input_type_t<F, 0>>;
    };

    template <typename F>
    using domain_t = typename domain<F>::type;

    //**************** DOMAIN ***********************

    //**************** CODOMAIN ***********************

    template <typename F>
    struct codomain
    {
        using type = return_type_of_function_t<F>;
    };

    template <typename F>
    using codomain_t = codomain<F>::type;

    //**************** CODOMAIN ***********************


    //**************** DISTANCE TYPE ******************

    // TODO: make the distance type based on the sizeof the domain of F.

    template <typename F>
    struct distance_type
    {
        using type = size_t;
    };


    template <typename I>
        requires std::is_object_v<std::remove_cvref_t<typename I::distance_type>> 
    struct distance_type
    {
        using type =  I::distance_type;
    };

    template <typename F>
    using distance_type_t = typename distance_type<F>::type; 

    //**************** DISTANCE TYPE ******************


    //**************** WEIGHT TYPE ******************

    // TODO: make the distance type based on the sizeof the domain of F.

    template <typename F>
    struct weight_type
    {
        using type = size_t;
    };


    template <typename I>
        requires std::is_object_v<std::remove_cvref_t<typename I::weight_type>> 
    struct weight_type
    {
        using type =  I::weight_type;
    };

    template <typename F>
    using weight_type_t = typename weight_type<F>::type; 

    //**************** WEIGHT TYPE ******************


    //**************** QUOTIENT TYPE ******************

    // TODO: make the distance type based on the sizeof the domain of F.

    template <typename T>
    struct quotient_type
    {
        using type = int;
    };

    template <typename T>
    using quotient_type_t = typename quotient_type<T>::type; 

    //**************** QUOTIENT TYPE ******************


    //**************** VALUE TYPE ******************

    template <typename T>
    struct value_type
    {
        using type = T::value_type;
    };

    template <typename T>
    using value_type_t = typename value_type<T>::type;

    //**************** VALUE TYPE ******************


    //**************** OUTPUT ARGS ********************


    //**************** OUTPUT ARGS ********************

} // namespace eop



#endif