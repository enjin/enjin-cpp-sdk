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

#ifndef ENJINCPPSDK_EVENTTYPEDEF_HPP
#define ENJINCPPSDK_EVENTTYPEDEF_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/models/EventType.hpp"
#include <map>
#include <memory>
#include <string>
#include <vector>

namespace enjin::sdk::events {

class ENJINSDK_EXPORT EventTypeDef {
public:
    EventTypeDef();

    EventTypeDef(models::EventType type, std::string key, std::vector<std::string> channels);

    ~EventTypeDef() = default;

    [[nodiscard]] bool in(const std::vector<models::EventType>& types) const;

    [[nodiscard]] models::EventType get_type() const;

    [[nodiscard]] const std::string& get_key() const;

    [[nodiscard]] const std::vector<std::string>& get_channels() const;

    [[nodiscard]] const std::string& get_name() const;

    bool operator==(const EventTypeDef& rhs) const;

    bool operator!=(const EventTypeDef& rhs) const;

    static std::vector<EventTypeDef> values();

    static std::vector<EventTypeDef> filter_by_channel_type(const std::string& channel);

    static EventTypeDef get_from_name(const std::string& name);

    static EventTypeDef get_from_key(const std::string& key);

private:
    models::EventType type;
    std::string key;
    std::vector<std::string> channels;
    std::string name;

    static std::unique_ptr<EventTypeDef> create(models::EventType type,
                                                const std::string& key,
                                                std::vector<std::string> channels);

    static std::map<models::EventType, std::unique_ptr<EventTypeDef>> create_map();

    inline static std::map<models::EventType, std::unique_ptr<EventTypeDef>> map = create_map();
};

}

#endif //ENJINCPPSDK_EVENTTYPEDEF_HPP
