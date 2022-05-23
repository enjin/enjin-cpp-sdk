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

#ifndef ENJINSDK_TESTABLESHAREDPLAYERFRAGMENTARGUMENTS_HPP
#define ENJINSDK_TESTABLESHAREDPLAYERFRAGMENTARGUMENTS_HPP

#if(ENJINSDK_BUILD_SHARED == 0)

#include "enjinsdk/shared/PlayerFragmentArguments.hpp"

namespace enjin::test::utils {

class TestableSharedPlayerFragmentArguments
        : public sdk::shared::PlayerFragmentArguments<TestableSharedPlayerFragmentArguments> {
public:
    TestableSharedPlayerFragmentArguments() = default;

    ~TestableSharedPlayerFragmentArguments() override = default;

    bool operator==(const TestableSharedPlayerFragmentArguments& rhs) const;

    bool operator!=(const TestableSharedPlayerFragmentArguments& rhs) const;
};

}

namespace enjin::sdk::shared {

template test::utils::TestableSharedPlayerFragmentArguments&
PlayerFragmentArguments<test::utils::TestableSharedPlayerFragmentArguments>::set_asset_id_format(
        models::AssetIdFormat asset_id_format);

template test::utils::TestableSharedPlayerFragmentArguments&
PlayerFragmentArguments<test::utils::TestableSharedPlayerFragmentArguments>::set_with_state_data();

template test::utils::TestableSharedPlayerFragmentArguments&
PlayerFragmentArguments<test::utils::TestableSharedPlayerFragmentArguments>::set_with_config_data();

template test::utils::TestableSharedPlayerFragmentArguments&
PlayerFragmentArguments<test::utils::TestableSharedPlayerFragmentArguments>::set_with_asset_blocks();

template test::utils::TestableSharedPlayerFragmentArguments&
PlayerFragmentArguments<test::utils::TestableSharedPlayerFragmentArguments>::set_with_creator();

template test::utils::TestableSharedPlayerFragmentArguments&
PlayerFragmentArguments<test::utils::TestableSharedPlayerFragmentArguments>::set_with_melt_details();

template test::utils::TestableSharedPlayerFragmentArguments&
PlayerFragmentArguments<test::utils::TestableSharedPlayerFragmentArguments>::set_with_metadata_uri();

template test::utils::TestableSharedPlayerFragmentArguments&
PlayerFragmentArguments<test::utils::TestableSharedPlayerFragmentArguments>::set_with_supply_details();

template test::utils::TestableSharedPlayerFragmentArguments&
PlayerFragmentArguments<test::utils::TestableSharedPlayerFragmentArguments>::set_with_transfer_settings();

template test::utils::TestableSharedPlayerFragmentArguments&
PlayerFragmentArguments<test::utils::TestableSharedPlayerFragmentArguments>::set_with_asset_variant_mode();

template test::utils::TestableSharedPlayerFragmentArguments&
PlayerFragmentArguments<test::utils::TestableSharedPlayerFragmentArguments>::set_with_asset_variants();

template test::utils::TestableSharedPlayerFragmentArguments&
PlayerFragmentArguments<test::utils::TestableSharedPlayerFragmentArguments>::set_with_variant_metadata();

template test::utils::TestableSharedPlayerFragmentArguments&
PlayerFragmentArguments<test::utils::TestableSharedPlayerFragmentArguments>::set_with_linking_info();

template test::utils::TestableSharedPlayerFragmentArguments&
PlayerFragmentArguments<test::utils::TestableSharedPlayerFragmentArguments>::set_qr_size(int size);

template test::utils::TestableSharedPlayerFragmentArguments&
PlayerFragmentArguments<test::utils::TestableSharedPlayerFragmentArguments>::set_with_wallet();

template test::utils::TestableSharedPlayerFragmentArguments&
PlayerFragmentArguments<test::utils::TestableSharedPlayerFragmentArguments>::set_with_assets_created();

}

#endif

#endif //ENJINSDK_TESTABLESHAREDPLAYERFRAGMENTARGUMENTS_HPP
