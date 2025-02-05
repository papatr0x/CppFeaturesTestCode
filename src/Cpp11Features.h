// (c) 2025 Patricio Palma C. (patriciop AT gmail)
//
// Created by Patricio Palma on 03-02-25.
//

#ifndef CPP11FEATURES_H
#define CPP11FEATURES_H

// Visit https://en.cppreference.com/w/cpp/11 for the full list of features in this release.

#include <vector>
#include "CppFeatures.h"
#include "Utilities.h"

// TODO: Pending C++11 features
//  - threads & locks
//  - variadic templates
//  - move semantics std::move
//  - rvalue references
//  decltype & decltype(auto)
//  noexcept
//  = delete
//  type deduction rules

// C++11 keyword "final".
// No class marked as final can be derived.
class Cpp11Features final : public CppFeatures
{
    Cpp11Features() : CppFeatures("C++11")
    {
        // x and y members where already initialized on declaration
        x = y = 7;
    }

    // C++11 in-class members initializer.
    // Initial values for class properties can be stated directly in class declaration
    int x = 1;
    int y = 1;

public:
    // C++11 keyword "= default"
    // TODO verify if this allows implement move operator
    // INFO explain the rule of 6 (or 5 w/o default ctor)
    ~Cpp11Features() override = default;

    // C++11 delegating constructors.
    // This constructor reuses the logic in the custom default constructor while adds more logic.
    explicit Cpp11Features(int j) : Cpp11Features()
    {
        constexpr auto p = 10; // C++11 new "constexpr" keyword
        x *= j*p;
        static_assert(p>0, "p is not > 0"); // C++11 static assert
    }

    // C++11 keyword "override"
    // It helps the programmer know when overriding a base class function as not using the keyword generates a warning.
    void show_features() override
    {
        ranged_for_loop();
        lambda_function();
        smart_pointers();
    }

private:
    void ranged_for_loop() const
    {
        print_title(__func__);
        // C++11 uniform initialization
        // It is a safer and natural way to initialize objects and object containers.
        // If there type narrowing it will complain, which is a good thing.
        const std::vector v = {1, 2, 3, 4, 5};

        int ni1(3.9); // 3.9 is chopped off to 3. Implicit convertion warning. This is how bad stuff begins.
        //int ni2{3.9}; // 3.9 (double) cannot be narrowed to int. Compiler error.

        // C++11 ranged for-loops and auto keyword
        // A modern way to do the old for-loop stuff.
        for (auto const& i : v)
        {
            std::cout << "in ranged loop " << i << std::endl;
        }
    }

    void lambda_function() const
    {
        print_title(__func__);
        // C++11 local lambda function
        auto local_func = [](const int p)
        {
            std::cout << "Hello, from lamda! " << p << "\n";
        };
        local_func(10);
    }

    void smart_pointers()
    {
        print_title(__func__);
        // C++11 Smart pointers
        // The old raw pointer but this time they know their business (create and destroy the object) and
        // do it on behalf of the programmer.

        // std::unique_ptr<> is a single owner ptr. It cannot be copied but moved.

        std::unique_ptr<Dummy> outerDummy;
        {
            // std::shared_ptr<> this uses a reference counter to a specific object,  multiple shared_ptr<> object
            // can exist and point to the same object. The object is destroyed only when no more shared_ptr object are
            // pointing to the object.
            auto sp = std::make_shared<Dummy>("shared/weak ptr example");

            // std::weak_ptr<> this allows to access a shared object, but it does not own an object.
            weakPtr = sp;
            smart_pointers_test("Scope 1");

            auto up = std::make_unique<Dummy>("unique ptr example");
            outerDummy = std::move(up); // C++11 std::move
        }
        smart_pointers_test("Scope 2");
    }

    void smart_pointers_test(const std::string& text) const
    {
        if (const auto sp = weakPtr.lock())
        {
            std::cout << text << " weakPtr is locked id = " << sp->id << std::endl;
        }
        else
        {
            std::cout << text <<" weakPtr could not be locked" << std::endl;
        }
    }

    // While it is a pointer, it works as a regular object. You do not need
    // to check for null before dereferencing
    std::weak_ptr<Dummy> weakPtr; // C++11 std::weak_ptr
};

#endif //CPP11FEATURES_H
