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
        : public testing::TestWithParam<std::string> {
};

TEST_F(EventTypeDefTest, EqualityBothSidesAreSameDefReturnsTrue) {
    // Arrange
    EventTypeDef lhs = EventTypeDef::get_from_name("PROJECT_CREATED");
    EventTypeDef rhs = EventTypeDef::get_from_name("PROJECT_CREATED");

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(EventTypeDefTest, EqualityBothSidesAreNotSameDefReturnsFalse) {
    // Arrange
    EventTypeDef lhs = EventTypeDef::get_from_name("PROJECT_CREATED");
    EventTypeDef rhs = EventTypeDef::get_from_name("PROJECT_DELETED");

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

TEST_P(EventTypeDefFilterByChannelTypes, FilterByChannelTypesReturnsDefsWithChannelTypesSubstringToChannelParam) {
    // Arrange
    const std::string channel = GetParam();
    std::vector<EventTypeDef> defs = EventTypeDef::values();

    // Act
    std::vector<EventTypeDef> filtered_defs = EventTypeDef::filter_by_channel_type(channel);

    // Assert
    for (const EventTypeDef& def : defs) {
        // Set expectation for if Definition contains the channel
        bool expected = std::find_if(def.get_channels().begin(),
                                     def.get_channels().end(),
                                     [channel](const std::string& c) {
                                         return channel.find(c) != std::string::npos;
                                     }) != def.get_channels().end();
        // Set actual for if the filtered Defs contains the Def
        bool actual = std::find(filtered_defs.begin(), filtered_defs.end(), def) != filtered_defs.end();

        EXPECT_EQ(expected, actual);
    }
}

INSTANTIATE_TEST_SUITE_P(GetFromNameTestCases,
                         EventTypeDefGetFromNameTest,
                         testing::Values(std::make_tuple("", enjin::sdk::models::EventType::UNKNOWN),
                                         std::make_tuple("PROJECT_CREATED",
                                                         enjin::sdk::models::EventType::PROJECT_CREATED)));

INSTANTIATE_TEST_SUITE_P(GetFromKeyTestCases,
                         EventTypeDefGetFromKeyTest,
                         testing::Values(std::make_tuple("EnjinCloud\\Events\\ProjectCreated",
                                                         enjin::sdk::models::EventType::PROJECT_CREATED)));

INSTANTIATE_TEST_SUITE_P(DefInTypesTestCases,
                         EventTypeDefInTypesTest,
                         testing::Values(std::make_tuple("PROJECT_CREATED", std::vector<enjin::sdk::models::EventType>{
                                 enjin::sdk::models::EventType::PROJECT_CREATED
                         })));

INSTANTIATE_TEST_SUITE_P(DefNotInTypesTestCases,
                         EventTypeDefNotInTypesTest,
                         testing::Values(std::make_tuple("PROJECT_DELETED", std::vector<enjin::sdk::models::EventType>{
                                 enjin::sdk::models::EventType::PROJECT_CREATED
                         })));

INSTANTIATE_TEST_SUITE_P(FilterByChannelTypesTestCases,
                         EventTypeDefFilterByChannelTypes,
                         testing::Values("player",
                                         "enjincloud.kovan.wallet.0x0",
                                         "enjincloud.mainnet.project.1234",
                                         "xyz"));
