#ifndef ORBIT_TRANSFORMATION_HPP
#define ORBIT_TRANSFORMATION_HPP

/*
orbit_transformations.hpp

PURPOSE:

FUNCTIONS:

DESCRIPTION:

*/

#include "function_concepts.hpp"
#include "utility_concepts.hpp"
#include "triple.hpp"

namespace eop
{
    struct OrbitTrf
    {

        // Precondition: y is reachable from x under f.
        template <typename F>
            requires transformation<F>
        static constexpr
        distance_type_t<F> distance(domain_t<F> x, const domain_t<F>& y, F f)
        {
            using N = distance_type_t<F>;
            N n{0};
            while (x != y)
            {
                x = f(x);
                n = n + N{1};
            }
            return n;
        }


        // Precondition: p(x) <-> f(x) is defined.
        // Postcondition: return value is collision point.
        // The collision point is non terminating if the orbit has a cycle.
        template <typename F, typename P>
            requires transformation<F> && unary_predicate<P> && same_domain<F, P>
        static constexpr 
        domain_t<F> collision_point(const domain_t<F>& x, F f, P p)
        {
            if (!p(x)) { return x; }

            domain_t<F> slow = x;
            domain_t<F> fast = f(x);

            while (fast != slow)
            {
                slow = f(slow);
                if (!p(fast)) { return fast; }
                fast = f(fast);
                if (!p(fast)) { return fast; }
                fast = f(fast);
            }
            return fast;
        }

        // Precondition: p(x) <-> f(x) is defined.
        // The collision point is non terminating if the orbit has a cycle.
        template <typename F, typename P>
            requires transformation<F> && unary_predicate<P> && same_domain<F, P>
        static constexpr 
        bool terminating(const domain_t<F>& x, F f, P p)
        {
            return !p(collision_point(x, f, p));
        }


        // Postcondition: return value is collision point.
        // Used 
        template <typename F>
            requires transformation<F>
        static constexpr 
        domain_t<F> collision_point_nonterminating_orbit(const domain_t<F>& x, F f)
        {
            domain_t<F> slow = x;
            domain_t<F> fast = f(x);

            while (fast != slow)
            {
                slow = f(slow);
                fast = f(fast);
                fast = f(fast);
            }
            return fast;
        }


        template <typename F>
            requires transformation<F>
        static constexpr 
        bool circular_nonterminating_orbit(const domain_t<F>& x, F f)
        {
            return x == f(collision_point_nonterminating_orbit(x, f));
        }


        // Precondition: p(x) <-> f(x) is defined.
        template <typename F, typename P>
            requires transformation<F> && unary_predicate<P> && same_domain<F, P>
        static constexpr 
        bool circular(const domain_t<F>& x, F f, P p)
        {
            domain_t<F> y = collision_point(x, f, p);
            return p(y) && x == f(y);
        }


        // Precondition: exists n £ distance_type<F> s.t. n >= 0 and f^n(x0) == f^n(x1)
        template <typename F>
            requires transformation<F>
        static constexpr 
        domain_t<F> convergent_point(domain_t<F> x0, domain_t<F> x1, F f)
        {
            while (x0 != x1)
            {
                x0 = f(x0);
                x1 = f(x1);
            }
            return x0;
        }

        
        template <typename F>
            requires transformation<F>
        static constexpr 
        domain_t<F> connection_point_nonterminating_orbit(const domain_t<F>& x, F f)
        {
            return convergent_point(x, f(collision_point_nonterminating_orbit(x, f)), f);
        }


        // Precondition: p(x) <-> f(x) is defined.
        template <typename F, typename P>
            requires transformation<F> && unary_predicate<P> && same_domain<F, P>
        static constexpr 
        domain_t<F> connection_point(const domain_t<F>& x, F f, P p)
        {
            domain_t<F> y = collision_point(x, f, p);
            if (!p(y)) { return y; }
            return convergent_point(x, f(y), f);
        }



        // Exercise 2.2
        // The algorithm is based on the following lemma:
        // If the orbits of 2 elements intersect, they have the same cyclic elements.
        // Get both the collision points and check the cyclic elements if present.
        template <typename F, typename Px, typename Py>
            requires transformation<F> && unary_predicate<Px> && unary_predicate<Py> && 
            same_domain<F, Px> && same_domain<Px, Py>
        static constexpr 
        bool intersect(const domain_t<F>& x, const domain_t<F>& y, F f, Px px, Py py)
        {
            auto x_coll = collision_point(x, f, px);
            auto y_coll = collision_point(y, f, py);

            if (!px(x_coll)) { return false; } 
            if (!py(y_coll)) { return false; }


            // Save the collision point of the fast. If we reach the collision point again it means we 
            // completed a cycle without reaching x so the 2 cycles do not intersect.
            auto y_check = y_coll;
            do
            {
                if (y_check == x_coll) { return true; }
                y_check = f(y_check);
            } while (y_check != y_coll);
            
            return false;
        }


        template <typename F>
            requires transformation<F>
        static constexpr 
        bool intersect_nonterminating_orbit(const domain_t<F>& x, const domain_t<F>& y, F f)
        {
            auto x_coll = collision_point_nonterminating_orbit(x, f);
            auto y_coll = collision_point_nonterminating_orbit(y, f);

            // Save the collision point. If we reach the collision point again it means we 
            // completed a cycle without reaching x so the 2 cycles do not intersect.
            auto y_check = y_coll;
            do
            {
                if (y_check == x_coll) { return true; }
                y_check = f(y_check);
            } while (y_check != y_coll);
            
            return false;
        }


        // Exercise 2.3 TODO.
        template <typename F>
            requires transformation<F> 
        static constexpr 
        domain_t<F> convergent_point_guarded(domain_t<F> x0, domain_t<F> x1, F f)
        {
           
        }



        template <typename F>
            requires transformation<F>
        static constexpr
        Triple<distance_type_t<F>, distance_type_t<F>, domain_t<F>>
        orbit_structure_nonterminating_orbit(const domain_t<F>& x, F f)
        {
            using N = distance_type_t<F>;
            domain_t<F> y = connection_point_nonterminating_orbit(x, f);
            return {distance(x, y, f), distance(f(y), y, f), y};    
        }


        // Precondition: p(x) <-> f(x) is defined.
        // Terminating orbit: m = h - 1 and n = 0.
        // Otherwise: m = h and n = c - 1. 
        template <typename F, typename P>
            requires transformation<F> && unary_predicate<P> && same_domain<F, P>
        static constexpr
        Triple<distance_type_t<F>, distance_type_t<F>, domain_t<F>>
        orbit_structure(const domain_t<F>& x, F f, P p)
        {
            using N = distance_type_t<F>;
            domain_t<F> y = connection_point(x, f, p);
            N m = distance(x, y, f);
            
            N n{0};
            if (p(y))
            {
                n = distance(f(y), y, f);
            }

            return {m, n, y};    
        }
    };
} // namespace eop


#endif