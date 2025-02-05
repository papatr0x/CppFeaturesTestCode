// (c) 2025 Patricio Palma C. (patriciop AT gmail)
//
// Created by Patricio Palma on 03-02-25.
//
// Visit https://en.cppreference.com/w/cpp/14 for the full list of features in this release.

#ifndef CPP14FEATURES_H
#define CPP14FEATURES_H
#include "CppFeatures.h"

class Cpp14Features final : public CppFeatures
{
public:
    Cpp14Features() : CppFeatures("C++14") { }

    void show_features() override
    {
        generic_lambdas();
        return_type_deduction();
        binary_literals();
        digits_separators();
    }

private:
    void generic_lambdas() const
    {
        print_title(__func__);

        // C++14 generic lambdas
        // INFO what is the difference between generic and non-generic lambdas.
        auto add = [](const auto& a, const auto& b) { return a + b; };
        std::cout << add(5, 6) << " "
                  << add(std::string("pepe"), std::string("jose")) << std::endl;
    }

    // Note this has to be defined before its use, even in a class.
    [[nodiscard]] auto return_type_deduction_impl() const
    {
        return 1;
    }

    void return_type_deduction() const
    {
        print_title(__func__);
        std::cout << "This value type was deducted " << return_type_deduction_impl() << std::endl;
    }

    // C++14 binary literals
    // Allows the programmer to introduce directly binary numbers in code. Easier that using hex or dec code.
    void binary_literals() const
    {
        print_title(__func__);
        std::cout << "This binary literal was written as 0b00001111 with value " << 0b00001111 << std::endl;
    }

    // C++14 digits separators
    // Provides more clarity to the programmer when writing numbers.
    void digits_separators() const
    {
        print_title(__func__);
        std::cout << "This literal was written as 1'000'000 with value " << 1'000'000 << std::endl;
    }

};


#endif //CPP14FEATURES_H
