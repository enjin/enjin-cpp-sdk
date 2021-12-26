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

#ifndef ENJINSDK_INCLUDE_HTTP_CLIENT_IMPL
#define ENJINSDK_INCLUDE_HTTP_CLIENT_IMPL 0
#endif

#if ENJINSDK_INCLUDE_HTTP_CLIENT_IMPL

#ifndef ENJINCPPSDK_MOCKHTTPSERVER_HPP
#define ENJINCPPSDK_MOCKHTTPSERVER_HPP

#include "enjinsdk/HttpRequest.hpp"
#include "enjinsdk/HttpResponse.hpp"
#include <optional>
#include <string>

namespace enjin::test::mocks {

/// \brief Provider for stubbed responses.
class ResponseProvider {
public:
    /// \brief Default constructor.
    ResponseProvider() = default;

    /// \brief Default destructor.
    ~ResponseProvider() = default;

    /// \brief Sets the response to be stubbed.
    /// \param response The stubbed response.
    void respond_with(sdk::http::HttpResponse response);

    /// \brief Returns the response stored by this provider.
    /// \return The optional for the response.
    [[nodiscard]] const std::optional<sdk::http::HttpResponse>& get_response() const;

private:
    std::optional<sdk::http::HttpResponse> response;
};

/// \brief Mock HTTP server for testing built-in HTTP client.
class MockHttpServer {
public:
    /// \brief Constructs a mock server instance.
    MockHttpServer();

    /// \brief Destructor.
    ~MockHttpServer();

    /// \brief Method to start the server.
    void start();

    /// \brief Method to stop the server.
    void stop();

    /// \brief Sets this server to respond for a given request.
    /// \param request The request.
    /// \return The response provider to be setup with the stubbed response.
    ResponseProvider& given(const sdk::http::HttpRequest& request);

    /// \brief Returns the URI for this server.
    /// \param path Optional path to extend the URI by.
    /// \return The URI.
    std::string uri();

private:
    class Impl;

    Impl* impl;
};

}

#endif //ENJINCPPSDK_MOCKHTTPSERVER_HPP

#endif
