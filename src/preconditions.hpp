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

    /*
    property(op: binary_operation)
    associative: op
        op -> for each a, b, c £ domain(op) : op(op(a, b), c) = op(a, op(b, c))
    */

    /*
    property(op: binary_operation)
    commutative: op
        op -> for each a, b £ domain(op) : op(a, b) = op(b, a)
    */

    /*
    left distributive and right distributive.
    property(op1: binary_operation, op2: binary_operation)
    distributive: op1, op2 
        domain(op1) = domain(op2) and codomain(op1) = codomain(op2);
        op1, op2 -> for each a, b, c £ domain(op1) : op1(a, op2(b, c)) = op2(op1(a, b), op1(a, c)) 
    */

    /*
    property(r: relation)
    transitive: r
        r -> if r(a, b) && r(b, c) then r(a, c) 
    */

    /*
    property(r: relation)
    total_ordering: r
        r -> transitive && trichotomy law (r(a, b), r(b, a), a = b)             
    */

    /*
    property(r: relation)
    weak_ordering: r
        r -> transitive && trichotomy law on an equivalence relation e (r(a, b), r(b, a), e(a,b))             
    */


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