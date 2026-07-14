#pragma once

#include <string>

/*
 * Supported database data types.
 *
 * These are the type names users can write when creating a table:
 *
 *   INTEGER
 *   REAL
 *   TEXT
 *   BOOLEAN
 *
 * DataType is our program's internal label for each type.
 */
enum class DataType {
    Integer,
    Real,
    Text,
    Boolean
};

/*
 * Convert a user's type word into our DataType enum.
 *
 * Example:
 *   "INTEGER" becomes DataType::Integer
 *   "TEXT"    becomes DataType::Text
 */
DataType parseDataType(const std::string& typeText);
