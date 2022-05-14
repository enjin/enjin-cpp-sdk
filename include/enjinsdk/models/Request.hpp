/* Copyright 2021 Enjin Pte. Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef ENJINCPPSDK_REQUEST_HPP
#define ENJINCPPSDK_REQUEST_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/IDeserializable.hpp"
#include "enjinsdk/models/Asset.hpp"
#include "enjinsdk/models/BlockchainData.hpp"
#include "enjinsdk/models/Project.hpp"
#include "enjinsdk/models/RequestState.hpp"
#include "enjinsdk/models/RequestType.hpp"
#include "enjinsdk/models/Wallet.hpp"
#include <optional>
#include <string>

namespace enjin::sdk::models {

/// \brief Models a request on the platform.
class ENJINSDK_EXPORT Request : public serialization::IDeserializable {
public:
    /// \brief Default constructor.
    Request() = default;

    ~Request() override = default;

    void deserialize(const std::string& json) override;

    /// \brief Returns the ID of this request.
    /// \return The ID.
    [[nodiscard]] const std::optional<int>& get_id() const;

    /// \brief Returns the hash ID of this request.
    /// \return The hash ID.
    [[nodiscard]] const std::optional<std::string>& get_transaction_id() const;

    /// \brief Returns the title of this request.
    /// \return The title.
    [[nodiscard]] const std::optional<std::string>& get_title() const;

    /// \brief Returns the contract address of this request.
    /// \return The address.
    [[nodiscard]] const std::optional<std::string>& get_contract() const;

    /// \brief Returns the type of this request.
    /// \return The request type.
    [[nodiscard]] const std::optional<RequestType>& get_type() const;

    /// \brief Returns the value of this request.
    /// \return The value.
    [[nodiscard]] const std::optional<std::string>& get_value() const;

    /// \brief Returns the retry state of this request.
    /// \return The retry state.
    [[nodiscard]] const std::optional<std::string>& get_retry_state() const;

    /// \brief Returns the state of this request.
    /// \return The request state.
    [[nodiscard]] const std::optional<RequestState>& get_state() const;

    /// \brief Returns if this request has been accepted or not.
    /// \return Whether this request has been accepted or not.
    [[nodiscard]] const std::optional<bool>& get_accepted() const;

    /// \brief Returns if the wallet of the transaction is a project wallet.
    /// \return Whether the wallet is a project wallet.
    [[nodiscard]] const std::optional<bool>& get_project_wallet() const;

    /// \brief Returns the blockchain data of this request.
    /// \return The blockchain data.
    [[nodiscard]] const std::optional<BlockchainData>& get_blockchain_data() const;

    /// \brief Returns the project of this request.
    /// \return The project.
    [[nodiscard]] const std::optional<Project>& get_project() const;

    /// \brief Returns the asset for this request.
    /// \return The asset.
    [[nodiscard]] const std::optional<Asset>& get_asset() const;

    /// Returns the wallet for this request.
    /// \return The wallet.
    [[nodiscard]] const std::optional<Wallet>& get_wallet() const;

    /// \brief Returns the datetime when this request was created.
    /// \return The datetime.
    /// \remarks The datetime is formatted using the ISO 8601 date format.
    [[nodiscard]] const std::optional<std::string>& get_created_at() const;

    /// \brief Returns the datetime when this request was last updated.
    /// \return The datetime.
    /// \remarks The datetime is formatted using the ISO 8601 date format.
    [[nodiscard]] const std::optional<std::string>& get_updated_at() const;

    bool operator==(const Request& rhs) const;

    bool operator!=(const Request& rhs) const;

private:
    std::optional<int> id;
    std::optional<std::string> transaction_id;
    std::optional<std::string> title;
    std::optional<std::string> contract;
    std::optional<RequestType> type;
    std::optional<std::string> value;
    std::optional<std::string> retry_state;
    std::optional<RequestState> state;
    std::optional<bool> accepted;
    std::optional<bool> project_wallet;
    std::optional<BlockchainData> blockchain_data;
    std::optional<Project> project;
    std::optional<Asset> asset;
    std::optional<Wallet> wallet;
    std::optional<std::string> created_at;
    std::optional<std::string> updated_at;

    constexpr static char ID_KEY[] = "id";
    constexpr static char TRANSACTION_ID_KEY[] = "transactionId";
    constexpr static char TITLE_KEY[] = "title";
    constexpr static char CONTRACT_KEY[] = "contract";
    constexpr static char TYPE_KEY[] = "type";
    constexpr static char VALUE_KEY[] = "value";
    constexpr static char RETRY_STATE_KEY[] = "retryState";
    constexpr static char STATE_KEY[] = "state";
    constexpr static char ACCEPTED_KEY[] = "accepted";
    constexpr static char PROJECT_WALLET_KEY[] = "projectWallet";
    constexpr static char BLOCKCHAIN_DATA_KEY[] = "blockchainData";
    constexpr static char PROJECT_KEY[] = "project";
    constexpr static char ASSET_KEY[] = "asset";
    constexpr static char WALLET_KEY[] = "wallet";
    constexpr static char CREATED_AT_KEY[] = "createdAt";
    constexpr static char UPDATED_AT_KEY[] = "updatedAt";
};

}

#endif //ENJINCPPSDK_REQUEST_HPP
