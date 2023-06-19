#ifndef CONCEPTS_HPP
#define CONCEPTS_HPP

/*
concepts.hpp


PURPOSE: define compile time predicates on types.

CONCEPTS:
    object: T is an object.
    default_constructible: T has a default constructor.
    movable: T can be moved.
    copyable: T can be copied. (Note: only copied, move is not required)
    partially_regular: T is default constructible, movable, copyable and destructible.
    regular: T is partially regular and equality comparable. *

    Note: The distinction is purely semantic.
    procedure: F is a function that can be called with Args.
    input_procedure: F is a procedure that only read the Args.
    output_procedure: F is a procedure that only write the Args.
    io_procedure: F is both input and output procedure.


* Actually in the book the regular concept has another property to be satisfied called underlying_type. 
I prefer to call it the header type. An header type is a type that is composed of an header and data.
The header has info about the data (size, stream open, and so on) while the data could be a file opened, a stream,
a piece of memory. When a type is composed in this way we can swap just the header and the reference to the data
instaed of copying/moving the data. Implementing this property as a concept is actually "hard" and not really 
useful in practice for a regular type. It can be implemented as an additional requirement for particular 
implementations of swap.


DESCRIPTION:
A concept is a compile time predicate that check if a type has some defined properties. The abstraction of the concept, that is, the 
possibility to reason not on concrete types but on a set of features that a type must have, allows to define algorithms 
and data structures in terms of properties and not in terms of types. 
Formally a concept is a description of requirements on one or more types on syntactic, semantic and requirements that these 
types must satisfy.


TODO:
- add the concept of direct/indirect type. The concept must be valid even for pointer-like objects (smart pointers
    or custom classes that act like pointers).


THOUGHTS:
Concepts are my favorite feature of C++20. They allow the definition of properties on types on a level of abstraction
that i find it beautiful and useful.
Note that the focus of this project is not to learn the syntax or the tricks on how to implement concepts 
or type_traits but to understand the abstraction and the hierarchy of properties on types.
I will use the standard library for basic concepts and type_traits to avoid to move the focus on other things.

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
    concept same_args = sizeof...(Args) == 0 || (std::same_as<T, Args> && ...);

    // ************************* UTILITY CONCEPTS *****************************************************



    template <typename T>
    concept object = std::is_object_v<T>;

    template <typename T>
    concept default_constructible = std::default_initializable<T>;

    template <typename T>
    concept movable = object<T> && std::move_constructible<T> && std::assignable_from<T&, T> && 
        std::swappable<T>;

    template <typename T>
    concept copyable = std::copy_constructible<T> && std::assignable_from<T&, T&> && 
        std::assignable_from<T&, const T&> && std::assignable_from<T&, const T>;

    template <typename T>
    concept partially_regular = default_constructible<T> && movable<T> && copyable<T> && std::destructible<T>;

    template <typename T>
    concept regular = partially_regular<T> && std::equality_comparable<T>;


    template <typename F, typename ...Args>
    concept procedure = std::invocable<F, Args...>;

    template <typename F, typename ...Args>
    concept input_procedure = procedure<F, Args...>;

    template <typename F, typename ...Args>
    concept output_procedure = procedure<F, Args...>;

    template <typename F, typename ...Args>
    concept io_procedure = input_procedure<F, Args...> && output_procedure<F, Args...>; 


    template <typename F, typename ...Args>
    concept regular_procedure = procedure<F, Args...> && (regular<Args> && ...);

    template <typename F, typename ...Args>
    concept functional_procedure = regular_procedure<F, Args...> && (direct_type<Args> && ...) && 
        non_void<std::invoke_result_t<F, Args...>>;

    template <typename F, typename ...Args>
    concept homogeneous_procedure = functional_procedure<F, Args...> && same_args<Args...>;

    template <typename F, typename ...Args>
    concept unary_function = functional_procedure<F, Args...> && (sizeof...(Args) == 1);


} // namespace eop



#endif