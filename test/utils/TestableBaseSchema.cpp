/* Copyright 2021 Enjin Pte. Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "TestableBaseSchema.hpp"

#include <utility>

namespace enjin::test::utils {

TestableBaseSchema::TestableBaseSchema(std::unique_ptr<sdk::http::IHttpClient> http_client)
        : BaseSchema(std::move(http_client), "test", nullptr) {
}

const std::unique_ptr<sdk::TrustedPlatformMiddleware>& TestableBaseSchema::get_middleware() {
    return middleware;
}

std::string TestableBaseSchema::create_request_body(sdk::graphql::AbstractGraphqlRequest& request) {
    return BaseSchema::create_request_body(request);
}

sdk::http::HttpRequest TestableBaseSchema::create_request(sdk::graphql::AbstractGraphqlRequest& request) {
    return BaseSchema::create_request(request);
}

}
