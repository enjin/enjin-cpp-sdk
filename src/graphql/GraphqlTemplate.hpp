#ifndef ENJINCPPSDK_GRAPHQLTEMPLATE_HPP
#define ENJINCPPSDK_GRAPHQLTEMPLATE_HPP

#include "StringUtils.hpp"
#include <list>
#include <map>
#include <string>

namespace enjin {
namespace sdk {
namespace graphql {

enum TemplateType {
    FRAGMENT,
    MUTATION,
    QUERY
};

class GraphqlTemplate {
public:
    static constexpr char arg_key[] = "#arg";
    static constexpr char import_key[] = "#import";
    static constexpr char namespace_key[] = "#namespace";

    GraphqlTemplate();

    GraphqlTemplate(const std::string &name,
                    TemplateType template_type,
                    const std::list<std::string> &contents,
                    std::map<std::string, GraphqlTemplate> fragments);

    ~GraphqlTemplate();

    void compile();

    std::string get_namespace();

    std::string get_name();

    TemplateType get_template_type();

    std::string get_contents();

    std::string get_compiled_contents();

    std::list<std::string> get_parameters();

    std::list<std::string> get_referenced_fragments();

    template<class InputIterator>
    static std::string read_namespace(InputIterator first, InputIterator last) {
        while (first != last) {
            const std::string &line = *first;
            if (line.find(namespace_key) != std::string::npos) {
                return enjin::sdk::utils::split(line, " ")[1];
            }

            first++;
        }

        return std::string();
    }

private:
    std::string template_namespace;
    std::string name;
    TemplateType template_type;
    std::string contents;
    std::string compiled_contents;
    std::list<std::string> parameters;
    std::list<std::string> referenced_fragments;
    std::map<std::string, GraphqlTemplate> fragments;

    std::string parse_contents(const std::list<std::string> &contents);
};

} // namespace graphql
} // namespace sdk
} // namespace enjin

#endif //ENJINCPPSDK_GRAPHQLTEMPLATE_HPP
