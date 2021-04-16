/* Copyright 2021 Enjin Pte Ltd.
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

#ifndef ENJINCPPSDK_ASSETTRANSFERFEETYPE_HPP
#define ENJINCPPSDK_ASSETTRANSFERFEETYPE_HPP

namespace enjin::sdk::models {

/// \brief Represents the different transfer types for assets.
enum class AssetTransferFeeType {
    UNKNOWN, ///< SDK value for unknown values from the platform.
    NONE,
    PER_TRANSFER,
    PER_CRYPTO_ITEM,
    RATIO_CUT,
    RATIO_EXTRA,
};

}

#endif //ENJINCPPSDK_ASSETTRANSFERFEETYPE_HPP
