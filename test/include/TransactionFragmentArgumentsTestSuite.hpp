#ifndef ENJINSDK_TRANSACTIONFRAGMENTARGUMENTSTESTSUITE_HPP
#define ENJINSDK_TRANSACTIONFRAGMENTARGUMENTSTESTSUITE_HPP

#include "enjinsdk/shared/TransactionFragmentArguments.hpp"
#include <type_traits>

namespace enjin::test::suites {

template<class T>
class TransactionFragmentArgumentsTestSuite {
    static_assert(std::is_base_of<sdk::shared::TransactionFragmentArguments<T>, T>::value,
                  "Type T does not inherit from TransactionFragmentArguments.");

public:
    static void set_transaction_fragment_arguments(sdk::shared::TransactionFragmentArguments<T>& o) {
        o.set_with_blockchain_data()
         .set_with_meta()
         .set_with_encoded_data()
         .set_with_asset_data()
         .set_with_signed_txs()
         .set_with_error()
         .set_with_nonce()
         .set_with_state()
         .set_with_receipt()
         .set_with_receipt_logs()
         .set_with_log_event();
    }
};

}

#endif //ENJINSDK_TRANSACTIONFRAGMENTARGUMENTSTESTSUITE_HPP
