#pragma once


/*

iterator_concepts.hpp

*/


#include <concepts>
#include "type_concepts.hpp"
#include "type_traits.hpp"

namespace eop
{
    template <typename T>
    concept readable = regular<T> && requires (T a)
    {
        typename T::value_type;
        {*a} -> std::same_as<typename T::value_type>;
    };


    template <typename T>
    concept iterator = regular<T> && requires (T a)
    {
        typename T::distance_type;
        requires std::integral<typename T::distance_type>;

        {++a} -> std::same_as<T&>; // not necessarily regular
        {a++};  // not necessarily regular
    };


    template <typename T>
    concept readable_iterator = iterator<T> && readable<T>;


    // Now the successor function (++ operator) is regular.
    template <typename T>
    concept forward_iterator = readable_iterator<T> && requires (T a)
    {
        { a++ } -> std::same_as<T>; // equality preserving  
    };


    template <typename T>
    concept indexed_iterator = forward_iterator<T> && requires (T a, distance_type_t<T> n)
    {
        // These operations are done in constant time.
        {a + n} -> std::same_as<T>;
        {a - a} -> std::same_as<typename T::distance_type>;
    };


    template <typename T>
    concept bidirectional_iterator = forward_iterator<T> && requires (T a)
    {
        // These operations are done in constant time.
        {--a} -> std::same_as<T&>;
        {a--} -> std::same_as<T>;

        // if successor(i) is defined -> predecessor(successor(i)) = i
    }; 


    template <typename T>
    concept random_access_iterator = indexed_iterator<T> && bidirectional_iterator<T> && totally_ordered<T> &&
        requires (T a, distance_type_t<T> n)
    {
        // All the operations are done in constant time: +, -, <.
        {a + n} -> std::same_as<T>;
        {a - n} -> std::same_as<T>;
    };
    
} // namespace eop
