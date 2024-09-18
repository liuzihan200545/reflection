#include <random>

#include "print.h"
#include <string>
#include "variable_traits.hpp"
#include "function_traits.hpp"
#include "loginfo.hpp"
#include "utils.hpp"
#include "magic_enum.hpp"

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
static constexpr auto functions = make_tuple(__VA_ARGS__);

#define func(F) field_traits{F,#F}

#define VARIABLES(...) \
static constexpr auto variables = make_tuple(__VA_ARGS__);

#define var(X) field_traits{X,#X}

#define END_CLASS() };

BEGIN_CLASS(Person)
    FUNCTIONS(func(&Person::GetMarried),
              func(&Person::IsFemale),
              func(&Person::IntroduceMySelf)
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

template <size_t... Idx, class Tuple>
int Visit(Tuple tuple,index_sequence<Idx...>) {
    int num = 0;
    ((num += std::get<Idx>(tuple)) , ...);
    return num;
}


int main() {

    constexpr auto info = type_Info<Person>();

    auto person = Person();
    auto instance = &person;

    constexpr size_t length = tuple_size_v<decltype(info.functions)>;

    static_for<0,length>([=](auto x) {
        constexpr string_view _name = std::get<x.value>(info.functions).name;
        auto function = std::get<x.value>(info.functions);
        constexpr int _length = std::get<x.value>(info.functions).param_count;
            auto _ptr = std::get<x.value>(info.functions).pointer;
            if constexpr (_length == 1 && std::is_same_v<typename decltype(function)::args_with_class,std::tuple<Person*,bool>>) {
                (instance->*_ptr)(true);
                cout << "\n";
            }
    });

    auto functions = info.functions;

    auto number = Intergral_constant<tuple_size_v<decltype(functions)>>{};

    auto tuple = std::tuple(1,2,3,4,5,6,7);
    auto ret = Visit(tuple,make_index_sequence<number.value>());

    log_DEBUG("Project {}","Completed");
}


