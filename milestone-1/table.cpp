#include "table.hpp"

Table::Table(const std::string& tableName, const std::vector<Column>& tableColumns, const std::vector<Row>& tableRows)
    : name(tableName), columns(tableColumns), rows(tableRows) {

}
