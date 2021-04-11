#ifndef ENJINSDK_TRANSACTIONREQUESTARGUMENTSTESTSUITE_HPP
#define ENJINSDK_TRANSACTIONREQUESTARGUMENTSTESTSUITE_HPP

#include "TransactionFragmentArgumentsTestSuite.hpp"
#include "enjinsdk/shared/TransactionRequestArguments.hpp"
#include <type_traits>

namespace enjin::test::suites {

template<class T>
class TransactionRequestArgumentsTestSuite : public TransactionFragmentArgumentsTestSuite<T> {
    static_assert(std::is_base_of<sdk::shared::TransactionRequestArguments<T>, T>::value,
                  "Type T does not inherit from TransactionRequestArguments.");

public:
    static void set_transaction_request_arguments(sdk::shared::TransactionRequestArguments<T>& o) {
        TransactionFragmentArgumentsTestSuite<T>::set_transaction_fragment_arguments(o);
        o.set_eth_address("1")
         .set_send(true);
    }
};

}

#endif //ENJINSDK_TRANSACTIONREQUESTARGUMENTSTESTSUITE_HPP
