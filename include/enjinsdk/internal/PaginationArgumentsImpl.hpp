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

#ifndef ENJINCPPSDK_SHAREDPAGINATIONARGUMENTSIMPL_HPP
#define ENJINCPPSDK_SHAREDPAGINATIONARGUMENTSIMPL_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/ISerializable.hpp"
#include "enjinsdk/models/PaginationOptions.hpp"
#include <optional>

namespace enjin::sdk::shared {

/// \brief Internal implementation class for storing values of a GraphQL Pagination request.
class ENJINSDK_EXPORT PaginationArgumentsImpl : public serialization::ISerializable {
public:
    /// \brief Default constructor to be used internally.
    PaginationArgumentsImpl() = default;

    ~PaginationArgumentsImpl() override = default;

    [[nodiscard]] std::string serialize() const override;

    /// \brief Sets the value for the associated field to the passed value.
    /// \param pagination The options.
    void set_pagination(models::PaginationOptions pagination);

    /// \brief Creates the associated value using the passed arguments.
    /// \param page The page value for the options.
    /// \param limit The limit value for the options.
    void set_pagination(int page, int limit);

    bool operator==(const PaginationArgumentsImpl& rhs) const;

    bool operator!=(const PaginationArgumentsImpl& rhs) const;

private:
    std::optional<models::PaginationOptions> pagination;
};

}

#endif //ENJINCPPSDK_SHAREDPAGINATIONARGUMENTSIMPL_HPP
