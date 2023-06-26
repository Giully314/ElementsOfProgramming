#ifndef ORBIT_ACTIONS_HPP
#define ORBIT_ACTIONS_HPP

/*
orbit_actions.hpp

PURPOSE:

FUNCTIONS:

DESCRIPTION:


TODO:
    - run tests to check correctness.

*/

#include "function_concepts.hpp"
#include "utility_concepts.hpp"
#include "pair.hpp"

namespace eop
{
    struct OrbitAct
    {
         // Precondition: y is reachable from x under f.
        template <typename F>
            requires action<F>
        static constexpr
        distance_type_t<F> distance(domain_t<F>& x, const domain_t<F>& y, F f)
        {
            using N = distance_type_t<F>;
            N n{0};
            while (x != y)
            {
                f(x);
                n = n + N{1};
            }
            return n;
        }


        // Precondition: p(x) <-> f(x) is defined.
        // Postcondition: value in x is the collision point.
        // The collision point is non terminating if the orbit has a cycle.
        template <typename F, typename P>
            requires action<F> && unary_predicate<P> && same_domain<F, P>
        static constexpr 
        void collision_point(domain_t<F>& x, F f, P p)
        {
            if (!p(x)) { return x; }

            domain_t<F> slow = x;
            f(x); //fast

            while (x != slow)
            {
                f(slow);
                if (!p(x)) { return x; }
                f(x);
                if (!p(x)) { return x; }
                x = f(x);
            }
        }


        // Precondition: p(x) <-> f(x) is defined.
        // The collision point is non terminating if the orbit has a cycle.
        template <typename F, typename P>
            requires action<F> && unary_predicate<P> && same_domain<F, P>
        static constexpr 
        bool terminating(domain_t<F>& x, F f, P p)
        {
            collision_point(x, f, p);
            return !p(x);
        }


        // Postcondition: the value in x is collision point.
        template <typename F>
            requires action<F>
        static constexpr 
        void collision_point_nonterminating_orbit(domain_t<F>& x, F f)
        {
            domain_t<F> slow = x;
            f(x); // fast

            while (x != slow)
            {
                f(slow);
                f(x);
                f(x);
            }
        }


        template <typename F>
            requires action<F>
        static constexpr 
        bool circular_nonterminating_orbit(domain_t<F>& x, F f)
        {
            domain_t<F> x0 = x;
            collision_point_nonterminating_orbit(x, f)
            f(x);
            return x0 == x;
        }


        // Precondition: p(x) <-> f(x) is defined.
        template <typename F, typename P>
            requires action<F> && unary_predicate<P> && same_domain<F, P>
        static constexpr 
        bool circular(domain_t<F>& x, F f, P p)
        {
            domain_t<F> x0 = x;
            collision_point(x, f, p)
            f(x);
            return p(x) && x0 == x;
        }


        // Precondition: exists n £ distance_type<F> s.t. n >= 0 and f^n(x0) == f^n(x1)
        // Convergent point is in x0.
        template <typename F>
            requires action<F>
        static constexpr 
        void convergent_point(domain_t<F>& x0, domain_t<F>& x1, F f)
        {
            while (x0 != x1)
            {
                f(x0);
                f(x1);
            }
        }


        template <typename F>
            requires action<F>
        static constexpr 
        void connection_point_nonterminating_orbit(domain_t<F>& x, F f)
        {
            domain_t<F> x0 = x;
            collision_point_nonterminating_orbit(x, f);
            f(x);
            convergent_point(x0, x, f);
        }

        // Precondition: p(x) <-> f(x) is defined.
        // Postcondition: 
        template <typename F, typename P>
            requires action<F> && unary_predicate<P> && same_domain<F, P>
        static constexpr 
        void connection_point(domain_t<F>& x, F f, P p)
        {
            domain_t<F> x0 = x;
            collision_point(x, f, p);
            if (!p(x)) { return; }
            f(x);
            convergent_point(x0, x, f);
        }


        // Exercise 2.2
        // The algorithm is based on the following lemma:
        // If the orbits of 2 elements intersect, they have the same cyclic elements.
        // Get both the collision points and check the cyclic elements if present.
        template <typename F, typename Px, typename Py>
            requires action<F> && unary_predicate<Px> && unary_predicate<Py> && 
            same_domain<F, Px> && same_domain<Px, Py>
        static constexpr 
        bool intersect(domain_t<F>& x, domain_t<F>& y, F f, Px px, Py py)
        {
            collision_point(x, f, px);
            collision_point(y, f, py);

            if (!px(x)) { return false; } 
            if (!py(y)) { return false; }


            // Save the collision point. If we reach the collision point again it means we 
            // completed a cycle without reaching x so the 2 cycles do not intersect.
            auto y_check = y;
            do
            {
                if (y_check == x) { return true; }
                f(y_check);
            } while (y_check != y);
            
            return false;
        }


        template <typename F>
            requires action<F> 
        static constexpr 
        bool intersect_nonterminating_orbit(domain_t<F>& x, domain_t<F>& y, F f)
        {
            collision_point(x, f, px);
            collision_point(y, f, py);

            // Save the collision point. If we reach the collision point again it means we 
            // completed a cycle without reaching x so the 2 cycles do not intersect.
            auto y_check = y;
            do
            {
                if (y_check == x) { return true; }
                f(y_check);
            } while (y_check != y);
            
            return false;
        }


        // Exercise 2.3 TODO.
        template <typename F>
            requires transformation<F> 
        static constexpr 
        domain_t<F> convergent_point_guarded(domain_t<F> x0, domain_t<F> x1, F f)
        {
           
        }


        // Postcondition: x is the connection point.
        template <typename F>
            requires action<F>
        static constexpr
        Pair<distance_type_t<F>, distance_type_t<F>>
        orbit_structure_nonterminating_orbit(domain_t<F>& x, F f)
        {
            using N = distance_type_t<F>;
            auto y = x;
            connection_point_nonterminating_orbit(y, f);
            auto d1 = distance(x, y, f);
            x = y;
            f(y);
            auto d2 = distance(y, x, f);
            return {d1, d2};    
        }


        // Precondition: p(x) <-> f(x) is defined.
        // Terminating orbit: m = h - 1 and n = 0.
        // Otherwise: m = h and n = c - 1. 
        template <typename F, typename P>
            requires action<F> && unary_predicate<P> && same_domain<F, P>
        static constexpr
        Pair<distance_type_t<F>, distance_type_t<F>>
        orbit_structure(domain_t<F>& x, F f, P p)
        {
            using N = distance_type_t<F>;
            auto y = x;
            connection_point(x, f, p);
            N m = distance(y, x, f);
            
            N n{0};
            if (p(x))
            {
                y = x;
                f(y);
                n = distance(f(y), x, f);
            }
            return {m, n};    
        }

    };
} // namespace eop



#endif