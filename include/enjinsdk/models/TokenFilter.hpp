#ifndef ENJINCPPSDK_TOKENFILTER_HPP
#define ENJINCPPSDK_TOKENFILTER_HPP

#include "enjinsdk/serialization/ISerializable.hpp"
#include <optional>
#include <string>
#include <vector>

namespace enjin::sdk::models {

/// \brief Models a filter input for token queries.
class TokenFilter : public enjin::sdk::serialization::ISerializable {
public:
    /// \brief Default constructor.
    TokenFilter() = default;

    std::string serialize() override;

    /// \brief Sets the filter to include other filters to intersect with.
    /// \param others The other filters.
    /// \return This filter for chaining.
    TokenFilter& set_and(const std::vector<TokenFilter>& others);

    /// \brief Sets the filter to include other filters to union with.
    /// \param others The other filters.
    /// \return This filter for chaining.
    TokenFilter& set_or(const std::vector<TokenFilter>& others);

    /// \brief Sets the token (item) ID to filter for.
    /// \param id The ID.
    /// \return This filter for chaining.
    TokenFilter& set_id(const std::string& id);

    /// \brief Sets the token (item) IDs to filter for.
    /// \param ids The IDs.
    /// \return This filter for chaining.
    TokenFilter& set_id_in(const std::vector<std::string>& ids);

    /// \brief Sets the name to filter.
    /// \param name The name.
    /// \return This filter for chaining.
    TokenFilter& set_name(const std::string& name);

    /// \brief Sets the filter to include
    /// \param text The text.
    /// \return This filter for chaining.
    TokenFilter& set_name_contains(const std::string& text);

    /// \brief Sets the names to filter for.
    /// \param names The names.
    /// \return This filter for chaining.
    TokenFilter& set_name_in(const std::vector<std::string>& names);

    /// \brief Sets the filter to include items with names which start with the passed prefix.
    /// \param prefix The prefix.
    /// \return This filter for chaining.
    TokenFilter& set_name_starts_with(const std::string& prefix);

    /// \brief Sets the filter to include items with names which end with the passed suffix.
    /// \param suffix The suffix.
    /// \return This filter for chaining.
    TokenFilter& set_name_ends_with(const std::string& suffix);

    /// \brief Sets the wallet to filter for.
    /// \param wallet The wallet address.
    /// \return This filter for chaining.
    TokenFilter& set_wallet(const std::string& wallet);

    /// \brief Sets the wallets to filter for.
    /// \param wallets The wallet addresses.
    /// \return This filter for chaining.
    TokenFilter& set_wallet_in(const std::vector<std::string>& wallets);

    bool operator==(const TokenFilter& rhs) const;

    bool operator!=(const TokenFilter& rhs) const;

private:
    std::optional<std::vector<TokenFilter>> and_filters;
    std::optional<std::vector<TokenFilter>> or_filters;
    std::optional<std::string> id;
    std::optional<std::vector<std::string>> id_in;
    std::optional<std::string> name;
    std::optional<std::string> name_contains;
    std::optional<std::vector<std::string>> name_in;
    std::optional<std::string> name_starts_with;
    std::optional<std::string> name_ends_with;
    std::optional<std::string> wallet;
    std::optional<std::vector<std::string>> wallet_in;

    constexpr static char AND_KEY[] = "and";
    constexpr static char OR_KEY[] = "or";
    constexpr static char ID_KEY[] = "id";
    constexpr static char ID_IN_KEY[] = "id_in";
    constexpr static char NAME_KEY[] = "name";
    constexpr static char NAME_CONTAINS_KEY[] = "name_contains";
    constexpr static char NAME_IN_KEY[] = "name_in";
    constexpr static char NAME_STARTS_WITH_KEY[] = "name_starts_with";
    constexpr static char NAME_ENDS_WITH_KEY[] = "name_ends_with";
    constexpr static char WALLET_KEY[] = "wallet";
    constexpr static char WALLET_IN_KEY[] = "wallet_in";
};

}

#endif //ENJINCPPSDK_TOKENFILTER_HPP
