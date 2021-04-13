#include "FakeGraphqlRequest.hpp"

namespace enjin::test::mocks {

FakeGraphqlRequest::FakeGraphqlRequest(std::string serialize_string)
        : sdk::graphql::AbstractGraphqlRequest("test"),
          serialize_string(std::move(serialize_string)) {
};

std::string FakeGraphqlRequest::serialize() const {
    return serialize_string;
}

}
