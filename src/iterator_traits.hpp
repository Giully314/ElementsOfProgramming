#pragma once


/*
iterator_traits.hpp

PURPOSE:


*/

namespace eop
{
    struct readable_iterator_tag {};
    struct output_iterator_tag{};
    struct forward_iterator_tag : public readable_iterator_tag {};
    struct bidirectional_iterator_tag : public forward_iterator_tag {};
    struct random_access_iterator_tag : public bidirectional_iterator_tag {};



} // namespace eop