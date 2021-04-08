#include "FakeGraphqlRequest.hpp"

#include <utility>

namespace enjin::test::mocks {

FakeGraphqlRequest::FakeGraphqlRequest(std::string serialize_string)
        : sdk::graphql::AbstractGraphqlRequest("test"),
          serialize_string(std::move(serialize_string)) {
};

std::string FakeGraphqlRequest::serialize() {
    return serialize_string;
}

}
