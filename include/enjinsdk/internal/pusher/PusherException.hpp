#ifndef ENJINCPPSDK_PUSHEREXCEPTION_HPP
#define ENJINCPPSDK_PUSHEREXCEPTION_HPP

#include "enjinsdk_export.h"
#include <exception>
#include <string>

namespace enjin::pusher {

/// \brief Exception class for Pusher events.
class ENJINSDK_EXPORT PusherException : public std::exception {
public:
    /// \brief Constructs the exception with a message and error code.
    /// \param message The message.
    /// \param error_code The error code.
    PusherException(const std::string& message, int error_code);

    ~PusherException() noexcept override = default;

    /// \brief Returns the error exception code.
    /// \return The error code.
    [[nodiscard]] int get_error_code() const;

private:
    int error_code;
};

}

#endif //ENJINCPPSDK_PUSHEREXCEPTION_HPP
