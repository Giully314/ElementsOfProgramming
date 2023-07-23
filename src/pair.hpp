#ifndef TRIPLE_HPP
#define TRIPLE_HPP

/*
pair.hpp

PURPOSE:

CLASSES:

DESCRIPTION:

*/


namespace eop
{
    // TODO: incomplete.
    template <typename T1, typename T2>
    struct Pair
    {
        Pair() = default;

        Pair(const T1& f, const T2& s) : first(f), second(s)
        {

        }

        T1 first;
        T2 second;
    };

} // namespace eop



#endif 