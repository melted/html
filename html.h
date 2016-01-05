#pragma once

#include <vector>
#include <string>
#include <tuple>
#include <sstream>
#include <ostream>

namespace html {

namespace {
    using namespace std;
}

using attr = pair<string, string>;

struct tag {
    enum tag_opt { none = 0, no_end = 1, inner_text = 2 };
    string text_;
    vector<attr> attrs_;
    tag_opt opts_;
    vector<tag> children_;

    tag(const char* s) : text_(s), opts_(inner_text) {}
    tag(string s) : text_(s), opts_(inner_text) {}
    tag(string t, vector<attr> a, vector<tag> c)
            : text_(t), attrs_(a), opts_(none), children_(c) {}
    tag(string t, vector<attr> a, tag_opt o, vector<tag> c)
    : text_(t), attrs_(a), opts_(o), children_(c) {}

    string render() {
        if (opts_ & inner_text) {
            return text_;
        }
        ostringstream os;

        os << "<" << text_;

        for(auto a : attrs_) {
            os << " " << a.first << "=\"" << a.second << "\"";
        }

        os << ">";

        if (opts_ & no_end) {
            return os.str();
        }

        for (auto c : children_) {
            os << c.render();
        }

        os << "</" << text_ << ">";
        return os.str();
    }

    operator string() {
        return render();
    }

    tag& attribute(attr a) {
        attrs_.push_back(a);
        return *this;
    }

    tag& add(tag child) {
        children_.push_back(child);
        return *this;
    }
};

ostream& operator<<(ostream& os, tag& t) {
    os << t.render();
    return os;
}

ostream& operator<<(ostream& os, tag&& t) {
    os << t.render();
    return os;
}

tag& operator<<(tag& t, tag& c) {
    t.add(c);
    return t;
}

tag& operator<<(tag& t, tag&& c) {
    t.add(c);
    return t;
}

tag& operator<<(tag& t, attr a) {
    t.attribute(a);
    return t;
}

#define def_attr(a) \
attr a(string s)  {\
    return make_pair(#a, s);\
}

#define def_tag(t)\
tag t(vector<attr> attrs, vector<tag> children) { \
    return tag(#t, attrs, tag::none, children); \
} \
\
tag t(vector<tag> children) {  \
    return tag(#t, {}, tag::none, children);\
}\
\
tag t() { \
    return tag(#t, {}, tag::none, {});\
}

// special as class is a c++ keyword
attr cls(string s) {
    return make_pair("class", s);
}

def_attr(href)
def_attr(id)

def_tag(html)
def_tag(div)
}