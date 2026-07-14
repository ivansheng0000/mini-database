#include "data_type.h"

#include <stdexcept>

DataType parseDataType(const std::string& typeText) {
    if (typeText == "INTEGER") {
        return DataType::Integer;
    }
    else if (typeText == "REAL") {
        return DataType::Real;
    }
    else if (typeText == "TEXT") {
        return DataType::Text;
    }
    else if (typeText == "BOOLEAN") {
        return DataType::Boolean;
    }

    throw std::runtime_error("Unknown data type: " + typeText);
}
