#ifndef ENJINCPPSDK_VERIFICATIONTESTSUITE_HPP
#define ENJINCPPSDK_VERIFICATIONTESTSUITE_HPP

#include <atomic>
#include <chrono>
#include <mutex>

namespace enjin::test::suites {

class VerificationTestSuite {
public:
    VerificationTestSuite();

    void set_expected_call_count(int count);

    void increment_call_counter();

    void verify_call_count(int time = 0) const;

private:
    std::atomic_int call_counter;
    int expected_count;
};

}

#endif //ENJINCPPSDK_VERIFICATIONTESTSUITE_HPP
