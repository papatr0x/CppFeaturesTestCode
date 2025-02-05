# Modern C++ Features Gym #
Since 2010 or a little later, C++ has officially started acquiring new capabilities—not
just modern technical features but also syntactic sugar that makes it more readable and
easier to maintain.

If you make a living as a C++ developer, then it’s important to ask yourself:

- What new C++ features do/don't I know how to use?
- Which features have I used? Have I used them correctly?
- What are the main use cases for a particular feature?

I created this project to help answer these questions. The goal is to have a somewhat
organized space to test each feature, see it in action, and ideally internalize it.

Simple examples of each feature, with the minimal logic needed to understand some of
the most common use cases. Just that. The gym and production environments are for acrobatics.
If you are an expert programmer, this will probably be boring.

## Requirements ##
- CMake 3.20 minimum required.
- C++ compiler

I have tested this with:
- Apple clang version 16.0.0 (clang-1600.0.26.6)
- Homebrew clang version 19.1.7
- (not verified yet) Microsoft C++ Compiler

## How to Build ##
On console

    cmake -B cmake-build
    cmake --build cmake-build --target CppFeaturesTestCode
The resulting code can be executed with

    cmake-build/CppFeaturesTestCode

## Notes ##
The zero warnings policy is a must, but in this project, as a special case some warnings are
expected (i.e. to demostrate [[nodiscard]] attribute.)
