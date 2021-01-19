#ifndef ENJINCPPSDK_WHITELISTED_HPP
#define ENJINCPPSDK_WHITELISTED_HPP

namespace enjin::sdk::models {

/// \brief Represents the whitelist settings.
enum class Whitelisted {
    NONE,
    SEND_AND_RECEIVE,
    SEND,
    RECEIVE,
    NO_FEES,
    ADDRESS,
};

}

#endif //ENJINCPPSDK_WHITELISTED_HPP
