#ifndef ENJINCPPSDK_CREATETOKEN_HPP
#define ENJINCPPSDK_CREATETOKEN_HPP

#include "enjinsdk/AbstractGraphqlRequest.hpp"
#include "enjinsdk/models/TokenSupplyModel.hpp"
#include "enjinsdk/models/TokenTransferFeeSettings.hpp"
#include "enjinsdk/models/TokenTransferable.hpp"
#include "enjinsdk/shared/TransactionRequestArgumentsTemplate.hpp"
#include <optional>
#include <string>

namespace enjin::sdk::project {

/// \brief Request for creating a token (item) on the platform.
class CreateToken : public graphql::AbstractGraphqlRequest,
                    public shared::TransactionRequestArgumentsTemplate<CreateToken> {
public:
    /// \brief Default constructor.
    CreateToken();

    ~CreateToken() override = default;

    std::string serialize() override;

    /// \brief Sets the name of the token.
    /// \param name The name.
    /// \return This request for chaining.
    CreateToken& set_name(const std::string& name);

    /// \brief Sets the total supply of the token.
    /// \param total_supply The total supply.
    /// \return This request for chaining.
    CreateToken& set_total_supply(const std::string& total_supply);

    /// \brief Sets the initial reserve of the token.
    /// \param initial_reserve The reserve.
    /// \return This request for chaining.
    CreateToken& set_initial_reserve(const std::string& initial_reserve);

    /// \brief Sets the supply model of the token.
    /// \param supply_model The supply model.
    /// \return This request for chaining.
    CreateToken& set_supply_model(models::TokenSupplyModel supply_model);

    /// \brief Sets the melt value of the token.
    /// \param melt_value The value.
    /// \return This request for chaining.
    /// \remarks Corresponds to the exchange rate.
    CreateToken& set_melt_value(const std::string& melt_value);

    /// \brief Sets the ratio of the melt value to be returned to the creator.
    /// \param melt_fee_ratio The ratio.
    /// \return This request for chaining.
    /// \remarks The ratio is in the range 0-5000 to allow fractional ratios, e.g. 1 = 0.01%, 5000 = 50%, ect...
    CreateToken& set_melt_fee_ratio(int melt_fee_ratio);

    /// \brief Sets the transferable type of the token.
    /// \param transferable The transferable type.
    /// \return This request for chaining.
    CreateToken& set_transferable(models::TokenTransferable transferable);

    /// \brief Sets the transfer fee settings of the token.
    /// \param transfer_fee_settings The settings.
    /// \return This request for chaining.
    CreateToken& set_transfer_fee_settings(const models::TokenTransferFeeSettingsInput& transfer_fee_settings);

    /// \brief Sets the fungible state of the token.
    /// \param nonfungible The state.
    /// \return This request for chaining.
    CreateToken& set_nonfungible(bool nonfungible);

    bool operator==(const CreateToken& rhs) const;

    bool operator!=(const CreateToken& rhs) const;

private:
    std::optional<std::string> name;
    std::optional<std::string> total_supply;
    std::optional<std::string> initial_reserve;
    std::optional<models::TokenSupplyModel> supply_model;
    std::optional<std::string> melt_value;
    std::optional<int> melt_fee_ratio;
    std::optional<models::TokenTransferable> transferable;
    std::optional<models::TokenTransferFeeSettingsInput> transfer_fee_settings;
    std::optional<bool> nonfungible;
};

}

#endif //ENJINCPPSDK_CREATETOKEN_HPP
