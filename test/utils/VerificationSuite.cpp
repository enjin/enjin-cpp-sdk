#include "VerificationSuite.hpp"

namespace enjin::test::utils {

void VerificationSuite::set_expected_call_count(int count) {
    expected_count = count;
}

void VerificationSuite::increment_call_counter() {
    call_counter++;
}

void VerificationSuite::verify_call_count(int time) const {
    // Waits and gives the calls an opportunity to be made if asynchronous
    std::mutex mutex;
    std::unique_lock<std::mutex> lock(mutex);
    std::condition_variable condition_variable;
    condition_variable.wait_for(lock, std::chrono::seconds(time), [this]() {
        return expected_count == call_counter;
    });

    EXPECT_EQ(expected_count, call_counter);
}

}
