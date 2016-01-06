#include <iostream>
#include "html.h"

// html.h defines the namespace htm, bring it in wherever you use the library,
// the point of the library is to make building html concise, and the prefix
// foils that. Be careful about the scope of the using directive though, the
// the library defines a massive amount of names, including favorites like i and
// b.
using namespace htm;

int main() {
    // The html is built from a class called tag, it includes the tag text
    // the attributes and an array of children. There are two special types
    // of tags, those that don't have an end tag (like link and br) and
    // inner text, which is just a bunch of text. Also a tag can omit the text
    // and just render as an array of children.
    //
    // This is a tag with an attribute and an empty children array
    tag t("div", { { "id", "mydiv" }}, { });
    // As all the standard tags have functions, one only needs to create
    // a tag directly if one wants to define a new type of tag.

    // A tag is rendered by calling the render function
    string s = t.render();

    // operator string() is overloaded so casting tag to a string renders it
    string s2 = string(t);

    // it can also be rendered by streaming to an ostream
    std::cout << t << endl;

    // All the tags in the html spec has been defined as functions
    // The ones with end tags have the following prototypes, using
    // div as an example:
    // tag div(vector<attr> attrs, vector<tag> children);
    // tag div(vector<tag> children);
    // tag div();
    // attr is the attribute datatype, it is an alias for pair<string, string>
    //
    // The member function add() on tag adds a child tag at the back of the
    // back of the child array. attribute() adds an attribute.
    // The operator<< has been defined for tag so streaming a tag adds it to
    // the children, an attr adds it to the attributes and a string is
    // added to the children as inner text.
    //
    // These are equivalent ways to build <div id="mydiv"><p>howdy</p></div>:
    auto t1 = div({ id("mydiv") }, {p( { "howdy"} )});
    auto t2 = div().attribute(id("mydiv")).add(p().add("howdy"));
    auto t3 = div();
    t3 << id("mydiv") << (p() << "howdy");

    // The tags without an end tag have prototypes like:
    // tag meta(vector<attr> a);
    // tag meta();

    // Some names in the html spec are illegal C++ function names and have
    // slightly different names in the library.
    //
    // These are:
    //
    // HTML name         Lib name
    // ---------         --------
    // class             cls
    // for               forc
    // http-equiv        http_equiv
    // accept-charset    accept_charset
    // default           default_attr
    // template          template_tag
    // main              main_tag    (not illegal to keep, but inconvenient)
}