#pragma once

#include <string>
#include <tuple>
#include "utils.hpp"
#include "variable_traits.hpp"
#include "function_traits.hpp"

template<class T>
struct TypeInfo {
};

#define BEGIN_CLASS(T)             \
template <> struct TypeInfo<T>{    \
using type = T;

#define FUNCTIONS(...) \
static constexpr auto functions = make_tuple(__VA_ARGS__); \
static constexpr int func_num = std::tuple_size_v<decltype(functions)>;

#define func(F) field_traits{F,#F}

#define VARIABLES(...) \
static constexpr auto variables = make_tuple(__VA_ARGS__); \
static constexpr int var_num = std::tuple_size_v<decltype(variables)>;

#define var(X) field_traits{X,#X}

#define END_CLASS() };

template <class T>
constexpr auto type_Info() {
    return TypeInfo<T>{};
}