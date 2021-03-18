#ifndef ENJINCPPSDK_SHAREDPAGINATIONARGUMENTSIMPL_HPP
#define ENJINCPPSDK_SHAREDPAGINATIONARGUMENTSIMPL_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/ISerializable.hpp"
#include "enjinsdk/models/PaginationOptions.hpp"
#include <optional>

namespace enjin::sdk::shared {

/// \brief Internal implementation class for storing values of a GraphQL Pagination request.
class ENJINSDK_EXPORT PaginationArgumentsImpl : public serialization::ISerializable {
public:
    /// \brief Default constructor to be used internally.
    PaginationArgumentsImpl() = default;

    ~PaginationArgumentsImpl() override = default;

    std::string serialize() override;

    /// \brief Sets the value for the associated field to the passed value.
    /// \param pagination The options.
    void set_pagination(models::PaginationOptions pagination);

    /// \brief Creates the associated value using the passed arguments.
    /// \param page The page value for the options.
    /// \param limit The limit value for the options.
    void set_pagination(int page, int limit);

    bool operator==(const PaginationArgumentsImpl& rhs) const;

    bool operator!=(const PaginationArgumentsImpl& rhs) const;

private:
    std::optional<models::PaginationOptions> pagination;
};

}

#endif //ENJINCPPSDK_SHAREDPAGINATIONARGUMENTSIMPL_HPP
