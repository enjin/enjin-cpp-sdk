#ifndef ENJINCPPSDK_IVARIABLEHOLDER_HPP
#define ENJINCPPSDK_IVARIABLEHOLDER_HPP

#include <any>
#include <string>

namespace enjin::sdk::graphql {

/// \brief Interface for GraphQL requests to set variables within them.
/// \tparam T The implementing type of the interface.
template<class T>
class IVariableHolder {
public:
    /// \brief Virtual destructor.
    virtual ~IVariableHolder() = default;

    /// \brief Sets a variable with the specified key and value.
    /// \param key The key.
    /// \param value The value.
    /// \return Reference to this for chaining.
    virtual T& set_variable(const std::string& key, std::any value) = 0;

    /// \brief Determines if a variable exists for the specified key.
    /// \param key The key.
    /// \return Whether the variable exists.
    virtual bool is_set(const std::string& key) = 0;
};

}

#endif //ENJINCPPSDK_IVARIABLEHOLDER_HPP
