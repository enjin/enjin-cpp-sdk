#ifndef ENJINSDK_PLAYERFRAGMENTARGUMENTSTESTSUITE_HPP
#define ENJINSDK_PLAYERFRAGMENTARGUMENTSTESTSUITE_HPP

#include "enjinsdk/shared/PlayerFragmentArguments.hpp"
#include <type_traits>

namespace enjin::test::suites {

template<class T>
class PlayerFragmentArgumentsTestSuite {
    static_assert(std::is_base_of<sdk::shared::PlayerFragmentArguments<T>, T>::value,
                  "Type T does not inherit from PlayerFragmentArguments.");

public:
    static void set_player_fragment_arguments(sdk::shared::PlayerFragmentArguments<T>& o) {
        o.set_with_linking_info()
         .set_qr_size(0)
         .set_with_wallet();
    }
};

}

#endif //ENJINSDK_PLAYERFRAGMENTARGUMENTSTESTSUITE_HPP
