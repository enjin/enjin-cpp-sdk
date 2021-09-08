/* Copyright 2021 Enjin Pte Ltd.
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

#include "DummyObject.hpp"
#include "JsonTestSuite.hpp"
#include "enjinsdk/GraphqlResponse.hpp"
#include "gtest/gtest.h"
#include <sstream>
#include <string>
#include <vector>

using namespace enjin::sdk::graphql;
using namespace enjin::test::suites;
using namespace enjin::test::utils;

class GraphqlResponseTest : public JsonTestSuite,
                            public testing::Test {
public:
    constexpr static char POPULATED_CURSOR_JSON[] =
            R"({"total":1,"perPage":1,"currentPage":1,"hasPages":true,"from":1,"to":1,"lastPage":1,"hasMorePages":true})";
    constexpr static char POPULATED_ERROR_JSON[] =
            R"({"message":"xyz","code":1,"details":"xyz","locations":[{"key":1}]})";

    static enjin::sdk::models::PaginationCursor create_default_pagination_cursor() {
        enjin::sdk::models::PaginationCursor cursor;
        cursor.deserialize(POPULATED_CURSOR_JSON);
        return cursor;
    }

    static GraphqlError create_default_graphql_error() {
        GraphqlError error;
        error.deserialize(POPULATED_ERROR_JSON);
        return error;
    }
};

TEST_F(GraphqlResponseTest, ConstructorParsesOneType) {
    // Arrange
    DummyObject expected = DummyObject::create_default_dummy_object();
    std::stringstream s;
    s << R"({"data":{"result":)"
      << expected.serialize()
      << R"(}})";

    // Act
    GraphqlResponse<enjin::test::utils::DummyObject> response(s.str());

    // Assert
    ASSERT_EQ(expected, response.get_result().value());
}

TEST_F(GraphqlResponseTest, ConstructorParsesOneBoolean) {
    // Arrange
    bool expected = true;
    std::string json(R"({"data":{"result":true}})");

    // Act
    GraphqlResponse<bool> response(json);

    // Assert
    ASSERT_EQ(expected, response.get_result().value());
}

TEST_F(GraphqlResponseTest, ConstructorParsesManyType) {
    // Arrange
    DummyObject expected = DummyObject::create_default_dummy_object();
    std::stringstream s;
    s << R"({"data":{"result":[)"
      << expected.serialize()
      << R"(,)"
      << expected.serialize()
      << R"(]}})";

    // Act
    GraphqlResponse<std::vector<DummyObject>> response(s.str());

    // Assert
    for (const auto& actual : response.get_result().value()) {
        EXPECT_EQ(expected, actual);
    }
}

TEST_F(GraphqlResponseTest, ConstructorParsesPaginatedType) {
    // Arrange
    DummyObject expected_obj = DummyObject::create_default_dummy_object();
    enjin::sdk::models::PaginationCursor expected_cursor = create_default_pagination_cursor();
    std::stringstream s;
    s << R"({"data":{"result":{"items":[)"
      << expected_obj.serialize()
      << R"(,)"
      << expected_obj.serialize()
      << R"(],"cursor":)"
      << POPULATED_CURSOR_JSON
      << R"(}}})";

    // Act
    GraphqlResponse<std::vector<DummyObject>> response(s.str());

    // Assert
    ASSERT_TRUE(response.get_result().has_value());
    ASSERT_TRUE(response.get_cursor().has_value());
    for (const auto& actual : response.get_result().value()) {
        EXPECT_EQ(expected_obj, actual);
    }
    EXPECT_EQ(expected_cursor, response.get_cursor().value());
}

TEST_F(GraphqlResponseTest, ConstructorParsesErrors) {
    // Arrange
    GraphqlError expected = create_default_graphql_error();
    std::stringstream s;
    s << R"({"errors":[)"
      << POPULATED_ERROR_JSON
      << R"(]})";

    // Act
    GraphqlResponse<DummyObject> response(s.str());

    // Assert
    ASSERT_TRUE(response.get_errors().has_value());
    for (const auto& actual : response.get_errors().value()) {
        EXPECT_EQ(expected, actual);
    }
}

TEST_F(GraphqlResponseTest, HasErrorsReturnsTrue) {
    // Arrange
    GraphqlError error = create_default_graphql_error();
    std::stringstream s;
    s << R"({"errors":[)"
      << POPULATED_ERROR_JSON
      << R"(]})";

    // Act
    GraphqlResponse<DummyObject> response(s.str());

    // Assert
    ASSERT_TRUE(response.has_errors());
}

TEST_F(GraphqlResponseTest, HasErrorsReturnsFalse) {
    // Arrange
    const std::string json(EMPTY_JSON_OBJECT);

    // Act
    GraphqlResponse<DummyObject> response(json);

    // Assert
    ASSERT_FALSE(response.has_errors());
}

TEST_F(GraphqlResponseTest, IsEmptyNonPaginatedTypeReturnsTrue) {
    // Arrange
    const std::string json(EMPTY_JSON_OBJECT);

    // Act
    GraphqlResponse<DummyObject> response(json);

    // Assert
    ASSERT_TRUE(response.is_empty());
}

TEST_F(GraphqlResponseTest, IsEmptyPaginatedTypeReturnsTrue) {
    // Arrange
    const std::string json(EMPTY_JSON_OBJECT);

    // Act
    GraphqlResponse<std::vector<DummyObject>> response(json);

    // Assert
    ASSERT_TRUE(response.is_empty());
}

TEST_F(GraphqlResponseTest, IsEmptyNonPaginatedTypeReturnsFalse) {
    // Arrange
    DummyObject expected = DummyObject::create_default_dummy_object();
    std::stringstream s;
    s << R"({"data":{"result":)"
      << expected.serialize()
      << R"(}})";

    // Act
    GraphqlResponse<DummyObject> response(s.str());

    // Assert
    ASSERT_FALSE(response.is_empty());
}

TEST_F(GraphqlResponseTest, IsEmptyPaginatedTypeReturnsFalse) {
    // Arrange
    DummyObject expected_obj = DummyObject::create_default_dummy_object();
    enjin::sdk::models::PaginationCursor expected_cursor = create_default_pagination_cursor();
    std::stringstream s;
    s << R"({"data":{"result":{"items":[)"
      << expected_obj.serialize()
      << R"(,)"
      << expected_obj.serialize()
      << R"(],"cursor":)"
      << POPULATED_CURSOR_JSON
      << R"(}}})";

    // Act
    GraphqlResponse<std::vector<DummyObject>> response(s.str());

    // Assert
    ASSERT_FALSE(response.is_empty());
}

TEST_F(GraphqlResponseTest, IsSuccessfulReturnsTrue) {
    // Arrange
    DummyObject expected = DummyObject::create_default_dummy_object();
    std::stringstream s;
    s << R"({"data":{"result":)"
      << expected.serialize()
      << R"(}})";

    // Act
    GraphqlResponse<DummyObject> response(s.str());

    // Assert
    ASSERT_TRUE(response.is_successful());
}

TEST_F(GraphqlResponseTest, IsSuccessfulReturnsFalse) {
    // Arrange
    const std::string json(EMPTY_JSON_OBJECT);

    // Act
    GraphqlResponse<DummyObject> response(json);

    // Assert
    ASSERT_FALSE(response.is_successful());
}

TEST_F(GraphqlResponseTest, IsPaginatedReturnsTrue) {
    // Arrange
    DummyObject expected_obj = DummyObject::create_default_dummy_object();
    enjin::sdk::models::PaginationCursor expected_cursor = create_default_pagination_cursor();
    std::stringstream s;
    s << R"({"data":{"result":{"items":[)"
      << expected_obj.serialize()
      << R"(,)"
      << expected_obj.serialize()
      << R"(],"cursor":)"
      << POPULATED_CURSOR_JSON
      << R"(}}})";

    // Act
    GraphqlResponse<std::vector<DummyObject>> response(s.str());

    // Assert
    ASSERT_TRUE(response.is_paginated());
}

TEST_F(GraphqlResponseTest, IsPaginatedReturnsFalse) {
    // Arrange
    const std::string json(EMPTY_JSON_OBJECT);

    // Act
    GraphqlResponse<DummyObject> response(json);

    // Assert
    ASSERT_FALSE(response.is_paginated());
}
