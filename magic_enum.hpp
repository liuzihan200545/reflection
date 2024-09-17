#pragma once

#include <string>

using namespace std;

namespace detail {
    template <class T,int N>
    string get_function_information(){
    #if defined(_MSC_VER)
            return __FUNCSIG__;
    #else
            return __PRETTY_FUNCTION__;
    #endif
    }


    template <int N>
struct int_constant{
        static constexpr int value = N;
    };

    template <int Beg,int End,class F>
    void static_for(F const & func){
        if constexpr (Beg == End){
            return;
        }
        else{
            func(integral_constant<int,Beg>());
            static_for<Beg+1,End>(func);
        }
    }
}

template <class T,int N>
string get_enum_name_static(){
    string s = detail::get_function_information<T,T(N)>();
#if defined(_MSC_VER)
    int pos1 = s.find_last_of(',');
    int pos2 = s.find_last_of('>');
    return s.substr(pos1+1,pos2-pos1-1);
#else
    int pos = s.find("N = ") + 4;
    int pos1 = s.find_first_of(";]",pos);
    return s.substr(pos,pos1 - pos);
#endif
}

template <class T>
string get_enum_name_dynamic(T n){
    string ret;
    detail::static_for<0,256>([&](auto i){
        if (n == static_cast<T>(i.value)){
            ret = get_enum_name_static<T,i>();
        }
    });
    return ret;
}