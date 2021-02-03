#ifndef ENJINCPPSDK_ICHANNEL_HPP
#define ENJINCPPSDK_ICHANNEL_HPP

#include <string>

namespace enjin::sdk::events {

/// \brief Interface for Enjin Cloud event channels.
class IChannel {
public:
    /// \brief Default destructor.
    virtual ~IChannel() = default;

    /// \brief Returns the channel formatted as a string.
    /// \return The stringified channel.
    [[nodiscard]] virtual std::string channel() const = 0;
};

}

#endif //ENJINCPPSDK_ICHANNEL_HPP
