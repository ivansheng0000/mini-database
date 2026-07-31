#include <cstdint>
#include <stdexcept>
#include <string>
#include <variant>

#include <gtest/gtest.h>

#include "column.hpp"
#include "database.hpp"
#include "data_type.hpp"
#include "row.hpp"
#include "table.hpp"
#include "value.hpp"

TEST(ParseDataTypeTest, AcceptsSupportedTypes) {
    EXPECT_EQ(parseDataType("INTEGER"), DataType::Integer);
    EXPECT_EQ(parseDataType("REAL"), DataType::Real);
    EXPECT_EQ(parseDataType("TEXT"), DataType::Text);
    EXPECT_EQ(parseDataType("BOOLEAN"), DataType::Boolean);
}

TEST(ParseDataTypeTest, RejectsUnknownType) {
    EXPECT_THROW(parseDataType("DATE"), std::runtime_error);
}

TEST(ParseValueTest, ParsesIntegerValue) {
    Value value = parseValue("25", DataType::Integer);

    ASSERT_TRUE(std::holds_alternative<std::int64_t>(value));
    EXPECT_EQ(std::get<std::int64_t>(value), 25);
}

TEST(ParseValueTest, ParsesRealValue) {
    Value value = parseValue("98.5", DataType::Real);

    ASSERT_TRUE(std::holds_alternative<double>(value));
    EXPECT_DOUBLE_EQ(std::get<double>(value), 98.5);
}

TEST(ParseValueTest, ParsesTextValue) {
    Value value = parseValue("Alice", DataType::Text);

    ASSERT_TRUE(std::holds_alternative<std::string>(value));
    EXPECT_EQ(std::get<std::string>(value), "Alice");
}

TEST(ParseValueTest, ParsesBooleanTrueValue) {
    Value value = parseValue("true", DataType::Boolean);

    ASSERT_TRUE(std::holds_alternative<bool>(value));
    EXPECT_TRUE(std::get<bool>(value));
}

TEST(ParseValueTest, ParsesBooleanFalseValue) {
    Value value = parseValue("false", DataType::Boolean);

    ASSERT_TRUE(std::holds_alternative<bool>(value));
    EXPECT_FALSE(std::get<bool>(value));
}

TEST(ParseValueTest, RejectsInvalidBooleanValue) {
    EXPECT_THROW(parseValue("yes", DataType::Boolean), std::runtime_error);
}

TEST(ParseValueTest, RejectsInvalidIntegerValue) {
    EXPECT_THROW(parseValue("abc", DataType::Integer), std::invalid_argument);
}

TEST(ValueMatchesTypeTest, IntegerValueMatchesIntegerType) {
    Value value = static_cast<std::int64_t>(25);

    EXPECT_TRUE(valueMatchesType(value, DataType::Integer));
}

TEST(ValueMatchesTypeTest, TextValueMatchesTextType) {
    Value value = std::string("Alice");

    EXPECT_TRUE(valueMatchesType(value, DataType::Text));
}

TEST(ValueMatchesTypeTest, TextValueDoesNotMatchIntegerType) {
    Value value = std::string("25");

    EXPECT_FALSE(valueMatchesType(value, DataType::Integer));
}

TEST(ColumnTest, StoresColumnInformation) {
    Column column("id", DataType::Integer, true);

    EXPECT_EQ(column.name, "id");
    EXPECT_EQ(column.type, DataType::Integer);
    EXPECT_TRUE(column.isPrimaryKey);
}

TEST(ColumnTest, StoresNonPrimaryKeyColumn) {
    Column column("name", DataType::Text, false);

    EXPECT_EQ(column.name, "name");
    EXPECT_EQ(column.type, DataType::Text);
    EXPECT_FALSE(column.isPrimaryKey);
}

TEST(RowTest, StoresValuesInOrder) {
    Row row({
        static_cast<std::int64_t>(1),
        std::string("Alice"),
        static_cast<std::int64_t>(20)
    });

    ASSERT_EQ(row.values.size(), 3);

    ASSERT_TRUE(std::holds_alternative<std::int64_t>(row.values[0]));
    EXPECT_EQ(std::get<std::int64_t>(row.values[0]), 1);

    ASSERT_TRUE(std::holds_alternative<std::string>(row.values[1]));
    EXPECT_EQ(std::get<std::string>(row.values[1]), "Alice");

    ASSERT_TRUE(std::holds_alternative<std::int64_t>(row.values[2]));
    EXPECT_EQ(std::get<std::int64_t>(row.values[2]), 20);
}

