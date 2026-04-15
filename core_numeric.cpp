// core_numeric.cpp
#include <concepts>
#include <iterator>
#include <vector>
#include <type_traits>
#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

namespace core_numeric {

// ---------------- Concepts obligatorios ----------------
template<typename C>
concept Iterable = requires (C c) {
    begin(c);
    end(c);
};

template<typename T>
concept Addable = requires (T a, T b) {
    { a + b } -> same_as<T>;
};

template<typename T>
concept Divisible = requires (T a, size_t n) {
    { a / n } -> same_as<T>;
};

// Concept adicional (propio): Comparable
template<typename T>
concept Comparable = requires (T a, T b) {
    { a < b } -> convertible_to<bool>;
    { a > b } -> convertible_to<bool>;
};

// ---------------- Algoritmos ----------------

// Algoritmo sum
template<Iterable C>
requires Addable<typename C::value_type> //Detectar errores al momento compilacion / definir funciones / construir APIs
auto sum(const C& container) {
    using T = typename C::value_type;
    T result{};
    for (const auto& value : container)
        result = result + value;
    return result;
}

// Algoritmo mean
template<Iterable C>
requires Divisible<typename C::value_type>
auto mean(const C& container) {
    using T = typename C::value_type;
    T total = sum(container);
    size_t n = distance(begin(container), end(container));
    return total / n;
}

// Algoritmo variance
template<Iterable C>
requires Addable<typename C::value_type> && Divisible<typename C::value_type>
auto variance(const C& container) {
    using T = typename C::value_type;
    T m = mean(container);
    T acc{};
    for (const auto& value : container) {
        T diff = value - m;
        acc = acc + diff * diff;
    }
    size_t n = distance(begin(container), end(container));
    return acc / n;
}

// max
template<Iterable C>
requires Comparable<typename C::value_type>
auto max(const C& container) {
    using T = typename C::value_type;
    auto it = begin(container);
    T max_val = *it;
    for (++it; it != end(container); ++it)
        if (*it > max_val)
            max_val = *it;
    return max_val;
}

// transform_reduce
template<Iterable C, typename F>
requires Addable<typename C::value_type>
auto transform_reduce(const C& container, F func) {
    using T = typename C::value_type;
    T result{};
    for (const auto& value : container)
        result = result + func(value);
    return result;
}

// Variadic templates y fold expressions
template<Addable T, typename... Args>
requires (Addable<Args> && ...)
auto sum_variadic(T first, Args... args) {
    return (first + ... + args); // fold expression
}

template<Divisible T, typename... Args>
requires (Divisible<Args> && ...)
auto mean_variadic(T first, Args... args) {
    auto total = (first + ... + args);
    size_t n = sizeof...(args) + 1;
    return total / n;
}

template<Addable T, typename... Args>
requires (Addable<Args> && ...)
auto variance_variadic(T first, Args... args) {
    vector<T> v{first, args...};
    return variance(v);
}

template<Comparable T, typename... Args>
requires (Comparable<Args> && ...)
auto max_variadic(T first, Args... args) {
    return std::max({first, args...});
}

// if constexpr
template<typename T>
void show_type_info() {
    if constexpr (is_integral_v<T>) {
        cout << "Tipo entero\n";
    } else {
        cout << "Tipo flotante\n";
    }
}

}
