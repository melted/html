#include <iostream>
#include "html.h"

using namespace html;

int main() {
    tag t = html::html();
    tag u = div();
    u << id("mydiv") << div({ cls("subdiv") }, { "Hello, world!"});
    t << u;
    std::cout << t << std::endl;
    return 0;
}