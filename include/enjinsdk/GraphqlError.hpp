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

#ifndef ENJINCPPSDK_GRAPHQLERROR_HPP
#define ENJINCPPSDK_GRAPHQLERROR_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/IDeserializable.hpp"
#include <map>
#include <optional>
#include <string>
#include <vector>

namespace enjin::sdk::graphql {

/// \brief Models the structure of a GraphQL response error.
class ENJINSDK_EXPORT GraphqlError : public serialization::IDeserializable {
public:
    /// \brief Default constructor.
    GraphqlError() = default;

    ~GraphqlError() override = default;

    void deserialize(const std::string& json) override;

    /// \brief Returns the error message.
    /// \return The error message.
    [[nodiscard]] const std::optional<std::string>& get_message() const;

    /// \brief Returns the error code.
    /// \return The error code.
    [[nodiscard]] const std::optional<int>& get_code() const;

    /// \brief Returns the error locations.
    /// \return The error locations.
    [[nodiscard]] const std::optional<std::vector<std::map<std::string, int>>>& get_locations() const;

    /// \brief Returns the error details.
    /// \return The error details.
    [[nodiscard]] const std::optional<std::string>& get_details() const;

    bool operator==(const GraphqlError& rhs) const;

    bool operator!=(const GraphqlError& rhs) const;

private:
    std::optional<std::string> message;
    std::optional<int> code;
    std::optional<std::vector<std::map<std::string, int>>> locations;
    std::optional<std::string> details;

    constexpr static char MESSAGE_KEY[] = "message";
    constexpr static char CODE_KEY[] = "code";
    constexpr static char LOCATIONS_KEY[] = "locations";
    constexpr static char DETAILS_KEY[] = "details";
};

}

#endif //ENJINCPPSDK_GRAPHQLERROR_HPP
