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

#ifndef ENJINCPPSDK_EVENTTYPEDEF_HPP
#define ENJINCPPSDK_EVENTTYPEDEF_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/models/EventType.hpp"
#include <map>
#include <memory>
#include <string>
#include <vector>

namespace enjin::sdk::events {

/// \brief Class acting as the definition for the EventType enum.
class ENJINSDK_EXPORT EventTypeDef {
public:
    /// \brief No argument constructor. Constructs definition for an unknown event.
    /// \remarks Intended for use by unique-pointer and other templates that must be able to access this constructor.
    EventTypeDef();

    /// \brief Primary constructor. Creates a event type definition with the given parameters.
    /// \param type The event type.
    /// \param key The event key.
    /// \param channels The channels the event broadcasts on.
    EventTypeDef(models::EventType type, std::string key, std::vector<std::string> channels);

    /// \brief Default destructor.
    ~EventTypeDef() = default;

    /// \brief Determines if this definition's type is present in the given types vector.
    /// \param types The types to check.
    /// \return Whether this definition's type was found among the given types vector.
    [[nodiscard]] bool in(const std::vector<models::EventType>& types) const;

    /// \brief Returns the type of this definition.
    /// \return The type.
    [[nodiscard]] models::EventType get_type() const;

    /// \brief Returns the key of the event for this definition.
    /// \return The event key.
    [[nodiscard]] const std::string& get_key() const;

    /// \brief Returns the channels this event broadcasts on.
    /// \return The event channels.
    [[nodiscard]] const std::vector<std::string>& get_channels() const;

    /// \brief Returns the name of this event.
    /// \return The name.
    [[nodiscard]] const std::string& get_name() const;

    bool operator==(const EventTypeDef& rhs) const;

    bool operator!=(const EventTypeDef& rhs) const;

    /// \brief Returns a vector of all event type definitions.
    /// \return The definitions.
    static std::vector<EventTypeDef> values();

    /// \brief Returns only the events which broadcast on the given channel.
    /// \param channel The channel.
    /// \return The events which broadcast on the given channel.
    static std::vector<EventTypeDef> filter_by_channel_type(const std::string& channel);

    /// \brief Returns the definition that has the given event name.
    /// \param name The event name.
    /// \return The definition.
    static EventTypeDef get_from_name(const std::string& name);

    /// \brief Returns the definition that has the given event key.
    /// \param key The event key.
    /// \return The definition.
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
