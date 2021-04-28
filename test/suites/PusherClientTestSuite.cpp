/* Copyright 2021 Enjin Pte Ltd.
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

#include "PusherClientTestSuite.hpp"

namespace enjin::test::suites {

enjin::pusher::PusherClient PusherClientTestSuite::create_testable_pusher_client() {
    pusher::PusherOptions options = create_default_pusher_options();
    return pusher::PusherClient(mock_ws_client, DEFAULT_KEY, options);
}

std::string PusherClientTestSuite::create_default_event(const std::string& channel, const std::string& data) {
    std::stringstream ss;
    ss << R"({"event":")"
       << DEFAULT_EVENT_NAME
       << R"(","channel":")"
       << channel
       << R"(","data":)"
       << data
       << R"(})";
    return ss.str();
}

pusher::PusherOptions PusherClientTestSuite::create_default_pusher_options() {
    pusher::PusherOptions options;
    options.set_cluster(DEFAULT_CLUSTER);
    options.set_encrypted(true);
    return options;
}

std::string PusherClientTestSuite::create_subscription_error_message() {
    std::stringstream ss;
    ss << R"({"event":")"
       << enjin::pusher::PusherConstants::CHANNEL_SUBSCRIPTION_ERROR
       << R"("})";
    return ss.str();
}

std::string
PusherClientTestSuite::create_subscription_success_message(const std::string& channel, const std::string& data) {
    std::stringstream ss;
    ss << R"({"event":")"
       << enjin::pusher::PusherConstants::CHANNEL_SUBSCRIPTION_SUCCEEDED
       << R"(","channel":")"
       << channel
       << R"(","data":)"
       << data
       << R"(})";
    return ss.str();
}

}
