#include "table.hpp"
#include "value.hpp"
#include <stdexcept>
Table::Table(const std::string& tableName, const std::vector<Column>& tableColumns, const std::vector<Row>& tableRows)
    : name(tableName), columns(tableColumns), rows(tableRows) {

}

bool Table::hasColumn(const std::string& columnName) const {
    for (const Column& column: columns) {
        if (column.name == columnName) {
            return true;
        }
    }
    return false;
}

void Table::addRow(const Row& row) {
    if (row.values.size() != columns.size()) {
        throw std::runtime_error("Row value count does not match column count.");
    }

    for (std::size_t i = 0; i < columns.size(); ++i) {
        if (!valueMatchesType(row.values[i], columns[i].type)){
            throw std::runtime_error("Row value type does not match column type.");
        }
    }

    for (std::size_t j = 0; j < columns.size(); ++j) {
        if (!columns[j].isPrimaryKey){
            continue;
        }
        for (const Row& existingRow: rows) {
            if (existingRow.values[j] == row.values[j]) {
                throw std::runtime_error("Duplicate primary key values.");
            }
        }
    }
    
    rows.push_back(row);
}
