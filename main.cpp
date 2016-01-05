#include <iostream>
#include "html.h"

using namespace html;

int main() {
    auto u =  div({ tag("hello") });
    u << id("stream") << div({ "attaboy" });
    auto t = html::html({ href("http://neon.se") }, { u });

    std::cout << t << std::endl;
    std::cout << div({ id("salutation") }, { "howdy" }) << std::endl;
    std::cout << div({ "Lookit here" }).attribute(id("another")) << std::endl;
    return 0;
}