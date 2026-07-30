#pragma once

#include <string>

enum class DataType {
    Integer,
    Real,
    Text,
    Boolean
};

DataType parseDataType(const std::string& typeText);
