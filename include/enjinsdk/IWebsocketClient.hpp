#ifndef ENJINCPPSDK_IWEBSOCKETCLIENT_HPP
#define ENJINCPPSDK_IWEBSOCKETCLIENT_HPP

#include <functional>
#include <string>

namespace enjin::sdk::websockets {

/// \brief Websocket client interface to be used for interfacing with the Enjin SDK event services.
class IWebsocketClient {
public:
    /// \brief Default destructor.
    virtual ~IWebsocketClient() = default;

    /// \brief Connects to the server at the given URI address.
    /// \param uri The URI.
    virtual void connect(const std::string& uri) = 0;

    /// \brief Closes the websocket connection.
    virtual void close() = 0;

    /// \brief Closes the websocket connection with the provided code and message.
    /// \param status_code The status code.
    /// \param reason The reason message.
    virtual void close(int status_code, const std::string& reason) = 0;

    /// \brief Sends a websocket message to the server.
    /// \param data The message string.
    virtual void send(const std::string& data) = 0;

    /// \brief Sets the handler for receiving open events.
    /// \param handler The handler.
    virtual void set_open_handler(const std::function<void()>& handler) = 0;

    /// \brief Sets the handler for receiving close events.
    /// \param handler The handler.
    /// \remarks The arguments for the handler are expected to be the status code and the reason.
    virtual void set_close_handler(const std::function<void(int close_status,
                                                            const std::string& message)>& handler) = 0;

    /// \brief Sets the handler for receiving string messages from the server.
    /// \param handler The handler.
    /// \remarks The argument for the handler is expected to be the message string.
    virtual void set_message_handler(const std::function<void(const std::string& message)>& handler) = 0;

    /// \brief Sets whether reconnecting is allowed.
    /// \param allowed Whether reconnecting is allowed.
    virtual void set_allow_reconnecting(bool allowed) = 0;
};

}

#endif //ENJINCPPSDK_IWEBSOCKETCLIENT_HPP
