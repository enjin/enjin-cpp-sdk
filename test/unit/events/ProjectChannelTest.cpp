#include "gtest/gtest.h"
#include "ProjectChannel.hpp"
#include "ChannelsTestSuite.hpp"
#include <string>

using namespace enjin::sdk::events;
using namespace enjin::test::suites;

class ProjectChannelTest : public ChannelsTestSuite,
                           public testing::Test {
};

TEST_F(ProjectChannelTest, ChannelReturnsExpectedString) {
    // Arrange
    const std::string expected("enjincloud.kovan.project.1");
    ProjectChannel channel(create_default_platform(), 1);

    // Act
    std::string actual = channel.channel();

    // Assert
    ASSERT_EQ(expected, actual);
}
