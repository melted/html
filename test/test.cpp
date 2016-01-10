#include <iostream>
#include <string>
#include "html.h"

using namespace htm;

void test_lvalues() {
    auto t = div();
    auto z = id("iddy");
    t << z;
    std::cout << t << std::endl;
}

void test_rvalues() {
    std::cout << (html() <<
                  (div() << id("mydiv") << p({"hello, world!"}))) << std::endl;
}
int main() {
    test_lvalues();
    test_rvalues();
    return 0;
}
