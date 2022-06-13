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

#ifndef ENJINCPPSDK_TRANSACTIONTYPE_HPP
#define ENJINCPPSDK_TRANSACTIONTYPE_HPP

namespace enjin::sdk::models {

/// \brief Represents the request type when creating or updating a transaction.
enum class TransactionType {
    Unknown, ///< SDK value for unknown values.
    AcceptAssignment,
    Assign,
    Approve,
    Create,
    Mint,
    Send,
    SendEnj,
    AdvancedSend,
    CreateTrade,
    CancelTrade,
    Melt,
    UpdateName,
    SetItemUri,
    SetWhitelisted,
    SetTransferable,
    SetMeltFee,
    DecreaseMaxMeltFee,
    SetTransferFee,
    DecreaseMaxTransferFee,
    ReleaseReserve,
    AddLog,
    SetApprovalForAll,
    ManageUpdate,
    SetDecimals,
    SetSymbol,
    Message,
};

}

#endif //ENJINCPPSDK_TRANSACTIONTYPE_HPP
