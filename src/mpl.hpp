#ifndef MPL_HPP
#define MPL_HPP

/*
mpl.hpp

PURPOSE: small metaprogramming header to support operations on types.

STRUCTS:
    typelist:           store a list of types.
    front:              access the first type of a typelist.
    extract:            extract the ith type of a typelist.
    callable:           get informations about a callable.
    is_callable:        check if a type is callable.
    num_of_params:      get the number of parameters of a callable.
    direct_params:      check if the parameters of a callable are direct (non pointers).
    regular_params:     check if the parameters of a callable are regular.
    homogeneous_params: check if the parameters of a callable are all the same.

DESCRIPTION:

USAGE:

*/

#include <functional>
#include <type_traits>
#include "type_concepts.hpp"


namespace eop
{

    template <typename ...Args> 
    struct typelist { };


    //***************************** SIZE OF TYPE LIST *******************************

    template <typename TList>
    struct list_size;

    template <typename ...Args>
    struct list_size<typelist<Args...>> 
    {
        inline static constexpr unsigned int value = sizeof...(Args);
    };


    template <typename TList>
    inline constexpr unsigned int list_size_v = list_size<TList>::value;

    //***************************** SIZE OF TYPE LIST *******************************


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
    struct extract : public extract<pop_front_t<TList>, I - 1>
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


    //*************************** IS CALLABLE ****************************

    template <typename F, typename TList>
    struct is_callable;

    template <typename F, typename ...Args>
        requires std::is_invocable_v<F, Args...>
    struct is_callable<F, typelist<Args...>> : public std::bool_constant<std::is_invocable_v<F, Args...>> {};

    template <typename F>
    inline constexpr bool is_callable_v = is_callable<F, params_of_function_t<F>>::value;   

    //*************************** IS CALLABLE ****************************


    //************************** NUMBER OF PARAMS *************************

    template <typename F>
    inline constexpr unsigned int num_of_params_v = list_size_v<params_of_function_t<F>>;

    //************************** NUMBER OF PARAMS *************************


    //************************** REGULAR PARAMS ***************************

    template <typename F, typename TList>
    struct regular_params;

    template <typename F, typename ...Args>
    struct regular_params<F, typelist<Args...>> : public std::false_type {};
    
    template <typename F, regular ...Args>
    struct regular_params<F, typelist<Args...>> : public std::true_type {};

    template <typename F>
    inline constexpr bool regular_params_v = regular_params<F, params_of_function_t<F>>::value;

    //************************** REGULAR PARAMS ***************************


    //************************** REMCV REGULAR PARAMS ***************************

    template <typename F, typename TList>
    struct remcvref_regular_params;

    template <typename F, typename ...Args>
    struct remcvref_regular_params<F, typelist<Args...>> : public std::false_type {};
    
    template <typename F, typename ...Args>
        requires (regular<std::remove_cvref_t<Args>> && ...)
    struct remcvref_regular_params<F, typelist<Args...>> : public std::true_type {};

    template <typename F>
    inline constexpr bool remcvref_regular_rmparams_v = remcvref_regular_params<F, params_of_function_t<F>>::value;

    //************************** REMCV REGULAR PARAMS ***************************


    //************************** DIRECT PARAMS ****************************

    template <typename F, typename TList>
    struct direct_params;

    template <typename F, typename ...Args>
    struct direct_params<F, typelist<Args...>> : public std::bool_constant<(!std::is_pointer_v<Args> && ...)> {};


    template <typename F>
    inline constexpr bool direct_params_v = direct_params<F, params_of_function_t<F>>::value;

    //************************** DIRECT PARAMS ****************************


    //************************** HOMOGENEOUS PARAMS ******************************

    template <typename F, typename TList>
    struct homogeneous_params;

    template <typename F, typename T, typename ...Args>
    struct homogeneous_params<F, typelist<T, Args...>> : 
        public std::bool_constant<
            (std::same_as<std::remove_cvref_t<T>, std::remove_cvref_t<Args>> && ...)> {};

        //(std::is_same_v<unqualify_type_t<T>, unqualify_type_t<Args>> && ...)> {};



    template <typename F, typename T>
    struct homogeneous_params<F, typelist<T>> : public std::true_type {};

    template <typename F>
    struct homogeneous_params<F, typelist<>> : public std::true_type {};

    template <typename F>
    inline constexpr bool homogeneous_params_v = homogeneous_params<F, params_of_function_t<F>>::value;

    //************************** HOMOGENEOUS PARAMS ******************************



    //*************************** OUPUT TYPES ************************************

    template <typename TList> 
    struct at_least_one_reference;

    template <typename ...Args> 
    struct at_least_one_reference<typelist<Args...>> : 
        public std::bool_constant<(std::is_lvalue_reference_v<Args> || ...)>
    {};


    template <typename TList>
    inline constexpr bool at_least_one_reference_v = at_least_one_reference<TList>::value;

    //*************************** OUPUT TYPES ************************************

} // namespace eop


#endif