#ifndef ENJINCPPSDK_TOKENCHANNEL_HPP
#define ENJINCPPSDK_TOKENCHANNEL_HPP

#include "IChannel.hpp"
#include "enjinsdk/models/Platform.hpp"
#include <string>

namespace enjin::sdk::events {

/// \brief Represents a channel to subscribe to for Enjin Cloud token events.
class TokenChannel : public IChannel {
public:
    TokenChannel() = delete;

    /// \brief Constructs a channel for the given network and token.
    /// \param platform The platform.
    /// \param token_id The token ID.
    TokenChannel(const models::Platform& platform, const std::string& token_id);

    ~TokenChannel() override = default;

    [[nodiscard]] std::string channel() const override;

private:
    models::Platform platform;
    std::string token_id;
};

}

#endif //ENJINCPPSDK_TOKENCHANNEL_HPP
