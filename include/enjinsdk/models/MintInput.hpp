#ifndef ENJINCPPSDK_MINTINPUT_HPP
#define ENJINCPPSDK_MINTINPUT_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/serialization/ISerializable.hpp"
#include <optional>
#include <string>

namespace enjin::sdk::models {

/// \brief Models a mint input for mint requests.
class ENJINSDK_EXPORT MintInput : public enjin::sdk::serialization::ISerializable {
public:
    /// \brief Default constructor.
    MintInput() = default;

    ~MintInput() override = default;

    std::string serialize() override;

    /// \brief Sets the Ethereum address to mint to.
    /// \param address The address.
    /// \return This input for chaining.
    MintInput& set_to(const std::string& address);

    /// \brief Sets the amount of assets to mint.
    /// \param value The amount.
    /// \return This input for chaining.
    MintInput& set_value(const std::string& value);

    bool operator==(const MintInput& rhs) const;

    bool operator!=(const MintInput& rhs) const;

private:
    std::optional<std::string> to;
    std::optional<std::string> value;

    constexpr static char TO_KEY[] = "to";
    constexpr static char VALUE_KEY[] = "value";
};

}

#endif //ENJINCPPSDK_MINTINPUT_HPP
