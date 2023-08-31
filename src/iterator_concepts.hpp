#pragma once


/*

iterator_concepts.hpp

*/


#include <concepts>
#include "type_concepts.hpp"
#include "type_traits.hpp"
#include "ordering_concepts.hpp"

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
    

    template <typename T>
    concept bifurcate_coordinate = regular<T> && requires (T a)
    {
        typename T::weight_type;
        requires std::integral<typename T::weight_type>;

        // True if the "node" is empty, that is, all other operations are invalid.
        { a.empty() } -> std::same_as<bool>; 
        
        { a.has_left_successor() } -> std::same_as<bool>;
        { a.has_right_successor() } -> std::same_as<bool>;
        { a.left_successor() } -> std::same_as<T>;
        { a.right_successor() } -> std::same_as<T>;

        // if b = a.left_successor() or  if b = a.right_successor() -> !b.empty().
    };


    template <typename T>
    concept bidirectional_bifurcate = bifurcate_coordinate<T> && 
        requires (T a)
    {
        { a.has_predecessor() } -> std::same_as<bool>;
        { a.predecessor() } -> std::same_as<T>;

        // The regularity implies that a.predecessor().left_successor() == a if a is a left child.
    };


} // namespace eop
