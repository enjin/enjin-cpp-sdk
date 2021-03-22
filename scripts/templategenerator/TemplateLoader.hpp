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
