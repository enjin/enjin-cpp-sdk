#include "PlayerChannel.hpp"
#include "../../suites/ChannelsTestSuite.hpp"
#include <string>

using namespace enjin::sdk::events;

class PlayerChannelTest : public ChannelsTestSuite {
};

TEST_F(PlayerChannelTest, ChannelReturnsExpectedString) {
    // Arrange
    const std::string expected("enjincloud.kovan.app.1.player.1");
    PlayerChannel channel(create_default_platform(), 1, "1");

    // Act
    std::string actual = channel.channel();

    // Assert
    ASSERT_EQ(expected, actual);
}
