#pragma once

#include <cstdint>
#include <functional>
#include <vector>

class Type {

public:
virtual ~Type() = default;

    explicit Type(const std::string& name) : name_(name) {}

    const std::string & get_name() const {
        return name_;
    }

private:
    std::string name_;
};

class Numeric : public Type {
public:
    enum class Kind {
        Int8 , Int16 , Int32 , Int64 , Int128 , Float , Double , Unknown
    };

    Numeric(Kind kind,bool is_signed) : Type(getName(kind)) , is_signed_(is_signed), kind_(kind) {}

    auto getKind() const { return kind_;}

    bool IsSigned() const { return is_signed_ ;}

    template <class T>
    static Numeric Create() {
        return Numeric(detect_kind<T>(),std::is_signed_v<T>);
    }

private:
    bool is_signed_;
    Kind kind_;



    template <class T>
    static Kind detect_kind() {
        if constexpr (std::is_same_v<int8_t,T>) {
            return Kind::Int8;
        }
        else if(std::is_same_v<int16_t,T>) {
            return Kind::Int16;
        }
        else if(std::is_same_v<int32_t,T>) {
            return Kind::Int32;
        }
        else if(std::is_same_v<int64_t,T>) {
            return Kind::Int64;
        }
        else if(std::is_same_v<__int128_t,T>) {
            return Kind::Int128;
        }
        else if(std::is_same_v<float,T>) {
            return Kind::Float;
        }
        else if(std::is_same_v<double,T>){
            return Kind::Double;
        }
        else {
            return Kind::Unknown;
        }
    }

    static std::string getName(const Kind kind) {
        switch (kind) {
            case Kind::Int8 :
                return "int8";
            case Kind::Int16 :
                return "int16";
            case Kind::Int32 :
                return "int32";
            case Kind::Int64 :
                return "int64";
            case Kind::Int128 :
                return "int128";
            case Kind::Float :
                return "float";
            case Kind::Double :
                return "double";
        }
        return "unKnown";
    }
};

class Enum : public Type {
public:
    struct Item {
        using value_type = int32_t;

        std::string name;
        value_type value;
    };

    Enum(const std::string& name) : Type(name) {}

    template <class T>
    void Add(const std::string& name,T value) {
        items_.emplace_back(Item({name,static_cast<typename Item::value_type>(value)}));
    }

    const auto & get_items() {
        return items_;
    }

private:
    std::vector<Item> items_;
};

class Class : public Type {
public:
};

template <class T>
class NumericFactory final {
public:
    static NumericFactory& Instance() {
        static NumericFactory inst(Numeric::Create<T>());
        return inst;
    }

    const Numeric& info() {
        return info_;
    }

private:
    Numeric info_;

    explicit NumericFactory(Numeric && info) : info_(std::move(info)) {}

};