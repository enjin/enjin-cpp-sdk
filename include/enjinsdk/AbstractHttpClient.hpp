#ifndef ENJINCPPSDK_ABSTRACTHTTPCLIENT_HPP
#define ENJINCPPSDK_ABSTRACTHTTPCLIENT_HPP

#include "enjinsdk/HttpResponse.hpp"
#include <future>
#include <optional>
#include <string>

namespace enjin::sdk::http {

/// \brief TODO
class AbstractHttpClient {
public:
    AbstractHttpClient() = default;

    explicit AbstractHttpClient(const std::string& base_uri);

    /// \brief
    virtual ~AbstractHttpClient() = default;

    // TODO: Add argument(s) for a HTTP request with all necessary information.
    virtual std::future<HttpResponse> send_request() = 0;

    bool set_base_uri(const std::string& uri);

protected:
    /// \brief
    constexpr static char QUERY[] = "query";
    /// \brief
    constexpr static char VARIABLES[] = "variables";

    /// \brief
    std::optional<std::string> base_uri;
};

}

#endif //ENJINCPPSDK_ABSTRACTHTTPCLIENT_HPP
