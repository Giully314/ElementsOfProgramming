#pragma once


/*
list.hpp

PURPOSE:

CLASSES:
    Node:
    ConstListIterator:
    ListIterator:
    List:


DESCRIPTION:
    A double linked list.
*/


#include <concepts>
#include <memory>
#include <utility>
#include <cstddef>

#include "type_concepts.hpp"
#include "utility_types.hpp"
#include "iterator_traits.hpp"



namespace eop
{
    template <typename T> 
    struct Node
    {
        using value_type = T;
        using self_type = Node<T>;

        Node() = default;
        
        template <typename ...Args>
            requires std::constructible_from<T, Args...> 
        Node(Args&& ...args) : data(std::forward<Args>(args)...)
        {

        }
        
        non_owned_ptr<self_type> prev = nullptr;
        std::unique_ptr<self_type> next;  
        T data;
    };



    template <typename T>
    class ConstListIterator
    {
    public:
        using iterator_category = bidirectional_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = const T;
        using pointer = T*;
        using const_pointer = const T*;
        using reference = T&;
        using const_reference = const T&;
        using size_type = std::size_t;


        ConstListIterator() = default;

        explicit ConstListIterator(non_owned_ptr<node_type> p_) : p(p_)
        {

        } 


        const_reference operator*() const 
        {
            return *p;
        }

        const_pointer operator->() const
        {
            return p;
        }


        ConstListIterator& operator++()
        {
            p = p->next.get();
            return *this; 
        }

        ConstListIterator operator++(int)
        {
            auto temp = *this;
            ++(*this);
            return temp;
        }

        ConstListIterator& operator--()
        {
            p = p->prev;
            return *this; 
        }

        ConstListIterator operator--(int)
        {
            auto temp = *this;
            --(*this);
            return temp;
        }





    private:
        using node_type = Node<T>;
        non_owned_ptr<node_type> p = nullptr;
    };



    template <typename T>
    class ConstListIterator
    {
    public:
        using node_type = Node<T>;

        using iterator_category = bidirectional_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = const T*;
        
        using reference =   T&;
        using const_reference = 
        using size_type = std::size_t;

        ConstListIterator() = default;

        explicit ConstListIterator(non_owned_ptr<node_type> p_) : p(p_)
        {

        }

        const_reference operator*() const
        {
            return *p;
        }

        const_pointer operator->() const
        {
            return p;
        }

    private:
        non_owned_ptr<node_type> p = nullptr;
    };

    
    template <typename T> 
        requires movable<T> || copyable<T> 
    class List 
    {
    public:
        using node_type = Node<T>;

        using value_type = T;
        using allocator_type = std::allocator<T>;
        using size_type = std::size_t;
        using difference_type = std::ptrdiff_t;
        using reference = value_type&;
        using const_reference = const value_type&;
        using pointer = std::allocator_traits<allocator_type>::pointer;
        using const_pointer = std::allocator_traits<allocator_type>::const_pointer;

        // TODO: typedef iterators


        List() = default;


        // To avoid recursion for unique_ptr deleter.
        ~List()
        {

        }

        [[nodiscard]]
        constexpr
        size_type size() const noexcept
        {
            return num_of_elements;
        }



        template <std::constructible_from<T> ...Args>
        void emplace_back(Args&& ...args)
        {
            if (root)
            {
                last->next = std::make_unique<node_type>(std::forward<Args>(args)...);
                last = last->next.get();
            }   
            else
            {
                root = std::make_unique<node_type>(std::forward<Args>(args)...);
                last = root.get();
            } 
        }


        template <std::constructible_from<T> ...Args>
        void emplace_front(Args&& ...args)
        {
            if (root)
            {
                auto new_node = std::make_unique<node_type>(std::forward<Args>(args)...);
                root->prev = new_node.get();
                new_node->next = std::move(root);
                root = std::move(new_node);
            }
            else
            {   
                root = std::make_unique<node_type>(std::forward<Args>(args)...);
                last = root.get();
            }
        }



    private:
        std::unique_ptr<node_type> root;
        non_owned_ptr<node_type> last = nullptr;
        size_type num_of_elements = 0;
    };
} // namespace eop
