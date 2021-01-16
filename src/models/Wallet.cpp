#include "enjinsdk/models/Wallet.hpp"

#include "RapidJsonUtils.hpp"

namespace enjin::sdk::models {

void Wallet::deserialize(const std::string& json) {
    rapidjson::Document document;
    document.Parse(json.c_str());
    if (document.IsObject()) {
        if (document.HasMember(ETH_ADDRESS_KEY) && document[ETH_ADDRESS_KEY].IsString()) {
            eth_address.emplace(document[ETH_ADDRESS_KEY].GetString());
        }
        if (document.HasMember(ENJ_ALLOWANCE_KEY) && document[ENJ_ALLOWANCE_KEY].IsFloat()) {
            enj_allowance.emplace(document[ENJ_ALLOWANCE_KEY].GetFloat());
        }
        if (document.HasMember(ENJ_BALANCE_KEY) && document[ENJ_BALANCE_KEY].IsFloat()) {
            enj_balance.emplace(document[ENJ_BALANCE_KEY].GetFloat());
        }
        if (document.HasMember(ETH_BALANCE_KEY) && document[ETH_BALANCE_KEY].IsFloat()) {
            eth_balance.emplace(document[ETH_BALANCE_KEY].GetFloat());
        }
        if (document.HasMember(TOKENS_CREATED_KEY) && document[TOKENS_CREATED_KEY].IsArray()) {
            tokens_created.emplace(utils::get_array_as_type_vector<Token>(document, TOKENS_CREATED_KEY));
        }
    }
}

const std::optional<std::string>& Wallet::get_eth_address() const {
    return eth_address;
}

const std::optional<float>& Wallet::get_enj_allowance() const {
    return enj_allowance;
}

const std::optional<float>& Wallet::get_enj_balance() const {
    return enj_balance;
}

const std::optional<float>& Wallet::get_eth_balance() const {
    return eth_balance;
}

const std::optional<std::vector<Token>>& Wallet::get_tokens_created() const {
    return tokens_created;
}

bool Wallet::operator==(const Wallet& rhs) const {
    return eth_address == rhs.eth_address &&
           enj_allowance == rhs.enj_allowance &&
           enj_balance == rhs.enj_balance &&
           eth_balance == rhs.eth_balance &&
           tokens_created == rhs.tokens_created;
}

bool Wallet::operator!=(const Wallet& rhs) const {
    return !(rhs == *this);
}

}
