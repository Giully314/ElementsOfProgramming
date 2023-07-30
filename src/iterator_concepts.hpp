#pragma once


/*

iterator_concepts.hpp

*/


#include <concepts>
#include "type_concepts.hpp"


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
        {a++} -> std::same_as<T>;  // not necessarily regular
    };


    template <typename T>
    concept readable_iterator = iterator<T> && readable<T>;
    
} // namespace eop
