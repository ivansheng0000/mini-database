#include <cstdint>
#include <stdexcept>
#include <string>
#include <variant>

#include <gtest/gtest.h>

/*
 * For now, the project is only one .cpp file and does not have a header yet.
 * Including the .cpp file lets us test the current helper functions directly.
 *
 * Later, when the project grows, we should move shared declarations into a
 * header file such as mini_database.h.
 */
#include "../milestone-1/mini_database.cpp"

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
