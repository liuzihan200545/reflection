#include "print.h"
#include <string>
#include "variable_traits.hpp"
#include "function_traits.hpp"
#include "utils.hpp"

using namespace std;

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
};

template<class T>
struct TypeInfo {
};

#define BEGIN_CLASS(T)             \
template <> struct TypeInfo<T>{    \
    using type = T;

#define END_CLASS() };

#define FUNCTIONS(...) using functions = tuple<__VA_ARGS__>;

#define VARIABLES(...) using variables = tuple<__VA_ARGS__>;

BEGIN_CLASS(Person)
FUNCTIONS(function_traits<decltype(&Person::IsFemale)>,
          function_traits<decltype(&Person::IntroduceMySelf)>,
          function_traits<decltype(&Person::GetMarried)>)
VARIABLES(variable_traits<decltype(&Person::height)>,
          variable_traits<decltype(&Person::familyName)>,
          variable_traits<decltype(&Person::isFemale)>)
END_CLASS()

int main() {
    using type1 = variable_traits<decltype(&Person::familyName)>::clazz;
    print_type<type1>();
}
