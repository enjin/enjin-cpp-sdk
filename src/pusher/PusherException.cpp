#include "enjinsdk/internal/pusher/PusherException.hpp"

namespace enjin::pusher {

PusherException::PusherException(const std::string& message, int error_code)
        : std::runtime_error(message), error_code(error_code) {
}

int PusherException::get_error_code() const {
    return error_code;
}

}
