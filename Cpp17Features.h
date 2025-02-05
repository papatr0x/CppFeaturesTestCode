// (c) 2025 Patricio Palma C. (patriciop AT gmail)
//
// Created by Patricio Palma on 03-02-25.
//

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
            std::cout << "a=" << a << " c=" << c << " b assigned to _" << std::endl;
        }
        {
            std::cout << "structured binding, mutable member\n";
            const auto& [a, b, c] = sb_test_struct{0, "bye", false};
            a = 100;
            std::cout << "a=" << a << " b=" << b << std::endl;
        }
        {
            std::cout << "structured binding, to an array\n";
            int a[2] = {1, 2};
            std::cout << format_array(a) << std::endl;
            auto [x, y] = a;
            std::cout << "x=" << x << " y=" << y << std::endl;
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
                std::cout << "returned value=" << *returned_value << std::endl;
            }
            else
            {
                std::cout << "returned value=std::nullopt" << std::endl;
            }
        }
    }

    void std_variant() const
    {
        print_title(__func__);
        std::variant<int, std::string, bool> variant;
        variant = true;

        std::cout << "variant is storing a bool true\n";
        std::cout << "variant=" << std::get<bool>(variant) << std::endl;
        try
        {
            std::cout << "variant=" << std::get<std::string>(variant) << std::endl;
        }
        catch (const std::bad_variant_access& e)
        {
            std::cout << e.what() << std::endl;
        }

        if (!std::holds_alternative<std::string>(variant))
        {
            std::cout << "variant does not holds a std::string type\n";
        }
        std::visit([](auto&& value) { std::cout << "std::visit " << value << "\n"; }, variant);
    }

    void if_switch_initializers() const
    {
        print_title(__func__);
        // some_value do not exist here
        if (const int some_value = 0; some_value != 0)
        {
            std::cout << "This is NOT displayed some_value=" << some_value << std::endl;
        }
        else
        {
            std::cout << "This is displayed some_value=" << some_value << std::endl;
        }
        // some_value do not exist here

        std::cout << "switch initializer example\n";
        auto get_a_value = []() -> int { return 1; };
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
        std::any variable;
        std::cout << "variable has_value=" << std::boolalpha << variable.has_value() << std::endl;
        variable = 3.14;
        std::cout << "variable has_value=" << std::boolalpha << variable.has_value() << std::endl;
        std::cout << "variable has type " << variable.type().name() << std::endl;
        std::cout << "variable=" << std::any_cast<double>(variable) << std::endl;

        variable = std::string("mary jane");
        std::cout << "variable has_value=" << std::boolalpha << variable.has_value() << std::endl;
        std::cout << "variable has type " << variable.type().name() << std::endl;
        std::cout << "variable=" << std::any_cast<std::string>(variable) << std::endl;

        try {
            std::cout << "variable=" << std::any_cast<float>(variable) << std::endl;
        }
        catch (std::bad_any_cast& e) {
            std::cout << e.what() << std::endl;
            std::cout << "failed to get float of a variant\n";
        }
    }

    void std_string_view() const
    {
        print_title(__func__);
        std::string str = "   trim me";
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
            for (const auto& entry : std::filesystem::directory_iterator(path)) {
                std::cout << entry.path() << '\n';
            }
        }
        catch (const std::filesystem::filesystem_error& e) {
            std::cout << "exception: " << e.what() << '\n';
        }
    }
};

#endif //CPP17FEATURES_H
