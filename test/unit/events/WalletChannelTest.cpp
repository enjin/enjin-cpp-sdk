#include "gtest/gtest.h"
#include "WalletChannel.hpp"
#include "ChannelsTestSuite.hpp"
#include <string>

using namespace enjin::sdk::events;
using namespace enjin::test::suites;

class WalletChannelTest : public ChannelsTestSuite,
                          public testing::Test {
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
