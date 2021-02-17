#include "PusherClientTestSuite.hpp"

namespace enjin::test::utils {

enjin::pusher::PusherClient PusherClientTestSuite::create_testable_pusher_client() {
    pusher::PusherOptions options = create_default_pusher_options();
    return pusher::PusherClient(mock_ws_client, DEFAULT_KEY, options);
}

std::string PusherClientTestSuite::create_default_event(const std::string& channel, const std::string& data) {
    return (std::stringstream()
            << R"({"event":")"
            << DEFAULT_EVENT_NAME
            << R"(","channel":")"
            << channel
            << R"(","data":)"
            << data
            << R"(})"
    ).str();
}

pusher::PusherOptions PusherClientTestSuite::create_default_pusher_options() {
    pusher::PusherOptions options;
    options.set_cluster(DEFAULT_CLUSTER);
    options.set_encrypted(true);
    return options;
}

std::string PusherClientTestSuite::create_subscription_error_message() {
    return (std::stringstream()
            << R"({"event":")"
            << enjin::pusher::Constants::CHANNEL_SUBSCRIPTION_ERROR
            << R"("})"
    ).str();
}

std::string
PusherClientTestSuite::create_subscription_success_message(const std::string& channel, const std::string& data) {
    return (std::stringstream()
            << R"({"event":")"
            << enjin::pusher::Constants::CHANNEL_SUBSCRIPTION_SUCCEEDED
            << R"(","channel":")"
            << channel
            << R"(","data":)"
            << data
            << R"(})"
    ).str();
}

}
