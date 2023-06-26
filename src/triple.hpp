#ifndef TRIPLE_HPP
#define TRIPLE_HPP

/*
triple.hpp

PURPOSE:

CLASSES:

DESCRIPTION:

*/


namespace eop
{
    // TODO: incomplete.
    template <typename T1, typename T2, typename T3>
    struct Triple
    {
        Triple() = default;

        Triple(const T1& f, const T2& s, const T3& t) : first(f), second(s), third(t)
        {

        }

        T1 first;
        T2 second;
        T3 third;
    };

} // namespace eop



#endif 