#ifndef ENJINSDK_FAKEGRAPHQLREQUEST_HPP
#define ENJINSDK_FAKEGRAPHQLREQUEST_HPP

#include "enjinsdk/internal/AbstractGraphqlRequest.hpp"
#include <string>

namespace enjin::test::mocks {

class FakeGraphqlRequest : public sdk::graphql::AbstractGraphqlRequest {
public:
    FakeGraphqlRequest() = delete;

    explicit FakeGraphqlRequest(std::string serialize_string = "");

    ~FakeGraphqlRequest() override = default;

    [[nodiscard]] std::string serialize() const override;

private:
    std::string serialize_string;
};

}

#endif //ENJINSDK_FAKEGRAPHQLREQUEST_HPP
