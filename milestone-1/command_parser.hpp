#pragma once

#include <string>

enum class CommandType {
    CreateTable,
    Insert,
    Select,
    Help,
    Exit,
    Unknown
};

CommandType getCommandType(const std::string& commandText);
