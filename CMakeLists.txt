cmake_minimum_required(VERSION 3.21)
project(class_model)

set(CMAKE_CXX_STANDARD 23)

add_executable(class_model main.cpp
        print.h
        refl.h
        variable_traits.hpp
        function_traits.hpp
        utils.hpp
        loginfo.hpp)
