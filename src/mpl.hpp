#ifndef MPL_HPP
#define MPL_HPP

/*
mpl.hpp

PURPOSE: small metaprogramming header to support operations on types.

STRUCTS:
    typelist: store a list of types.
    front: access the first type of a typelist.
    extract: extract the ith type of a typelist.
    callable: get informations about a callable.

DESCRIPTION:

THOUGHTS:

*/

#include <functional>


namespace eop
{
    template <typename ...Args> 
    struct typelist { };


    //************************   FRONT     ****************************

    template <typename TList>
    struct front;

    template <typename Head, typename ...Tail>
    struct front<typelist<Head, Tail...>>
    {
        using type = Head;
    };

    template <typename TList>
    using front_t = typename front<TList>::type;

    //************************   FRONT     ****************************


    //************************   POP_FRONT     ****************************

    template <typename TList>
    struct pop_front;

    template <typename Head, typename ...Tail>
    struct pop_front<typelist<Head, Tail...>>
    {
        using type = typelist<Tail...>;
    };  

    template <typename TList>
    using pop_front_t = typename pop_front<TList>::type;

    //************************   POP_FRONT     ****************************



    //************************   EXTRACT     ****************************

    template <typename TList, unsigned I>
    struct extract : public extract<pop_front<TList>, I - 1>
    {
    };

    template <typename TList>
    struct extract<TList, 0> : public front<TList>
    {
        
    };

    template <typename TList, size_t I>
    using extract_t = typename extract<TList, I>::type;

    //************************   EXTRACT     ****************************



    //*************** CALLABLE INFO *******************
    

    template <typename F>
    struct callable_info;

    template <typename Result, typename ...Args>
    struct callable_info<std::function<Result(Args...)>>
    {
        using return_type = Result;
        using params = typelist<Args...>;
    };


    template <typename F>
    struct return_type_of_function
    {
        using function_type = decltype(std::function{std::declval<F>()});
        using type = typename callable_info<function_type>::return_type;
    };

    template <typename F>
    using return_type_of_function_t = typename return_type_of_function<F>::type;


    template <typename F>
    struct params_of_function
    {
        using function_type = decltype(std::function{std::declval<F>()});
        using type = typename callable_info<function_type>::params;
    };

    template <typename F>
    using params_of_function_t = typename params_of_function<F>::type;

    //*************** CALLABLE INFO *******************


} // namespace eop


#endif