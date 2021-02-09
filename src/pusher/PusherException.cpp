#include "enjinsdk/internal/pusher/PusherException.hpp"

namespace enjin::pusher {

PusherException::PusherException(const std::string& message, int error_code)
        : std::exception(message.c_str()), error_code(error_code) {
}

int PusherException::get_error_code() const {
    return error_code;
}

}
