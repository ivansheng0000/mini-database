#pragma once

#include "column.hpp"
#include "row.hpp"

#include <string>
#include <vector>

struct Table {
    std::string name;
    std::vector<Column> columns;
    std::vector<Row> rows;

    Table(const std::string& tableName, const std::vector<Column>& tableColumns, const std::vector<Row>& tableRows);
};
