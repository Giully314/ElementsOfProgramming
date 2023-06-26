#include <cstdlib>
#include <iostream>
#include <format>

#include "orbit.hpp"
#include "triple.hpp"

int main()
{

    std::srand(123152);

    auto x = std::rand();
    auto f = [](int z){ return std::rand(); };
    auto info = eop::Orbit::orbit_structure_nonterminating_orbit(x, f);

    std::cout << std::format("handle: {} cycle: {}  connection_p: {}", info.first, info.second, info.third) << std::endl;

    // Seed 0:          handle: 4617        cycle: 5902     connection_p: 17634
    // Seed 123:        handle: 110552      cycle: 63367    connection_p: 9780
    // Seed 123152:     handle: 31347       cycle: 50469    connection_p: 28546


    return 0;
}