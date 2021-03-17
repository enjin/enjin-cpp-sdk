#ifndef ENJINCPPSDK_PUSHERERRORCODES_HPP
#define ENJINCPPSDK_PUSHERERRORCODES_HPP

namespace enjin::pusher {

/// \brief Error codes that may be received from Pusher.
enum class ErrorCodes : int {
    UNKNOWN = 0, ///< \brief A catch all error code.
    SUBSCRIPTION_ERROR = 5003,
};

}

#endif //ENJINCPPSDK_PUSHERERRORCODES_HPP
