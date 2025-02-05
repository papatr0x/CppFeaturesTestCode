//
// Created by Patricio Palma on 03-02-25.
//

#ifndef UTILITIES_H
#define UTILITIES_H

#include <iostream>
#include <sstream>
#include <string>

struct Dummy
{
    explicit Dummy(const std::string& aId) : id(aId)
    {
        std::cout << "constructing Dummy object id=" << aId << '\n';
    }
    ~Dummy()
    {
        std::cout << "destroying Dummy object id=" << id << '\n';
    }
    std::string id;
};

// C++20 concept
template <std::ranges::range Container>
std::string format_vector(const Container& container)
{
    std::ostringstream os;
    os << "[ ";
    for (auto it = container.begin(); it != container.end(); ++it)
    {
        if (it != container.begin())
            os << ", ";
        os << *it;
    }
    os << " ]";
    return os.str();
}

template <typename T, size_t N>
std::string format_array(const T(&array)[N])
{
    std::ostringstream os;
    os << "[ ";
    for (int i = 0; i < N; ++i)
    {
        if (i != 0)
            os << ", ";
        os << array[i] ;
    }
    os << " ]";
    return os.str();
}

#endif //UTILITIES_H
