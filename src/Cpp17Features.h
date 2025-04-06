// (c) 2025 Patricio Palma (ppalma.dev AT protonmail.com)
//
// Created by Patricio Palma on 03-02-25.
//
// Visit https://en.cppreference.com/w/cpp/17 for the full list of features in this release.

#ifndef CPP17FEATURES_H
#define CPP17FEATURES_H
#include <any>
#include <filesystem>
#include <optional>
#include <variant>
#include "CppFeatures.h"

class Cpp17Features final : public CppFeatures
{
public:
    Cpp17Features() : CppFeatures("C++17") { }
    void show_features() override
    {
        structured_binding();
        nodiscard_attribute();
        std_optional();
        std_variant();
        if_switch_initializers();
        std_any();
        std_string_view();
        std_filesystem();
    }

private:
    struct sb_test_struct
    {
        mutable int a = 1;
        std::string b = "hello";
        bool c = true;
    };
    void structured_binding() const
    {
        print_title(__func__);
        {
            std::cout << "structured binding, to const references\n";
            const auto& [a,b,c] = sb_test_struct();
            std::cout << "a=" << a << " b=" << b << " c=" << c << std::endl;
        }
        {
            std::cout << "structured binding, partial\n";
            const auto& [a,_,c] = sb_test_struct();
            std::cout << "a=" << a << " c=" << c << " b assigned to _" << '\n';
        }
        {
            std::cout << "structured binding, mutable member\n";
            const auto& [a, b, c] = sb_test_struct{0, "bye", false};
            a = 100;
            std::cout << "a=" << a << " b=" << b << '\n';
        }
        {
            std::cout << "structured binding, to an array\n";
            int a[2] = {1, 2};
            std::cout << format_array(a) << '\n';
            auto [x, y] = a;
            std::cout << "x=" << x << " y=" << y << '\n';
        }
    }

    [[nodiscard]] int nodiscard_attribute_impl() const
    {
        return 0;
    }

    void nodiscard_attribute() const
    {
        print_title(__func__);
        // WARNING returned value is discarded
        nodiscard_attribute_impl();

        // this does not show warning
        auto _ = nodiscard_attribute_impl();
    }

    void std_optional_argument(const std::optional<int>& arg) const
    {
        if (!arg)
        {
            std::cout << "No argument received (std::nullopt)\n";
        }
        else
        {
            std::cout << "Argument " << *arg << " received\n";
        }
    }

    [[nodiscard]] std::optional<int> std_optional_return(bool hasReturnValue) const
    {
        if (!hasReturnValue)
        {
            return std::nullopt;
        }
        return 100;
    }

    void std_optional() const
    {
        print_title(__func__);

        std_optional_argument(std::nullopt);
        std_optional_argument(100);
        for (const auto value : {true, false})
        {
            if (const auto& returned_value = std_optional_return(value))
            {
                std::cout << "returned value=" << *returned_value << '\n';
            }
            else
            {
                std::cout << "returned value=std::nullopt" << '\n';
            }
        }
    }

    void std_variant() const
    {
        print_title(__func__);

        // C++17 std::variant
        // This is the evolution of unions. An object of this class can contains a value of any type specified
        // in the template. Below variable "variant" can contain either an int, a std::string or a bool value.
        // In case of error, a variant object can be valueless.
        std::variant<int, std::string, bool> variant = true;
        try
        {
            std::cout << "get by type        variant=" << std::get<bool>(variant) << '\n';     // OK
            std::cout << "get by index       variant=" << std::get<2>(variant) << '\n';        // OK
            std::cout << "get by std::string (throws) variant=" << std::get<std::string>(variant) << '\n'; // This throws.
        }
        catch (const std::bad_variant_access& e)
        {
            std::cout << "variant do not contains std::string\n";
            std::cout << e.what() << '\n';
        }

        // you can check for specific type availability with std::holds_alternative<T>(variant)
        if (!std::holds_alternative<std::string>(variant))
        {
            std::cout << "variant does not holds a std::string type\n";
        }

        // the recommended way to look for the available type is to use std::visit which is safer.
        std::visit([](auto&& value) { std::cout << "std::visit " << value << '\n'; }, variant);
    }

    void if_switch_initializers() const
    {
        print_title(__func__);

        // C++17 if initializer -- if (initializer; expr) { ...
        // variable defined in init section are available into if and else blocks.
        if (const int some_value = 0; some_value != 0)
        {
            // some_value exists here
            std::cout << "This is NOT displayed some_value=" << some_value << std::endl;
        }
        else
        {
            // some_value exists here too
            std::cout << "This is displayed some_value=" << some_value << std::endl;
        }
        // some_value do NOT exist here

        std::cout << "switch initializer example\n";
        auto get_a_value = []() -> int { return 1; };
        // C++17 switch initializer. Works the same as if initializer.
        switch (int some_value = get_a_value(); some_value)
        {
        case 1:
            std::cout << "in case 1: some_value=" << some_value << std::endl;
            break;
        default:
            std::cout << "in default: some_value=" << some_value << std::endl;
        }
        // some_value do not exist here
    }

    void std_any() const
    {
        print_title(__func__);

        // C++17 std::any
        // It is a type safe container for copy constructible type.
        // std::any adds flexibility at the cost of using std::any_cast which has to be explicit
        std::any variable;
        std::cout << "variable has_value=" << std::boolalpha << variable.has_value() << '\n';

        variable = 3.14;
        std::cout << "variable has_value=" << std::boolalpha << variable.has_value() << '\n';
        std::cout << "variable has type " << variable.type().name() << '\n';
        std::cout << "variable=" << std::any_cast<double>(variable) << '\n';

        variable = std::string("mary jane");
        std::cout << "variable has_value=" << std::boolalpha << variable.has_value() << '\n';
        std::cout << "variable has type " << variable.type().name() << '\n';
        std::cout << "variable=" << std::any_cast<std::string>(variable) << '\n';

        try {
            // this will throw
            std::cout << "variable=" << std::any_cast<float>(variable) << std::endl;
        }
        catch (std::bad_any_cast& e) {
            std::cout << e.what() << '\n';
            std::cout << "failed to get float of a variant\n";
        }
    }

    void std_string_view() const
    {
        print_title(__func__);

        const std::string str = "   trim me";
        std::string_view v = str;
        v.remove_prefix(std::min(v.find_first_not_of(' '), v.size()));
        std::cout << "base string=" << str << '\n'
                  << "string view=" << v << '\n';
    }

    void std_filesystem() const
    {
        print_title(__func__);
        const std::string path = "."; // current directory

        try {
            int i = 0;
            for (const auto& entry : std::filesystem::directory_iterator(path))
            {
                std::cout << entry.path() << '\n';
                if ( ++i >= 5)
                {
                    break;
                }
            }
        }
        catch (const std::filesystem::filesystem_error& e) {
            std::cout << "exception: " << e.what() << '\n';
        }
    }
};

#endif //CPP17FEATURES_H
