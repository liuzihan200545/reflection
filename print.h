#pragma once

#include <format>
#include <iostream>

using namespace std;

template<typename... _Args>
void print(format_string<_Args...> __fmt, _Args&&... __args){
    std::cout <<  std::vformat(__fmt.get(), std::make_format_args(__args...)) << "\n";
}



