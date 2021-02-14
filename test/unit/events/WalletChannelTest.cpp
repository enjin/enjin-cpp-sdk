#include "WalletChannel.hpp"
#include "../../suites/ChannelsTestSuite.hpp"
#include <string>

using namespace enjin::sdk::events;

class WalletChannelTest : public ChannelsTestSuite {
};

TEST_F(WalletChannelTest, ChannelReturnsExpectedString) {
    // Arrange
    const std::string expected("enjincloud.kovan.wallet.1");
    WalletChannel channel(create_default_platform(), "1");

    // Act
    std::string actual = channel.channel();

    // Assert
    ASSERT_EQ(expected, actual);
}
