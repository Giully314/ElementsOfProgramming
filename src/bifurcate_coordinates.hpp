#pragma once

/*
bifurcate_coordinate.hpp

PURPOSE: define basic operations of bifurcate coordinates.
*/

#include "type_traits.hpp"
#include "bifurcate_coordinate_concepts.hpp"
#include "function_concepts.hpp"
#include "number.hpp"
#include "orbit_transformations.hpp"
#include "utility_types.hpp"

#include <concepts>

namespace eop
{
    // Precondition: has_predecessor(j)
    template <bidirectional_bifurcate T>
    [[nodiscard]]
    constexpr 
    bool is_left_successor(T j)
    {
        T i = j.predecessor();
        return i.has_left_successor() && i.left_successor() == j;
    }

    // Precondition: has_predecessor(j)
    template <bidirectional_bifurcate T>
    [[nodiscard]]
    constexpr
    bool is_right_successor(T j)
    {
        T i = j.predecessor();
        return i.has_right_successor() && i.right_successor() == j;
    }


    enum class visit
    {
        pre, // before left successor
        in, // after left successor but before right
        post // after right 
    };


    // Precondition: tree(c)
    template <bifurcate_coordinate C>
    [[nodiscard]]
    constexpr
    weight_type_t<C> weight_recursive(C c)
    {
        using N = weight_type_t<C>;

        if (c.empty())
        {
            return N{0};
        }
        N l{0};
        N r{0};

        if (c.has_left_successor())
        {
            l = weight_recursive(c.left_successor());
        }
        if (c.has_right_successor())
        {
            r = weight_recursive(c.right_successor());
        }
        return l + r + 1;
    }

    // Precondition: tree(c)
    template <bifurcate_coordinate C>
    [[nodiscard]]
    constexpr
    weight_type_t<C> height_recursive(C c)
    {
        using N = weight_type_t<C>;

        if (c.empty())
        {
            return N{0};
        }
        N l{0};
        N r{0};

        if (c.has_left_successor())
        {
            l = weight_recursive(c.left_successor());
        }
        if (c.has_right_successor())
        {
            r = weight_recursive(c.right_successor());
        }
        return Integer::max(l, r) + 1;
    }


    // Precondition: tree(c) and !c.empty()
    template <bifurcate_coordinate C, binary_procedure Proc>
        requires std::same_as<input_type_t<Proc, 0>, visit> && 
            std::same_as<input_type_t<Proc, 1>, C>
    [[nodiscard]]
    constexpr
    Proc traverse_nonempty(C c, Proc proc)
    {
        proc(visit::pre, c);

        if (c.has_left_successor())
        {
            proc = traverse_nonempty(c.left_successor(), proc);
        }

        proc(visit::in, c);

        if (c.has_right_successor())
        {
            proc = traverse_nonempty(c.right_successor(), proc);
        }

        proc(visit::post, c);
        return proc;
    }



    // The value returned is the change in height.
    // Precondition: c.has_predecessor() && v != post
    template <bidirectional_bifurcate C>
    constexpr
    int traverse_step(visit& v, C& c)
    {
        switch (v)
        {
        case visit::pre:
            if (c.has_left_successor())
            {
                c = c.left_successor();
                return 1;
            }
            v = visit::in;
            return 0;
        
        case visit::in:
            if (c.has_right_successor())
            {
                c = c.right_successor();
                return 1;
            }
            v = visit::post;
            return 0;

        case visit::post:
            if (is_left_successor(c))
            {
                v = visit::in;
            }
            c = c.predecessor();
            return -1;
        }
    }


    // Precondition: tree(x)
    template <bidirectional_bifurcate C>
    [[nodiscard]]
    constexpr
    bool reachable(C x, C y)
    {
        if (c.empty())
        {
            return false;
        }
        C root = x;
        visit v = visit::pre;

        do
        {
            if (x == y)
            {
                return true;
            }
            traverse_step(v, x);
        } while (x != root || v != visit::post);
    }


    // Precondition: tree(c)
    template <bidirectional_bifurcate C>
    weight_type_t<C> weight(C c)
    {
        using N = weight_type_t<C>;

        if (c.empty())
        {
            return N{0};
        }

        C root = c;
        visit v = visit::pre;
        N n{1}; // Invariant: n is count of pre visits so far.
        do
        {
            traverse_step(v, c);
            if (v == visit::pre)
            {
                ++n;
            }
        } while (c != root || v != post);
        return n;
    }

    // Precondition: tree(c)
    template <bidirectional_bifurcate C>
    weight_type_t<C> height(C c)
    {
        using N = weight_type_t<C>;

        if (c.empty())
        {
            return N{0};
        }

        C root = c;
         visit v = visit::pre;
        N n{1}; // Invariant: n is max of height of pre visits so far.
        N m{1}; // Invariant: m is height of current pre visit.
        do
        {
            m = m - N{1} + N{traverse_step(v, c) + 1};
            n = Integer::max(n, m); 
        } while (c != root || v != post);
        return n;
    }


    // Precondition: tree 
    template <bidirectional_bifurcate C, binary_procedure Proc>
        requires std::same_as<input_type_t<Proc, 0>, visit> && 
            std::same_as<input_type_t<Proc, 1>, C>
    Proc traverse(C c, Proc proc)
    {
        if (c.empty())
        {
            return proc;
        }
        C root = c;
        visit v = visit::pre;
        proc(pre, c);
        do
        {
            traverse_step(v, c);
            proc(v, c);
        } while (c != root || v != post);
    }



    // Exercise 7.3
    template <bidirectional_bifurcate C>
    bool is_dag(C c)
    {
           
    }


    template <bidirectional_bifurcate C>
    class BidirectionalBifurcateIterator
    {
    public:
           

    private:
        non_owned_ptr<C> p = nullptr;
    };

} // namespace eop
