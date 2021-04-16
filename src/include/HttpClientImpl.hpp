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

#ifndef ENJINCPPSDK_HTTPCLIENTIMPL_HPP
#define ENJINCPPSDK_HTTPCLIENTIMPL_HPP

#include "enjinsdk_export.h"
#include "httplib.h"
#include "enjinsdk/IHttpClient.hpp"
#include "enjinsdk/Logger.hpp"
#include <future>
#include <memory>
#include <string>

namespace enjin::sdk::http {

/// \brief Implementation class for an HTTP client using cpp-httplib.
class ENJINSDK_EXPORT HttpClientImpl : public IHttpClient {
public:
    HttpClientImpl() = delete;

    /// \brief Creates the HTTP client with the base URI.
    /// \param base_uri The base URI for the client.
    /// \param logger The logger. Null pointer by default.
    explicit HttpClientImpl(std::string base_uri, std::shared_ptr<utils::Logger> logger = nullptr);

    ~HttpClientImpl() override;

    void start() override;

    void stop() override;

    std::future<HttpResponse> send_request(const HttpRequest& request) override;

    /// \brief Returns the base URI of this client.
    /// \return The URI.
    [[nodiscard]] const std::string& get_base_uri() const;

    [[nodiscard]] bool is_open() const override;

private:
    const std::string base_uri;

    bool open = false;

    std::unique_ptr<httplib::Client> http_client;
    std::shared_ptr<utils::Logger> logger;

    void log_error(const std::string& message);

    static httplib::Headers create_headers(const HttpRequest& request);
};

}

#endif //ENJINCPPSDK_HTTPCLIENTIMPL_HPP

#endif
