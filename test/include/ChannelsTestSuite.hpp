/* Copyright 2021 Enjin Pte. Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef ENJINCPPSDK_CHANNELSTESTSUITE_HPP
#define ENJINCPPSDK_CHANNELSTESTSUITE_HPP

#include "enjinsdk/models/Platform.hpp"

namespace enjin::test::suites {

class ChannelsTestSuite {
public:
    constexpr static char PlatformJson[] = R"({"id":1,"name":"","network":"test","contracts":{},"notifications":{}})";

    static enjin::sdk::models::Platform create_default_platform() {
        enjin::sdk::models::Platform platform;
        platform.deserialize(PlatformJson);
        return platform;
    }
};

}

#endif //ENJINCPPSDK_CHANNELSTESTSUITE_HPP
