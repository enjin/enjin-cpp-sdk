#ifndef ENJINCPPSDK_SHAREDSENDASSET_HPP
#define ENJINCPPSDK_SHAREDSENDASSET_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/AbstractGraphqlRequest.hpp"
#include "enjinsdk/shared/TransactionRequestArgumentsTemplate.hpp"
#include <optional>
#include <string>

namespace enjin::sdk::shared {

/// \brief Request for sending a asset.
class ENJINSDK_EXPORT SendAsset : public graphql::AbstractGraphqlRequest,
                                  public TransactionRequestArgumentsTemplate<SendAsset> {
public:
    /// \brief Default constructor.
    SendAsset();

    ~SendAsset() override = default;

    std::string serialize() override;

    /// \brief Sets the wallet address of the recipient.
    /// \param recipient_address The address.
    /// \return This request for chaining.
    SendAsset& set_recipient_address(const std::string& recipient_address);

    /// \brief Sets the asset ID.
    /// \param asset_id The ID.
    /// \return This request for chaining.
    SendAsset& set_asset_id(const std::string& asset_id);

    /// \brief Sets the index for non-fungible assets.
    /// \param asset_index The index.
    /// \return This request for chaining.
    SendAsset& set_asset_index(const std::string& asset_index);

    /// \brief Sets the amount to send.
    /// \param value The amount.
    /// \return This request for chaining.
    SendAsset& set_value(const std::string& value);

    /// \brief Sets the data to forward with the transaction.
    /// \param data The data.
    /// \return This request for chaining.
    SendAsset& set_data(const std::string& data);

    bool operator==(const SendAsset& rhs) const;

    bool operator!=(const SendAsset& rhs) const;

private:
    std::optional<std::string> recipient_address;
    std::optional<std::string> asset_id;
    std::optional<std::string> asset_index;
    std::optional<std::string> value;
    std::optional<std::string> data;
};

}

#endif //ENJINCPPSDK_SHAREDSENDASSET_HPP
