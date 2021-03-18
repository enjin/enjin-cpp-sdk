#include "gtest/gtest.h"
#include "PlayerChannel.hpp"
#include "ChannelsTestSuite.hpp"
#include <string>

using namespace enjin::sdk::events;
using namespace enjin::test::suites;

class PlayerChannelTest : public ChannelsTestSuite,
                          public testing::Test {
};

TEST_F(PlayerChannelTest, ChannelReturnsExpectedString) {
    // Arrange
    const std::string expected("enjincloud.kovan.project.1.player.1");
    PlayerChannel channel(create_default_platform(), 1, "1");

    // Act
    std::string actual = channel.channel();

    // Assert
    ASSERT_EQ(expected, actual);
}
