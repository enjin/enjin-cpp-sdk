#ifndef ENJINCPPSDK_ACCESSTOKEN_HPP
#define ENJINCPPSDK_ACCESSTOKEN_HPP

#include "enjinsdk/serialization/IDeserializable.hpp"
#include <optional>
#include <string>

namespace enjin::sdk::models {

/// \brief Models a successful auth object.
class AccessToken : public enjin::sdk::serialization::IDeserializable {
public:
    /// \brief Default constructor.
    AccessToken() = default;

    void deserialize(const std::string& json) override;

    /// \brief Returns the auth token.
    /// \return The auth token.
    std::optional<std::string> get_token();

    /// \brief Returns the number of seconds until the auth expires.
    /// \return The number of seconds until the auth expires.
    std::optional<long> get_expires_in();

    bool operator==(const AccessToken& rhs) const;

    bool operator!=(const AccessToken& rhs) const;

private:
    std::optional<std::string> token;
    std::optional<long> expires_in;

    constexpr static char TOKEN_KEY[] = "accessToken";
    constexpr static char EXPIRES_IN_KEY[] = "expiresIn";
};

}

#endif //ENJINCPPSDK_ACCESSTOKEN_HPP
