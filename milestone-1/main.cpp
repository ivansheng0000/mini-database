/*
 * Milestone 1: Mini Database
 * ==========================
 *
 * Goal
 * ----
 * Build the first working version of a small in-memory database.
 *
 * The project is now split into multiple files:
 *
 *   data_type.hpp / data_type.cpp
 *     - Defines the supported database data types.
 *     - Converts user type words like "INTEGER" into DataType values.
 *
 *   value.hpp / value.cpp
 *     - Defines Value, which can store one INTEGER, REAL, TEXT, or BOOLEAN.
 *     - Converts user input like "25" into the correct C++ value.
 *
 *   main.cpp
 *     - Will contain the program loop later.
 *     - For now, it only starts the program.
 *
 * Next things to build
 * --------------------
 * 1. Table structure
 * 2. Column structure
 * 3. Row structure
 * 4. CREATE TABLE command
 * 5. INSERT command
 * 6. SELECT command
 */

#include <iostream>

int main() {
    std::cout << "Mini Database\n";
    return 0;
}
