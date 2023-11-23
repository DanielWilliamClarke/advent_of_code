#include <iostream>
#include <iomanip>

#include "example/example.h"

int main () {
    Example example(true);

    std::cout << "Hello World" << std::setw(5) << example.a << std::endl;
}