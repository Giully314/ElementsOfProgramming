#pragma once

/*
vector.hpp

PURPOSE:

CLASSES:
    ConstVectorIterator: Iterator for cbegin, cend.
    VectorIterator: Iterator for begin, end.
    Vector: a dynamic array.

DESCRIPTION:
    A dynamic array inspired by std::vector.

TODO:
    destruction should be fast if the type is trivial. Just a free is enough in this case.

*/

#include "type_concepts.hpp"
#include "iterator.hpp"
#include "utility_types.hpp"

#include <compare>
#include <utility>
#include <concepts>
#include <memory>
#include <cstring>
#include <cstddef>

namespace eop
{
    // Satisfy the random_access_iterator_concept.
    template <typename T>
    class ConstVectorIterator
    {
    public:
        using iterator_category = random_access_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = const T;
        using pointer = T*;
        using const_pointer = const T*;
        using reference = T&;
        using const_reference = const T&;
        using size_type = std::size_t;


        ConstVectorIterator() = default;
        
        explicit ConstVectorIterator(const non_owned_ptr<T> p_) : p(p_)
        {

        }

        friend
        constexpr 
        auto operator<=>(const ConstVectorIterator&, const ConstVectorIterator&) = default;


        const_reference operator*() const
        {
            return *p;
        }

        const_pointer operator->() const
        {
            return p;
        }


        ConstVectorIterator& operator++()
        {
            ++p;
            return *this;
        }


        [[nodiscard]]
        ConstVectorIterator operator++(int)
        {
            auto temp = *this;
            ++(*this);
            return temp;
        }


        ConstVectorIterator& operator--()
        {
            --p;
            return *this;
        }

        [[nodiscard]]
        ConstVectorIterator operator--(int)
        {
            auto n = p;
            --p;
            return n;
        }


        ConstVectorIterator& operator+=(const std::size_t n)
        {
            p += n;
            return *this;
        }

        ConstVectorIterator& operator-=(const std::size_t n)
        {
            p -= n;
            return *this;
        }


        [[nodiscard]]
        friend
        ConstVectorIterator operator+(ConstVectorIterator a, const std::size_t n)
        {
            a += n;
            return a;
        }


        [[nodiscard]]
        friend
        ConstVectorIterator operator-(ConstVectorIterator a, const std::size_t n)
        {
            a -= n;
            return a;
        }

        // Precondition: a and b are iterator to the same vector.
        [[nodiscard]]
        friend
        size_type operator-(const ConstVectorIterator& a, const ConstVectorIterator& b)
        {
            return b.p - a.p;
        }   
    
    private:
        non_owned_ptr<T> p = nullptr;
    };


    template <typename T>
    class VectorIterator : public ConstVectorIterator<T> // ??, seen from mvc
    {
    public:
        using iterator_category = random_access_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = value_type*;
        using const_pointer = const value_type*;
        using reference = value_type&;
        using const_reference = const value_type&;
        using size_type = std::size_t;


        VectorIterator() = default;
        
        explicit VectorIterator(non_owned_ptr<T> p_) : p(p_)
        {

        }

        friend
        constexpr 
        auto operator<=>(const VectorIterator&, const VectorIterator&) = default;


        reference operator*()
        {
            return *p;
        }

        pointer operator->()
        {
            return p;
        }


        VectorIterator& operator++()
        {
            ++p;
            return *this;
        }

        VectorIterator operator++(int)
        {
            VectorIterator temp = *this;
            ++(*this);
            return temp;
        }


        VectorIterator& operator--()
        {
            --p;
            return *this;
        }

        VectorIterator operator--(int)
        {
            VectorIterator n = p;
            --p;
            return n;
        }


        VectorIterator& operator+=(const std::size_t n)
        {
            p += n;
            return *this;
        }

        VectorIterator& operator-=(const std::size_t n)
        {
            p -= n;
            return *this;
        }


        [[nodiscard]]
        friend
        VectorIterator operator+(VectorIterator a, const std::size_t n)
        {
            a += n;
            return a;
        }


        [[nodiscard]]
        friend
        VectorIterator operator-(VectorIterator a, const std::size_t n)
        {
            a -= n;
            return a;
        }


        // Precondition: a and b are iterator to the same vector.
        [[nodiscard]]
        friend
        size_type operator-(const VectorIterator& a, const VectorIterator& b)
        {
            return b.p - a.p;
        }


    private:
        non_owned_ptr<T> p = nullptr;
    };




