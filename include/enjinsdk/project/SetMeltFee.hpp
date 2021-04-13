#ifndef ENJINCPPSDK_PROJECTSETMELTFEE_HPP
#define ENJINCPPSDK_PROJECTSETMELTFEE_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/internal/AbstractGraphqlRequest.hpp"
#include "enjinsdk/shared/TransactionRequestArguments.hpp"
#include <optional>
#include <string>

namespace enjin::sdk::project {

/// \brief Request for setting the melt fee of an asset.
class ENJINSDK_EXPORT SetMeltFee : public graphql::AbstractGraphqlRequest,
                                   public shared::TransactionRequestArguments<SetMeltFee> {
public:
    /// \brief Default constructor.
    SetMeltFee();

    ~SetMeltFee() override = default;

    [[nodiscard]] std::string serialize() const override;

    /// \brief Sets the asset ID.
    /// \param asset_id The ID.
    /// \return This request for chaining.
    SetMeltFee& set_asset_id(const std::string& asset_id);

    /// \brief Sets the index for non-fungible assets.
    /// \param asset_index The index.
    /// \return This request for chaining.
    SetMeltFee& set_asset_index(const std::string& asset_index);

    /// \brief Sets the new melt fee for the asset.
    /// \param melt_fee The new ratio.
    /// \return This request for chaining.
    /// \remarks The ratio is in the range 0-5000 to allow fractional ratios, e.g. 1 = 0.01%, 5000 = 50%, ect...
    SetMeltFee& set_melt_fee(int melt_fee);

    bool operator==(const SetMeltFee& rhs) const;

    bool operator!=(const SetMeltFee& rhs) const;

private:
    std::optional<std::string> asset_id;
    std::optional<std::string> asset_index;
    std::optional<int> melt_fee;
};

}

namespace enjin::sdk::shared {

template ENJINSDK_EXPORT project::SetMeltFee&
TransactionFragmentArguments<project::SetMeltFee>::set_with_blockchain_data();

template ENJINSDK_EXPORT project::SetMeltFee& TransactionFragmentArguments<project::SetMeltFee>::set_with_meta();

template ENJINSDK_EXPORT project::SetMeltFee&
TransactionFragmentArguments<project::SetMeltFee>::set_with_encoded_data();

template ENJINSDK_EXPORT project::SetMeltFee& TransactionFragmentArguments<project::SetMeltFee>::set_with_asset_data();

template ENJINSDK_EXPORT project::SetMeltFee& TransactionFragmentArguments<project::SetMeltFee>::set_with_signed_txs();

template ENJINSDK_EXPORT project::SetMeltFee& TransactionFragmentArguments<project::SetMeltFee>::set_with_error();

template ENJINSDK_EXPORT project::SetMeltFee& TransactionFragmentArguments<project::SetMeltFee>::set_with_nonce();

template ENJINSDK_EXPORT project::SetMeltFee& TransactionFragmentArguments<project::SetMeltFee>::set_with_state();

template ENJINSDK_EXPORT project::SetMeltFee& TransactionFragmentArguments<project::SetMeltFee>::set_with_receipt();

template ENJINSDK_EXPORT project::SetMeltFee&
TransactionFragmentArguments<project::SetMeltFee>::set_with_receipt_logs();

template ENJINSDK_EXPORT project::SetMeltFee& TransactionFragmentArguments<project::SetMeltFee>::set_with_log_event();

template ENJINSDK_EXPORT project::SetMeltFee&
TransactionRequestArguments<project::SetMeltFee>::set_eth_address(const std::string& address);

template ENJINSDK_EXPORT project::SetMeltFee& TransactionRequestArguments<project::SetMeltFee>::set_send(bool send);

}

#endif //ENJINCPPSDK_PROJECTSETMELTFEE_HPP
