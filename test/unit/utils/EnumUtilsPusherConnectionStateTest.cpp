#include "EnumUtils.hpp"
#include "gtest/gtest.h"
#include <string>
#include <tuple>

using namespace enjin::sdk::utils;
using namespace enjin::pusher;

class PusherConnectionStateTest : public testing::TestWithParam<std::tuple<std::string, ConnectionState>> {
};

TEST_P(PusherConnectionStateTest, SerializeConnectionStateReturnsExpectedString) {
    // Arrange
    const std::string& expected = std::get<0>(GetParam());
    ConnectionState value = std::get<1>(GetParam());

    // Act
    std::string actual = serialize_pusher_connection_state(value);

    // Assert
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(SerializePusherConnectionState,
                         PusherConnectionStateTest,
                         testing::Values(std::make_tuple("ALL", ConnectionState::ALL),
                                         std::make_tuple("CONNECTED", ConnectionState::CONNECTED),
                                         std::make_tuple("CONNECTING", ConnectionState::CONNECTING),
                                         std::make_tuple("DISCONNECTED", ConnectionState::DISCONNECTED),
                                         std::make_tuple("DISCONNECTING", ConnectionState::DISCONNECTING),
                                         std::make_tuple("RECONNECTING", ConnectionState::RECONNECTING)));
