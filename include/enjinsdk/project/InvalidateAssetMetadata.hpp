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

#ifndef ENJINCPPSDK_PROJECTINVALIDATEASSETMETADATA_HPP
#define ENJINCPPSDK_PROJECTINVALIDATEASSETMETADATA_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/internal/AbstractGraphqlRequest.hpp"
#include <optional>
#include <string>

namespace enjin::sdk::project {

/// \brief Request for invalidating the cached metadata of a asset on the platform.
class ENJINSDK_EXPORT InvalidateAssetMetadata : public graphql::AbstractGraphqlRequest {
public:
    /// \brief Default constructor.
    InvalidateAssetMetadata();

    ~InvalidateAssetMetadata() override = default;

    [[nodiscard]] std::string serialize() const override;

    /// \brief Sets the asset ID.
    /// \param id The ID.
    /// \return This request for chaining.
    InvalidateAssetMetadata& set_id(const std::string& id);

    bool operator==(const InvalidateAssetMetadata& rhs) const;

    bool operator!=(const InvalidateAssetMetadata& rhs) const;

private:
    std::optional<std::string> id;
};

}

#endif //ENJINCPPSDK_PROJECTINVALIDATEASSETMETADATA_HPP
