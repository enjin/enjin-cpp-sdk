#ifndef ENJINCPPSDK_PROJECTRELEASERESERVE_HPP
#define ENJINCPPSDK_PROJECTRELEASERESERVE_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/internal/AbstractGraphqlRequest.hpp"
#include "enjinsdk/shared/TransactionRequestArguments.hpp"
#include <optional>
#include <string>

namespace enjin::sdk::project {

/// \brief Request for releasing the reserve of an asset.
class ENJINSDK_EXPORT ReleaseReserve : public graphql::AbstractGraphqlRequest,
                                       public shared::TransactionRequestArguments<ReleaseReserve> {
public:
    /// \brief Default constructor.
    ReleaseReserve();

    ~ReleaseReserve() override = default;

    std::string serialize() override;

    /// \brief Sets the asset ID.
    /// \param asset_id The ID.
    /// \return This request for chaining.
    ReleaseReserve& set_asset_id(const std::string& asset_id);

    /// \brief Sets the amount to release.
    /// \param value The amount.
    /// \return This request for chaining.
    ReleaseReserve& set_value(const std::string& value);

    bool operator==(const ReleaseReserve& rhs) const;

    bool operator!=(const ReleaseReserve& rhs) const;

private:
    std::optional<std::string> asset_id;
    std::optional<std::string> value;
};

}

namespace enjin::sdk::shared {

template ENJINSDK_EXPORT project::ReleaseReserve&
TransactionFragmentArguments<project::ReleaseReserve>::set_with_blockchain_data();

template ENJINSDK_EXPORT project::ReleaseReserve&
TransactionFragmentArguments<project::ReleaseReserve>::set_with_meta();

template ENJINSDK_EXPORT project::ReleaseReserve&
TransactionFragmentArguments<project::ReleaseReserve>::set_with_encoded_data();

template ENJINSDK_EXPORT project::ReleaseReserve&
TransactionFragmentArguments<project::ReleaseReserve>::set_with_asset_data();

template ENJINSDK_EXPORT project::ReleaseReserve&
TransactionFragmentArguments<project::ReleaseReserve>::set_with_signed_txs();

template ENJINSDK_EXPORT project::ReleaseReserve&
TransactionFragmentArguments<project::ReleaseReserve>::set_with_error();

template ENJINSDK_EXPORT project::ReleaseReserve&
TransactionFragmentArguments<project::ReleaseReserve>::set_with_nonce();

template ENJINSDK_EXPORT project::ReleaseReserve&
TransactionFragmentArguments<project::ReleaseReserve>::set_with_state();

template ENJINSDK_EXPORT project::ReleaseReserve&
TransactionFragmentArguments<project::ReleaseReserve>::set_with_receipt();

template ENJINSDK_EXPORT project::ReleaseReserve&
TransactionFragmentArguments<project::ReleaseReserve>::set_with_receipt_logs();

template ENJINSDK_EXPORT project::ReleaseReserve&
TransactionFragmentArguments<project::ReleaseReserve>::set_with_log_event();

template ENJINSDK_EXPORT project::ReleaseReserve&
TransactionRequestArguments<project::ReleaseReserve>::set_eth_address(const std::string& address);

template ENJINSDK_EXPORT project::ReleaseReserve&
TransactionRequestArguments<project::ReleaseReserve>::set_send(bool send);

}

#endif //ENJINCPPSDK_PROJECTRELEASERESERVE_HPP
