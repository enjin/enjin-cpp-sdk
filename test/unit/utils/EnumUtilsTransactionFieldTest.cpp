#include "EnumUtils.hpp"
#include "gtest/gtest.h"
#include <string>
#include <tuple>

using namespace enjin::sdk::models;
using namespace enjin::sdk::utils;

class TransactionFieldTest : public testing::TestWithParam<std::tuple<std::string, TransactionField>> {
};

TEST_P(TransactionFieldTest, SerializeTransactionFieldReturnsExpectedString) {
    // Arrange
    const std::string& expected = std::get<0>(GetParam());
    TransactionField value = std::get<1>(GetParam());

    // Act
    std::string actual = serialize_transaction_field(value);

    // Assert
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(SerializeTransactionField,
                         TransactionFieldTest,
                         testing::Values(std::make_tuple("id", TransactionField::ID),
                                         std::make_tuple("state", TransactionField::STATE),
                                         std::make_tuple("title", TransactionField::TITLE),
                                         std::make_tuple("createdAt", TransactionField::CREATED_AT)));
