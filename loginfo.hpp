#pragma once

#include <format>
#include <iostream>
#include <source_location>
#include <string>
#include "magic_enum.hpp"

using namespace std;

#define foreach_log_level(f) \
f(DEBUG)                 \
f(INFO)                  \
f(WARNING)               \
f(ERROR)

#define _FUNCTION(x) x,

enum log_level{
    foreach_log_level(_FUNCTION)
};

#undef _FUNCTION

// TODO : Use the string literal to initialze the log function

struct project_log_level {

    static log_level _log_level;

    static void set_log_level(log_level _level) {
        _log_level = _level;
    }

};

log_level project_log_level::_log_level = log_level::DEBUG;

struct with_source_location {
private:
    source_location m_loc;
    string m_inner;

public:
    with_source_location(string inner, source_location loc = source_location::current())
        : m_loc(loc), m_inner(move(inner)) {}

    const string& fmt() const {
        return m_inner;
    }

    const source_location& loc() const {
        return m_loc;
    }
};

template <class... Args>
void log(const with_source_location& loc, Args&&... args) {
    try {
        string formatted = std::vformat(loc.fmt(), std::make_format_args(std::forward<Args>(args)...));
        std::cout << formatted << std::endl;
    } catch (const std::format_error& e) {
        std::cerr << "Format error: " << e.what() << std::endl;
    }
}

template <class... Args>
inline void generic_log(log_level level,const with_source_location&& loc, Args&&... args) {
    if(level >= project_log_level::_log_level) {
        std::cout << format("[{}]  func:[{}]  ",get_int_name_dynamic(level),loc.loc().function_name());
        log(loc,args...);

        // TODO: support print out the log level

        //cout << format("[{}]",get_enum_name_dynamic(level)) << endl;
    }
}

#define _FUNCTION(name) \
template <class... Args> \
inline void log_##name(const with_source_location&& loc, Args&&... args){ \
    generic_log(log_level::name,std::move(loc),forward<Args...>(args)...);  \
}

foreach_log_level(_FUNCTION)

#undef _FUNCTION

// Example usage
void example_function() {
    log(with_source_location("Test message: {}"), "Hello, World!");
}

