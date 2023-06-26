#ifndef FUNCTION_CONCEPTS_HPP
#define FUNCTION_CONCEPTS_HPP

/*
function_concepts.hpp


PURPOSE: define compile time predicates on functions.

CONCEPTS:
    Note: The distinction is purely semantic.
    procedure: F is a function that can be called with Args.
    input_procedure: F is a procedure that only read the Args.
    output_procedure: F is a procedure that only write the Args.
    io_procedure: F is both input and output procedure.

    regular_procedure:
    functional_procedure:
    homogeneous_procedure:
    unary_procedure:


DESCRIPTION:
A concept is a compile time predicate that check if a type has some defined properties. The abstraction of the concept, that is, the 
possibility to reason not on concrete types but on a set of features that a type must have, allows to define algorithms 
and data structures in terms of properties and not in terms of types. 
Formally a concept is a description of requirements on one or more types on syntactic, semantic and requirements that these 
types must satisfy.



USAGE:
    template <unary_procedure F>
    void apply()

*/

#include <concepts>
#include <type_traits>
#include "type_concepts.hpp"
#include "utility_concepts.hpp"
#include "mpl.hpp"
#include "type_traits.hpp"

namespace eop
{
    template <typename F>
    concept procedure = is_callable_v<F>;

    template <typename F>
    concept input_procedure = procedure<F>;

    template <typename F>
    concept output_procedure = procedure<F>;

    template <typename F>
    concept io_procedure = input_procedure<F> && output_procedure<F>; 


    template <typename F>
    concept regular_procedure = procedure<F> && regular_params_v<F>;

    template <typename F>
    concept functional_procedure = regular_procedure<F> && direct_params_v<F> && 
        non_void<return_type_of_function_t<F>>;

    template <typename F>
    concept homogeneous_procedure = functional_procedure<F> && homogeneous_params_v<F>;

    template <typename F>
    concept unary_procedure = functional_procedure<F> && num_of_params_v<F> == 1;


    template <typename F>
    concept predicate = functional_procedure<F> && std::same_as<codomain_t<F>, bool>;

    template <typename F>
    concept homogeneous_predicate = predicate<F> && homogeneous_procedure<F>;

    template <typename F>
    concept unary_predicate = predicate<F> && unary_procedure<F>;

    template <typename F>
    concept operation = homogeneous_procedure<F> && std::same_as<domain_t<F>, codomain_t<F>>;

    template <typename F>
    concept transformation = operation<F> && unary_procedure<F> && std::integral<distance_type_t<F>>;


    template <typename F>
    concept action = operation<F> && unary_procedure<F> && std::integral<distance_type_t<F>> && 
                        std::is_lvalue_reference_v<domain_t<F>>;

} // namespace eop



#endif