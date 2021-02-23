#ifndef ENJINCPPSDK_TOKENSTATEDATA_HPP
#define ENJINCPPSDK_TOKENSTATEDATA_HPP

#include "enjinsdk/models/TokenSupplyModel.hpp"
#include "enjinsdk/serialization/IDeserializable.hpp"
#include <optional>
#include <string>

namespace enjin::sdk::models {

/// \brief Models the state data of a item.
class TokenStateData : public enjin::sdk::serialization::IDeserializable {
public:
    /// \brief Default constructor.
    TokenStateData() = default;

    void deserialize(const std::string& json) override;

    /// \brief Returns the fungible state of the item this state belongs to.
    /// \return Whether this item is fungible.
    [[nodiscard]] const std::optional<bool>& get_non_fungible() const;

    /// \brief Returns the block number of the last update.
    /// \return The block number.
    [[nodiscard]] const std::optional<int>& get_block_height() const;

    /// \brief Returns the wallet address of the creator of the item this state belongs to.
    /// \return The creator's wallet address.
    [[nodiscard]] const std::optional<std::string>& get_creator() const;

    /// \brief Returns the first block the item appeared on.
    /// \return The block number.
    [[nodiscard]] const std::optional<int>& get_first_block() const;

    /// \brief Returns the reserve of the item this state belongs to.
    /// \return The reserve amount.
    [[nodiscard]] const std::optional<std::string>& get_reserve() const;

    /// \brief Returns the supply model of the item this state belongs to.
    /// \return The supply model.
    [[nodiscard]] const std::optional<TokenSupplyModel>& get_supply_model() const;

    /// \brief Returns the amount of the item in circulation.
    /// \return The amount in circulation.
    [[nodiscard]] const std::optional<std::string>& get_circulating_supply() const;

    /// \brief Returns the amount of the item available for minting.
    /// \return The amount available.
    [[nodiscard]] const std::optional<std::string>& get_mintable_supply() const;

    /// \brief Returns the total supply of the item this state belongs to.
    /// \return The total supply.
    [[nodiscard]] const std::optional<std::string>& get_total_supply() const;

    bool operator==(const TokenStateData& rhs) const;

    bool operator!=(const TokenStateData& rhs) const;

private:
    std::optional<bool> non_fungible;
    std::optional<int> block_height;
    std::optional<std::string> creator;
    std::optional<int> first_block;
    std::optional<std::string> reserve;
    std::optional<TokenSupplyModel> supply_model;
    std::optional<std::string> circulating_supply;
    std::optional<std::string> mintable_supply;
    std::optional<std::string> total_supply;

    constexpr static char NONFUNGIBLE_KEY[] = "nonFungible";
    constexpr static char BLOCK_HEIGHT_KEY[] = "blockHeight";
    constexpr static char CREATOR_KEY[] = "creator";
    constexpr static char FIRST_BLOCK_KEY[] = "firstBlock";
    constexpr static char RESERVE_KEY[] = "reserve";
    constexpr static char SUPPLY_MODEL_KEY[] = "supplyModel";
    constexpr static char CIRCULATING_SUPPLY_KEY[] = "circulatingSupply";
    constexpr static char MINTABLE_SUPPLY_KEY[] = "mintableSupply";
    constexpr static char TOTAL_SUPPLY_KEY[] = "totalSupply";
};

}

#endif //ENJINCPPSDK_TOKENSTATEDATA_HPP
