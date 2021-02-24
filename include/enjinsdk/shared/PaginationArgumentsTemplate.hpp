#ifndef ENJINCPPSDK_SHAREDPAGINATIONARGUMENTSTEMPLATE_HPP
#define ENJINCPPSDK_SHAREDPAGINATIONARGUMENTSTEMPLATE_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/internal/PaginationArguments.hpp"
#include "enjinsdk/models/PaginationOptions.hpp"
#include "enjinsdk/serialization/ISerializable.hpp"
#include <utility>

namespace enjin::sdk::shared {

/// \brief Fragment interface used to set pagination options for a pagination returned by the platform.
/// \tparam T The type of the implementing class.
template<class T>
class ENJINSDK_EXPORT PaginationArgumentsTemplate : public serialization::ISerializable {
public:
    /// \brief Default constructor.
    PaginationArgumentsTemplate() = default;

    ~PaginationArgumentsTemplate() override = default;

    std::string serialize() override {
        return std::string();
    }

    /// \brief Sets the pagination options via a move.
    /// \param pagination The options to move.
    /// \return This request for chaining.
    T& set_pagination(models::PaginationOptions pagination) {
        impl.set_pagination(std::move(pagination));
        return dynamic_cast<T&>(*this);
    }

    /// \brief Creates pagination options that are then set.
    /// \param page The page to start on.
    /// \param limit The number of items per page.
    /// \return This request for chaining.
    T& set_pagination(int page, int limit) {
        impl.set_pagination(page, limit);
        return dynamic_cast<T&>(*this);
    }

    bool operator==(const PaginationArgumentsTemplate& rhs) const {
        return impl == rhs.impl;
    }

    bool operator!=(const PaginationArgumentsTemplate& rhs) const {
        return rhs != *this;
    }

private:
    PaginationArguments impl;
};

}

#endif //ENJINCPPSDK_SHAREDPAGINATIONARGUMENTSTEMPLATE_HPP
