#pragma once

#include "custom_traits.h"


template <typename T>
std::ostream &print_ip(T &&value, std::ostream &outStream = std::cout)
{
    return print_ip_impl(std::forward<T>(value), outStream);
}
 
