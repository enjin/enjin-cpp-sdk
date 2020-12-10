#ifndef ENJINCPPSDK_GRAPHQLQUERYREGISTRY_HPP
#define ENJINCPPSDK_GRAPHQLQUERYREGISTRY_HPP

#include <map>
#include <string>

namespace enjin {
namespace sdk {
namespace graphql {

/// \brief Class for registering and storing GraphQL templates.
class GraphqlQueryRegistry {
public:
    /// \brief Default constructor.
    GraphqlQueryRegistry();

    /// \brief Default destructor.
    ~GraphqlQueryRegistry();

    /// \brief Registers a new template if one with the given name does not already exist.
    /// \param name The template name.
    /// \param query The template to register.
    /// \return True if registered, false if a template with the given name already exists.
    bool register_template(const std::string& name, const std::string& query);

    /// \brief Returns true if this registry contains a template with the given name.
    /// \param name The template name.
    /// \return True if the name is registered, false otherwise.
    bool has_operation_for_name(const std::string& name);

    /// \brief Returns the template string if the registry contains the template or an empty string if not.
    /// \param name The template name.
    /// \return The template string.
    std::string get_operation_for_name(const std::string& name);

private:
    std::map<std::string, std::string> registered;

    void register_template_constants();
};

} // namespace graphql
} // namespace sdk
} // namespace enjin

#endif //ENJINCPPSDK_GRAPHQLQUERYREGISTRY_HPP
