#include "../../mocks//MockEventListener.hpp"
#include "enjinsdk/EventListenerRegistration.hpp"
#include "gtest/gtest.h"
#include <algorithm>
#include <functional>
#include <vector>

using namespace enjin::sdk::events;

class RegistrationListenerConfigurationTest : public testing::Test {
public:
    inline static const std::vector<enjin::sdk::models::EventType> types = {
            enjin::sdk::models::EventType::UNKNOWN,
            enjin::sdk::models::EventType::PROJECT_CREATED,
            enjin::sdk::models::EventType::PROJECT_DELETED,
            enjin::sdk::models::EventType::PROJECT_LINKED,
            enjin::sdk::models::EventType::PROJECT_LOCKED,
            enjin::sdk::models::EventType::PROJECT_UNLINKED,
            enjin::sdk::models::EventType::PROJECT_UNLOCKED,
            enjin::sdk::models::EventType::PROJECT_UPDATED,
            enjin::sdk::models::EventType::BLOCKCHAIN_LOG_PROCESSED,
            enjin::sdk::models::EventType::MESSAGE_PROCESSED,
            enjin::sdk::models::EventType::PLAYER_CREATED,
            enjin::sdk::models::EventType::PLAYER_DELETED,
            enjin::sdk::models::EventType::PLAYER_LINKED,
            enjin::sdk::models::EventType::PLAYER_UNLINKED,
            enjin::sdk::models::EventType::PLAYER_UPDATED,
            enjin::sdk::models::EventType::ASSET_CREATED,
            enjin::sdk::models::EventType::ASSET_MELTED,
            enjin::sdk::models::EventType::ASSET_MINTED,
            enjin::sdk::models::EventType::ASSET_TRANSFERRED,
            enjin::sdk::models::EventType::ASSET_UPDATED,
            enjin::sdk::models::EventType::TRADE_COMPLETED,
            enjin::sdk::models::EventType::TRADE_CREATED,
            enjin::sdk::models::EventType::TRANSACTION_BROADCAST,
            enjin::sdk::models::EventType::TRANSACTION_CANCELED,
            enjin::sdk::models::EventType::TRANSACTION_DROPPED,
            enjin::sdk::models::EventType::TRANSACTION_EXECUTED,
            enjin::sdk::models::EventType::TRANSACTION_FAILED,
            enjin::sdk::models::EventType::TRANSACTION_PENDING,
            enjin::sdk::models::EventType::TRANSACTION_PROCESSING,
            enjin::sdk::models::EventType::TRANSACTION_UPDATED,
    };
};

TEST_F(RegistrationListenerConfigurationTest, RegistrationHasConfiguredListenerWhenCreated) {
    // Arrange
    std::shared_ptr<IEventListener> mock_listener(new MockEventListener);
    EventListenerRegistration::RegistrationListenerConfiguration configuration(mock_listener);

    // Act
    std::unique_ptr<EventListenerRegistration> registration = configuration.create();

    // Assert
    ASSERT_EQ(mock_listener.get(), &registration->get_listener());
}

TEST_F(RegistrationListenerConfigurationTest, NoGivenMatcherRegistrationIsCreatedWithAllowAllMatcher) {
    // Arrange
    std::shared_ptr<IEventListener> mock_listener(new MockEventListener);
    EventListenerRegistration::RegistrationListenerConfiguration configuration(mock_listener);

    // Act
    std::unique_ptr<EventListenerRegistration> registration = configuration.create();

    // Assert
    for (auto t : types) {
        EXPECT_TRUE(registration->get_matcher()(t));
    }
}

TEST_F(RegistrationListenerConfigurationTest, WithMatcherRegistrationIsCreatedWithCorrectMatcher) {
    // Arrange
    const std::function<bool(enjin::sdk::models::EventType)> matcher = [](enjin::sdk::models::EventType type) {
        return false;
    };
    std::shared_ptr<IEventListener> mock_listener(new MockEventListener);
    EventListenerRegistration::RegistrationListenerConfiguration configuration(mock_listener);

    // Act
    std::unique_ptr<EventListenerRegistration> registration = configuration.with_matcher(matcher)
                                                                           .create();

    // Assert
    for (auto t : types) {
        EXPECT_FALSE(registration->get_matcher()(t));
    }
}

TEST_F(RegistrationListenerConfigurationTest, WithAllowedEventsRegistrationIsCreatedWithCorrectMatcher) {
    // Arrange
    const std::vector<enjin::sdk::models::EventType> allowed_events = {
            enjin::sdk::models::EventType::PLAYER_LINKED,
            enjin::sdk::models::EventType::PLAYER_UNLINKED,
            enjin::sdk::models::EventType::PLAYER_UPDATED,
            enjin::sdk::models::EventType::ASSET_MELTED,
            enjin::sdk::models::EventType::ASSET_MINTED,
            enjin::sdk::models::EventType::ASSET_TRANSFERRED,
            enjin::sdk::models::EventType::ASSET_UPDATED,
    };
    std::shared_ptr<IEventListener> mock_listener(new MockEventListener);
    EventListenerRegistration::RegistrationListenerConfiguration configuration(mock_listener);

    // Act
    std::unique_ptr<EventListenerRegistration> registration = configuration.with_allowed_events(allowed_events)
                                                                           .create();

    // Assert
    for (auto t : types) {
        if (std::find(allowed_events.begin(), allowed_events.end(), t) != allowed_events.end()) {
            EXPECT_TRUE(registration->get_matcher()(t));
        } else {
            EXPECT_FALSE(registration->get_matcher()(t));
        }
    }
}

TEST_F(RegistrationListenerConfigurationTest, WithIgnoredEventsRegistrationIsCreatedWithCorrectMatcher) {
    // Arrange
    const std::vector<enjin::sdk::models::EventType> ignored_events = {
            enjin::sdk::models::EventType::PLAYER_LINKED,
            enjin::sdk::models::EventType::PLAYER_UNLINKED,
            enjin::sdk::models::EventType::PLAYER_UPDATED,
            enjin::sdk::models::EventType::ASSET_MELTED,
            enjin::sdk::models::EventType::ASSET_MINTED,
            enjin::sdk::models::EventType::ASSET_TRANSFERRED,
            enjin::sdk::models::EventType::ASSET_UPDATED,
    };
    std::shared_ptr<IEventListener> mock_listener(new MockEventListener);
    EventListenerRegistration::RegistrationListenerConfiguration configuration(mock_listener);

    // Act
    std::unique_ptr<EventListenerRegistration> registration = configuration.with_ignored_events(ignored_events)
                                                                           .create();

    // Assert
    for (auto t : types) {
        if (std::find(ignored_events.begin(), ignored_events.end(), t) == ignored_events.end()) {
            EXPECT_TRUE(registration->get_matcher()(t));
        } else {
            EXPECT_FALSE(registration->get_matcher()(t));
        }
    }
}
