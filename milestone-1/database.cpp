#include "database.hpp"
#include <stdexcept>

Database::Database()
    : tables() {
}

bool Database::hasTable(const std::string& tableName) const {
    return tables.find(tableName) != tables.end();
}

void Database::createTable(const Table& table){
    if (hasTable(table.name)){
        throw std::runtime_error("Table already exists: " + table.name);
    }
    
    tables.emplace(table.name, table);
}