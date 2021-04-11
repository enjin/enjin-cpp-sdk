#ifndef ENJINSDK_PAGINATIONARGUMENTSTESTSUITE_HPP
#define ENJINSDK_PAGINATIONARGUMENTSTESTSUITE_HPP

#include "enjinsdk/shared/PaginationArguments.hpp"
#include <type_traits>

namespace enjin::test::suites {

template<class T>
class PaginationArgumentsTestSuite {
    static_assert(std::is_base_of<sdk::shared::PaginationArguments<T>, T>::value,
                  "Type T does not inherit from PaginationArguments.");

public:
    static void set_pagination_arguments(sdk::shared::PaginationArguments<T>& o) {
        o.set_pagination(0, 0);
    }
};

}

#endif //ENJINSDK_PAGINATIONARGUMENTSTESTSUITE_HPP
