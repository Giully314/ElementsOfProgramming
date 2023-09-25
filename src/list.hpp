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
#include <optional>

#include "type_concepts.hpp"
#include "utility_types.hpp"
#include "iterator.hpp"



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
        
        std::unique_ptr<self_type> next;
        non_owned_ptr<self_type> prev;

        // An empty optional represents the null node (end iterator).
        // It is always safe to access this data directly if the node is not the node
        // pointed by the end iterator.
        std::optional<T> data;
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

        [[nodiscard]]
        friend 
        bool operator=(ConstListIterator, ConstListIterator) = default;



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


        [[nodiscard]]
        friend
        ConstListIterator operator+(ConstantListIterator it, size_type n)
        {
            while (n > 0)
            {
                ++it;
                --n;
            }

            return it;
        }

        // Precondition: a and b must be iterators of the same range and 
        // a < b defined as a must come before b if we start from begin().
        [[nodiscard]]
        friend
        size_type operator-(ConstantListIterator a, ConstantListIterator b)
        {
            size_type n = 0;
            while (a != b)
            {
                ++a;
                ++n;
            }
            return n;
        }


    private:
        using node_type = Node<T>;
        non_owned_ptr<node_type> p = nullptr;
    };




    template <typename T>
    class ListIterator
    {
        using iterator_category = bidirectional_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = const T;
        using pointer = T*;
        using const_pointer = const T*;
        using reference = T&;
        using const_reference = const T&;
        using size_type = std::size_t;


        ListIterator() = default;

        explicit ListIterator(non_owned_ptr<node_type> p_) : p(p_)
        {

        } 

        [[nodiscard]]
        friend 
        bool operator=(ListIterator, ListIterator) = default;



        creference operator*() const 
        {
            return *p;
        }

        pointer operator->() const
        {
            return p;
        }


        ListIterator& operator++()
        {
            p = p->next.get();
            return *this; 
        }

        ListIterator operator++(int)
        {
            auto temp = *this;
            ++(*this);
            return temp;
        }

        ListIterator& operator--()
        {
            p = p->prev;
            return *this; 
        }

        ListIterator operator--(int)
        {
            auto temp = *this;
            --(*this);
            return temp;
        }


        // TODO: n could be negative meaning go backward.
        [[nodiscard]]
        friend
        ListIterator operator+(ListIterator it, size_type n)
        {
            while (n > 0)
            {
                ++it;
                --n;
            }

            return it;
        }

        // Precondition: a and b must be iterators of the same range and 
        // a < b defined as a must come before b if we start from begin().
        [[nodiscard]]
        friend
        size_type operator-(ListIterator a, ListIterator b)
        {
            size_type n = 0;
            while (a != b)
            {
                ++a;
                ++n;
            }
            return n;
        }


    private:
        using node_type = Node<T>;
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
        using iterator = ListIterator<T>;
        using const_iterator = ConstListIterator<T>;


        List()
        {
            null_node = std::make_unique<Node<T>>();
        }


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
                last->next = 
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



        iterator begin()
        {
            return ListIterator{root.get()};
        }

        const_iterator begin() const 
        {
            return ConstListIterator{root.get()};
        }



    private:
        std::unique_ptr<node_type> root;
        std::unique_ptr<node_type> null_node;
        non_owned_ptr<node_type> last = nullptr;

        size_type num_of_elements = 0;
    };
} // namespace eop
