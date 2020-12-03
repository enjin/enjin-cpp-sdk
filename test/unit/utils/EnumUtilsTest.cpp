#include "EnumUtils.hpp"

#include "GraphqlTemplate.hpp"
#include "gtest/gtest.h"
#include <tuple>

using namespace enjin::sdk::utils;

class EnumUtilsTemplateTypeTest
        : public ::testing::TestWithParam<std::tuple<enjin::sdk::graphql::TemplateType, std::string>> {

};

TEST_P(EnumUtilsTemplateTypeTest, GetName) {
    // Arrange
    const std::string expected = std::get<1>(GetParam());
    const enjin::sdk::graphql::TemplateType input = std::get<0>(GetParam());

    // Act
    std::string actual = get_name(input);

    // Assert
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_CASE_P

(
        TemplateTypeGetNameTests,
        EnumUtilsTemplateTypeTest,
        ::testing::Values(
                std::make_tuple(enjin::sdk::graphql::TemplateType::FRAGMENT, "FRAGMENT"),
                std::make_tuple(enjin::sdk::graphql::TemplateType::MUTATION, "MUTATION"),
                std::make_tuple(enjin::sdk::graphql::TemplateType::QUERY, "QUERY")
        ));