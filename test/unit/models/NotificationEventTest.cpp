#include "enjinsdk/models/NotificationEvent.hpp"
#include "gtest/gtest.h"

using namespace enjin::sdk::models;

class NotificationEventTest : public testing::Test {
public:
    static NotificationEvent create_default_notification_event() {
        return NotificationEvent(EventType::PROJECT_CREATED, "project", "xyz");
    }
};

TEST_F(NotificationEventTest, EqualityBothSidesAreSameDefReturnsTrue) {
    // Arrange
    NotificationEvent lhs = NotificationEvent(EventType::PROJECT_CREATED, "project", "xyz");
    NotificationEvent rhs = NotificationEvent(EventType::PROJECT_CREATED, "project", "xyz");

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(NotificationEventTest, EqualityBothSidesAreNotSameDefReturnsFalse) {
    // Arrange
    NotificationEvent lhs = NotificationEvent(EventType::PROJECT_CREATED, "project", "xyz");
    NotificationEvent rhs = NotificationEvent(EventType::PROJECT_DELETED, "player", "abc");

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
