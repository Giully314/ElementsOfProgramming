#ifndef ORDERING_CONCEPTS_HPP
#define ORDERING_CONCEPTS_HPP

#include <concepts> 
#include "type_concepts.hpp"
#include "function_concepts.hpp"


namespace eop
{
    template <typename T>
    concept totally_ordered = regular<T> && requires (T a, T b)
    {
        {a < b} -> std::convertible_to<bool>;
    };
} // namespace eop



#endif 