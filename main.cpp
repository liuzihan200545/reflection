#include <random>

#include "print.h"
#include <string>
#include "variable_traits.hpp"
#include "function_traits.hpp"
#include "loginfo.hpp"
#include "utils.hpp"

using namespace std;
using namespace std::string_literals;

bool Func(double d) {
    return true;
}

struct Person final {

    string familyName;
    float height;
    bool isFemale;

    void IntroduceMySelf(int a,int b) const {
        print_elements_with_space(a,b);
    }

    bool IsFemale(bool _is_femal) {
        print(false);
        return false;
    }

    bool GetMarried(Person& other) {
        bool success = other.isFemale != isFemale;
        if(isFemale) {
            familyName = "Mrs." + familyName;
        }
        else {
            familyName = "Mr." + familyName;
        }
        return success;
    }

};

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

BEGIN_CLASS(Person)
    FUNCTIONS(func(&Person::GetMarried),
              func(&Person::IsFemale),
              func(&Person::IntroduceMySelf)
    )
    VARIABLES(var(&Person::height),
              var(&Person::familyName),
              var(&Person::isFemale)
              )
END_CLASS()

template <class T>
constexpr auto type_Info() {
    return TypeInfo<T>{};
}

template <int N>
auto function() -> int {
    return N;
}

template <size_t... Idx, class Tuple,class Func>
void VisitTuple(Tuple tuple,std::index_sequence<Idx...>,Func&& f) {
    (f(std::get<Idx>(tuple)) , ...);
}

int main() {

    constexpr auto info = type_Info<Person>();

    auto person = Person();
    auto instance = &person;

    constexpr size_t length = tuple_size_v<decltype(info.functions)>;

    /*static_for<0,length>([=](auto x) {
        constexpr string_view _name = std::get<x.value>(info.functions).name;
        auto function = std::get<x.value>(info.functions);
        constexpr int _length = std::get<x.value>(info.functions).param_count;
        auto _ptr = std::get<x.value>(info.functions).pointer;
        if constexpr (_length == 1 && std::is_same_v<typename decltype(function)::args_with_class,std::tuple<Person*,bool>>) {
            (instance->*_ptr)(true);
        }
    });*/



    /*auto functions = info.functions;

    auto number = Intergral_constant<tuple_size_v<decltype(functions)>>{};

    auto tuple = std::tuple(1,2,3,4,5,6,7);
    auto ret = Visit(tuple,make_index_sequence<number.value>());

    log_DEBUG("Project {}","Completed");*/



    VisitTuple(info.functions,make_index_sequence<info.func_num>(),
        [&](auto&& obj) {
            print(obj.param_count);
        });

    VisitTuple(info.variables,make_index_sequence<info.var_num>(),
        [&](auto&& obj) {
            auto ptr = obj.pointer;
            print(instance->*ptr);
        });


}


