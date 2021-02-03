#include "ChannelsTestSuite.hpp"
#include "TokenChannel.hpp"
#include <string>

using namespace enjin::sdk::events;

class TokenChannelTest : public ChannelsTestSuite {
};

TEST_F(TokenChannelTest, ChannelReturnsExpectedString) {
    // Arrange
    const std::string expected("enjincloud.kovan.token.1");
    TokenChannel channel(create_default_platform(), "1");

    // Act
    std::string actual = channel.channel();

    // Assert
    ASSERT_EQ(expected, actual);
}
