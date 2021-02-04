#include "EventTypeDef.hpp"
#include "gtest/gtest.h"
#include <string>
#include <tuple>
#include <vector>

using namespace enjin::sdk::events;

class EventTypeDefTest : public testing::Test {
};

class EventTypeDefGetFromNameTest
        : public testing::TestWithParam<std::tuple<std::string, enjin::sdk::models::EventType>> {
};

class EventTypeDefGetFromKeyTest
        : public testing::TestWithParam<std::tuple<std::string, enjin::sdk::models::EventType>> {
};

class EventTypeDefInTypesTest
        : public testing::TestWithParam<std::tuple<std::string, std::vector<enjin::sdk::models::EventType>>> {
};

class EventTypeDefNotInTypesTest
        : public testing::TestWithParam<std::tuple<std::string, std::vector<enjin::sdk::models::EventType>>> {
};

class EventTypeDefFilterByChannelTypes
        : public testing::TestWithParam<std::vector<std::string>> {
};

TEST_F(EventTypeDefTest, EqualityBothSidesAreSameDefReturnsTrue) {
    // Arrange
    EventTypeDef lhs = EventTypeDef::get_from_name("APP_CREATED");
    EventTypeDef rhs = EventTypeDef::get_from_name("APP_CREATED");

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(EventTypeDefTest, EqualityBothSidesAreNotSameDefReturnsFalse) {
    // Arrange
    EventTypeDef lhs = EventTypeDef::get_from_name("APP_CREATED");
    EventTypeDef rhs = EventTypeDef::get_from_name("APP_DELETED");

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_P(EventTypeDefGetFromNameTest, GetFromName) {
    // Arrange
    const enjin::sdk::models::EventType expected = std::get<1>(GetParam());
    const std::string& name = std::get<0>(GetParam());

    // Act
    EventTypeDef def = EventTypeDef::get_from_name(name);

    // Assert
    ASSERT_EQ(expected, def.get_type());
}

TEST_P(EventTypeDefGetFromKeyTest, GetFromKey) {
    // Arrange
    const enjin::sdk::models::EventType expected = std::get<1>(GetParam());
    const std::string& key = std::get<0>(GetParam());

    // Act
    EventTypeDef def = EventTypeDef::get_from_key(key);

    // Assert
    ASSERT_EQ(expected, def.get_type());
}

TEST_P(EventTypeDefInTypesTest, InDefIsInTypes) {
    // Arrange
    const std::string& name = std::get<0>(GetParam());
    const std::vector<enjin::sdk::models::EventType>& types = std::get<1>(GetParam());
    EventTypeDef def = EventTypeDef::get_from_name(name);

    // Act
    bool actual = def.in(types);

    // Assert
    ASSERT_TRUE(actual);
}

TEST_P(EventTypeDefNotInTypesTest, InDefIsNotInTypes) {
    // Arrange
    const std::string& name = std::get<0>(GetParam());
    const std::vector<enjin::sdk::models::EventType>& types = std::get<1>(GetParam());
    EventTypeDef def = EventTypeDef::get_from_name(name);

    // Act
    bool actual = def.in(types);

    // Assert
    ASSERT_FALSE(actual);
}

TEST_P(EventTypeDefFilterByChannelTypes, FilterByChannelTypes) {
    // Arrange
    const std::vector<std::string>& channels = GetParam();
    std::vector<EventTypeDef> defs = EventTypeDef::values();

    // Act
    std::vector<EventTypeDef> filtered_defs = EventTypeDef::filter_by_channel_types(channels);

    // Assert
    for (const EventTypeDef& def : defs) {
        // Set expectation for if Def contains the channel
        bool expected = std::find_if(def.get_channels().begin(), def.get_channels().end(),
                                     [channels](const std::string& c) {
                                         return std::find(channels.begin(), channels.end(), c) != channels.end();
                                     }) != def.get_channels().end();
        // Set actual for if the filtered Defs contains the Def
        bool actual = std::find(filtered_defs.begin(), filtered_defs.end(), def) != filtered_defs.end();

        EXPECT_EQ(expected, actual);
    }
}

INSTANTIATE_TEST_SUITE_P(GetFromNameTestCases,
                         EventTypeDefGetFromNameTest,
                         testing::Values(std::make_tuple("", enjin::sdk::models::EventType::UNKNOWN),
                                         std::make_tuple("APP_CREATED", enjin::sdk::models::EventType::APP_CREATED)));

INSTANTIATE_TEST_SUITE_P(GetFromKeyTestCases,
                         EventTypeDefGetFromKeyTest,
                         testing::Values(std::make_tuple("EnjinCloud\\Events\\AppCreated",
                                                         enjin::sdk::models::EventType::APP_CREATED)));

INSTANTIATE_TEST_SUITE_P(DefInTypesTestCases,
                         EventTypeDefInTypesTest,
                         testing::Values(std::make_tuple("APP_CREATED", std::vector<enjin::sdk::models::EventType>{
                                 enjin::sdk::models::EventType::APP_CREATED
                         })));

INSTANTIATE_TEST_SUITE_P(DefNotInTypesTestCases,
                         EventTypeDefNotInTypesTest,
                         testing::Values(std::make_tuple("APP_DELETED", std::vector<enjin::sdk::models::EventType>{
                                 enjin::sdk::models::EventType::APP_CREATED
                         })));

INSTANTIATE_TEST_SUITE_P(FilterByChannelTypesTestCases,
                         EventTypeDefFilterByChannelTypes,
                         testing::Values(std::vector<std::string>{"player"}));
