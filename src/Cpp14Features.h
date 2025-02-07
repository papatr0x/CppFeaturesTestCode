// (c) 2025 Patricio Palma C. (patriciop AT gmail)
//
// Created by Patricio Palma on 03-02-25.
//
// Visit https://en.cppreference.com/w/cpp/14 for the full list of features in this release.

#ifndef CPP14FEATURES_H
#define CPP14FEATURES_H
#include "CppFeatures.h"

// TODO
//  std::exchange

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

/*
    void type_deduction() const
    {

        These notes are a summary of https://www.youtube.com/watch?v=wQxj20X-tIU by Scott Meyers

        Template type deduction rules evolution:
        C++98
            Template Rules
                - T value
                - T&/T*
        C++11
            - Template Rules
                - T value
                    - λ implicit return
                - T&/T*
                - T&&
            - C++11 λ capture (based on T&/T*)
            - auto object
            - decltype
        C++14
            - Template Rules
                - T value
                    - λ implicit return
                - T&/T*
                - T&&
            - λ capture (based on T&/T*)
            - auto return type (based in template rules)
            - λ auto parameter (based in template rules)
            - auto object
                - auto object
                - λ init capture
            - decltype
                -decltype
                -decltype(auto)

        To understand type deduction, we need to know the template declaration, and the expression used
        to invoke the template. Type deduction consist of deducing two types, the T in template declaration
        and ParamType in the template function definition.

        Reference and Pointers
        template<typename T>
        void f(ParamType param);

        f(expr); // here T and ParamType are deduced from expr.

        T is deduced based on the way ParamType is declared

        void f(T& param);
        int x = ..;
        const int cx = x;
        const int& rx = x;
        f(x)  -> T = int, ParamType = int&
        f(cx) -> T = const int, ParamType = const int&
        f(rx) -> T = const int, ParamTYpe = const int&

        void f(const T& param);     // CONST
        x, cx, rf are the same
        f(x)  -> T = int, ParamType = const int&
        f(cx) -> T = int, ParamType = const int&
        f(rx) -> T = int, ParamTYpe = const int&

        void f(T* param);
        int x = ...
        const int* pcx = &x;
        f(&x)  -> T = int, ParamType = int*
        f(pcx) -> T = const int, ParamType = const int*

        The deduction rules for T&/T* works the same. ParamType is deduced in the call and
        T's type is deduced by pattern matching on ParamType.

        auto uses the same for template type deduction, acting as the type T
        for x, cx, rf  as before
        auto& v1 = x;   // auto's type = int       -> v1's type = int&
        auto& v2 = cx;  // auto's type = const int -> v2's type = const int&
        auto& v3 = rx;  // auto's type = const int -> v3's type = const int&

        const auto& v4 = x;     // auto's type = int -> v4's type = const int&
        const auto& v5 = cx;    // auto's type = int -> v5's type = const int&
        const auto& v6 = rx;    // auto's type = int -> v6's type = const int&

        Universal References
        Is used by Scott to refer to rvalue references in a template declaration. This kind of
        references binds to lvalue and rvalues.

        template<typename T>
        void f(T&& param);
        f(expr);
        for x, cx, rf as before
        f(x);   // x is lvalue  -> T = int&, ParamType = int&
        f(cx);  // cx is lvalue -> T = const int&, ParamType = const int&
        f(rx);  // rx is lvalue -> T = const int&, ParamType = const int&
        f(22);  // 22 is rvalue -> T = int, ParamType = int&&

        reference collapsing is the reference result of combining function declaration reference
        and the type reference.
        in the last case the T&& of the param  and the T&& of the 22 (which is a rvalue), generates
        a rvalue &&. for the rest of the cases it is always a reference &

        By Value Parameters
        template<typename T>
        void f(T param);
        f(expr);

        if expr is reference or constant or volatile (cv) ignore that.
        for x, cx, rf as before
        f(x);   // T = int, ParamType = int
        f(cx);  // T = int, ParamType = int
        f(rx);  // T = int, ParamType = int

        important to consider is that f argument is a brand-new variable (by value).
        for x, cx, rf as before
        auto v1 = x;    // v1's type = int, auto's type = int
        auto v2 = cx;   // v2's type = int, auto's type = int
        auto v3 = rx;   // v3's type = int, auto's type = int

        references must be added to auto, as auto never deduce references
        auto v4 = rx;   // v4's type = int
        auto& v5 = rx;  // v5's type = const int&
        auto&& v6 = rx; // v6's type = const int& (rx is lvalue)

        const Expressions with const
        Top level const and volatile is ignored if you are dealing with by-value
        void func(const int* const param1, // const ptr to const
                  const int* param2,       // ptr to const
                  int* param3)             // ptr
        auto p1 = param1;   // p1's type = const int* (constness ignored)
        auto p2 = param2;   // p2's type = const int*
        auto p3 = param3;   // p3's type = int*
    }
*/

};


#endif //CPP14FEATURES_H
