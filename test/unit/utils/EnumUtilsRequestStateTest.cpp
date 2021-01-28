#include "EnumUtils.hpp"
#include "gtest/gtest.h"
#include <string>
#include <tuple>

using namespace enjin::sdk::models;
using namespace enjin::sdk::utils;

class RequestStateTest : public testing::TestWithParam<std::tuple<std::string, RequestState>> {
};

TEST_P(RequestStateTest, DeserializeRequestStateReturnsExpectedValue) {
    // Arrange
    RequestState expected = std::get<1>(GetParam());
    const std::string& str = std::get<0>(GetParam());

    // Act
    RequestState actual = deserialize_request_state(str);

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_P(RequestStateTest, SerializeRequestStateReturnsExpectedString) {
    // Arrange
    const std::string& expected = std::get<0>(GetParam());
    RequestState value = std::get<1>(GetParam());

    // Act
    std::string actual = serialize_request_state(value);

    // Assert
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(SerializableRequestState,
                         RequestStateTest,
                         testing::Values(std::make_tuple("PENDING", RequestState::PENDING),
                                         std::make_tuple("BROADCAST", RequestState::BROADCAST),
                                         std::make_tuple("TP_PROCESSING", RequestState::TP_PROCESSING),
                                         std::make_tuple("EXECUTED", RequestState::EXECUTED),
                                         std::make_tuple("CANCELED_USER", RequestState::CANCELED_USER),
                                         std::make_tuple("CANCELED_PLATFORM", RequestState::CANCELED_PLATFORM),
                                         std::make_tuple("DROPPED", RequestState::DROPPED),
                                         std::make_tuple("FAILED", RequestState::FAILED),
                                         std::make_tuple("", RequestState::UNKNOWN)));
