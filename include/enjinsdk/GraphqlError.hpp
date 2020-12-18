#ifndef ENJINCPPSDK_GRAPHQLERROR_HPP
#define ENJINCPPSDK_GRAPHQLERROR_HPP

#include "enjinsdk/serialization/ISerializable.hpp"
#include <map>
#include <optional>
#include <string>
#include <vector>

namespace enjin::sdk::graphql {

/// \brief Models the structure of a GraphQL response error.
class GraphqlError : enjin::sdk::serialization::ISerializable {
public:
    /// \brief Default constructor.
    GraphqlError() = default;

    void deserialize(const char* json) override;

    std::string serialize() override;

    /// \brief Returns the error message.
    /// \return Optional for the error message.
    std::optional<std::string> get_message();

    /// \brief Returns the error code.
    /// \return Optional for the error code.
    std::optional<int> get_code();

    /// \brief Returns the error locations.
    /// \return Optional for the error locations.
    std::optional<std::vector<std::map<std::string, int>>> get_locations();

    /// \brief Returns the error details.
    /// \return Optional for the error details.
    std::optional<std::string> get_details();

private:
    std::optional<std::string> message;
    std::optional<int> code;
    std::optional<std::vector<std::map<std::string, int>>> locations;
    std::optional<std::string> details;

    constexpr static char MESSAGE[] = "message";
    constexpr static char CODE[] = "code";
    constexpr static char LOCATIONS[] = "locations";
    constexpr static char DETAILS[] = "details";
};

}

#endif //ENJINCPPSDK_GRAPHQLERROR_HPP
