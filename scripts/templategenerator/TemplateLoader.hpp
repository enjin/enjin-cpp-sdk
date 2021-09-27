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

#ifndef ENJINSDK_TEMPLATELOADER_HPP
#define ENJINSDK_TEMPLATELOADER_HPP

#include "Template.hpp"
#include "TemplateType.hpp"
#include <filesystem>
#include <map>
#include <memory>
#include <regex>

namespace enjin::generator {

class TemplateLoader {
public:
    TemplateLoader() = delete;

    explicit TemplateLoader(std::filesystem::path resource_dir);

    ~TemplateLoader() = default;

    void load();

    [[nodiscard]] const std::map<std::string, Template>& get_operations() const;

private:
    std::filesystem::path resource_dir;
    std::map<std::string, Template> operations;
    std::shared_ptr<std::map<std::string, Template>> fragments;

    static constexpr char BACK_SLASH_REGEX[] =
            R"(^(?:[a-zA-Z\\:-]*schemas\\)(?:player|project|shared)\\(fragment|mutation|query)\\(?:[a-zA-Z]+)\.gql$)";
    static constexpr char FORWARD_SLASH_REGEX[] =
            R"(^(?:[a-zA-Z/:-]*schemas/)(?:player|project|shared)/(fragment|mutation|query)/(?:[a-zA-Z]+)\.gql$)";

    void load_raw_resources();

    void load_and_cache_template_contents(const std::filesystem::path& path, TemplateType type);
};

}

#endif //ENJINSDK_TEMPLATELOADER_HPP
