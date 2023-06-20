#ifndef UTILITY_CONCEPTS_HPP
#define UTILITY_CONCEPTS_HPP


/*
utility_concepts.hpp

CONCEPTS:
    direct_type: check if a type is direct (non pointer).
    non_void:    check if a type is non void.
    same_args:   check if all types are the same.

DESCRIPTION:
A concept is a compile time predicate that check if a type has some defined properties. The abstraction of the concept, that is, the 
possibility to reason not on concrete types but on a set of features that a type must have, allows to define algorithms 
and data structures in terms of properties and not in terms of types. 
Formally a concept is a description of requirements on one or more types on syntactic, semantic and requirements that these 
types must satisfy.




TODO:
- add the concept of direct/indirect type. The concept must be valid even for pointer-like objects (smart pointers
    or custom classes that act like pointers).

*/



#include <concepts> 
#include <type_traits>

namespace eop
{
    // ************************* UTILITY CONCEPTS *****************************************************
    template <typename T>
    concept direct_type = !std::is_pointer_v<T>;

    template <typename T>
    concept non_void = !std::is_void_v<T>;

    template <typename T, typename ...Args>
    concept same_types = sizeof...(Args) == 0 || (std::same_as<T, Args> && ...);

    // ************************* UTILITY CONCEPTS *****************************************************
} // namespace eop

#endif