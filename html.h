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
            if (a.second != "") {
                os << " " << a.first << "=\"" << a.second << "\"";
            } else {
                os << " " << a.first;
            }
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

tag& operator<<(tag& t, attr& a) {
    t.attribute(a);
    return t;
}

tag& operator<<(tag& t, attr&& a) {
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
def_tag(summary)
def_tag(menu)
def_tag(dialog)
def_tag(script)
def_tag(noscript)
def_tage(template_tag, "template")
def_tag(canvas)


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
def_ne_tag(menuitem)


// Global attributes
def_attre(cls, "class")

def_attr(accesskey)
def_attr(contenteditable)
def_attr(contextmenu)
def_attr(dir)
def_attr(draggable)
def_attr(dropzone)
def_attr(hidden)
def_attr(id)
def_attr(itemid)
def_attr(itemprop)
def_attr(itemref)
def_attr(itemscope)
def_attr(itemtype)
def_attr(lang)
def_attr(spellcheck)
def_attr(style)
def_attr(tabindex)
def_attr(title)
def_attr(translate)
def_attr(href)

// Global event handlers
def_attr(onabort)
def_attr(onautocomplete)
def_attr(onautocompleteerror)
def_attr(onblur)
def_attr(oncancel)
def_attr(oncanplay)
def_attr(oncanplaythrough)
def_attr(onchange)
def_attr(onclick)
def_attr(onclose)
def_attr(oncontextmenu)
def_attr(oncuechange)
def_attr(ondblclick)
def_attr(ondrag)
def_attr(ondragend)
def_attr(ondragenter)
def_attr(ondragexit)
def_attr(ondragleave)
def_attr(ondragover)
def_attr(ondragstart)
def_attr(ondrop)
def_attr(ondurationchange)
def_attr(onemptied)
def_attr(onended)
def_attr(onerror)
def_attr(onfocus)
def_attr(oninput)
def_attr(oninvalid)
def_attr(onkeydown)
def_attr(onkeypress)
def_attr(onkeyup)
def_attr(onload)
def_attr(onloadeddata)
def_attr(onloadedmetadata)
def_attr(onloadstart)
def_attr(onmousedown)
def_attr(onmouseenter)
def_attr(onmouseleave)
def_attr(onmousemove)
def_attr(onmouseout)
def_attr(onmouseover)
def_attr(onmouseup)
def_attr(onwheel)
def_attr(onpause)
def_attr(onplay)
def_attr(onplaying)
def_attr(onprogress)
def_attr(onratechange)
def_attr(onreset)
def_attr(onresize)
def_attr(onscroll)
def_attr(onseeked)
def_attr(onseeking)
def_attr(onselect)
def_attr(onshow)
def_attr(onsort)
def_attr(onstalled)
def_attr(onsubmit)
def_attr(onsuspend)
def_attr(ontimeupdate)
def_attr(ontoggle)
def_attr(onvolumechange)
def_attr(onwaiting)

#undef def_tag
#undef def_tage
#undef def_attr
#undef def_attre
#undef def_ne_tag
}