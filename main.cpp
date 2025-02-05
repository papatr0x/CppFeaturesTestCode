// (c) 2025 Patricio Palma C. (patriciop AT gmail)

// This is intended to practice/remeber just some of the "new" C++ Features, starting from C++11
// until C++23 (or C++26 maybe).
// It is not intended as a comprehensive list or to show off advanced abilities in C++. Ideally this should be boring
// for experts but enough for the average user to get the gist of a feature and some of its main use cases.
// Code logic here is focuses on exercise a specific feature and is not intended to do anything else.

#include "Cpp11Features.h"
#include "Cpp14Features.h"
#include "Cpp17Features.h"
#include "Cpp20Features.h"
#include "Cpp23Features.h"
#include "Cpp26Features.h"

int main()
{
    Cpp11Features cpp11(77);
    cpp11.show_features();

    Cpp14Features cpp14;
    cpp14.show_features();

    Cpp17Features cpp17;
    cpp17.show_features();

    Cpp20Features cpp20;
    cpp20.show_features();

    Cpp23Features cpp23;
    cpp23.show_features();

    Cpp26Features cpp26;
    cpp26.show_features();

    return 0;
}
