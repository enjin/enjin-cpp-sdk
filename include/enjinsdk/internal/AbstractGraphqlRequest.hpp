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

#ifndef ENJINCPPSDK_IGRAPHQLREQUEST_HPP
#define ENJINCPPSDK_IGRAPHQLREQUEST_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/ISerializable.hpp"
#include <string>
#include <utility>

namespace enjin::sdk::graphql {

/// \brief Base class for representing a GraphQL request to the platform.
class ENJINSDK_EXPORT AbstractGraphqlRequest : public serialization::ISerializable {
public:
    AbstractGraphqlRequest() = delete;

    ~AbstractGraphqlRequest() override = default;

    /// \brief Gets the namespace of the request.
    /// \return The namespace.
    [[nodiscard]] const std::string& get_namespace() const;

    bool operator==(const AbstractGraphqlRequest& rhs) const;

    bool operator!=(const AbstractGraphqlRequest& rhs) const;

protected:
    /// \brief Constructs a request with the passed template key (namespace).
    /// \param template_key The template key.
    explicit AbstractGraphqlRequest(std::string template_key);

private:
    const std::string template_key;
};

}

#endif //ENJINCPPSDK_IGRAPHQLREQUEST_HPP
