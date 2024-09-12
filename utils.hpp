#include <iostream>

using namespace std;

template <class T>
struct type_impl {
    static constexpr void get_info() {
        string s = __PRETTY_FUNCTION__;
        unsigned long pos = s.find("with T = ") + 9;
        unsigned long pos1 = s.find(']');
        cout << s.substr(pos,pos1-pos) << endl;
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