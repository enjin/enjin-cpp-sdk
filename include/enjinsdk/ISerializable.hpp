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

#ifndef ENJINCPPSDK_SERIALIZABLE_HPP
#define ENJINCPPSDK_SERIALIZABLE_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/JsonValue.hpp"
#include <string>

namespace enjin::sdk::serialization {

/// \brief Interface for serialization.
class ENJINSDK_EXPORT ISerializable {
public:
    /// \brief Default destructor.
    virtual ~ISerializable() = default;

    /// \brief Returns a JSON string with this object's data.
    /// \return This object as a JSON string.
    /// \remark Null fields are to be omitted from the JSON string.
    [[nodiscard]] virtual std::string serialize() const = 0;

    /// \brief Returns a JSON value representing this object.
    /// \return The JSON value.
    [[nodiscard]] virtual json::JsonValue to_json() const = 0;
};

}

#endif //ENJINCPPSDK_SERIALIZABLE_HPP
