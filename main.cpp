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
};

template<class T>
struct TypeInfo {
};

#define BEGIN_CLASS(T)             \
template <> struct TypeInfo<T>{    \
using type = T;

#define FUNCTIONS(...) \
static constexpr auto functions = make_tuple( \
    __VA_ARGS__ \
);

#define VARIABLES(...) \
static constexpr auto variables = make_tuple( \
    __VA_ARGS__ \
);

#define END_CLASS() };

BEGIN_CLASS(Person)
    FUNCTIONS(&Person::GetMarried,&Person::IsFemale,&Person::IntroduceMySelf)
END_CLASS()

template <class T>
void test(T content) {
    if(is_same_v<T,bool>) {
        cout << "fuck" << endl;
    }
}

int main() {
    print("Hank");
    print(true);
    auto p = Person();
    print(p);
    print(typeid(p).name());
}


