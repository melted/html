#include <iostream>
#include "html.h"

using namespace html;

int main() {
    std::cout << (html::html() <<
            (div() << id("mydiv") << p({"hello, world!"}))) << std::endl;
    return 0;
}