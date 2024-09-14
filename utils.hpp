#pragma once

#include <iostream>
#include "function_traits.hpp"
#include "variable_traits.hpp"

using namespace std;

//TODO: cross compiler

template <class T>
struct type_impl {
    static constexpr void get_info() {
        string s = __PRETTY_FUNCTION__;
        unsigned long pos = s.find("with T = ") + 9;
        unsigned long pos1 = s.find(';');
        cout << s.substr(pos,pos1-pos) << endl;
    }

    static constexpr string get_info_s() {
        string s = __PRETTY_FUNCTION__;
        unsigned long pos = s.find("with T = ") + 9;
        unsigned long pos1 = s.find(';');
        return s.substr(pos,pos1-pos);
    }
};

template <class T>
void print_type() {
    type_impl<T>::get_info();
}

template <class T>
void print_type_of_val(T t) {
    type_impl<T>::get_info();
}

template <class Ret,class... Params>
auto function_pointer_type(Ret(*)(Params...)) -> Ret(*)(Params...);

template <class Ret,class ... Params,class Class>
auto function_pointer_type(Ret(Class::*)(Params...)) -> Ret(Class::*)(Params...);

template <class Ret,class ... Params,class Class>
auto function_pointer_type(Ret(Class::*)(Params...) const ) -> Ret(Class::*)(Params...) const;

template <auto F>
using function_pointer_type_t = decltype(function_pointer_type(F));

template <class Type>
auto variable_pointer_type(Type*) -> Type*;

template <class Class,class Type>
auto variable_pointer_type(Type(Class::*)) -> Type(Class::*);

template <auto X>
using variable_pointer_type_t = decltype(variable_pointer_type(X));

template <auto F>
using function_traits_t = function_traits<function_pointer_type_t<F>>;

template <auto F>
using variable_traits_t = variable_traits<variable_pointer_type_t<F>>;

template <class T,bool isFunc>
struct basic_field_traits;

template <class T>
struct basic_field_traits<T,true> : public function_traits<T>{
    using traits = function_traits<T>;

    constexpr bool is_member() const {
        return traits::is_member;
    }

    constexpr bool is_const() const {
        return traits::is_const;
    }

    constexpr bool is_function() const {
        return true;
    }

    constexpr bool is_variable() const {
        return false;
    }
};

template <class T>
struct basic_field_traits<T,false> : public variable_traits<T>{
    using traits = variable_traits<T>;

    constexpr bool is_member() const {
        return traits::is_member;
    }

    constexpr bool is_const() const {
        return traits::is_const;
    }

    constexpr bool is_function() const {
        return false;
    }

    constexpr bool is_variable() const {
        return true;
    }
};

template <class T>
struct my_is_function {
    static constexpr bool value = is_function_v<remove_pointer_t<T>> || is_member_function_pointer_v<T>;
};

template <class T>
inline constexpr bool my_is_function_v = my_is_function<T>::value;

template <class T>
struct field_traits : public basic_field_traits<T,my_is_function_v<T>>{
    constexpr field_traits(T&& pointer) : pointer(pointer){}
    T pointer;
};

// Check if the type can be printed out by cout
template <typename T>
struct has_insertion_operator {
    template <typename U>
    static auto test(int) -> decltype(std::cout << std::declval<U>(), std::true_type{});

    template <typename>
    static std::false_type test(...);

public:
    static constexpr bool value = decltype(test<T>(0))::value;
};

template <class T>
static constexpr bool has_insertion_operator_v = has_insertion_operator<T>::value;