    template <typename T>
        requires movable<T> || copyable<T>
    class Vector
    {
    public:
        using value_type = T;
        using allocator = std::allocator<T>;
        using size_type = std::size_t;
        using iterator = VectorIterator<T>;
        using const_iterator =  ConstVectorIterator<T>;


        Vector() = default;

        Vector(const Vector& other)
        {
            copy_from(other);
        }

        Vector& operator=(const Vector& other)
        {
            copy_from(other);
            return *this;
        }


        Vector(Vector&& other)
        {
            move_from(other);
        }

        Vector& operator=(Vector&& other)
        {
            move_from(other);
            return *this;
        }


        // Return the last element. Throw if out of range.
        constexpr
        value_type& back()
        {
            return data[num_of_elements-1];
        }

        // Return the last element. Throw if out of range.
        constexpr
        const value_type& back() const
        {
            return data[num_of_elements-1];
        }

        // Return the first element. Throw if out of range.
        constexpr
        value_type& front()
        {
            return data[0];
        }

        // Return the first element. Throw if out of range.
        constexpr
        const value_type& front() const
        {
            return data[0];
        }


        constexpr 
        size_type size() const noexcept 
        {
            return num_of_elements;
        }

        constexpr
        size_type capacity() const noexcept 
        {
            return num_of_elements;
        }



        template <typename ...Args>
            requires std::constructible_from<T, Args...>
        void emplace_back(Args&& ...args)
        {
            should_reallocate();
            std::construct_at(&data[num_of_elements++], std::forward<Args>(args)...);
        }


        void reserve(size_type new_capacity)
        {
            if (new_capacity <= max_capacity)
            {
                return;
            }

            allocate_and_move(new_capacity);
        }


        [[nodiscard]]
        constexpr 
        iterator begin() noexcept 
        {
            return VectorIterator(data.get());
        }

        [[nodiscard]]
        constexpr 
        const_iterator begin() const noexcept 
        {
            return ConstVectorIterator(data.get());
        }


        [[nodiscard]]
        constexpr 
        iterator end()
        {
            return VectorIterator(&data[num_of_elements]);
        }

        [[nodiscard]]
        constexpr 
        const_iterator end() const noexcept 
        {
            return ConstVectorIterator(&data[num_of_elements]);
        }   


        [[nodiscard]]
        constexpr const_iterator cbegin() const noexcept  
        {
            return ConstVectorIterator(data.get());
        }

        [[nodiscard]]
        constexpr const_iterator cend() const noexcept 
        {
            return ConstVectorIterator(&data[num_of_elements]);
        }


    private:

        void copy_from(const Vector& other)
        {
            num_of_elements = other.num_of_elements;
            max_capacity = other.max_capacity;
            data = std::make_unique<T[]>(num_of_elements);
            std::uninitialized_copy_n(other.data.get(), num_of_elements, data.get());
        }

        void move_from(Vector& other)
        {
            num_of_elements = other.num_of_elements;
            max_capacity = other.max_capacity;
            data = std::move(other.data);
        }


        // Reallocate if necessary.
        // If the type is trivially copyable, just do a memcpy.
        void should_reallocate() requires std::is_trivially_copyable_v<T>
        {
            if (num_of_elements < max_capacity) [[likely]]
            {
                return;
            }

            // the +1 is to avoid calling the function with max_capacity = 0.
            // This avoid to do a check inside the function but could not be an optimal
            // thing to do in terms of memory.
            allocate_and_move((max_capacity + 1) * load_factor);   
        }


        // allocate a new memory and copy/move the data.
        void allocate_and_move(size_type new_capacity) 
        {
            auto new_data = std::make_unique<T[]>(new_capacity);
            max_capacity = new_capacity;
            move_to(new_data);
            data = std::move(new_data);
        }


        // Precondition: new_data has capacity >= size.
        void move_to(const std::unique_ptr<T[]>& new_data)
        {
            if constexpr (std::is_trivially_copyable_v<T>)
            {
                std::memcpy(new_data.get(), data.get(), sizeof(T) * num_of_elements);
            }
            else if constexpr (movable<T>)
            {
                std::uninitialized_move_n(data.get(), num_of_elements, new_data.get());
            }
            else // do a copy
            {
                std::uninitialized_copy_n(data.get(), num_of_elements, new_data.get());
            }
        }


    private:
        std::unique_ptr<T[]> data;
        size_type num_of_elements = 0;
        size_type max_capacity = 0;
        size_type load_factor = 2;
    };
} // namespace eop