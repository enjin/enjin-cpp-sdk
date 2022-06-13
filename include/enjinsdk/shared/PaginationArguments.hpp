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

#ifndef ENJINCPPSDK_SHAREDPAGINATIONARGUMENTS_HPP
#define ENJINCPPSDK_SHAREDPAGINATIONARGUMENTS_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/ISerializable.hpp"
#include "enjinsdk/JsonUtils.hpp"
#include "enjinsdk/JsonValue.hpp"
#include "enjinsdk/models/PaginationInput.hpp"
#include <optional>
#include <string>
#include <type_traits>
#include <utility>

namespace enjin::sdk::shared {

/// \brief Fragment interface used to set pagination options for a pagination returned by the platform.
/// \tparam T The type of the implementing class.
template<class T>
class ENJINSDK_EXPORT PaginationArguments : public serialization::ISerializable {
public:
    ~PaginationArguments() override = default;

    [[nodiscard]] std::string serialize() const override {
        return to_json().to_string();
    }

    /// \brief Sets the pagination options via a move.
    /// \param pagination The pagination input.
    /// \return This request for chaining.
    T& set_pagination(models::PaginationInput pagination) {
        pagination_opt = std::move(pagination);
        return static_cast<T&>(*this);
    }

    /// \brief Creates pagination options that are then set.
    /// \param page The page to start on.
    /// \param limit The number of items per page.
    /// \return This request for chaining.
    T& set_pagination(int page, int limit) {
        pagination_opt = models::PaginationInput().set_page(page).set_limit(limit);
        return static_cast<T&>(*this);
    }

    [[nodiscard]] json::JsonValue to_json() const override {
        json::JsonValue json = json::JsonValue::create_object();

        utils::JsonUtils::try_set_field(json, "pagination", pagination_opt);

        return json;
    }

    bool operator==(const PaginationArguments& rhs) const {
        return pagination_opt == rhs.pagination_opt;
    }

    bool operator!=(const PaginationArguments& rhs) const {
        return !(*this == rhs);
    }

protected:
    /// \brief Sole constructor.
    PaginationArguments() {
        static_assert(std::is_base_of<PaginationArguments, T>::value,
                      "Class T does not inherit from PaginationArguments.");
    }

private:
    std::optional<models::PaginationInput> pagination_opt;
};

}

#endif //ENJINCPPSDK_SHAREDPAGINATIONARGUMENTS_HPP
