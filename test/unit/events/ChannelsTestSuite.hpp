#ifndef ENJINCPPSDK_CHANNELSTESTSUITE_HPP
#define ENJINCPPSDK_CHANNELSTESTSUITE_HPP

#include "enjinsdk/models/Platform.hpp"
#include "gtest/gtest.h"

class ChannelsTestSuite : public testing::Test {
public:
    constexpr static char PLATFORM_JSON[] = R"({"id":1,"name":"","network":"kovan","contracts":{},"notifications":{}})";

    static enjin::sdk::models::Platform create_default_platform() {
        enjin::sdk::models::Platform platform;
        platform.deserialize(PLATFORM_JSON);
        return platform;
    }
};

#endif //ENJINCPPSDK_CHANNELSTESTSUITE_HPP
