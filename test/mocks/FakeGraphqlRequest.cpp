/* Copyright 2021 Enjin Pte Ltd.
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
