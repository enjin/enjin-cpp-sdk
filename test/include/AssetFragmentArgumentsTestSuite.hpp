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

#ifndef ENJINSDK_ASSETFRAGMENTARGUMENTSTESTSUITE_HPP
#define ENJINSDK_ASSETFRAGMENTARGUMENTSTESTSUITE_HPP

#include "enjinsdk/JsonValue.hpp"
#include "enjinsdk/shared/AssetFragmentArguments.hpp"
#include <type_traits>

namespace enjin::test::suites {

template<class T>
class AssetFragmentArgumentsTestSuite {
    static_assert(std::is_base_of<sdk::shared::AssetFragmentArguments<T>, T>::value,
                  "Type T does not inherit from AssetFragmentArguments.");

public:
    static constexpr char AssetFragmentJson[] =
            R"({"assetIdFormat":"hex64","withStateData":true,"withConfigData":true,"withAssetBlocks":true,"withCreator":true,"withMeltDetails":true,"withMetadataURI":true,"withSupplyDetails":true,"withTransferSettings":true,"withAssetVariantMode":true,"withAssetVariants":true,"withVariantMetadata":true})";

    static sdk::json::JsonValue create_json_object() {
        sdk::json::JsonValue json;

        json.try_parse_as_object(AssetFragmentJson);
        return json;
    }

    static void set_asset_fragment_arguments(sdk::shared::AssetFragmentArguments<T>& o) {
        o.set_asset_id_format(sdk::models::AssetIdFormat::Hex64)
         .set_with_state_data()
         .set_with_config_data()
         .set_with_asset_blocks()
         .set_with_creator()
         .set_with_melt_details()
         .set_with_metadata_uri()
         .set_with_supply_details()
         .set_with_transfer_settings()
         .set_with_asset_variant_mode()
         .set_with_asset_variants()
         .set_with_variant_metadata();
    }
};

}

#endif //ENJINSDK_ASSETFRAGMENTARGUMENTSTESTSUITE_HPP
