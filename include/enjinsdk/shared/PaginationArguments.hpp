#ifndef ENJINCPPSDK_SHAREDPAGINATIONARGUMENTS_HPP
#define ENJINCPPSDK_SHAREDPAGINATIONARGUMENTS_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/ISerializable.hpp"
#include "enjinsdk/internal/PaginationArgumentsImpl.hpp"
#include "enjinsdk/models/PaginationOptions.hpp"
#include <utility>

namespace enjin::sdk::shared {

/// \brief Fragment interface used to set pagination options for a pagination returned by the platform.
/// \tparam T The type of the implementing class.
template<class T>
class ENJINSDK_EXPORT PaginationArguments : public serialization::ISerializable {
public:
    ~PaginationArguments() override = default;

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

    bool operator==(const PaginationArguments& rhs) const {
        return impl == rhs.impl;
    }

    bool operator!=(const PaginationArguments& rhs) const {
        return rhs != *this;
    }

protected:
    /// \brief Default constructor.
    PaginationArguments() = default;

private:
    PaginationArgumentsImpl impl;
};

}

#endif //ENJINCPPSDK_SHAREDPAGINATIONARGUMENTS_HPP
