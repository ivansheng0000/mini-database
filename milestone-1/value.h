#pragma once

#include "data_type.h"

#include <cstdint>
#include <string>
#include <variant>

/*
 * A Value is one cell of data in the database.
 *
 * It can hold exactly one of the supported C++ types:
 *
 *   std::int64_t  for INTEGER
 *   double        for REAL
 *   std::string   for TEXT
 *   bool          for BOOLEAN
 */
using Value = std::variant<
    std::int64_t,
    double,
    std::string,
    bool
>;

/*
 * Convert a user's value into the correct C++ type.
 *
 * The expectedType tells us what the value should become.
 *
 * Example:
 *   input: "25", expectedType: DataType::Integer
 *   result: a Value containing std::int64_t
 */
Value parseValue(const std::string& input, DataType expectedType);
