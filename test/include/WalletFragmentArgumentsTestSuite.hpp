#ifndef ENJINSDK_WALLETFRAGMENTARGUMENTSTESTSUITE_HPP
#define ENJINSDK_WALLETFRAGMENTARGUMENTSTESTSUITE_HPP

#include "enjinsdk/shared/WalletFragmentArguments.hpp"
#include <type_traits>

namespace enjin::test::suites {

template<class T>
class WalletFragmentArgumentsTestSuite {
    static_assert(std::is_base_of<sdk::shared::WalletFragmentArguments<T>, T>::value,
                  "Type T does not inherit from WalletFragmentArguments.");

public:
    static void set_wallet_fragment_arguments(sdk::shared::WalletFragmentArguments<T>& o) {
        o.set_with_assets_created();
    }
};

}

#endif //ENJINSDK_WALLETFRAGMENTARGUMENTSTESTSUITE_HPP
