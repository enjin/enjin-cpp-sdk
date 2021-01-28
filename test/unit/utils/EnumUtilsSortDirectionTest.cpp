#include "EnumUtils.hpp"
#include "gtest/gtest.h"
#include <string>
#include <tuple>

using namespace enjin::sdk::models;
using namespace enjin::sdk::utils;

class SortDirectionTest : public testing::TestWithParam<std::tuple<std::string, SortDirection>> {
};

TEST_P(SortDirectionTest, SerializeSortDirectionReturnsExpectedString) {
    // Arrange
    const std::string& expected = std::get<0>(GetParam());
    SortDirection value = std::get<1>(GetParam());

    // Act
    std::string actual = serialize_sort_direction(value);

    // Assert
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(SerializeSortDirection,
                         SortDirectionTest,
                         testing::Values(std::make_tuple("asc", SortDirection::ASCENDING),
                                         std::make_tuple("desc", SortDirection::DESCENDING)));
