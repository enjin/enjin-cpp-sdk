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

#include "TemplateLoader.hpp"
#include "enjinsdk_utils/StringUtils.hpp"
#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>

namespace fs = std::filesystem;
using namespace enjin::generator;
using namespace enjin::utils;

void generate(const fs::path& file_path, const fs::path& resource_dir) {
    TemplateLoader loader(resource_dir);
    loader.load();

    std::ofstream file(file_path.filename());

    // Create the file header
    file << "#include \"TemplateConstants.hpp\"\n"
         << "\n"
         << "namespace enjin::sdk::graphql {\n"
         << "\n"
         << "const std::map<std::string, std::string> TemplateConstants::templates = [] {\n"
         << "\tstd::map<std::string, std::string> templates;\n"
         << "\n";

    // Populate the map with the constants
    for (const auto& entry : loader.get_operations()) {
        auto k = entry.second.get_template_namespace();
        auto v = replace(entry.second.compile(), "\n", " ");

        std::stringstream ss;
        ss << "\t" << "templates.emplace(\"" << k << "\", \"" << v << "\");\n";
        file << ss.str();
    }

    // Create the file tail
    file << "\n"
         << "\treturn templates;\n"
         << "}();\n"
         << "\n"
         << "}\n";

    file.close();
}

int main(int argc, char* argv[]) {
    if (argc < 3 || argc > 3) {
        return 1;
    }

    generate(argv[1], argv[2]);

    return 0;
}
