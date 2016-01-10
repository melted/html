#pragma once

#include <vector>
#include <string>
#include <tuple>
#include <map>
#include <sstream>
#include <ostream>

namespace htm {


using attr = std::pair<std::string, std::string>;

struct tag {
    enum tag_opt { none = 0, no_end = 1, inner_text = 2 };

    std::string text_;
    std::map<std::string, std::string> attrs_;

    tag_opt opts_;
    std::vector<tag> children_;

    tag() : text_(""), opts_(none) {}
    tag(const char* s) : text_(s), opts_(inner_text) {}
    tag(std::string s) : text_(s), opts_(inner_text) {}
    tag(std::string t, std::vector<attr> a, std::vector<tag> c)
            : text_(t), attrs_(a.begin(), a.end()), opts_(none), children_(c) {}
    tag(std::string t, std::vector<attr> a, tag_opt o, std::vector<tag> c)
    : text_(t), attrs_(a.begin(), a.end()), opts_(o), children_(c) {}

    std::string render() {
        if (opts_ & inner_text) {
            return text_;
        }
        std::ostringstream os;
        if (text_ != "") {
            os << "<" << text_;

            for (auto a : attrs_) {
                os << " " << a.first << "=\"" << a.second << "\"";
            }

            os << ">";
        }

        if (opts_ & no_end) {
            return os.str();
        }

        for (auto c : children_) {
            os << c.render();
        }

        if (text_ != "") {
            os << "</" << text_ << ">";
        }
        return os.str();
    }

    operator std::string() {
        return render();
    }

    tag& attribute(attr a) {
        attrs_[a.first] = a.second;
        return *this;
    }

