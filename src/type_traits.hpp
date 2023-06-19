#ifndef TYPE_TRAITS_HPP
#define TYPE_TRAITS_HPP

/*
type_traits.hpp

PURPOSE: manipulate and check traits on types at compile time.

CONCEPTS:


DESCRIPTION:
type traits are the foundation of concepts. Manipulate and check properties on types at compile time,
define functions from a type to another and so on.



THOUGHTS:
Note that the focus of this project is not to learn the syntax or the tricks on how to implement concepts 
or type_traits but to understand the abstraction and the hierarchy of properties on types.
I will use the standard library for basic concepts and type_traits to avoid to move the focus on other things.

*/

#include "mpl.hpp"

namespace eop
{

    //*************** INPUT TYPE *********************

    template <typename F, size_t I>
    struct input_type
    {
        using type = mpl::extract_t<mpl::params_of_function_t<F>, I>;
    };

    template <typename F, size_t I>
    using input_type_t = typename input_type<F, I>::type;

    //*************** INPUT TYPE *********************
} // namespace eop



#endif