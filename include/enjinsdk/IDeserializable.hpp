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

#ifndef ENJINCPPSDK_IDESERIALIZABLE_HPP
#define ENJINCPPSDK_IDESERIALIZABLE_HPP

#include "enjinsdk_export.h"
#include <string>

namespace enjin::sdk::serialization {

/// \brief Interface for deserialization.
class ENJINSDK_EXPORT IDeserializable {
public:
    /// \brief Default destructor.
    virtual ~IDeserializable() = default;

    /// \brief Parses the JSON string and assigns valid values to this object's fields.
    /// \param json The JSON string.
    virtual void deserialize(const std::string& json) = 0;
};

}

#endif //ENJINCPPSDK_IDESERIALIZABLE_HPP
