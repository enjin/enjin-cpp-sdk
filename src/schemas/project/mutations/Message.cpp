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

#include "enjinsdk/project/Message.hpp"

#include "RapidJsonUtils.hpp"

namespace enjin::sdk::project {

Message::Message() : graphql::AbstractGraphqlRequest("enjin.sdk.project.Message") {
}

std::string Message::serialize() const {
    rapidjson::Document document(rapidjson::kObjectType);
    utils::join_serialized_object_to_document(document, ProjectTransactionRequestArguments::serialize());

    if (message.has_value()) {
        utils::set_string_member(document, "message", message.value());
    }

    return utils::document_to_string(document);
}

Message& Message::set_message(const std::string& message) {
    Message::message = message;
    return *this;
}

bool Message::operator==(const Message& rhs) const {
    return static_cast<const graphql::AbstractGraphqlRequest&>(*this) ==
           static_cast<const graphql::AbstractGraphqlRequest&>(rhs) &&
           static_cast<const ProjectTransactionRequestArguments<Message>&>(*this) ==
           static_cast<const ProjectTransactionRequestArguments<Message>&>(rhs) &&
           message == rhs.message;
}

bool Message::operator!=(const Message& rhs) const {
    return !(rhs == *this);
}

}