TEST(TableTest, StoresNameColumnsAndRows) {
    std::vector<Column> columns = {
        Column("id", DataType::Integer, true),
        Column("name", DataType::Text, false),
        Column("age", DataType::Integer, false)
    };

    std::vector<Row> rows = {
        Row({
            static_cast<std::int64_t>(1),
            std::string("Alice"),
            static_cast<std::int64_t>(20)
        }),
        Row({
            static_cast<std::int64_t>(2),
            std::string("Bob"),
            static_cast<std::int64_t>(21)
        })
    };

    Table table("students", columns, rows);

    EXPECT_EQ(table.name, "students");
    ASSERT_EQ(table.columns.size(), 3);
    ASSERT_EQ(table.rows.size(), 2);

    EXPECT_EQ(table.columns[0].name, "id");
    EXPECT_EQ(table.columns[0].type, DataType::Integer);
    EXPECT_TRUE(table.columns[0].isPrimaryKey);

    ASSERT_TRUE(std::holds_alternative<std::string>(table.rows[1].values[1]));
    EXPECT_EQ(std::get<std::string>(table.rows[1].values[1]), "Bob");
}

TEST(TableTest, HasColumnReturnsTrueForExistingColumn) {
    Table table(
        "students",
        {
            Column("id", DataType::Integer, true),
            Column("name", DataType::Text, false),
            Column("age", DataType::Integer, false)
        },
        {}
    );

    EXPECT_TRUE(table.hasColumn("name"));
}

TEST(TableTest, HasColumnReturnsFalseForMissingColumn) {
    Table table(
        "students",
        {
            Column("id", DataType::Integer, true),
            Column("name", DataType::Text, false)
        },
        {}
    );

    EXPECT_FALSE(table.hasColumn("email"));
}

TEST(TableTest, AddRowAcceptsValidRow) {
    Table table(
        "students",
        {
            Column("id", DataType::Integer, true),
            Column("name", DataType::Text, false),
            Column("age", DataType::Integer, false)
        },
        {}
    );

    table.addRow(Row({
        static_cast<std::int64_t>(1),
        std::string("Alice"),
        static_cast<std::int64_t>(20)
    }));

    ASSERT_EQ(table.rows.size(), 1);
    EXPECT_EQ(std::get<std::string>(table.rows[0].values[1]), "Alice");
}

TEST(TableTest, AddRowRejectsWrongNumberOfValues) {
    Table table(
        "students",
        {
            Column("id", DataType::Integer, true),
            Column("name", DataType::Text, false),
            Column("age", DataType::Integer, false)
        },
        {}
    );

    EXPECT_THROW(
        table.addRow(Row({
            static_cast<std::int64_t>(1),
            std::string("Alice")
        })),
        std::runtime_error
    );

    EXPECT_TRUE(table.rows.empty());
}

TEST(TableTest, AddRowRejectsWrongValueType) {
    Table table(
        "students",
        {
            Column("id", DataType::Integer, true),
            Column("name", DataType::Text, false),
            Column("age", DataType::Integer, false)
        },
        {}
    );

    EXPECT_THROW(
        table.addRow(Row({
            static_cast<std::int64_t>(1),
            std::string("Alice"),
            std::string("twenty")
        })),
        std::runtime_error
    );

    EXPECT_TRUE(table.rows.empty());
}

TEST(TableTest, AddRowRejectsDuplicatePrimaryKey) {
    Table table(
        "students",
        {
            Column("id", DataType::Integer, true),
            Column("name", DataType::Text, false)
        },
        {}
    );

    table.addRow(Row({
        static_cast<std::int64_t>(1),
        std::string("Alice")
    }));

    EXPECT_THROW(
        table.addRow(Row({
            static_cast<std::int64_t>(1),
            std::string("Bob")
        })),
        std::runtime_error
    );

    EXPECT_EQ(table.rows.size(), 1);
}

TEST(DatabaseTest, StartsWithNoTables) {
    Database database;

    EXPECT_TRUE(database.tables.empty());
    EXPECT_FALSE(database.hasTable("students"));
}

TEST(DatabaseTest, CreateTableStoresTableByName) {
    Database database;

    std::vector<Column> columns = {
        Column("id", DataType::Integer, true),
        Column("name", DataType::Text, false)
    };

    std::vector<Row> rows = {
        Row({
            static_cast<std::int64_t>(1),
            std::string("Alice")
        })
    };

    Table studentsTable("students", columns, rows);

    database.createTable(studentsTable);

    ASSERT_EQ(database.tables.size(), 1);
    EXPECT_TRUE(database.hasTable("students"));
    EXPECT_FALSE(database.hasTable("courses"));
    EXPECT_EQ(database.tables.at("students").name, "students");
    EXPECT_EQ(database.tables.at("students").columns.size(), 2);
    EXPECT_EQ(database.tables.at("students").rows.size(), 1);
}

TEST(DatabaseTest, CreateTableRejectsDuplicateTableName) {
    Database database;

    std::vector<Column> columns = {
        Column("id", DataType::Integer, true)
    };

    std::vector<Row> rows;

    Table firstTable("students", columns, rows);
    Table duplicateTable("students", columns, rows);

    database.createTable(firstTable);

    EXPECT_THROW(database.createTable(duplicateTable), std::runtime_error);
    EXPECT_EQ(database.tables.size(), 1);
}
