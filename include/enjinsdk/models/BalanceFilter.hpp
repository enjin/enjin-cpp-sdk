#ifndef ENJINCPPSDK_BALANCEFILTER_HPP
#define ENJINCPPSDK_BALANCEFILTER_HPP

#include "enjinsdk/serialization/ISerializable.hpp"
#include <optional>
#include <string>
#include <vector>

namespace enjin::sdk::models {

/// \brief Models a filter input for balance queries.
class BalanceFilter : public enjin::sdk::serialization::ISerializable {
public:
    /// \brief Default constructor.
    BalanceFilter() = default;

    std::string serialize() override;

    /// \brief Sets the filter to include other filters to intersect with.
    /// \param others The other filters.
    /// \return This filter for chaining.
    BalanceFilter& set_and(const std::vector<BalanceFilter>& others);

    /// \brief Sets the filter to include other filters to union with.
    /// \param others The other filters.
    /// \return This filter for chaining.
    BalanceFilter& set_or(const std::vector<BalanceFilter>& others);

    /// \brief Sets the token (item) ID to filter for.
    /// \param token_id The token ID.
    /// \return This filter for chaining.
    BalanceFilter& set_token_id(const std::string& token_id);

    /// \brief Sets the token (item) IDs to filter for.
    /// \param token_ids The token IDs.
    /// \return This filter for chaining.
    BalanceFilter& set_token_id_in(const std::vector<std::string>& token_ids);

    /// \brief Sets the wallet to filter by.
    /// \param wallet The wallet address.
    /// \return This filter for chaining.
    BalanceFilter& set_wallet(const std::string& wallet);

    /// \brief Sets the wallets to filter by.
    /// \param wallets The wallet addresses.
    /// \return This filter for chaining.
    BalanceFilter& set_wallet_in(const std::vector<std::string>& wallets);

    /// \brief Sets the filter to include balances equal to the passed value.
    /// \param value The vaue to compare by.
    /// \return This filter for chaining.
    BalanceFilter& set_value(int value);

    /// \brief Sets the filter to include balances greater than the passed value.
    /// \param value value The vaue to compare by.
    /// \return This filter for chaining.
    BalanceFilter& set_value_greater_than(int value);

    /// \brief Sets the filter to include balances greater than or equal to the passed value.
    /// \param value value The vaue to compare by.
    /// \return This filter for chaining.
    BalanceFilter& set_value_greater_than_or_equal(int value);

    /// \brief Sets the filter to include balances less than the passed value.
    /// \param value value The vaue to compare by.
    /// \return This filter for chaining.
    BalanceFilter& set_value_less_than(int value);

    /// \brief Sets the filter to include balances greater than or equal to the passed value.
    /// \param value value The vaue to compare by.
    /// \return This filter for chaining.
    BalanceFilter& set_value_less_than_or_equal(int value);

    bool operator==(const BalanceFilter& rhs) const;

    bool operator!=(const BalanceFilter& rhs) const;

private:
    std::optional<std::vector<BalanceFilter>> and_filters;
    std::optional<std::vector<BalanceFilter>> or_filters;
    std::optional<std::string> token_id;
    std::optional<std::vector<std::string>> token_id_in;
    std::optional<std::string> wallet;
    std::optional<std::vector<std::string>> wallet_in;
    std::optional<int> value;
    std::optional<int> value_gt;
    std::optional<int> value_gte;
    std::optional<int> value_lt;
    std::optional<int> value_lte;

    constexpr static char AND_KEY[] = "and";
    constexpr static char OR_KEY[] = "or";
    constexpr static char TOKEN_ID_KEY[] = "tokenId";
    constexpr static char TOKEN_ID_IN_KEY[] = "tokenId_in";
    constexpr static char WALLET_KEY[] = "wallet";
    constexpr static char WALLET_IN_KEY[] = "wallet_in";
    constexpr static char VALUE_KEY[] = "value";
    constexpr static char VALUE_GT_KEY[] = "value_gt";
    constexpr static char VALUE_GTE_KEY[] = "value_gte";
    constexpr static char VALUE_LT_KEY[] = "value_lt";
    constexpr static char VALUE_LTE_KEY[] = "value_lte";
};

}

#endif //ENJINCPPSDK_BALANCEFILTER_HPP