    tag& add(tag child) {
        children_.push_back(child);
        return *this;
    }
};

std::ostream& operator<<(std::ostream& os, tag& t) {
    os << t.render();
    return os;
}

std::ostream& operator<<(std::ostream& os, tag&& t) {
    os << t.render();
    return os;
}

template<typename Tag>
Tag& operator<<(Tag&& t, Tag&& c) {
    return t.add(c);
}

template<typename Tag>
Tag& operator<<(Tag&& t, attr a) {
    return t.attribute(a);
}

template <typename Tag>
Tag& operator<<(Tag&& t, std::string s) {
    return t.add(tag(s));
}

template <typename Tag>
Tag& operator<<(Tag&& t, const char* s) {
    return t.add(tag(s));
}

#define def_attr(a) def_attr_ex(a, #a)

#define def_attr_ex(a, n)             \
attr a(std::string s)  {              \
    return std::make_pair(n, s);      \
}

#define def_bool_attr(a) def_bool_attr_ex(a, #a)

#define def_bool_attr_ex(a, n)        \
attr a()  {                           \
    return std::make_pair(n, "");     \
}

#define def_tag(t)   def_tag_ex(t, #t)

#define def_tag_ex(t, s)                               \
tag t(std::vector<attr> attrs,                         \
           std::vector<tag> children) {                \
    return tag(s, attrs, tag::none, children);         \
}                                                      \
                                                       \
tag t(std::vector<tag> children) {                     \
    return tag(s, {}, tag::none, children);            \
}                                                      \
                                                       \
tag t() {                                              \
    return tag(s, {}, tag::none, {});                  \
}

#define def_ne_tag(t)                                  \
tag t(std::vector<attr> attrs) {                       \
    return tag(#t, attrs, tag::no_end, {});            \
}                                                      \
                                                       \
tag t() {                                              \
    return tag(#t, {}, tag::no_end, {});               \
}


def_tag(a)
def_tag(abbr)
def_tag(address)
def_tag(area)
def_tag(article)
def_tag(aside)
def_tag(audio)
def_tag(b)
def_tag(bdi)
def_tag(bdo)
def_tag(blockquote)
def_tag(body)
def_tag(button)
def_tag(canvas)
def_tag(caption)
def_tag(cite)
def_tag(code)
def_tag(colgroup)
def_tag(data)
def_tag(datalist)
def_tag(dd)
def_tag(del)
def_tag(details)
def_tag(dfn)
def_tag(dialog)
def_tag(div)
def_tag(dl)
def_tag(dt)
def_tag(em)
def_tag(fieldset)
def_tag(figcaption)
def_tag(figure)
def_tag(footer)
def_tag(form)
def_tag(h1)
def_tag(h2)
def_tag(h3)
def_tag(h4)
def_tag(h5)
def_tag(h6)
def_tag(head)
def_tag(header)
def_tag(hgroup)
def_tag(html)
def_tag(i)
def_tag(iframe)
def_tag(ins)
def_tag(kbd)
def_tag(label)
def_tag(legend)
def_tag(li)
def_tag(map)
def_tag(mark)
def_tag(math)
def_tag(menu)
def_tag(meter)
def_tag(nav)
def_tag(noscript)
def_tag(object)
def_tag(ol)
def_tag(optgroup)
def_tag(option)
def_tag(output)
def_tag(p)
def_tag(picture)
def_tag(pre)
def_tag(progress)
def_tag(q)
def_tag(rp)
def_tag(rt)
def_tag(ruby)
def_tag(s)
def_tag(samp)
def_tag(script)
def_tag(section)
def_tag(select)
def_tag(small)
def_tag(span)
def_tag(strong)
def_tag(style)
def_tag(sub)
def_tag(summary)
def_tag(sup)
def_tag(svg)
def_tag(table)
def_tag(tbody)
def_tag(td)
def_tag(textarea)
def_tag(tfoot)
def_tag(th)
def_tag(thead)
def_tag(time)
def_tag(tr)
def_tag(u)
def_tag(ul)
def_tag(var)
def_tag(video)
def_tag_ex(template_tag, "template")
def_tag_ex(main_tag, "main")

def_ne_tag(base)
def_ne_tag(br)
def_ne_tag(col)
def_ne_tag(embed)
def_ne_tag(hr)
def_ne_tag(img)
def_ne_tag(input)
def_ne_tag(link)
def_ne_tag(menuitem)
def_ne_tag(meta)
def_ne_tag(param)
def_ne_tag(source)
def_ne_tag(track)
def_ne_tag(wbr)


// Global attributes
def_attr_ex(cls, "class")

def_attr(accesskey)
def_attr(contenteditable)
def_attr(contextmenu)
def_attr(dir)
def_attr(draggable)
def_attr(dropzone)
def_bool_attr(hidden)
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

// tag attributes

def_attr_ex(http_equiv, "http-equiv")
def_attr_ex(accept_charset, "accept-charset")
def_attr_ex(forc, "for")
def_bool_attr_ex(default_attr, "default")

def_attr(accept)
def_attr(action)
def_attr(alt)
def_attr(autocomplete)
def_attr(charset)
def_attr(cite)
def_attr(cols)
def_attr(colspan)
def_attr(content)
def_attr(coords)
def_attr(crossorigin)
def_attr(data)
def_attr(datetime)
def_attr(dirname)
def_attr(download)
def_attr(enctype)
def_attr(form)
def_attr(formaction)
def_attr(formenctype)
def_attr(formmethod)
def_attr(formtarget)
def_attr(headers)
def_attr(height)
def_attr(high)
def_attr(href)
def_attr(hreflang)
def_attr(icon)
def_attr(inputmode)
def_attr(kind)
def_attr(label)
def_attr(list)
def_attr(loop)
def_attr(low)
def_attr(manifest)
def_attr(max)
def_attr(maxlength)
def_attr(media)
def_attr(mediagroup)
def_attr(method)
def_attr(min)
def_attr(minlength)
def_attr(name)
def_attr(nonce)
def_attr(optimum)
def_attr(pattern)
def_attr(ping)
def_attr(placeholder)
def_attr(poster)
def_attr(preload)
def_attr(radiogroup)
def_attr(rel)
def_attr(rows)
def_attr(rowspan)
def_attr(sandbox)
def_attr(scope)
def_attr(shape)
def_attr(sizes)
def_attr(sorted)
def_attr(span)
def_attr(src)
def_attr(srcdoc)
def_attr(srclang)
def_attr(srcset)
def_attr(start)
def_attr(step)
def_attr(target)
def_attr(type)
def_attr(usemap)
def_attr(value)
def_attr(width)
def_attr(wrap)

def_bool_attr(async)
def_bool_attr(allowfullscreen)
def_bool_attr(autofocus)
def_bool_attr(autoplay)
def_bool_attr(checked)
def_bool_attr(controls)
def_bool_attr(defer)
def_bool_attr(disabled)
def_bool_attr(formnovalidate)
def_bool_attr(ismap)
def_bool_attr(multiple)
def_bool_attr(muted)
def_bool_attr(novalidate)
def_bool_attr(open)
def_bool_attr(readonly)
def_bool_attr(required)
def_bool_attr(reversed)
def_bool_attr(scoped)
def_bool_attr(seamless)
def_bool_attr(selected)
def_bool_attr(sortable)
def_bool_attr(typemustmatch)

//  event handlers
def_attr(onafterprint)
def_attr(onbeforeprint)
def_attr(onbeforeunload)
def_attr(onhashchange)
def_attr(onlanguagechange)
def_attr(onmessage)
def_attr(onoffline)
def_attr(ononline)
def_attr(onpagehide)
def_attr(onpageshow)
def_attr(onpopstate)
def_attr(onrejectionhandled)
def_attr(onstorage)
def_attr(onunhandledrejection)
def_attr(onunload)

#undef def_tag
#undef def_tag_ex
#undef def_attr
#undef def_attr_ex
#undef def_bool_attr
#undef def_bool_attr_ex
#undef def_ne_tag
}