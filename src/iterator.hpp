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
            ++n;
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
} // namespace eop
