#pragma once 

#include <cstddef>
#include <type_traits>

#include <charconv>
#include <optional>
#include <string_view>
#include <variant>
#include <unordered_map>
#include <string>
#include <vector>
#include <iostream>
namespace Json {


struct JSONObject;

using JSONList = std::vector<JSONObject>;
using JSONMap =  std::unordered_map<std::string, JSONObject>;
struct JSONObject {
    std::variant<
        std::monostate,
        bool,
        int,
        double,
        std::string,
        JSONList,
        JSONMap 
    > inner;
    
    static JSONObject fromFile(std::string_view filename);
    static std::pair<JSONObject, size_t> parse(std::string_view json);
    static bool canEatToken(std::string_view json, std::string_view token);
    static char unescape_char(char ch);

    bool asBool() const;
    int asInt() const;
    double asDouble() const;
    std::string asString() const;
    JSONMap asMap() const;
    JSONList asList() const;

    bool isBool() const;
    bool isInt() const;
    bool isDouble() const ;
    bool isString() const ;
    bool isMap() const;
    bool isList() const;

    JSONObject& operator[](const std::string& key);
    JSONObject& operator[](size_t index);
    JSONObject operator[](const std::string& key) const; 
    JSONObject operator[](size_t index) const;
    bool operator==(std::monostate);
    bool operator!=(std::monostate);

    template<typename T>
    static std::optional<T> tryParseNum(std::string_view str) {
        T value;
        int n, res = 0;
        if constexpr (std::is_same_v<T, int>) {
            res = sscanf(str.data(), "%d%n", &value, &n);
        } else if constexpr (std::is_same_v<T, double>) {
            res = sscanf(str.data(), "%lf%n", &value, &n);
        }
        if(res && n == str.size()) {
            return value;
        }
        return std::nullopt;
    }
    
};

  
template <class ...Fs>
struct overloaded : Fs... {
    using Fs::operator()...;
};

template <class ...Fs>
overloaded(Fs...) -> overloaded<Fs...>;

std::ostream& operator<<(std::ostream& os, const JSONObject& obj);

} // namespace Json
