#include "enjinsdk/GraphqlError.hpp"

#include "rapidjson/document.h"

namespace enjin::sdk::graphql {

void GraphqlError::deserialize(const std::string& json) {
    rapidjson::Document document;
    document.Parse(json.c_str());
    if (document.IsObject()) {
        if (document.HasMember(MESSAGE_KEY) && document[MESSAGE_KEY].IsString()) {
            message.emplace(document[MESSAGE_KEY].GetString());
        }
        if (document.HasMember(CODE_KEY) && document[CODE_KEY].IsInt()) {
            code.emplace(document[CODE_KEY].GetInt());
        }
        if (document.HasMember(DETAILS_KEY) && document[DETAILS_KEY].IsString()) {
            details.emplace(document[DETAILS_KEY].GetString());
        }
        if (document.HasMember(LOCATIONS_KEY) && document[LOCATIONS_KEY].IsArray()) {
            locations.emplace(std::vector<std::map<std::string, int>>());

            for (auto& l : document[LOCATIONS_KEY].GetArray()) {
                if (!l.IsObject()) {
                    continue;
                }

                std::map<std::string, int> location;
                for (auto& m : l.GetObject()) {
                    location[m.name.GetString()] = m.value.GetInt();
                }
                locations.value().emplace_back(location);
            }
        }
    }
}

const std::optional<std::string>& GraphqlError::get_message() const {
    return message;
}

const std::optional<int>& GraphqlError::get_code() const {
    return code;
}

const std::optional<std::vector<std::map<std::string, int>>>& GraphqlError::get_locations() const {
    return locations;
}

const std::optional<std::string>& GraphqlError::get_details() const {
    return details;
}

bool GraphqlError::operator==(const GraphqlError& rhs) const {
    return message == rhs.message &&
           code == rhs.code &&
           locations == rhs.locations &&
           details == rhs.details;
}

bool GraphqlError::operator!=(const GraphqlError& rhs) const {
    return !(rhs == *this);
}

}
