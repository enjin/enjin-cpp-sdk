#include "EnumUtils.hpp"
#include "gtest/gtest.h"
#include <string>
#include <tuple>

using namespace enjin::sdk::models;
using namespace enjin::sdk::utils;

class WhitelistedTest : public testing::TestWithParam<std::tuple<std::string, Whitelisted>> {
};

TEST_P(WhitelistedTest, SerializeWhitelistedReturnsExpectedString) {
    // Arrange
    const std::string& expected = std::get<0>(GetParam());
    Whitelisted value = std::get<1>(GetParam());

    // Act
    std::string actual = serialize_whitelisted(value);

    // Assert
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(SerializeWhitelisted,
                         WhitelistedTest,
                         testing::Values(std::make_tuple("NONE", Whitelisted::NONE),
                                         std::make_tuple("SEND_AND_RECEIVE", Whitelisted::SEND_AND_RECEIVE),
                                         std::make_tuple("SEND", Whitelisted::SEND),
                                         std::make_tuple("RECEIVE", Whitelisted::RECEIVE),
                                         std::make_tuple("NO_FEES", Whitelisted::NO_FEES),
                                         std::make_tuple("ADDRESS", Whitelisted::ADDRESS)));
