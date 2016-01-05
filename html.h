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

    tag() : text_(""), opts_(none) {}
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

#define def_attr(a) def_attre(a, #a)

#define def_attre(a, n)          \
attr a(string s)  {              \
    return make_pair(n, s);      \
}

#define def_tag(t)   def_tage(t, #t)

#define def_tage(t, s)                                 \
tag t(vector<attr> attrs, vector<tag> children) {      \
    return tag(s, attrs, tag::none, children);         \
}                                                      \
                                                       \
tag t(vector<tag> children) {                          \
    return tag(s, {}, tag::none, children);            \
}                                                      \
                                                       \
tag t() {                                              \
    return tag(s, {}, tag::none, {});                  \
}

#define def_ne_tag(t)                                  \
tag t(vector<attr> attrs) {                            \
    return tag(#t, attrs, tag::no_end, {});            \
}                                                      \
                                                       \
tag t() {                                              \
    return tag(#t, {}, tag::no_end, {});               \
}

def_attre(cls, "class")

def_attr(href)
def_attr(id)

def_tag(html)
def_tag(head)
def_tag(style)
def_tag(body)
def_tag(article)
def_tag(section)
def_tag(nav)
def_tag(aside)
def_tag(h1)
def_tag(h2)
def_tag(h3)
def_tag(h4)
def_tag(h5)
def_tag(h6)
def_tag(hgroup)
def_tag(header)
def_tag(footer)
def_tag(address)
def_tag(p)
def_tag(pre)
def_tag(blockquote)
def_tag(ol)
def_tag(ul)
def_tag(li)
def_tag(dl)
def_tag(dt)
def_tag(dd)
def_tag(figure)
def_tag(figcaption)
def_tag(div)
def_tag(a)
def_tag(em)
def_tag(strong)
def_tag(small)
def_tag(s)
def_tag(cite)
def_tag(q)
def_tag(dfn)
def_tag(abbr)
def_tag(ruby)
def_tag(rt)
def_tag(rp)
def_tag(data)
def_tag(time)
def_tag(code)
def_tag(var)
def_tag(samp)
def_tag(kbd)
def_tag(sub)
def_tag(sup)
def_tag(i)
def_tag(b)
def_tag(u)
def_tag(mark)
def_tag(bdi)
def_tag(bdo)
def_tag(span)
def_tag(ins)
def_tag(del)
def_tag(picture)
def_tag(iframe)
def_tag(object)
def_tag(video)
def_tag(audio)
def_tag(map)
def_tag(area)
def_tag(table)
def_tag(caption)
def_tag(colgroup)
def_tag(tbody)
def_tag(thead)
def_tag(tfoot)
def_tag(tr)
def_tag(td)
def_tag(th)
def_tag(form)
def_tag(label)
def_tag(button)
def_tag(select)
def_tag(datalist)
def_tag(optgroup)
def_tag(option)
def_tag(textarea)
// def_tag(keygen) // discouraged by spec
def_tag(output)
def_tag(progress)
def_tag(meter)
def_tag(fieldset)
def_tag(legend)
def_tag(details)

def_ne_tag(base)
def_ne_tag(meta)
def_ne_tag(link)
def_ne_tag(hr)
def_ne_tag(br)
def_ne_tag(wbr)
def_ne_tag(source)
def_ne_tag(img)
def_ne_tag(embed)
def_ne_tag(param)
def_ne_tag(track)
def_ne_tag(col)
def_ne_tag(input)

#undef def_tag
#undef def_tage
#undef def_attr
#undef def_attre
#undef def_ne_tag
}