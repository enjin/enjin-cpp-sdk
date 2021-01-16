#ifndef ENJINCPPSDK_LINKINGINFO_HPP
#define ENJINCPPSDK_LINKINGINFO_HPP

#include "enjinsdk/serialization/IDeserializable.hpp"
#include <optional>
#include <string>

namespace enjin::sdk::models {

/// \brief Models the linking information for a player.
class LinkingInfo : public enjin::sdk::serialization::IDeserializable {
public:
    /// \brief Default constructor.
    LinkingInfo() = default;

    void deserialize(const std::string& json) override;

    /// \brief Returns the linking code used to link a wallet to the player this info belongs to.
    /// \return The linking code.
    [[nodiscard]] const std::optional<std::string>& get_code() const;

    /// \brief Returns the URL for the QR image that links a wallet to the player this info belongs to.
    /// \return The URL for the image.
    [[nodiscard]] const std::optional<std::string>& get_qr() const;

    bool operator==(const LinkingInfo& rhs) const;

    bool operator!=(const LinkingInfo& rhs) const;

private:
    std::optional<std::string> code;
    std::optional<std::string> qr;

    constexpr static char CODE_KEY[] = "code";
    constexpr static char QR_KEY[] = "qr";
};

}

#endif //ENJINCPPSDK_LINKINGINFO_HPP
