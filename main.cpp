#include <iostream>
#include "html.h"

using namespace html;

int main() {
    auto u =  div({ tag("hello") });
    tag t("html", { { "href", "http://neon.se" } }, tag::none, { u });

    std::cout << t << std::endl;
    return 0;
}