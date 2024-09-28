#pragma once

#include <string>
#include "utils.hpp"

using namespace std;

template <class T>
string get_type_name() {
    string s = __PRETTY_FUNCTION__;
    auto pos = s.find("T = ");
    pos += 4;
    auto pos2 = s.find_first_of(";]",pos);
    return s.substr(pos,pos2 - pos);
}

template <class T>
string get_type_name_dynamic(T t) {
    string s = __PRETTY_FUNCTION__;
    auto pos = s.find("T = ");
    pos += 4;
    auto pos2 = s.find_first_of(";]",pos);
    return s.substr(pos,pos2 - pos);
}

template <class T,T N>
string get_int_name_static() {
    string s = __PRETTY_FUNCTION__;
    auto pos = s.find("N = ");
    pos += 4;
    auto pos2 = s.find_first_of(";]",pos);
    return s.substr(pos,pos2 - pos);
}

template <class T>
string get_int_name_dynamic(T n) {
    string ret;
    static_for<0,16>([&](auto i) {
        if(i.value == n) {
            ret = get_int_name_static<T,T(i.value)>();
        }
    });
    return ret;
}

enum Color {
    BLUE,YELLOW,RED,GREEN
};
