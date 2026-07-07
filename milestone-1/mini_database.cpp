/*
 * Milestone 1: Mini Database
 * ==========================
 *
 * Goal
 * ----
 * Build the first working version of a small database program. Keep this
 * milestone simple: store records in memory, let the user work with them,
 * and print clear results. Do not add advanced features until the basic
 * version works correctly.
 *
 * What to implement
 * -----------------
 * 1. Define a record.
 *    - Use a struct or class.
 *    - Add the fields required by the assignment.
 *    - Give each record a value that can be used to identify it.
 *
 * 2. Store the records.
 *    - Choose a standard C++ container, such as std::vector.
 *    - Keep all records in that container while the program is running.
 *
 * 3. Add the required database operations.
 *    - Add a new record.
 *    - Display the stored records.
 *    - Find a record by its identifying value.
 *    - Add update or delete only if Milestone 1 requires them.
 *
 * 4. Create a simple user interface.
 *    - Show a numbered menu.
 *    - Read the user's choice and any required record information.
 *    - Run the matching operation.
 *    - Keep showing the menu until the user chooses to exit.
 *
 * 5. Handle simple errors.
 *    - Reject invalid menu choices.
 *    - Do not add a record if its identifying value must be unique and is
 *      already in use.
 *    - Print a friendly message when a requested record cannot be found.
 *    - Make sure bad input does not leave the program in a broken state.
 *
 * Suggested order
 * ---------------
 * 1. Write the record type.
 * 2. Write and test one operation at a time.
 * 3. Add the menu after the operations work.
 * 4. Test empty data, one record, several records, duplicate identifiers,
 *    missing records, and invalid input.
 *
 * Keep the code readable: use small functions, clear names, and short
 * comments that explain why something is done. This file is intentionally
 * not implemented yet.
 */

#include <cstdint>
#include <stdexcept>
#include <string>
#include <variant>

/*
 * Supported database data types.
 *
 * These are the types the user is allowed to write when creating a table:
 *
 *   INTEGER
 *   REAL
 *   TEXT
 *   BOOLEAN
 *
 * DataType is our program's "label" for the type.
 * Value is the real C++ storage type that can hold one actual value.
 */
enum class DataType {
    Integer,
    Real,
    Text,
    Boolean
};

using Value = std::variant<
    std::int64_t,
    double,
    std::string,
    bool
>;

/*
 * Convert a user's type word into our DataType enum.
 *
 * Example:
 *   "INTEGER" becomes DataType::Integer
 *   "TEXT"    becomes DataType::Text
 */
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

/*
 * Convert a user's value into the correct C++ type.
 *
 * The expectedType tells us what the value should become.
 *
 * Example:
 *   input: "25", expectedType: DataType::Integer
 *   result: a Value containing std::int64_t
 */
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
