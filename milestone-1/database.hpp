#pragma once

#include "table.hpp"

#include <string>
#include <unordered_map>

struct Database {
    std::unordered_map<std::string, Table> tables;

    Database();
    
    bool hasTable(const std::string& tableName) const;
    void createTable(const Table& table);
};
