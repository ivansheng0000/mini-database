#include "value.h"

#include <cstdint>
#include <stdexcept>
#include <string>

Value parseValue(const std::string& input, DataType expectedType) {
    if (expectedType == DataType::Integer) {
        return static_cast<std::int64_t>(std::stoll(input));
    }
    else if (expectedType == DataType::Real) {
        return std::stod(input);
    }
    else if (expectedType == DataType::Text) {
        return input;
    }
    else if (expectedType == DataType::Boolean) {
        if (input == "true") {
            return true;
        }
        else if (input == "false") {
            return false;
        }

        throw std::runtime_error("Boolean must be true or false.");
    }

    throw std::runtime_error("Invalid data type.");
}
