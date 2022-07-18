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
#include <functional>
#include <map>
#include <optional>
#include <string>
#include <vector>

namespace enjin::test::mocks {

/// \brief HTTP request builder to be used when setting expectations of a request in MockHttpServer.
class Request {
public:
    /// \brief Default destructor.
    ~Request() = default;

    /// \brief Marks this request as using the Delete HTTP method.
    /// \return This request for chaining.
    Request& using_delete();

    /// \brief Marks this request as using the Get HTTP method.
    /// \return This request for chaining.
    Request& using_get();

    /// \brief Marks this request as using the Post HTTP method.
    /// \return This request for chaining.
    Request& using_post();

    /// \brief Marks this request as using the Put HTTP method.
    /// \return This request for chaining.
    Request& using_put();

    /// \brief Adds a body to this request.
    /// \param body The serialized body.
    /// \return This request for chaining.
    Request& with_body(std::string body);

    /// \brief Adds the relative path to this request.
    /// \param path The relative path.
    /// \return This request for chaining.
    Request& with_path(std::string path);

    /// \brief Creates a new instance of this class.
    /// \return A new instance of this class.
    [[nodiscard]] static Request create();

    bool operator==(const Request& rhs) const;

    bool operator!=(const Request& rhs) const;

    bool operator<(const Request& rhs) const;

    bool operator>(const Request& rhs) const;

    bool operator<=(const Request& rhs) const;

    bool operator>=(const Request& rhs) const;

private:
    std::optional<std::string> m_body;
    std::optional<std::string> m_path;
    std::optional<sdk::http::HttpMethod> m_method;

    Request() = default;

    [[nodiscard]] const std::optional<std::string>& get_body() const;

    [[nodiscard]] const std::optional<std::string>& get_path() const;

    [[nodiscard]] const std::optional<sdk::http::HttpMethod>& get_method() const;

    friend class MockHttpServer;
};

/// \brief HTTP response builder to be used when setting a stub response in MockHttpServer.
class Response {
public:
    /// \brief Default destructor.
    ~Response() = default;

    /// \brief Adds a body to this response.
    /// \param body The serialized body.
    /// \return This response for chaining.
    Response& with_body(std::string body);

    /// \brief Adds a header to this response.
    /// \param name The header name (key).
    /// \param value The header value.
    /// \return This response for chaining.
    Response& with_header(std::string name, std::string value);

    /// \brief Adds the status code to this response.
    /// \param code The status code.
    /// \return This response for chaining.
    Response& with_status_code(int code);

    /// \brief Marks this response as being successful with a status code of 200.
    /// \return This response for chaining.
    Response& with_success();

    /// \brief Creates a new instance of this class.
    /// \return A new instance of this class.
    [[nodiscard]] static Response create();

private:
    std::optional<std::string> m_body;
    std::map<std::string, std::string> m_headers;
    std::optional<int> m_status_code;

    Response() = default;

    [[nodiscard]] const std::optional<std::string>& get_body() const;

    [[nodiscard]] const std::map<std::string, std::string>& get_headers() const;

    [[nodiscard]] const std::optional<int>& get_status_code() const;

    friend class MockHttpServer;
};

/// \brief Represents the data of a request received by the mock HTTP server.
class RequestMessage {
public:
    /// \brief Default destructor.
    ~RequestMessage() = default;

    /// \brief Returns the body of the request.
    /// \return The request body.
    [[nodiscard]] const std::string& get_body() const;

    /// \brief Returns the headers of the request.
    /// \return The headers.
    [[nodiscard]] const std::map<std::string, std::string>& get_headers() const;

    /// \brief Returns the HTTP method of the request.
    /// \return The HTTP method.
    [[nodiscard]] const std::string& get_method() const;

    /// \brief Returns the relative path of the request.
    /// \return The relative path.
    [[nodiscard]] const std::string& get_path() const;

private:
    std::string body;
    std::map<std::string, std::string> headers;
    std::string method;
    std::string path;

    RequestMessage() = default;

    RequestMessage& add_header(std::string name, std::string value);

    RequestMessage& set_body(std::string value);

    RequestMessage& set_method(std::string value);

    RequestMessage& set_path(std::string value);

    friend class MockHttpServer;
};

/// \brief Represents the data of a response sent by the mock HTTP server.
class ResponseMessage {
public:
    /// \brief Default destructor.
    ~ResponseMessage() = default;

    /// \brief Returns the body of the response.
    /// \return The response body.
    [[nodiscard]] const std::string& get_body() const;

    /// \brief Returns the headers of the response.
    /// \return The headers.
    [[nodiscard]] const std::map<std::string, std::string>& get_headers() const;

    /// \brief Returns the status code of the response.
    /// \return The status code.
    [[nodiscard]] int get_status_code() const;

private:
    std::string body;
    std::map<std::string, std::string> headers;
    int status_code = 0;

    ResponseMessage() = default;

    ResponseMessage& add_header(std::string name, std::string value);

    ResponseMessage& set_body(std::string value);

    ResponseMessage& set_status_code(int value);

    friend class MockHttpServer;
};

/// \brief Provider for stubbed responses.
class ResponseProvider {
public:
    /// \brief Default destructor.
    ~ResponseProvider() = default;

    /// \brief Sets the response to be stubbed.
    /// \param response The stubbed response.
    void respond_with(Response response);

    /// \brief Returns the response stored by this provider.
    /// \return The optional for the response.
    [[nodiscard]] const std::optional<Response>& get_response() const;

private:
    std::optional<Response> m_response;

    ResponseProvider() = default;

    friend class MockHttpServer;
};

/// \brief A log entry of traffic recorded by the mock HTTP server.
class LogEntry {
public:
    /// \brief Default destructor.
    ~LogEntry() = default;

    /// \brief Returns the request message received.
    /// \return The optional for the message.
    [[nodiscard]] const std::optional<RequestMessage>& get_request_message() const;

    /// \brief Returns the the response message sent.
    /// \return The optional for the message.
    [[nodiscard]] const std::optional<ResponseMessage>& get_response_message() const;

private:
    std::optional<RequestMessage> request;
    std::optional<ResponseMessage> response;

    LogEntry() = default;

    void set_request_message(RequestMessage message);

    void set_response_message(ResponseMessage message);

    friend class MockHttpServer;
};

/// \brief Mock HTTP server for testing HTTP requests.
class MockHttpServer {
public:
    /// \brief Constructs a mock server instance.
    MockHttpServer();

    /// \brief Destructor.
    ~MockHttpServer();

    /// \brief Starts the server.
    void start();

    /// \brief Stops the server.
    void stop();

    /// \brief Setup a handler for the next message received by this server. Intended for use establishing expectations.
    /// \param handler The message handler.
    /// \remarks This server will only use the handler on a new message received by it and will not retroactively apply
    /// the handler to any messages it received in the past.
    void next_message(std::function<void(const sdk::http::HttpRequest&)> handler);

    /// \brief Sets this server to respond for a given request.
    /// \param request The request.
    /// \return The response provider to be setup with the stubbed response.
    ResponseProvider& given(const Request& request);

    /// \brief Returns the URI for this server.
    /// \return The URI.
    std::string uri();

    /// \brief Searches this server's logs for all mock traffic which matches the given request.
    /// \param request The request to search by.
    /// \return The log entries matching the given request.
    [[nodiscard]] std::vector<LogEntry> find_received_requests(const Request& request) const;

private:
    class Impl;

    Impl* impl;
};

}

#endif //ENJINCPPSDK_MOCKHTTPSERVER_HPP

#endif
