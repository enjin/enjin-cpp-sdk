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

#ifndef ENJINSDK_MOCKHTTPCLIENT_HPP
#define ENJINSDK_MOCKHTTPCLIENT_HPP

#include "enjinsdk/IHttpClient.hpp"
#include "gmock/gmock.h"

namespace enjin::test::mocks {

class MockHttpClient : public sdk::http::IHttpClient {
public:
    MOCK_METHOD(void, start, (), (override));

    MOCK_METHOD(void, stop, (), (override));

    MOCK_METHOD(std::future<sdk::http::HttpResponse>, send_request, (sdk::http::HttpRequest request), (override));

    MOCK_METHOD(bool, is_open, (), (const, override));

    MOCK_METHOD(void, set_default_request_header, (std::string key, std::string value), (override));

    MOCK_METHOD(void,
                set_logger,
                (sdk::http::HttpLogLevel level, std::shared_ptr<sdk::utils::LoggerProvider> logger_provider),
                (override));
};

}

#endif //ENJINSDK_MOCKHTTPCLIENT_HPP
