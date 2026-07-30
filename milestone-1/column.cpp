#include "column.hpp"

Column::Column(const std::string& columnName, DataType columnType, bool primaryKey)
    : name(columnName),
      type(columnType),
      isPrimaryKey(primaryKey) {
}
