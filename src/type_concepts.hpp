#ifndef TYPE_CONCEPTS_HPP
#define TYPE_CONCEPTS_HPP

/*
type_concepts.hpp


PURPOSE: define compile time predicates on types.

CONCEPTS:
    object: T is an object.
    default_constructible: T has a default constructor.
    movable: T can be moved.
    copyable: T can be copied. (Note: only copied, move is not required)
    partially_regular: T is default constructible, movable, copyable and destructible.
    regular: T is partially regular and equality comparable. *


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

*/

#include <type_traits>
#include <concepts>

namespace eop
{
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

} // namespace eop


#endif