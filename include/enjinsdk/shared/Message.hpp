#ifndef ENJINCPPSDK_MESSAGE_HPP
#define ENJINCPPSDK_MESSAGE_HPP

#include "enjinsdk/AbstractGraphqlRequest.hpp"
#include "enjinsdk/shared/TransactionRequestArgumentsTemplate.hpp"
#include <optional>
#include <string>

namespace enjin::sdk::shared {

/// \brief Request to sign a message to prove wallet ownership.
class Message : public graphql::AbstractGraphqlRequest,
                public TransactionRequestArgumentsTemplate<Message> {
public:
    /// \brief Default constructor.
    Message();

    ~Message() override = default;

    std::string serialize() override;

    /// \brief Sets the message to sign.
    /// \param message The message.
    /// \return This request for chaining.
    Message& set_message(const std::string& message);

    bool operator==(const Message& rhs) const;

    bool operator!=(const Message& rhs) const;

private:
    std::optional<std::string> message;
};

}

#endif //ENJINCPPSDK_MESSAGE_HPP
