#pragma once

#include "data_type.hpp"

#include <string>

struct Column {
    std::string name;
    DataType type;
    bool isPrimaryKey;

    Column(const std::string& columnName, DataType columnType, bool primaryKey);
};
