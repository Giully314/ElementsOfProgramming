
#include "../vector.hpp"

#include <cstdlib>
#include <iostream>
#include <algorithm>

constexpr size_t N = 32; 

using namespace eop;

Vector<int> populate_vector_rand()
{
    Vector<int> v;    
    v.reserve(N);
    for (auto i = 0; i < N; ++i)
    {
        v.emplace_back(std::rand());
    } 

    return v;
}

Vector<int> populate_vector_seq()
{
    Vector<int> v;    
    v.reserve(N);
    for (auto i = 0; i < N; ++i)
    {
        v.emplace_back(i);
    } 

    return v;
}




void print_vector(const Vector<int>& v)
{
    for (auto i : v)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}


int main()
{
    auto v = populate_vector_rand();
    print_vector(v);
    std::sort(v.begin(), v.end());
    // std::ranges::sort(v);
    print_vector(v);


    return 0;
}