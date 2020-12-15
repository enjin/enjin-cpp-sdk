#ifndef ENJINCPPSDK_IGRAPHQLREQUEST_HPP
#define ENJINCPPSDK_IGRAPHQLREQUEST_HPP

#include "enjinsdk/IVariableHolder.hpp"
#include <any>
#include <map>
#include <string>
#include <type_traits>

namespace enjin::sdk::graphql {

/// \brief Interface for GraphQL requests.
class IGraphqlRequest {
public:
    /// \brief Virtual destructor.
    ~IGraphqlRequest() = default;

    /// \brief Gets the variable mapping of the request.
    /// \return The variable mapping.
    virtual std::map<std::string, std::any> get_variables() = 0;

    /// \brief Gets the namespace of the request.
    /// \return The namespace.
    virtual std::string& get_namespace() = 0;
};

/// \brief Class for storing variables to be used in a GraphQL request to the platform.
/// \tparam T The type of the implementing class.
template<class T>
class GraphqlRequest : public IGraphqlRequest, public IVariableHolder<T> {
public:
    /// \brief Constructs a request with empty variable mapping and template key.
    GraphqlRequest() : GraphqlRequest(std::map<std::string, std::any>(), "") {};

    /// \brief Default destructor.
    ~GraphqlRequest() = default;

    T& set_variable(const std::string& key, std::any value) override {
        variables.emplace(key, value);
        return dynamic_cast<T&>(*this);
    };

    bool is_set(const std::string& key) override {
        if (variables.find(key) != variables.end()) {
            return true;
        }

        return false;
    }

    std::map<std::string, std::any> get_variables() override {
        return variables;
    }

    std::string& get_namespace() override {
        return template_key;
    }

protected:
    /// \brief Constructs a request with the passed template key (namespace) and an empty variable mapping.
    /// \param template_key The template key.
    explicit GraphqlRequest(const std::string& template_key) : GraphqlRequest(std::map<std::string, std::any>(),
                                                                              template_key) {}

    /// \brief Constructs a request with the passed variable mapping and template key (namespace).
    /// \param variables The variable mapping.
    /// \param template_key The template key.
    GraphqlRequest(const std::map<std::string, std::any>& variables, const std::string& template_key) :
            variables(variables), template_key(template_key) {}

private:
    std::string template_key;
    std::map<std::string, std::any> variables;
};

}

#endif //ENJINCPPSDK_IGRAPHQLREQUEST_HPP
