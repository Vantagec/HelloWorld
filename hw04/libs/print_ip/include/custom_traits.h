#pragma once

#include <cstdint>
#include <type_traits>
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <tuple>
#include <algorithm>



namespace {
template <typename T>
struct is_std_string: std::false_type {};

template <>
struct is_std_string<std::string>: std::true_type {};

}

template <typename T>
inline constexpr bool is_std_string_v = is_std_string<T>::value;

namespace { 

template <typename ... Args>
struct is_std_vector_helper: std::false_type {};

template <typename ... Args>
struct is_std_vector_helper<std::vector<Args...>>: std::true_type {};

template <typename ... Args>
using is_std_vector = is_std_vector_helper<Args...>;

}


template <typename T>
inline constexpr bool is_std_vector_v = is_std_vector<T>::value;

namespace { 

template <typename ... Args>
struct is_std_list_helper: std::false_type {};

template <typename ... Args>
struct is_std_list_helper<std::list<Args...>>: std::true_type {};

template <typename ... Args>
using is_std_list = is_std_list_helper<Args...>;

}


inline constexpr bool is_std_list_v = is_std_list<T>::value;



template <typename T>
inline constexpr bool is_std_list_or_vector_v = is_std_list_v<T> || is_std_vector_v<T>;

namespace { 

template <typename ... Args>
struct is_std_tuple_helper: std::false_type {};

template <typename ... Args>
struct is_std_tuple_helper<std::tuple<Args...>>: std::true_type {};

template <typename ... Args>
using is_std_tuple = is_std_tuple_helper<Args...>;

}


template <typename ... Args>
inline constexpr bool is_std_tuple_v = is_std_tuple<Args...>::value;

namespace {
template <typename T, std::enable_if_t<std::is_integral_v<T>, bool> = true>
std::ostream &print_ip_impl(T value, std::ostream &outStream)
{
    auto ptr = reinterpret_cast<const std::uint8_t *>(&value) + sizeof(T) - 1;
    for (size_t i = sizeof(typename std::enable_if_t<std::is_integral<T>::value, T>); i > 0 ; --i, --ptr) {
        outStream << std::to_string(*ptr);
        if (i > 1)
            outStream << ".";

    }

    return outStream;
}

template <typename T, std::enable_if_t<is_std_string_v<T>, bool> = true>
std::ostream &print_ip_impl(T value, std::ostream &outStream)
{
    return outStream << value;
}

template <typename T, std::enable_if_t<is_std_list_or_vector_v<T>, bool> = true>
std::ostream &print_ip_impl(T &&value, std::ostream &outStream)
{
    if (value.empty())
        return outStream;

    outStream << value.front();

    std::for_each(std::next(value.cbegin()), value.cend(), [&outStream](auto item)
                  {
                      outStream << "." << std::to_string(item);
                  });

    return outStream;
}

namespace {

template<typename TupleLike, std::size_t I = 0>
void printTypes(const TupleLike &t, std::ostream &outStream)
{
    if constexpr (I < std::tuple_size_v<TupleLike>) {
        using SelectedType = std::tuple_element_t<I, TupleLike>;
        using PredSelectedType = std::tuple_element_t<I - 1, TupleLike>;
        static_assert(std::is_same_v<PredSelectedType, SelectedType>, "все типы кортежа должны быть одинаковыми");
        outStream << "." << std::get<I>(t);
        printTypes<TupleLike, I + 1>(t, outStream);
    }
}

}

template <typename T, std::enable_if_t<is_std_tuple_v<T>, bool> = true>
std::ostream &print_ip_impl(T &&value, std::ostream &outStream)
{
    constexpr auto tupleSize = std::tuple_size_v<T>;
    if constexpr (tupleSize > 0)
        outStream << std::get<0>(value);
    else
        return outStream;

    if constexpr (tupleSize > 1)
        printTypes<T, 1>(value, outStream);

    return outStream;
}

}

