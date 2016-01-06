#include <iostream>
#include "html.h"

using namespace htm;

int main() {
    std::cout << (html() <<
            (div() << id("mydiv") << p({"hello, world!"}))) << std::endl;
    return 0;
}