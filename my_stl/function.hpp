#pragma once
#include <memory>
#include <typeinfo>
#include <exception>
#include "../print.h"

namespace inner {
    struct bad_function_call final : std::exception {
        explicit bad_function_call() = default;

        virtual const char* what() const noexcept override {
            return "bad function call : invalid function !!!";
        }
    };
}

typedef void(*pfunc_t)();

template <class F>
struct Function {
    static_assert(!std::is_same_v<F,F>, "The template of the function is invalid!!!");
};

template <class Ret, class... Args>
struct Function<Ret(Args...)> {

    struct Base {
        virtual Ret call(Args... args) = 0;
        virtual ~Base() = default;
        virtual const std::type_info& M_type() const = 0;
    };

    template <class F>
    struct Inner final : Base {
        F f;

        explicit Inner(F f) : f(std::move(f)) {}

        virtual Ret call(Args... args) override {
            return f(std::forward<Args>(args)...);
        }

        virtual const std::type_info& M_type() const override {
            return typeid(F);
        }

        virtual ~Inner() override {
            log_DEBUG("The destructor of Inner");
        }
    };

    std::shared_ptr<Base> m_ptr;

    template <class F> requires (!is_same_v<decay_t<F>,Function>)
    explicit Function(F func) : m_ptr(std::make_shared<Inner<F>>(std::move(func))) {}

    Function(Function &&) = default;

    Function &operator=(Function &&) = default;

    Function(const Function &other) {
        this->m_ptr = other.m_ptr;
    }

    Function &operator=(const Function &other) {
        this->m_ptr = other.m_ptr;
        return *this;
    }

    Ret operator()(Args... args) {
        if (!m_ptr) [[unlikely]] {
            throw inner::bad_function_call();
        }
        return m_ptr->call(std::forward<Args>(args)...);
    }

    const std::type_info& M_type() const noexcept {
        return m_ptr->M_type();
    }

    explicit operator bool () const noexcept {
        return m_ptr != nullptr;
    }

    bool operator==(nullptr_t) const {
        return m_ptr == nullptr;
    }

    bool operator!=(nullopt_t) const {
        return m_ptr != nullptr;
    }

};
