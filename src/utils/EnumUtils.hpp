#ifndef ENJINCPPSDK_ENUMUTILS_HPP
#define ENJINCPPSDK_ENUMUTILS_HPP

#include "enjinsdk/models/RequestState.hpp"
#include "enjinsdk/models/RequestType.hpp"
#include "enjinsdk/models/SortDirection.hpp"
#include "enjinsdk/models/TokenField.hpp"
#include "enjinsdk/models/TokenSupplyModel.hpp"
#include "enjinsdk/models/TokenTransferFeeType.hpp"
#include "enjinsdk/models/TokenTransferable.hpp"
#include "enjinsdk/models/TokenVariantMode.hpp"
#include "enjinsdk/models/TransactionField.hpp"
#include <string>

namespace enjin::sdk::utils {

enjin::sdk::models::RequestState deserialize_request_state(const std::string& s) noexcept;

enjin::sdk::models::RequestType deserialize_request_type(const std::string& s) noexcept;

enjin::sdk::models::TokenSupplyModel deserialize_token_supply_model(const std::string& s) noexcept;

enjin::sdk::models::TokenTransferFeeType deserialize_token_transfer_fee_type(const std::string& s) noexcept;

enjin::sdk::models::TokenTransferable deserialize_token_transferable(const std::string& s) noexcept;

enjin::sdk::models::TokenVariantMode deserialize_token_variant_mode(const std::string& s) noexcept;

std::string serialize_request_state(enjin::sdk::models::RequestState v) noexcept;

std::string serialize_request_type(enjin::sdk::models::RequestType v) noexcept;

std::string serialize_sort_direction(enjin::sdk::models::SortDirection v) noexcept;

std::string serialize_token_field(enjin::sdk::models::TokenField v) noexcept;

std::string serialize_token_supply_model(enjin::sdk::models::TokenSupplyModel v) noexcept;

std::string serialize_token_transfer_fee_type(enjin::sdk::models::TokenTransferFeeType v) noexcept;

std::string serialize_token_transferable(enjin::sdk::models::TokenTransferable v) noexcept;

std::string serialize_token_variant_mode(enjin::sdk::models::TokenVariantMode v) noexcept;

std::string serialize_transaction_field(enjin::sdk::models::TransactionField v) noexcept;

}

#endif //ENJINCPPSDK_ENUMUTILS_HPP
