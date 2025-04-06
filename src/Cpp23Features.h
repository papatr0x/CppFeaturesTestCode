// (c) 2025 Patricio Palma (ppalma.dev AT protonmail.com)
//
// Created by Patricio Palma on 03-02-25.
//
// Visit https://en.cppreference.com/w/cpp/23 for the full list of features in this release.

#ifndef CPP23FEATURES_H
#define CPP23FEATURES_H
#include "CppFeatures.h"

class Cpp23Features final : public CppFeatures
{
public:
    Cpp23Features() : CppFeatures("C++23") { }
    void show_features() override
    {
        std::cout << "Not yet implemented" << std::endl;
    }
};

#endif //CPP23FEATURES_H
