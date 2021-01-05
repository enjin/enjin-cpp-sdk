#include "gtest/gtest.h" // Load Google-Test first to avoid conflicts with CPP-REST-SDK

#include "enjinsdk/BaseSchema.hpp"
#include "../../utils/MockHttpServer.hpp"

using namespace enjin::sdk;

class BaseSchemaTest : public testing::Test {
public:
    enjin::test::utils::MockHttpServer mock_server;

protected:
    void SetUp() override {
        mock_server.start();
    }

    void TearDown() override {
        mock_server.shutdown();
    }
};

TEST_F(BaseSchemaTest, SomeTest) {
    // Arrange

    // Act

    // Assert
    ASSERT_TRUE(false);
}
