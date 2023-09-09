#pragma once

/*
iterator.hpp
*/

#include "iterator_concepts.hpp"
#include "type_traits.hpp"
#include "number.hpp"

namespace eop
{
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


    
    struct readable_iterator_tag {};
    struct output_iterator_tag{};
    struct forward_iterator_tag{};
    struct bidirectional_iterator_tag{};
    struct random_access_iterator_tag{};


} // namespace eop
