// (c) 2025 Patricio Palma (ppalma.dev AT protonmail.com)
//
// Created by Patricio Palma on 03-02-25.
//
// Visit https://en.cppreference.com/w/cpp/26 for the full list of features in this release.

#ifndef CPP26FEATURES_H
#define CPP26FEATURES_H
#include "CppFeatures.h"

class Cpp26Features final : public CppFeatures
{
public:
    Cpp26Features() : CppFeatures("C++26") { }
    void show_features() override
    {
        std::cout << "Not yet implemented. Probably it is a little too soon for that.\n";
    }
};

#endif //CPP26FEATURES_H
