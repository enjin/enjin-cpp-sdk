#ifndef ENJINCPPSDK_JSONTESTSUITE_HPP
#define ENJINCPPSDK_JSONTESTSUITE_HPP

#include "gtest/gtest.h"

class JsonTestSuite : public testing::Test {
public:
    constexpr static char EMPTY_JSON_OBJECT[] = "{}";
};


#endif //ENJINCPPSDK_JSONTESTSUITE_HPP
