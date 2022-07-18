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

#ifndef ENJINCPPSDK_IHTTPCLIENT_HPP
#define ENJINCPPSDK_IHTTPCLIENT_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/HttpLogLevel.hpp"
#include "enjinsdk/HttpRequest.hpp"
#include "enjinsdk/HttpResponse.hpp"
#include "enjinsdk/LoggerProvider.hpp"
#include <future>

namespace enjin::sdk::http {

/// \brief HTTP client interface to be used for interfacing with the Enjin SDK platform clients.
class ENJINSDK_EXPORT IHttpClient {
public:
    /// \brief Default destructor.
    virtual ~IHttpClient() = default;

    /// \brief Starts this client.
    virtual void start() = 0;

    /// \brief Stops this client.
    virtual void stop() = 0;

    /// \brief Sends an HTTP request asynchronously.
    /// \param request The HTTP request.
    /// \return The future for accessing the response.
    virtual std::future<HttpResponse> send_request(HttpRequest request) = 0;

    /// \brief Determines if this client is open.
    /// \return Whether this client is open.
    [[nodiscard]] virtual bool is_open() const = 0;

    /// \brief Assigns a default request header for all requests sent by this client.
    /// \param key The header key.
    /// \param value The header value.
    virtual void set_default_request_header(std::string key, std::string value) = 0;

    /// \brief Assigns a logger provider and a HTTP log level for requests and responses processed by this client.
    /// \param level The HTTP log level.
    /// \param logger_provider The logger provider.
    /// \remarks If the HTTP log level is set to HttpLogLevel::NONE or if the logger provider pointer is null, then no
    /// logging shall occur.
    virtual void set_logger(HttpLogLevel level, std::shared_ptr<utils::LoggerProvider> logger_provider) = 0;
};

}

#endif //ENJINCPPSDK_IHTTPCLIENT_HPP
