#include "JsonTestSuite.hpp"
#include "PusherEvent.hpp"
#include <string>

using namespace enjin::pusher;

class PusherEventTest : public JsonTestSuite {
public:
    PusherEvent class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"user_id":"1","channel":"1","event":"1","data":"1"})";

    static PusherEvent create_default_pusher_event() {
        PusherEvent event;
        event.deserialize(POPULATED_JSON_OBJECT);
        return event;
    }
};

TEST_F(PusherEventTest, DeserializeEmptyStringFieldsDoNotHaveValues) {
    // Arrange
    const std::string json;

    // Act
    class_under_test.deserialize(json);

    // Assert
    EXPECT_FALSE(class_under_test.get_user_id().has_value());
    EXPECT_FALSE(class_under_test.get_channel_name().has_value());
    EXPECT_FALSE(class_under_test.get_event_name().has_value());
    EXPECT_FALSE(class_under_test.get_data().has_value());
}

TEST_F(PusherEventTest, DeserializeEmptyJsonObjectFieldsDoNotHaveValues) {
    // Arrange
    const std::string json(EMPTY_JSON_OBJECT);

    // Act
    class_under_test.deserialize(json);

    // Assert
    EXPECT_FALSE(class_under_test.get_user_id().has_value());
    EXPECT_FALSE(class_under_test.get_channel_name().has_value());
    EXPECT_FALSE(class_under_test.get_event_name().has_value());
    EXPECT_FALSE(class_under_test.get_data().has_value());
}

TEST_F(PusherEventTest, DeserializePopulatedJsonObjectFieldsHaveExpectedValues) {
    // Arrange
    const std::string expected_string("1");
    const std::string json(POPULATED_JSON_OBJECT);

    // Act
    class_under_test.deserialize(json);

    // Assert
    EXPECT_EQ(expected_string, class_under_test.get_user_id().value());
    EXPECT_EQ(expected_string, class_under_test.get_channel_name().value());
    EXPECT_EQ(expected_string, class_under_test.get_event_name().value());
    EXPECT_EQ(expected_string, class_under_test.get_data().value());
}

TEST_F(PusherEventTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    PusherEvent lhs;
    PusherEvent rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(PusherEventTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    PusherEvent lhs = create_default_pusher_event();
    PusherEvent rhs = create_default_pusher_event();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(PusherEventTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    PusherEvent lhs = create_default_pusher_event();
    PusherEvent rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(PusherEventTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    PusherEvent lhs;
    PusherEvent rhs = create_default_pusher_event();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
