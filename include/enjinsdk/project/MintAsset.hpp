#ifndef ENJINCPPSDK_PROJECTMINTASSET_HPP
#define ENJINCPPSDK_PROJECTMINTASSET_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/internal/AbstractGraphqlRequest.hpp"
#include "enjinsdk/models/MintInput.hpp"
#include "enjinsdk/shared/TransactionRequestArguments.hpp"
#include <optional>
#include <string>
#include <vector>

namespace enjin::sdk::project {

/// \brief Request for minting a asset.
class ENJINSDK_EXPORT MintAsset : public graphql::AbstractGraphqlRequest,
                                  public shared::TransactionRequestArguments<MintAsset> {
public:
    /// \brief Default constructor.
    MintAsset();

    ~MintAsset() override = default;

    [[nodiscard]] std::string serialize() const override;

    /// \brief Sets the asset ID.
    /// \param asset_id The ID.
    /// \return This request for chaining.
    MintAsset& set_asset_id(const std::string& asset_id);

    /// \brief Sets the mints to be performed.
    /// \param mints The mints.
    /// \return This request for chaining.
    MintAsset& set_mints(const std::vector<models::MintInput>& mints);

    bool operator==(const MintAsset& rhs) const;

    bool operator!=(const MintAsset& rhs) const;

private:
    std::optional<std::string> asset_id;
    std::optional<std::vector<models::MintInput>> mints;
};

}

namespace enjin::sdk::shared {

template ENJINSDK_EXPORT project::MintAsset&
TransactionFragmentArguments<project::MintAsset>::set_with_blockchain_data();

template ENJINSDK_EXPORT project::MintAsset& TransactionFragmentArguments<project::MintAsset>::set_with_meta();

template ENJINSDK_EXPORT project::MintAsset& TransactionFragmentArguments<project::MintAsset>::set_with_encoded_data();

template ENJINSDK_EXPORT project::MintAsset& TransactionFragmentArguments<project::MintAsset>::set_with_asset_data();

template ENJINSDK_EXPORT project::MintAsset& TransactionFragmentArguments<project::MintAsset>::set_with_signed_txs();

template ENJINSDK_EXPORT project::MintAsset& TransactionFragmentArguments<project::MintAsset>::set_with_error();

template ENJINSDK_EXPORT project::MintAsset& TransactionFragmentArguments<project::MintAsset>::set_with_nonce();

template ENJINSDK_EXPORT project::MintAsset& TransactionFragmentArguments<project::MintAsset>::set_with_state();

template ENJINSDK_EXPORT project::MintAsset& TransactionFragmentArguments<project::MintAsset>::set_with_receipt();

template ENJINSDK_EXPORT project::MintAsset& TransactionFragmentArguments<project::MintAsset>::set_with_receipt_logs();

template ENJINSDK_EXPORT project::MintAsset& TransactionFragmentArguments<project::MintAsset>::set_with_log_event();

template ENJINSDK_EXPORT project::MintAsset&
TransactionRequestArguments<project::MintAsset>::set_eth_address(const std::string& address);

template ENJINSDK_EXPORT project::MintAsset& TransactionRequestArguments<project::MintAsset>::set_send(bool send);

}

#endif //ENJINCPPSDK_PROJECTMINTASSET_HPP
