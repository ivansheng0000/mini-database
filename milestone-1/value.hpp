#pragma once

#include "data_type.hpp"

#include <cstdint>
#include <string>
#include <variant>

using Value = std::variant<
    std::int64_t,
    double,
    std::string,
    bool
>;

Value parseValue(const std::string& input, DataType expectedType);
