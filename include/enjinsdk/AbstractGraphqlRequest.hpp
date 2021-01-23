#ifndef ENJINCPPSDK_IGRAPHQLREQUEST_HPP
#define ENJINCPPSDK_IGRAPHQLREQUEST_HPP

#include "enjinsdk/serialization/ISerializable.hpp"
#include <string>
#include <utility>

namespace enjin::sdk::graphql {

/// \brief Base class for representing a GraphQL request to the platform.
class AbstractGraphqlRequest : public serialization::ISerializable {
public:
    /// \brief Constructs a request with an empty namespace.
    AbstractGraphqlRequest() = default;

    /// \brief Default destructor.
    ~AbstractGraphqlRequest() override = default;

    /// \brief Gets the namespace of the request.
    /// \return The namespace.
    [[nodiscard]] const std::string& get_namespace() const;

    bool operator==(const AbstractGraphqlRequest& rhs) const;

    bool operator!=(const AbstractGraphqlRequest& rhs) const;

protected:
    /// \brief Constructs a request and moves the passed template key (namespace).
    /// \param template_key The template key to be moved.
    explicit AbstractGraphqlRequest(std::string template_key);

private:
    const std::string template_key;
};

}

#endif //ENJINCPPSDK_IGRAPHQLREQUEST_HPP
