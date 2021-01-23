#ifndef ENJINCPPSDK_PAGINATIONARGUMENTS_HPP
#define ENJINCPPSDK_PAGINATIONARGUMENTS_HPP

#include "enjinsdk/models/PaginationOptions.hpp"
#include "enjinsdk/serialization/ISerializable.hpp"
#include <optional>

namespace enjin::sdk::shared {

/// \brief Internal implementation class for storing values of a GraphQL Pagination request.
class PaginationArguments : public serialization::ISerializable {
public:
    /// \brief Default constructor.
    PaginationArguments() = default;

    ~PaginationArguments() override = default;

    std::string serialize() override;

    /// \brief Sets the value for the associated field to the passed value.
    /// \param pagination The options.
    void set_pagination(models::PaginationOptions pagination);

    /// \brief Creates the associated value using the passed arguments.
    /// \param page The page value for the options.
    /// \param limit The limit value for the options.
    void set_pagination(int page, int limit);

    bool operator==(const PaginationArguments& rhs) const;

    bool operator!=(const PaginationArguments& rhs) const;

private:
    std::optional<models::PaginationOptions> pagination;
};

}

#endif //ENJINCPPSDK_PAGINATIONARGUMENTS_HPP
