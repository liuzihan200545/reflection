#pragma once

// implement my own type traits library
namespace my_type_traits {

    // pointer remover
    template <class T>
    struct remove_pointer {
        using type = T;
    };

    template <class T>
    struct remove_pointer<T *> {
        using type = T;
    };

    template <class T>
    using remove_pointer_v = typename ::my_type_traits::remove_pointer<T>::type;

    // function traits
    template <class T>
    struct function_traits;

    // function with single parameter
    template <class Ret,class Param>
    struct function_traits <Ret(*)(Param)> {
        using params = Param;
        using ret = Ret;
        static constexpr bool is_class = false;
    };

    template <class Ret,class... Param>
    struct function_traits<Ret(*)(Param...)> {
        using ret = Ret;
        using params = tuple<Param...>;
        static constexpr bool is_class = false;
    };

    // class member function
    template <class Ret,class Class,class Param>
    struct function_traits <Ret(Class::*)(Param)> {
        using ret = Ret;
        using params = Param;
        using class_type = Class;
        static constexpr bool is_class = true;
    };

    template <class Ret,class Class,class ... Param>
    struct function_traits <Ret(Class::*)(Param...)> {
        using ret = Ret;
        using params = tuple<Param...>;
        using class_type = Class;
        static constexpr bool is_class = true;
    };

    // remove const from a type
    template <class T>
    struct remove_const {};

    template <class T>
    struct remove_const <const T> {
        using type = T;
    };

    // variable type traits
    template <class T>
    struct variable_traits;

    template <class Class,class Type>
    struct variable_traits<Type Class::* > {
        using type = Type;
        using class_type = Class;
        static constexpr bool is_class = true;
    };

    // class to assist debug the template coding
    // It can print out the type of the class T
    template <class T>
    struct type_impl {
        static constexpr void get_info() {
            string s = __PRETTY_FUNCTION__;
            unsigned long pos = s.find("with T = ") + 9;
            unsigned long pos1 = s.find(']');
            cout << s.substr(pos,pos1-pos) << endl;
        }
    };

    //use the compile_time error to show the type info
    template <class T>
    struct show_tmpl;

    namespace utils {
        template <class T>
        void print_type() {
            my_type_traits::type_impl<T>::get_info();
        }

        template <class T>
        void print_type_of_val(T t) {
            my_type_traits::type_impl<T>::get_info();
        }
    }

}


