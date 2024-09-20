#include <random>

#include "print.h"
#include <string>
#include "loginfo.hpp"
#include "reflection.hpp"
#include "variable_traits.hpp"
#include "function_traits.hpp"

using namespace std;
using namespace std::string_literals;

struct Person final {

    string familyName;
    float height;
    bool isFemale;

    Person(string _name,float _height,bool _isfemale) {
        familyName = _name;
        height = _height;
        isFemale = _isfemale;
    }

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

BEGIN_CLASS(Person)
    FUNCTIONS(func(&Person::IntroduceMySelf))

    VARIABLES(var(&Person::height),
              var(&Person::familyName),
              var(&Person::isFemale)
              )
END_CLASS()

template <size_t... Idx, class Tuple,class Func>
void VisitTuple(Tuple tuple,std::index_sequence<Idx...>,Func&& f) {
    (f(std::get<Idx>(tuple)) , ...);
}

int main() {

    constexpr auto info = type_Info<Person>();

    auto person = Person("Hank",19,false);
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
            //print(obj.param_count);
            obj.invoke(instance,1,2);
        });

    VisitTuple(info.variables,make_index_sequence<info.var_num>(),
        [&](auto&& obj) {
            print(obj.invoke(instance));
        });

}


