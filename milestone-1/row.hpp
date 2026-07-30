#pragma once

#include "value.hpp"

#include <vector>

struct Row {
    std::vector<Value> values;

    Row(std::vector<Value> rowValues);
};
