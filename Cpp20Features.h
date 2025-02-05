// (c) 2025 Patricio Palma C. (patriciop AT gmail)
//
// Created by Patricio Palma on 03-02-25.
//

#ifndef CPP20FEATURES_H
#define CPP20FEATURES_H

#include <algorithm>
#include <ranges>
#include "CppFeatures.h"

class Cpp20Features final : public CppFeatures
{
public:
    Cpp20Features() : CppFeatures("C++20") { }
    void show_features() override
    {
        std_ranges_and_std_views();
    }

private:
    void std_ranges_and_std_views() const
    {
        print_title(__func__);
        {
            std::vector<int> numbers{0, 3, 6, 4, 5, 9};
            std::cout << "initial vector " << format_vector(numbers) << std::endl;

            std::ranges::sort(numbers);
            std::cout << "sorted vector " << format_vector(numbers) << std::endl;

            std::cout << "numbers=" << format_vector(numbers) << std::endl;
            std::ranges::for_each(numbers, [](auto& value) {return value*2;});
        }
        {
            auto numbers = std::views::iota(1) | std::views::take(10);

            std::cout << "initial generated vector " << format_vector(numbers) << std::endl;

            auto reversed = numbers | std::views::reverse;

            // FIX format_vector() fails miserably trying to access reversed
            // std::cout << "reversed vector " << format_vector(reversed) << std::endl;
        }

        // How operator| works? How an array is constructed using iota and take.

    }
};

#endif //CPP20FEATURES_H
