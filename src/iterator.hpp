#pragma once

/*
iterator.hpp
*/

#include <concepts>
#include "type_concepts.hpp"
#include "ordering_concepts.hpp"
#include "type_traits.hpp"
#include "number.hpp"

namespace eop
{   
    struct readable_iterator_tag {};
    struct output_iterator_tag{};
    struct forward_iterator_tag : public readable_iterator_tag {};
    struct bidirectional_iterator_tag : public forward_iterator_tag {};
    struct random_access_iterator_tag : public bidirectional_iterator_tag {};


    template <typename T>
    concept readable = regular<T> && requires (T a)
    {
        typename T::value_type;
        typename T::iterator_tag;
        requires std::derived_from<typename T::iterator_tag, readable_iterator_tag>;

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
        requires std::derived_from<typename T::iterator_tag, forward_iterator_tag>;  
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
        requires std::derived_from<typename T::iterator_tag, bidirectional_iterator_tag>;

        // These operations are done in constant time.
        {--a} -> std::same_as<T&>;
        {a--} -> std::same_as<T>;

        // if successor(i) is defined -> predecessor(successor(i)) = i
    }; 


    template <typename T>
    concept random_access_iterator = indexed_iterator<T> && bidirectional_iterator<T> && totally_ordered<T> &&
        requires (T a, distance_type_t<T> n)
    {
        requires std::derived_from<typename T::iterator_tag, random_access_iterator_tag>;

        // All the operations are done in constant time: +, -, <.
        {a + n} -> std::same_as<T>;
        {a - n} -> std::same_as<T>;
    };



    // Precondition: n >= 0 && weak_range(f, n)
    template <iterator I>
    I operator+(I f, distance_type_t<I> n)
    {
        while (!Integer::is_zero(n))
        {
            --n;
            ++f;
        }
        return f;
    }


    // Precondtion: bounded_range(f, l)
    template <iterator I>
    distance_type_t<I> operator-(I l, I f)
    {
        distance_type_t n{0};
        while (f != l)
        {
            ++n;
            ++f;
        }
        return n;
    }


    // Precondition: n >= 0 && £f s.t. weak_range(f, n) && l = f + n.
    template <bidirectional_iterator I>
    I operator-(I l, distance_type_t<I> n)
    {
        while (!Integer::is_zero(n))
        {
            --n;
            --l;
        }
        return l;
    }    
} // namespace eop
