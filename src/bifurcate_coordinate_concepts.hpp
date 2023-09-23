#pragma once

/*
bifurcate_coordinate_concepts.hpp
*/

#include <concepts>
#include "type_concepts.hpp"

namespace eop
{   
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
