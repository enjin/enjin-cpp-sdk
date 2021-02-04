#include "enjinsdk/EventListenerRegistration.hpp"
#include "gtest/gtest.h"
#include <vector>

using namespace enjin::sdk::events;

class EventListenerRegistrationTest : public testing::Test {
public:
    inline static const std::vector<enjin::sdk::models::EventType> types = {
            enjin::sdk::models::EventType::UNKNOWN,
            enjin::sdk::models::EventType::APP_CREATED,
            enjin::sdk::models::EventType::APP_DELETED,
            enjin::sdk::models::EventType::APP_LINKED,
            enjin::sdk::models::EventType::APP_LOCKED,
            enjin::sdk::models::EventType::APP_UNLINKED,
            enjin::sdk::models::EventType::APP_UNLOCKED,
            enjin::sdk::models::EventType::APP_UPDATED,
            enjin::sdk::models::EventType::BLOCKCHAIN_LOG_PROCESSED,
            enjin::sdk::models::EventType::MESSAGE_PROCESSED,
            enjin::sdk::models::EventType::PLAYER_CREATED,
            enjin::sdk::models::EventType::PLAYER_DELETED,
            enjin::sdk::models::EventType::PLAYER_LINKED,
            enjin::sdk::models::EventType::PLAYER_UNLINKED,
            enjin::sdk::models::EventType::PLAYER_UPDATED,
            enjin::sdk::models::EventType::TOKEN_CREATED,
            enjin::sdk::models::EventType::TOKEN_MELTED,
            enjin::sdk::models::EventType::TOKEN_MINTED,
            enjin::sdk::models::EventType::TOKEN_TRANSFERRED,
            enjin::sdk::models::EventType::TOKEN_UPDATED,
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

TEST_F(EventListenerRegistrationTest, AllowAllMatcherAllowsAllEventTypes) {
    // Assert
    for (auto t : types) {
        EXPECT_TRUE(EventListenerRegistration::ALLOW_ALL_MATCHER(t));
    }
}
