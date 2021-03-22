#ifndef ENJINSDK_TEMPLATE_HPP
#define ENJINSDK_TEMPLATE_HPP

#include "TemplateType.hpp"
#include <map>
#include <memory>
#include <optional>
#include <string>
#include <vector>

namespace enjin::generator {

class Template {
public:
    Template() = delete;

    Template(const std::string& template_namespace,
             const TemplateType& type,
             const std::vector<std::string>& contents,
             const std::shared_ptr<std::map<std::string, Template>>& fragments);

    ~Template() = default;

    [[nodiscard]] std::string compile() const;

    [[nodiscard]] const std::string& get_template_namespace() const;

    [[nodiscard]] const std::string& get_name() const;

    [[nodiscard]] TemplateType get_type() const;

    static std::optional<std::string> read_namespace(const std::vector<std::string>& contents);

private:
    std::string template_namespace;
    std::string name;
    TemplateType type;
    std::shared_ptr<std::map<std::string, Template>> fragments;
    std::vector<std::string> contents;
    std::vector<std::string> parameters;
    std::vector<std::string> referenced_fragments;

    static constexpr char NAMESPACE_KEY[] = "#namespace";
    static constexpr char IMPORT_KEY[] = "#import";
    static constexpr char ARG_KEY[] = "#arg";

    void parse_contents(const std::vector<std::string>& contents);

    static std::string process_arg(const std::string& line);

    static std::string process_import(const std::string& line);
};

}

#endif //ENJINSDK_TEMPLATE_HPP
