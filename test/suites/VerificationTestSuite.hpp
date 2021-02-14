#ifndef ENJINCPPSDK_VERIFICATIONTESTSUITE_HPP
#define ENJINCPPSDK_VERIFICATIONTESTSUITE_HPP

#include "gtest/gtest.h"
#include <atomic>
#include <chrono>
#include <mutex>

namespace enjin::test::utils {

class VerificationTestSuite : public testing::Test {
public:
    void set_expected_call_count(int count);

    void increment_call_counter();

    void verify_call_count(int time = 0) const;

private:
    std::atomic_int call_counter = 0;
    int expected_count = 0;
};

}

#endif //ENJINCPPSDK_VERIFICATIONTESTSUITE_HPP
