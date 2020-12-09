#ifndef ENJINCPPSDK_GRAPHQLQUERYREGISTRY_HPP
#define ENJINCPPSDK_GRAPHQLQUERYREGISTRY_HPP

#include <map>
#include <string>

namespace enjin {
namespace sdk {
namespace graphql {

class GraphqlQueryRegistry {
public:
    GraphqlQueryRegistry();

    ~GraphqlQueryRegistry();

    bool register_template(const std::string &name, const std::string &query);

    bool has_operation_for_name(const std::string &name);

    std::string get_operation_for_name(const std::string &name);

private:
    std::map<std::string, std::string> registered;

    void register_template_constants();
};

} // namespace graphql
} // namespace sdk
} // namespace enjin

#endif //ENJINCPPSDK_GRAPHQLQUERYREGISTRY_HPP
