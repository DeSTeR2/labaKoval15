#include <iostream>

#include "fibRandom.hpp"
#include "rectangle.hpp"

long long findSize(int n) {
    long long in = 0;
    
    for (int i = 0; i < 200; ++i)
        in += isInRectangle(fibRandom(), fibRandom());
    return 20 * 20 * in / 100 ;
}
