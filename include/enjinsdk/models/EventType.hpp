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

#ifndef ENJINCPPSDK_EVENTTYPE_HPP
#define ENJINCPPSDK_EVENTTYPE_HPP

namespace enjin::sdk::models {

/// \brief Enums defining the different types of notifications that may be received from the platform.
enum class EventType {
    Unknown, ///< SDK value for unknown values from the platform.
    ProjectCreated,
    ProjectDeleted,
    ProjectLinked,
    ProjectLocked,
    ProjectUnlinked,
    ProjectUnlocked,
    ProjectUpdated,
    BlockchainLogProcessed,
    MessageProcessed,
    PlayerCreated,
    PlayerDeleted,
    PlayerLinked,
    PlayerUnlinked,
    PlayerUpdated,
    AssetCreated,
    AssetMelted,
    AssetMinted,
    AssetTransferred,
    AssetUpdated,
    TradeAssetCompleted,
    TradeAssetCreated,
    TransactionBroadcast,
    TransactionCanceled,
    TransactionDropped,
    TransactionExecuted,
    TransactionFailed,
    TransactionPending,
    TransactionProcessing,
    TransactionUpdated,
};

}

#endif //ENJINCPPSDK_EVENTTYPE_HPP
