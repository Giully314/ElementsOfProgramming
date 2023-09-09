#pragma once

/*
vector.hpp

PURPOSE:

CLASSES:

DESCRIPTION:

*/

#include "type_concepts.hpp"
#include <utility>
#include <concepts>
#include <memory>
#include <cstring>

namespace eop
{
    // Satisfy the random_access_iterator_concept.
    template <typename T>
    class VectorIterator
    {

    };



    template <typename T>
        requires movable<T> || copyable<T>
    class Vector
    {
    public:
        using value_type = T;
        using allocator = std::allocator<T>;
        using size_type = size_t;
        using iterator = VectorIterator<T>;
        using const_iterator = const iterator;


        Vector() = default;

        Vector(const Vector&);
        Vector& operator=(const Vector&);

        Vector(Vector&&);
        Vector& operator=(Vector&&);


        template <typename ...Args>
            requires std::constructible_from<T, Args...>
        void emplace_back(Args&& ...args)
        {
            should_reallocate();
            std::construct_at(&data[size++], std::forward<Args>(args)...);
        }


        void reserve(size_type new_capacity)
        {
            if (new_capacity <= capacity)
            {
                return;
            }

            allocate_and_move(new_capacity);
        }


    private:
        // Reallocate if necessary.
        // If the type is trivially copyable, just do a memcpy.
        void should_reallocate() requires std::is_trivially_copyable_v<T>
        {
            if (size < capacity) [[likely]]
            {
                return;
            }

            allocate_and_move((capacity + 1) * load_factor);   
        }


        // allocate a new memory and copy/move the data.
        void allocate_and_move(size_type new_capacity) requires std::is_trivially_copyable_v<T>
        {
            auto new_data = std::make_unique<T[]>(new_capacity);

            if (size == 0) // nothing to copy
            {
                data = std::move(new_data);
            }
            else
            {
                std::memcpy(new_data.get(), data.get(), sizeof(T) * size);
            }
        }


        void allocate_and_move(size_type new_capacity) requires movable<T>;
        void allocate_and_move(size_type new_capacity);


    private:
        std::unique_ptr<T[]> data;
        size_type size = 0;
        size_type capacity = 0;
        size_type load_factor = 2;
    };
} // namespace eop