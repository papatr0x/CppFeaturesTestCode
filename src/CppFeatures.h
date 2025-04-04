// (c) 2025 Patricio Palma (ppalma.dev@protonmail.com)
//
// Created by Patricio Palma on 03-02-25.
//

#ifndef CPPFEATURES_H
#define CPPFEATURES_H

#include <iostream>
#include <string>

class CppFeatures {
public:
    explicit CppFeatures(const std::string& versionString)
    {
        std::cout << "----- " << versionString << " -----" << std::endl;
    }
    virtual ~CppFeatures() = default;
    virtual void show_features() = 0;

protected:
    void print_title(const std::string& title) const
    {
        std::cout << "* " << title << " example *\n";
    }
};

#endif //CPPFEATURES_H
