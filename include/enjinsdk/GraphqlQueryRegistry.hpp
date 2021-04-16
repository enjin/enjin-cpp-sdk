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

#ifndef ENJINCPPSDK_GRAPHQLQUERYREGISTRY_HPP
#define ENJINCPPSDK_GRAPHQLQUERYREGISTRY_HPP

#include "enjinsdk_export.h"
#include <map>
#include <string>

namespace enjin::sdk::graphql {

/// \brief Class for registering and storing GraphQL templates.
class ENJINSDK_EXPORT GraphqlQueryRegistry {
public:
    /// \brief Default constructor.
    GraphqlQueryRegistry();

    /// \brief Default destructor.
    ~GraphqlQueryRegistry() = default;

    /// \brief Registers a new template if one with the given name does not already exist.
    /// \param name The template name.
    /// \param query The template to register.
    /// \return True if registered, false if a template with the given name already exists.
    bool register_template(const std::string& name, const std::string& query);

    /// \brief Returns true if this registry contains a template with the given name.
    /// \param name The template name.
    /// \return True if the name is registered, false otherwise.
    [[nodiscard]] bool has_operation_for_name(const std::string& name) const;

    /// \brief Returns the template string if the registry contains the template or an empty string if not.
    /// \param name The template name.
    /// \return The template string.
    [[nodiscard]] std::string get_operation_for_name(const std::string& name) const;

private:
    std::map<std::string, std::string> registered;

    void register_template_constants();
};

}

#endif //ENJINCPPSDK_GRAPHQLQUERYREGISTRY_HPP
