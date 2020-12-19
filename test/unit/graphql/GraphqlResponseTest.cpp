#include "enjinsdk/GraphqlResponse.hpp"
#include "gtest/gtest.h"
#include <optional>
#include <sstream>
#include <string>
#include <vector>

using namespace enjin::sdk::graphql;

class GraphqlResponseTest : public testing::Test {
public:
    class DummyClass : public enjin::sdk::serialization::ISerializable {
    public:
        std::optional<int> id;
        constexpr static char ID_KEY[] = "id";

        DummyClass() = default;

        explicit DummyClass(int id) {
            this->id = std::optional<int>(id);
        }

        ~DummyClass() override = default;

        void deserialize(const char* json) override {
            rapidjson::Document document;
            document.Parse(json);

            if (document.IsObject()) {
                if (document.HasMember(ID_KEY) && document[ID_KEY].IsInt()) {
                    id = std::optional<int>(document[ID_KEY].GetInt());
                }
            }
        }

        std::string serialize() override {
            rapidjson::Document document;
            document.SetObject();
            rapidjson::Document::AllocatorType& allocator = document.GetAllocator();

            if (id.has_value()) {
                rapidjson::Value v(id.value());
                document.AddMember(ID_KEY, v, allocator);
            }

            rapidjson::StringBuffer buffer;
            rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
            document.Accept(writer);
            const char* json = buffer.GetString();

            return std::string(json);
        }

        bool operator==(const DummyClass& rhs) const {
            return id == rhs.id;
        }

        bool operator!=(const DummyClass& rhs) const {
            return !(rhs == *this);
        }

    };

    constexpr static char EMPTY_JSON_OBJECT[] = "{}";

    static DummyClass create_default_dummy_object() {
        return DummyClass(1);
    }

    static enjin::sdk::models::PaginationCursor create_default_pagination_cursor() {
        enjin::sdk::models::PaginationCursor cursor;
        cursor.deserialize(
                R"({"total":1,"perPage":1,"currentPage":1,"hasPages":true,"from":1,"to":1,"lastPage":1,"hasMorePages":true})");
        return cursor;
    }

    static GraphqlError create_default_graphql_error() {
        GraphqlError error;
        error.deserialize(R"({"message":"xyz","code":1,"details":"xyz","locations":[{"key":1}]})");
        return error;
    }
};

TEST_F(GraphqlResponseTest, ConstructorParsesNonPaginatedType) {
    // Arrange
    DummyClass expected = create_default_dummy_object();
    std::stringstream s;
    s << R"({"data":{"result":)"
      << expected.serialize()
      << R"(}})";

    // Act
    GraphqlResponse<DummyClass> response(s.str().c_str());

    // Assert
    ASSERT_TRUE(response.get_result().has_value());
    ASSERT_EQ(expected, response.get_result().value());
}

TEST_F(GraphqlResponseTest, ConstructorParsesPaginatedType) {
    // Arrange
    DummyClass expected_obj = create_default_dummy_object();
    enjin::sdk::models::PaginationCursor expected_cursor = create_default_pagination_cursor();
    std::stringstream s;
    s << R"({"data":{"result":{"items":[)"
      << expected_obj.serialize()
      << R"(,)"
      << expected_obj.serialize()
      << R"(],"cursor":)"
      << expected_cursor.serialize()
      << R"(}}})";

    // Act
    GraphqlResponse<std::vector<DummyClass>> response(s.str().c_str());

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
    GraphqlResponse<DummyClass> response(s.str().c_str());

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
    GraphqlResponse<DummyClass> response(s.str().c_str());

    // Assert
    ASSERT_TRUE(response.has_errors());
}

TEST_F(GraphqlResponseTest, HasErrorsReturnsFalse) {
    // Arrange
    const char* json = EMPTY_JSON_OBJECT;

    // Act
    GraphqlResponse<DummyClass> response(json);

    // Assert
    ASSERT_FALSE(response.has_errors());
}

TEST_F(GraphqlResponseTest, IsEmptyNonPaginatedTypeReturnsTrue) {
    // Arrange
    const char* json = EMPTY_JSON_OBJECT;

    // Act
    GraphqlResponse<DummyClass> response(json);

    // Assert
    ASSERT_TRUE(response.is_empty());
}

TEST_F(GraphqlResponseTest, IsEmptyPaginatedTypeReturnsTrue) {
    // Arrange
    const char* json = EMPTY_JSON_OBJECT;

    // Act
    GraphqlResponse<std::vector<DummyClass>> response(json);

    // Assert
    ASSERT_TRUE(response.is_empty());
}

TEST_F(GraphqlResponseTest, IsEmptyNonPaginatedTypeReturnsFalse) {
    // Arrange
    DummyClass expected = create_default_dummy_object();
    std::stringstream s;
    s << R"({"data":{"result":)"
      << expected.serialize()
      << R"(}})";

    // Act
    GraphqlResponse<DummyClass> response(s.str().c_str());

    // Assert
    ASSERT_FALSE(response.is_empty());
}

TEST_F(GraphqlResponseTest, IsEmptyPaginatedTypeReturnsFalse) {
    // Arrange
    DummyClass expected_obj = create_default_dummy_object();
    enjin::sdk::models::PaginationCursor expected_cursor = create_default_pagination_cursor();
    std::stringstream s;
    s << R"({"data":{"result":{"items":[)"
      << expected_obj.serialize()
      << R"(,)"
      << expected_obj.serialize()
      << R"(],"cursor":)"
      << expected_cursor.serialize()
      << R"(}}})";

    // Act
    GraphqlResponse<std::vector<DummyClass>> response(s.str().c_str());

    // Assert
    ASSERT_FALSE(response.is_empty());
}

TEST_F(GraphqlResponseTest, IsSuccessfulReturnsTrue) {
    // Arrange
    DummyClass expected = create_default_dummy_object();
    std::stringstream s;
    s << R"({"data":{"result":)"
      << expected.serialize()
      << R"(}})";

    // Act
    GraphqlResponse<DummyClass> response(s.str().c_str());

    // Assert
    ASSERT_TRUE(response.is_successful());
}

TEST_F(GraphqlResponseTest, IsSuccessfulReturnsFalse) {
    // Arrange
    const char* json = EMPTY_JSON_OBJECT;

    // Act
    GraphqlResponse<DummyClass> response(json);

    // Assert
    ASSERT_FALSE(response.is_successful());
}

TEST_F(GraphqlResponseTest, IsPaginatedReturnsTrue) {
    // Arrange
    DummyClass expected_obj = create_default_dummy_object();
    enjin::sdk::models::PaginationCursor expected_cursor = create_default_pagination_cursor();
    std::stringstream s;
    s << R"({"data":{"result":{"items":[)"
      << expected_obj.serialize()
      << R"(,)"
      << expected_obj.serialize()
      << R"(],"cursor":)"
      << expected_cursor.serialize()
      << R"(}}})";

    // Act
    GraphqlResponse<std::vector<DummyClass>> response(s.str().c_str());

    // Assert
    ASSERT_TRUE(response.is_paginated());
}

TEST_F(GraphqlResponseTest, IsPaginatedReturnsFalse) {
    // Arrange
    const char* json = EMPTY_JSON_OBJECT;

    // Act
    GraphqlResponse<DummyClass> response(json);

    // Assert
    ASSERT_FALSE(response.is_paginated());
}
