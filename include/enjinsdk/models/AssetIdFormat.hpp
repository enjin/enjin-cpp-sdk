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

#ifndef ENJINCPPSDK_ASSETIDFORMAT_HPP
#define ENJINCPPSDK_ASSETIDFORMAT_HPP

namespace enjin::sdk::models {

/// \brief Values used to specify the format to render an asset's ID in.
enum class AssetIdFormat {
    Hex64,
    Hex256,
    Uint256,
};

}

#endif //ENJINCPPSDK_ASSETIDFORMAT_HPP
