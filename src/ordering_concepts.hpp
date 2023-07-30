#pragma once

#include <concepts> 
#include "type_concepts.hpp"
#include "function_concepts.hpp"
#include "relation_concepts.hpp"
#include "relations.hpp"


namespace eop
{
    // Property: weak ordering.
    template <typename F>
    concept weak_ordering_relation = relation<F>;

    // Property: total ordering.
    template <typename F>
    concept total_ordering_relation = relation<F>;

    template <typename T>
    concept totally_ordered = regular<T> && total_ordering_relation<less<T>> && has_less_op<T>;
} // namespace eop
