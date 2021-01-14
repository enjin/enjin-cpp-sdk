#include "../../utils/DummyObject.hpp"
#include "enjinsdk/GraphqlResponse.hpp"
#include "gtest/gtest.h"
#include <optional>
#include <sstream>
#include <string>
#include <vector>

using namespace enjin::sdk::graphql;

class GraphqlResponseTest : public testing::Test {
public:
    constexpr static char EMPTY_JSON_OBJECT[] = "{}";
    constexpr static char POPULATED_CURSOR_JSON[] = R"({"total":1,"perPage":1,"currentPage":1,"hasPages":true,"from":1,"to":1,"lastPage":1,"hasMorePages":true})";
    constexpr static char POPULATED_ERROR_JSON[] = R"({"message":"xyz","code":1,"details":"xyz","locations":[{"key":1}]})";

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

TEST_F(GraphqlResponseTest, ConstructorParsesNonPaginatedType) {
    // Arrange
    enjin::test::utils::DummyObject expected = enjin::test::utils::DummyObject::create_default_dummy_object();
    std::stringstream s;
    s << R"({"data":{"result":)"
      << expected.serialize()
      << R"(}})";

    // Act
    GraphqlResponse<enjin::test::utils::DummyObject> response(s.str().c_str());

    // Assert
    ASSERT_TRUE(response.get_result().has_value());
    ASSERT_EQ(expected, response.get_result().value());
}

TEST_F(GraphqlResponseTest, ConstructorParsesPaginatedType) {
    // Arrange
    enjin::test::utils::DummyObject expected_obj = enjin::test::utils::DummyObject::create_default_dummy_object();
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
    GraphqlResponse<std::vector<enjin::test::utils::DummyObject>> response(s.str().c_str());

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
    s << R"({"error":{"errors":[)"
      << expected.serialize()
      << R"(]}})";

    // Act
    GraphqlResponse<enjin::test::utils::DummyObject> response(s.str().c_str());

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
    s << R"({"error":{"errors":[)"
      << error.serialize()
      << R"(]}})";

    // Act
    GraphqlResponse<enjin::test::utils::DummyObject> response(s.str().c_str());

    // Assert
    ASSERT_TRUE(response.has_errors());
}

TEST_F(GraphqlResponseTest, HasErrorsReturnsFalse) {
    // Arrange
    const char* json = EMPTY_JSON_OBJECT;

    // Act
    GraphqlResponse<enjin::test::utils::DummyObject> response(json);

    // Assert
    ASSERT_FALSE(response.has_errors());
}

TEST_F(GraphqlResponseTest, IsEmptyNonPaginatedTypeReturnsTrue) {
    // Arrange
    const char* json = EMPTY_JSON_OBJECT;

    // Act
    GraphqlResponse<enjin::test::utils::DummyObject> response(json);

    // Assert
    ASSERT_TRUE(response.is_empty());
}

TEST_F(GraphqlResponseTest, IsEmptyPaginatedTypeReturnsTrue) {
    // Arrange
    const char* json = EMPTY_JSON_OBJECT;

    // Act
    GraphqlResponse<std::vector<enjin::test::utils::DummyObject>> response(json);

    // Assert
    ASSERT_TRUE(response.is_empty());
}

TEST_F(GraphqlResponseTest, IsEmptyNonPaginatedTypeReturnsFalse) {
    // Arrange
    enjin::test::utils::DummyObject expected = enjin::test::utils::DummyObject::create_default_dummy_object();
    std::stringstream s;
    s << R"({"data":{"result":)"
      << expected.serialize()
      << R"(}})";

    // Act
    GraphqlResponse<enjin::test::utils::DummyObject> response(s.str().c_str());

    // Assert
    ASSERT_FALSE(response.is_empty());
}

TEST_F(GraphqlResponseTest, IsEmptyPaginatedTypeReturnsFalse) {
    // Arrange
    enjin::test::utils::DummyObject expected_obj = enjin::test::utils::DummyObject::create_default_dummy_object();
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
    GraphqlResponse<std::vector<enjin::test::utils::DummyObject>> response(s.str().c_str());

    // Assert
    ASSERT_FALSE(response.is_empty());
}

TEST_F(GraphqlResponseTest, IsSuccessfulReturnsTrue) {
    // Arrange
    enjin::test::utils::DummyObject expected = enjin::test::utils::DummyObject::create_default_dummy_object();
    std::stringstream s;
    s << R"({"data":{"result":)"
      << expected.serialize()
      << R"(}})";

    // Act
    GraphqlResponse<enjin::test::utils::DummyObject> response(s.str().c_str());

    // Assert
    ASSERT_TRUE(response.is_successful());
}

TEST_F(GraphqlResponseTest, IsSuccessfulReturnsFalse) {
    // Arrange
    const char* json = EMPTY_JSON_OBJECT;

    // Act
    GraphqlResponse<enjin::test::utils::DummyObject> response(json);

    // Assert
    ASSERT_FALSE(response.is_successful());
}

TEST_F(GraphqlResponseTest, IsPaginatedReturnsTrue) {
    // Arrange
    enjin::test::utils::DummyObject expected_obj = enjin::test::utils::DummyObject::create_default_dummy_object();
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
    GraphqlResponse<std::vector<enjin::test::utils::DummyObject>> response(s.str().c_str());

    // Assert
    ASSERT_TRUE(response.is_paginated());
}

TEST_F(GraphqlResponseTest, IsPaginatedReturnsFalse) {
    // Arrange
    const char* json = EMPTY_JSON_OBJECT;

    // Act
    GraphqlResponse<enjin::test::utils::DummyObject> response(json);

    // Assert
    ASSERT_FALSE(response.is_paginated());
}
