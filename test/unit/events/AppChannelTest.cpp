#include "AppChannel.hpp"
#include "ChannelsTestSuite.hpp"
#include <string>

using namespace enjin::sdk::events;

class AppChannelTest : public ChannelsTestSuite {
};

TEST_F(AppChannelTest, ChannelReturnsExpectedString) {
    // Arrange
    const std::string expected("enjincloud.kovan.app.1");
    AppChannel channel(create_default_platform(), 1);

    // Act
    std::string actual = channel.channel();

    // Assert
    ASSERT_EQ(expected, actual);
}
