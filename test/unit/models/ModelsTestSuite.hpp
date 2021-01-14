#ifndef ENJINCPPSDK_MODELSTESTSUITE_HPP
#define ENJINCPPSDK_MODELSTESTSUITE_HPP

#include "gtest/gtest.h"

class ModelsTestSuite : public testing::Test {
public:
    constexpr static char EMPTY_JSON_OBJECT[] = "{}";
};


#endif //ENJINCPPSDK_MODELSTESTSUITE_HPP
