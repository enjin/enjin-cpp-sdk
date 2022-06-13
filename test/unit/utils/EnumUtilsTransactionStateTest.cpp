/* Copyright 2021 Enjin Pte. Ltd.
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

#include "enjinsdk/EnumUtils.hpp"
#include "gtest/gtest.h"
#include <string>
#include <tuple>

using namespace enjin::sdk::models;
using namespace enjin::sdk::utils;

class TransactionStateTest : public testing::TestWithParam<std::tuple<std::string, TransactionState>> {
};

TEST_P(TransactionStateTest, DeserializeTransactionStateReturnsExpectedValue) {
    // Arrange
    TransactionState expected = std::get<1>(GetParam());
    const std::string& str = std::get<0>(GetParam());

    // Act
    TransactionState actual = EnumUtils::deserialize_transaction_state(str);

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_P(TransactionStateTest, SerializeTransactionStateReturnsExpectedString) {
    // Arrange
    const std::string& expected = std::get<0>(GetParam());
    TransactionState value = std::get<1>(GetParam());

    // Act
    std::string actual = EnumUtils::serialize_transaction_state(value);

    // Assert
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(SerializableTransactionState,
                         TransactionStateTest,
                         testing::Values(std::make_tuple("PENDING", TransactionState::Pending),
                                         std::make_tuple("BROADCAST", TransactionState::Broadcast),
                                         std::make_tuple("TP_PROCESSING", TransactionState::TpProcessing),
                                         std::make_tuple("EXECUTED", TransactionState::Executed),
                                         std::make_tuple("CANCELED_USER", TransactionState::CanceledUser),
                                         std::make_tuple("CANCELED_PLATFORM", TransactionState::CanceledPlatform),
                                         std::make_tuple("DROPPED", TransactionState::Dropped),
                                         std::make_tuple("FAILED", TransactionState::Failed),
                                         std::make_tuple("", TransactionState::Unknown)));
