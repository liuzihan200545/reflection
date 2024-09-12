#pragma once

#include <type_traits>

namespace detail {

    template <class T> struct variable_type {
        using type = T;
    };

    template <class T,class Class> struct variable_type<T(Class::*)> {
        using type = T;
    };

}

template <class T>
using variable_type_t = typename detail::variable_type<T>::type;

namespace internal {

    template <class T> struct basic_variable_traits {
        using type = variable_type_t<T>;
        static constexpr bool is_member = std::is_member_pointer_v<T>;
    };

}

template <class T> struct variable_traits;

template <class T>
struct variable_traits< T* > : internal::basic_variable_traits<T> {
    using pointer_type = T*;
};

template <class Class,class T>
struct variable_traits< T(Class::*) > : internal::basic_variable_traits<T(Class::*)> {
    using pointer_type = T(Class::*);
    using clazz = Class;
};