#pragma once


/*
bifurcate_algorithms.hpp

PURPOSE:

FUNCTIONS:


DESCRIPTION:


*/


#include "bifurcate_coordinate_concepts.hpp"
#include "bifurcate_coordinates.hpp"
#include "function_concepts.hpp"
#include "type_traits.hpp"

namespace eop
{
    template <bidirectional_bifurcate C, unary_procedure Proc>
        requires std::same_as<domain_t<Proc>, value_type_t<C>>
    void for_each(C c, Proc p)
    {
        visit v;
        auto root = c;

        do
        {

        } 
    } 
} // namespace eop
