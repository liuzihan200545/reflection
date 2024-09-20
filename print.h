#pragma once

#include <format>
#include <iostream>
#include "utils.hpp"

using namespace std;

template<typename... Args>
void println(format_string<Args...> _fmt, Args&&... _args){
    std::cout <<  std::vformat(_fmt.get(), std::make_format_args(_args...)) << "\n";
}

struct print_counter {

    static int get_n() {
        return n;
    }

    static void count_plus() {
        n++;
    }

private:
    static int n;
};

int print_counter::n = 0;

template <class T>
void print(T content) {

    if constexpr (has_insertion_operator_v<T>) {
        if constexpr (std::is_same_v<T,bool>) {
            if(content == true) {
                println("[{}]: {}",print_counter::get_n(),"true");
                print_counter::count_plus();
            }
            else if constexpr (std::is_same_v<const char*,T>) {
                // 处理 const char*，将其转换为 std::string
                println("[{}]: {}", print_counter::get_n(), std::string(content));
            }
            else {
                println("[{}]: {}",print_counter::get_n(),"false");
                print_counter::count_plus();
            }
        }
        else{
            //std::cout << '[' << print_counter::get_n << "]: " << content << endl;
            println("[{}]: {}",print_counter::get_n(),content);
            print_counter::count_plus();
        }
    }

    else {
        // 不支持输出的类型
        auto ret = format("The {} type doesn't support the 'cout <<' operation.", type_impl<T>::get_info_s());
        std::cout << ret << std::endl;
    }
}

// print mutiple variables with space be the spliter
template <class ... Args>
void print_elements_with_space(Args ... args) {
    auto func = [=](auto x) {
        using type = decltype(x);
        if constexpr (has_insertion_operator_v<type>) {
            cout << x ;
        }
        else {
            auto ret = format("The {} type doesn't support the 'cout <<' operation.", type_impl<type>::get_info_s());
            cerr << ret ;
        }
    };
    ((func(args),cout << " ") , ...);
    std::cout << "\n";
}