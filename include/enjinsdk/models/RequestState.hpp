#ifndef ENJINCPPSDK_REQUESTSTATE_HPP
#define ENJINCPPSDK_REQUESTSTATE_HPP

namespace enjin::sdk::models {

/// \brief Represents the state of a request.
enum class RequestState {
    UNKNOWN, ///< SDK value for unknown values.
    PENDING,
    BROADCAST,
    TP_PROCESSING,
    EXECUTED,
    CANCELED_USER,
    CANCELED_PLATFORM,
    DROPPED,
    FAILED,
};

}

#endif //ENJINCPPSDK_REQUESTSTATE_HPP
