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

    void IntroduceMySelf() const {}

    bool IsFemale() {
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

    static void print_name() {

    }
};

template<class T>
struct TypeInfo {
};

#define BEGIN_CLASS(T)             \
template <> struct TypeInfo<T>{    \
using type = T;

#define FUNCTIONS(...) \
static constexpr auto functions = make_tuple(__VA_ARGS__);

#define func(F) field_traits{F,#F}

#define VARIABLES(...) \
static constexpr auto variables = make_tuple(__VA_ARGS__);

#define var(X) field_traits{X,#X}

#define END_CLASS() };

BEGIN_CLASS(Person)
    FUNCTIONS(func(&Person::GetMarried),
              func(&Person::IsFemale),
              func(&Person::IntroduceMySelf),
              func(&Person::print_name)
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

template <int Beg,int End>
constexpr void static_for(auto _func) {
    if constexpr (Beg == End) {
        return;
    }
    else {
        _func(Intergral_constant<Beg>{});
        static_for<Beg+1,End>(_func);
    }
}

int main() {
    constexpr auto info = type_Info<Person>();

    print(std::get<3>(info.functions).name);

    static_for<0,3>([=](auto x) {
        print(std::get<x.value>(info.functions).name);
    });
}


