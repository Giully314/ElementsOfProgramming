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


namespace eop
{

    // ************************ PROPERTIES *************************************************


    // ************************ PROPERTIES *************************************************



    // ************************* PRECONDITIONS *********************************************


    // ************************* PRECONDITIONS *********************************************



    
} // namespace eop

#endif 