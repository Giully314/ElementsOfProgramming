#ifndef PRECONDITIONS_HPP
#define PRECONDITIONS_HPP

/*

PURPOSE:

PRECONDITIONS:

DESCRIPTION:
Precondition is a check on the state of a specific object to make sure that some properties request 
by the function at the start are respected. Precondition, unlike concepts, are runtime and acts on the objects
passed to the function.


Properties = concepts + preconditions. Properties describes requirements on objects of types 
that have particular properties. 

*/

#define DEBUG


#ifdef DEBUG
#define PRECONDITION(f, ...) f(__VA_ARGS__)
#else
#define PRECONDITION(...)
#endif


#include <limits>


namespace eop
{

    // ************************ PROPERTIES *************************************************


    // ************************ PROPERTIES *************************************************



    // ************************* PRECONDITIONS *********************************************

    // Exercise 2.1
    // Return true if the addition is safe to do, false otherwise.
    bool check_int_addition(int a, int b)
    {
        if (a < 0 && b < 0)
        {
            return a + b < 0;
        }
        else if (a > 0 && b > 0)
        {
            return a + b > 0;
        }


        // This version has less comparisons
        // if (a < 0)
        // {
        //     return b >= std::numeric_limits<int>::min() - a;
        // }
        // if (a > 0)
        // {
        //     return b <= std::numeric_limits<int>::max() - a;
        // }

        return true;
    }


    // ************************* PRECONDITIONS *********************************************


} // namespace eop

#endif 