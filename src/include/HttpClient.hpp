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

#ifndef ENJINSDK_INCLUDE_HTTP_CLIENT_IMPL
#define ENJINSDK_INCLUDE_HTTP_CLIENT_IMPL 0
#endif

#if ENJINSDK_INCLUDE_HTTP_CLIENT_IMPL

#ifndef ENJINCPPSDK_HTTPCLIENT_HPP
#define ENJINCPPSDK_HTTPCLIENT_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/IHttpClient.hpp"
#include "enjinsdk/LoggerProvider.hpp"
#include <future>
#include <memory>
#include <string>

namespace enjin::sdk::http {

/// \brief Built-in HTTP client for this SDK.
class ENJINSDK_EXPORT HttpClient : public IHttpClient {
public:
    HttpClient() = delete;

    /// \brief Creates the HTTP client with the base URI.
    /// \param base_uri The base URI for the client.
    /// \param logger_provider The logger provider. Null pointer by default.
    explicit HttpClient(std::string base_uri, std::shared_ptr<utils::LoggerProvider> logger_provider = nullptr);

    /// \brief Destructor.
    ~HttpClient() override;

    void start() override;

    void stop() override;

    std::future<HttpResponse> send_request(const HttpRequest& request) override;

    /// \brief Returns the base URI of this client.
    /// \return The URI.
    [[nodiscard]] const std::string& get_base_uri() const;

    [[nodiscard]] bool is_open() const override;

private:
    class Impl;

    Impl* impl;
};

}

#endif //ENJINCPPSDK_HTTPCLIENT_HPP

#endif
