#include "JsonTestSuite.hpp"
#include "enjinsdk/models/Request.hpp"
#include <string>

using namespace enjin::sdk::models;

class RequestTest : public JsonTestSuite {
public:
    Request class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"id":1,"transactionId":"1","title":"1","contract":"1","type":"APPROVE","value":"1","retryState":"1","state":"PENDING","accepted":true,"blockchainData":{},"createdAt":"1","updatedAt":"1"})";
};

TEST_F(RequestTest, DeserializeEmptyStringFieldsDoNotHaveValues) {
    // Arrange
    const std::string json;

    // Act
    class_under_test.deserialize(json);

    // Assert
    EXPECT_FALSE(class_under_test.get_id().has_value());
    EXPECT_FALSE(class_under_test.get_transaction_id().has_value());
    EXPECT_FALSE(class_under_test.get_title().has_value());
    EXPECT_FALSE(class_under_test.get_contract().has_value());
    EXPECT_FALSE(class_under_test.get_type().has_value());
    EXPECT_FALSE(class_under_test.get_value().has_value());
    EXPECT_FALSE(class_under_test.get_retry_state().has_value());
    EXPECT_FALSE(class_under_test.get_state().has_value());
    EXPECT_FALSE(class_under_test.get_accepted().has_value());
    EXPECT_FALSE(class_under_test.get_blockchain_data().has_value());
    EXPECT_FALSE(class_under_test.get_created_at().has_value());
    EXPECT_FALSE(class_under_test.get_updated_at().has_value());
}

TEST_F(RequestTest, DeserializeEmptyJsonObjectFieldsDoNotHaveValues) {
    // Arrange
    const std::string json(EMPTY_JSON_OBJECT);

    // Act
    class_under_test.deserialize(json);

    // Assert
    EXPECT_FALSE(class_under_test.get_id().has_value());
    EXPECT_FALSE(class_under_test.get_transaction_id().has_value());
    EXPECT_FALSE(class_under_test.get_title().has_value());
    EXPECT_FALSE(class_under_test.get_contract().has_value());
    EXPECT_FALSE(class_under_test.get_type().has_value());
    EXPECT_FALSE(class_under_test.get_value().has_value());
    EXPECT_FALSE(class_under_test.get_retry_state().has_value());
    EXPECT_FALSE(class_under_test.get_state().has_value());
    EXPECT_FALSE(class_under_test.get_accepted().has_value());
    EXPECT_FALSE(class_under_test.get_blockchain_data().has_value());
    EXPECT_FALSE(class_under_test.get_created_at().has_value());
    EXPECT_FALSE(class_under_test.get_updated_at().has_value());
}

TEST_F(RequestTest, DeserializePopulatedJsonObjectFieldsHaveExpectedValues) {
    // Arrange
    const int expected_int = 1;
    const bool expected_bool = true;
    const std::string expected_string("1");
    const RequestState expected_request_state = RequestState::PENDING;
    const RequestType expected_request_type = RequestType::APPROVE;
    const BlockchainData expected_blockchain_data;

    const std::string json(POPULATED_JSON_OBJECT);

    // Act
    class_under_test.deserialize(json);

    // Assert
    EXPECT_EQ(expected_int, class_under_test.get_id().value());
    EXPECT_EQ(expected_string, class_under_test.get_transaction_id().value());
    EXPECT_EQ(expected_string, class_under_test.get_title().value());
    EXPECT_EQ(expected_string, class_under_test.get_contract().value());
    EXPECT_EQ(expected_request_type, class_under_test.get_type().value());
    EXPECT_EQ(expected_string, class_under_test.get_value().value());
    EXPECT_EQ(expected_string, class_under_test.get_retry_state().value());
    EXPECT_EQ(expected_request_state, class_under_test.get_state().value());
    EXPECT_EQ(expected_bool, class_under_test.get_accepted().value());
    EXPECT_EQ(expected_blockchain_data, class_under_test.get_blockchain_data().value());
    EXPECT_EQ(expected_string, class_under_test.get_created_at().value());
    EXPECT_EQ(expected_string, class_under_test.get_updated_at().value());
}

TEST_F(RequestTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    Request lhs;
    Request rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(RequestTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    Request lhs;
    Request rhs;
    lhs.deserialize(POPULATED_JSON_OBJECT);
    rhs.deserialize(POPULATED_JSON_OBJECT);

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(RequestTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    Request lhs;
    Request rhs;
    lhs.deserialize(POPULATED_JSON_OBJECT);

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(RequestTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    Request lhs;
    Request rhs;
    rhs.deserialize(POPULATED_JSON_OBJECT);

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
