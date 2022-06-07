/* Copyright 2021 Enjin Pte. Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "gtest/gtest.h"
#include "JsonTestSuite.hpp"
#include "enjinsdk/internal/GraphqlResponseUtils.hpp"
#include <optional>
#include <sstream>
#include <string>

using namespace enjin::sdk::graphql;
using namespace enjin::sdk::models;
using namespace enjin::test::suites;

class GraphqlResponseUtilsTest : public JsonTestSuite,
                                 public testing::Test {
public:
    constexpr static char DEFAULT_CURSOR_JSON[] =
            R"({"total":1,"perPage":1,"currentPage":1,"hasPages":true,"from":1,"to":1,"lastPage":1,"hasMorePages":true})";

    static PaginationCursor create_default_cursor() {
        PaginationCursor cursor;
        cursor.deserialize(DEFAULT_CURSOR_JSON);
        return cursor;
    }
};

TEST_F(GraphqlResponseUtilsTest, GetBoolResultEmptyJsonReturnsEmptyOptional) {
    // Arrange
    const std::string json;

    // Act
    auto actual = get_bool_result(json);

    // Assert
    ASSERT_FALSE(actual.has_value());
}

TEST_F(GraphqlResponseUtilsTest, GetBoolResultEmptyJsonObjectReturnsEmptyOptional) {
    // Arrange
    const std::string json(EmptyJsonObject);

    // Act
    auto actual = get_bool_result(json);

    // Assert
    ASSERT_FALSE(actual.has_value());
}

TEST_F(GraphqlResponseUtilsTest, GetBoolResultResultIsNotBooleanReturnsEmptyOptional) {
    // Arrange
    const std::string json(R"({"result":"value"})");

    // Act
    auto actual = get_bool_result(json);

    // Assert
    ASSERT_FALSE(actual.has_value());
}

TEST_F(GraphqlResponseUtilsTest, GetBoolResultResultIsTrueReturnsOptionalWithTrueValue) {
    // Arrange
    const std::string json(R"({"result":true})");

    // Act
    auto actual = get_bool_result(json);

    // Assert
    ASSERT_TRUE(actual.value());
}

TEST_F(GraphqlResponseUtilsTest, GetBoolResultResultIsFalseReturnsOptionalWithFalseValue) {
    // Arrange
    const std::string json(R"({"result":false})");

    // Act
    auto actual = get_bool_result(json);

    // Assert
    ASSERT_FALSE(actual.value());
}

TEST_F(GraphqlResponseUtilsTest, GetPaginationDataEmptyJsonReturnsEmptyOptional) {
    // Arrange
    const std::string json;

    // Act
    auto actual = get_pagination_data(json);

    // Assert
    ASSERT_FALSE(actual.has_value());
}

TEST_F(GraphqlResponseUtilsTest, GetPaginationDataEmptyJsonObjectReturnsEmptyOptional) {
    // Arrange
    const std::string json(EmptyJsonObject);

    // Act
    auto actual = get_pagination_data(json);

    // Assert
    ASSERT_FALSE(actual.has_value());
}

TEST_F(GraphqlResponseUtilsTest, GetPaginationDataResultObjectHasNoPaginationDataReturnsEmptyItemsArrayAndCursor) {
    // Arrange
    const PaginationCursor expected_cursor;
    const std::string json(R"({"result":{}})");

    // Act
    auto actual = get_pagination_data(json);

    // Assert
    EXPECT_EQ(expected_cursor, actual->first);
    EXPECT_TRUE(actual->second.empty());
}

TEST_F(GraphqlResponseUtilsTest, GetPaginationDataJsonHasItemsAndCursorReturnsExpectedItemsArrayAndCursor) {
    // Arrange
    const PaginationCursor expected_cursor = create_default_cursor();
    const std::string expected_item(R"({"key":"value"})");
    std::stringstream ss;
    ss << R"({"result":{"items":[)" << expected_item << R"(],"cursor":)" << DEFAULT_CURSOR_JSON << R"(}})";

    // Act
    auto actual = get_pagination_data(ss.str());

    // Assert
    EXPECT_EQ(expected_cursor, actual.value().first);
    EXPECT_FALSE(actual.value().second.empty());
    for (const auto& actual_item : actual.value().second) {
        EXPECT_EQ(expected_item, actual_item);
    }
}

TEST_F(GraphqlResponseUtilsTest, GetSerializedObjectArrayEmptyJsonReturnsEmptyOptional) {
    // Arrange
    const std::string json;

    // Act
    auto actual = get_serialized_object_array(json);

    // Assert
    ASSERT_FALSE(actual.has_value());
}

TEST_F(GraphqlResponseUtilsTest, GetSerializedObjectArrayNoResultReturnsEmptyOptional) {
    // Arrange
    const std::string json(EmptyJsonObject);

    // Act
    auto actual = get_serialized_object_array(json);

    // Assert
    ASSERT_FALSE(actual.has_value());
}

TEST_F(GraphqlResponseUtilsTest, GetSerializedObjectArrayResultArrayIsEmptyReturnsEmptyArray) {
    // Arrange
    const std::string json(R"({"result":[]})");

    // Act
    auto actual = get_serialized_object_array(json);

    // Assert
    ASSERT_TRUE(actual.value().empty());
}

TEST_F(GraphqlResponseUtilsTest, GetSerializedObjectArrayResultArrayHasObjectsReturnsArrayString) {
    // Arrange
    const std::string expected_obj(R"({"key":"value"})");
    std::stringstream ss;
    ss << R"({"result":[)" << expected_obj << "," << expected_obj << R"(]})";

    // Act
    auto actual = get_serialized_object_array(ss.str());

    // Assert
    ASSERT_FALSE(actual.value().empty());
    for (const auto& actual_obj : actual.value()) {
        EXPECT_EQ(expected_obj, actual_obj);
    }
}

TEST_F(GraphqlResponseUtilsTest, GetSerializedResultObjectEmptyJsonReturnsEmptyOptional) {
    // Arrange
    const std::string json;

    // Act
    auto actual = get_serialized_result_object(json);

    // Assert
    ASSERT_FALSE(actual.has_value());
}

TEST_F(GraphqlResponseUtilsTest, GetSerializedResultObjectNoResultKeyInJsonReturnsEmptyOptional) {
    // Arrange
    const std::string json(EmptyJsonObject);

    // Act
    auto actual = get_serialized_result_object(json);

    // Assert
    ASSERT_FALSE(actual.has_value());
}

TEST_F(GraphqlResponseUtilsTest, GetSerializedResultObjectResultIsNotObjectReturnsEmptyOptional) {
    // Arrange
    const std::string json(R"({"result":1})");

    // Act
    auto actual = get_serialized_result_object(json);

    // Assert
    ASSERT_FALSE(actual.has_value());
}

TEST_F(GraphqlResponseUtilsTest, GetSerializedResultObjectValueIsObjectReturnsValueString) {
    // Arrange
    const std::string expected(R"({"key":"value"})");
    std::stringstream ss;
    ss << R"({"result":)" << expected << R"(})";

    // Act
    auto actual = get_serialized_result_object(ss.str());

    // Assert
    ASSERT_EQ(expected, actual.value());
}

TEST_F(GraphqlResponseUtilsTest, IsJsonPaginatedJsonIsEmptyReturnsFalse) {
    // Arrange
    const std::string json;

    // Act
    bool actual = is_json_paginated(json);

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(GraphqlResponseUtilsTest, IsJsonPaginatedJsonDoesNotHavePaginationDataReturnsFalse) {
    // Arrange
    const std::string json(R"({"result":{}})");

    // Act
    bool actual = is_json_paginated(json);

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(GraphqlResponseUtilsTest, IsJsonPaginatedJsonHasPaginationDataReturnsTrue) {
    // Arrange
    const std::string json(R"({"result":{"cursor":{}}})");

    // Act
    bool actual = is_json_paginated(json);

    // Assert
    ASSERT_TRUE(actual);
}
