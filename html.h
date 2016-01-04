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
};

ostream& operator<<(ostream& os, tag& t) {
    os << t.render();
    return os;
}

tag div(vector<attr> attrs, vector<tag> children) {
    return tag("div", attrs, tag::none, children);
}

tag div(vector<tag> children) {
    return tag("div", vector<attr>(), tag::none, children);
}

}